// #include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/atlas_texture.hpp>

// temp
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

//#include <godot_cpp/variant/utility_functions.hpp>
#include <algorithm>

#include "player/playerController.h"
#include "player/playerChar.h"
#include "gameInstance.h"
#include "runManager.h"
#include "gun/gun.h"
#include "gun/gunDropped.h"
#include "interactible/itemChest.h"
#include "shared/utility.h"
#include "ui/hud.h"
#include "pickup/pickupAmmo.h"

using namespace godot;
using namespace std::chrono;

constexpr int MaxLevel = 20;

constexpr int GunSpriteAtlasStepX { 8 };
constexpr int GunSpriteAtlasStepY { 24 };

constexpr double ExperienceThresholds[] {
	0, 100, 225, 375, 550, 750, 975, 1225, 1500, 1800, 2125,
	2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000
};

void PlayerController::_bind_methods() {
	ClassDB::bind_method(D_METHOD("ProcessMovementInput"), &PlayerController::ProcessMovementInput);
	ClassDB::bind_method(D_METHOD("OnHitByProjectile"), &PlayerController::OnHitByProjectile);
	ClassDB::bind_method(D_METHOD("SetPlayer"), &PlayerController::SetPlayer);
	ClassDB::bind_method(D_METHOD("GetPlayer"), &PlayerController::GetPlayer);
	ClassDB::bind_method(D_METHOD("GetCrosshair"), &PlayerController::GetCrosshair);
	ClassDB::bind_method(D_METHOD("SetCurrentGunSlot"), &PlayerController::SetCurrentGunSlot);
	ClassDB::bind_method(D_METHOD("GetCurrentGunSlot"), &PlayerController::GetCurrentGunSlot);
	ClassDB::bind_method(D_METHOD("UpdateAmmoLabel"), &PlayerController::UpdateAmmoLabel);
	ClassDB::bind_method(D_METHOD("PickupAreaEntered"), &PlayerController::PickupAreaEntered);
	ClassDB::bind_method(D_METHOD("PickupAreaExited"), &PlayerController::PickupAreaExited);
	ClassDB::bind_method(D_METHOD("InteractibleAreaEntered"), &PlayerController::InteractibleAreaEntered);
	ClassDB::bind_method(D_METHOD("InteractibleAreaExited"), &PlayerController::InteractibleAreaExited);
	ClassDB::bind_method(D_METHOD("Interact"), &PlayerController::Interact);
	ClassDB::bind_method(D_METHOD("SwapGunOnGround"), &PlayerController::SwapGunOnGround);
	ClassDB::bind_method(D_METHOD("PickupTimerTimeout"), &PlayerController::PickupTimerTimeout);
	ClassDB::bind_method(D_METHOD("ScanForGuns"), &PlayerController::ScanForGuns);
	ClassDB::bind_method(D_METHOD("GetClosestGunDropped"), &PlayerController::GetClosestGunDropped);

	//ClassDB::bind_method(D_METHOD("ApplyRecoil"), &PlayerController::ApplyRecoil);
	//ClassDB::bind_method(D_METHOD("OnGunFired"), &PlayerController::OnGunFired);
	//ClassDB::bind_method(D_METHOD("ReloadEnd"), &PlayerController::GunReloadEnd);
}

PlayerController::PlayerController() {
	DroppedGunsInRadius.reserve(8);
}

void PlayerController::_ready() {
	InputMap::get_singleton()->load_from_project_settings();
}

void PlayerController::_unhandled_input(const Ref<InputEvent>& p_event) {
	if (p_event.ptr()->is_action_pressed("lmb")) {
		if (!isLMBHeld) {
			Gun* currentGun = ControlledPlayer->GetCurrentGun();

			if (currentGun && currentGun->GunDef->FireMode != EFireMode::Automatic && !IsReloading) {
				currentGun->TryPrimaryFire(ControlledPlayer->get_global_position(), GetCrosshair()->get_global_position());
			}
		}
		isLMBHeld = true;
	}
	else if (p_event.ptr()->is_action_released("lmb")) {
		isLMBHeld = false;
	}

	if (p_event.ptr()->is_action_pressed("rmb")) {
		isRMBHeld = true;
	}
	else if (p_event.ptr()->is_action_released("rmb")) {
		isRMBHeld = false;
	}

	if (ControlledPlayer) {
		if (p_event.ptr()->is_action_pressed("weaponSlot1")) {
			SwitchGun(0);
		}
		else if (p_event.ptr()->is_action_pressed("weaponSlot2")) {
			SwitchGun(1);
		}
		else if (p_event.ptr()->is_action_pressed("weaponSlot3")) {
			SwitchGun(2);
		}

		if (p_event.ptr()->is_action_pressed("reload") && !IsReloading) {
			Gun* gun = ControlledPlayer->GetCurrentGun();

			if (gun && gun->TryReload()) {
				GunReloadStart();
			}
		}

		if (p_event.ptr()->is_action_pressed("interact")) {
			Interact();
		}

		if (p_event.ptr()->is_action_pressed("debug0")) {
			GameInstance::GetInstance().GenerateAndDropGun(-1, GameInstance::GetInstance().GetRunManager()->CurrentAreaLevel, nullptr);
		}

		if (p_event.ptr()->is_action_pressed("debug1")) {
			for (size_t i = 0; i < PlayerNumGunSlots; i++) {
				Gun* gun = GetPlayer()->GetGunInSlot(i);

				if (gun) {
					print_line((int32_t)gun->GunDef.use_count());
				}
			}

			print_orphan_nodes();
		}

		if (p_event.ptr()->is_action_pressed("debug2")) {
			if (ControlledPlayer->GetCurrentGun()) {
				print_line(ControlledPlayer->GetCurrentGun()->GunDef->GetGunPartsString().c_str());
				print_line(vformat("Total Rarity: %d", ControlledPlayer->GetCurrentGun()->GunDef->RarityScore));
			}
		}

		if (p_event.ptr()->is_action_pressed("debug3")) {
			GameInstance::GetInstance().TestSpawnWave(1);
		}

		if (p_event.ptr()->is_action_pressed("debug4")) {
			GameInstance::GetInstance().GenerateAndDropGun(0, GameInstance::GetInstance().GetRunManager()->CurrentAreaLevel, nullptr);
		}

		if (p_event.ptr()->is_action_pressed("debug5")) {
			GameInstance::GetInstance().GenerateAndDropGun(1, GameInstance::GetInstance().GetRunManager()->CurrentAreaLevel, nullptr);
		}

		if (p_event.ptr()->is_action_pressed("debug6")) {
			GameInstance::GetInstance().GenerateAndDropGun(2, GameInstance::GetInstance().GetRunManager()->CurrentAreaLevel, nullptr);
		}

		if (p_event.ptr()->is_action_pressed("debug7")) {
			GameInstance::GetInstance().GenerateAndDropGun(3, GameInstance::GetInstance().GetRunManager()->CurrentAreaLevel, nullptr);
		}

		if (p_event.ptr()->is_action_pressed("debug8")) {
			GameInstance::GetInstance().GenerateAndDropGun(4, GameInstance::GetInstance().GetRunManager()->CurrentAreaLevel, nullptr);
		}
	}
}

void PlayerController::_process(double delta) {
	const Rect2 viewportSize = get_viewport()->get_visible_rect();
	const Vector2 mousePosition = get_viewport()->get_mouse_position();

	const Vector2 screenCentre = viewportSize.get_center();

	if (PlayerCrosshair) {
		Vector2 chPosition = mousePosition - screenCentre;
		PlayerCrosshair->set_position(chPosition);
		PlayerCrosshair->UpdateCrosshairSpreadTarget(ControlledPlayer->Inaccuracy + ControlledPlayer->GetCurrentGun()->GunDef->Spread);
		//ControlledPlayer->look_at(PlayerCrosshair->get_global_position());
		//PlayerCrosshair->set_global_rotation(0.f);
	}
}

void PlayerController::_physics_process(double delta) {
	if (ControlledPlayer) {
		Vector2 movement = ProcessMovementInput();
		ControlledPlayer->ApplyMovement(movement);

		if (PlayerCrosshair) {
			ControlledPlayer->look_at(PlayerCrosshair->get_global_position());
		}

		if (isLMBHeld) {
			Gun* currentGun = ControlledPlayer->GetCurrentGun();

			if (currentGun && currentGun->GunDef->FireMode == EFireMode::Automatic && !IsReloading) {
				currentGun->TryPrimaryFire(ControlledPlayer->get_global_position(), GetCrosshair()->get_global_position());
			}
		}

		if (CanRecoverInaccuracy) {
			RecoverInaccuracy(delta);
		}

		if (IsReloading) {
			ProcessReload(delta);
		}
	}
}

Vector2 PlayerController::ProcessMovementInput() {
	Vector2 movementInput = Input::get_singleton()->get_vector("move_left", "move_right", "move_up", "move_down");
	return movementInput;
}

void PlayerController::OnHitByProjectile(Projectile* proj) {
	TakeDamage(proj->DmgInfo);
}

// Health kan laves om til et component med sit eget system. Placeholder her
void PlayerController::TakeDamage(DamageInfo& di) {
	// No shields yet

	ControlledPlayer->CurrentHealth -= di.GetTotalDamage();
	PlayerHUD->UpdateHealthCurrent(ControlledPlayer->CurrentHealth);
}

void PlayerController::SwitchGun(int32_t slot) {
	if (PlayerNumGunSlots > slot && slot >= 0) {
		if (IsReloading) {
			Gun* gun = ControlledPlayer->GetCurrentGun();
			gun->ReloadTimer->stop();
			GunReloadEnd();
		}
		ControlledPlayer->SwitchToGunInSlot(slot);
	}
}

void PlayerController::Interact() {
	if (InteractibleInFocus) {
		Node* parent = InteractibleInFocus->get_parent();

		if (parent) {
			if (parent->is_in_group("GunDropped")) {
				GunDropped* dgun = static_cast<GunDropped*>(parent);

				if (dgun->CanBePickedUp) {
					if (PlayerNumGunSlots > NumEquippedGuns) {
						PickUpGunInSlot(NumEquippedGuns);
						NumEquippedGuns++;
					}
					else {
						Gun* curGun = GetPlayer()->GetCurrentGun();

						if (curGun) {
							SwapGunOnGround();
						}
					}
				}
			}
			else {
				InteractibleInFocus->Activate();
			}
		}
	}

	/*
	if (DroppedGunInFocus && DroppedGunInFocus->CanBePickedUp) {
		if (PlayerNumGunSlots > NumEquippedGuns) {
			PickUpGunInSlot(NumEquippedGuns);
			NumEquippedGuns++;
		}
		else {
			Gun* curGun = GetPlayer()->GetCurrentGun();

			if (curGun) {
				SwapGunOnGround();
			}
		}
	}
	*/
}

void PlayerController::SetPlayer(Player* player) {
	ControlledChar = player;
	ControlledPlayer = player;

	HUD* hud = player->get_node<HUD>("CanvasLayer/PlayerHUD");
	if (hud) {
		PlayerHUD = hud;
		PlayerHUD->BindController(this);
		PlayerHUD->UpdateLevel(ControlledPlayer->Level);
	}

	Crosshair* crosshair = player->get_node<Crosshair>("VisualNodes/Crosshair");
	if (crosshair) {
		PlayerCrosshair = crosshair;
	}

	Sprite2D* gunSprite = player->get_node<Sprite2D>("GunSprite");
	if (gunSprite) {
		GunSprite = gunSprite;
	}

	Label* label = player->get_node<Label>("VisualNodes/Label");
	if (label) {
		DebugLabel = label;
	}

	Camera2D* camera = player->get_node<Camera2D>("PlayerCamera");
	if (camera) {
		PlayerCamera = camera;
	}

	Area2D* pickupRadius = player->get_node<Area2D>("PickupRadius");
	if (pickupRadius) {
		PickupRadius = pickupRadius;

		PickupRadius->connect("area_entered", callable_mp(this, &PlayerController::PickupAreaEntered));
		PickupRadius->connect("area_exited", callable_mp(this, &PlayerController::PickupAreaExited));
	}

	Area2D* gunPickupRadius = player->get_node<Area2D>("GunPickupRadius");
	if (gunPickupRadius) {
		GunPickupRadius = gunPickupRadius;

		// Note to self: Du kan spare 2 timer i fremtiden ved ikke at sætte CALLABLE_DEFERRED og skabe interne race conditions
		GunPickupRadius->connect("area_entered", callable_mp(this, &PlayerController::InteractibleAreaEntered));
		GunPickupRadius->connect("area_exited", callable_mp(this, &PlayerController::InteractibleAreaExited));
	}

	Timer* gunPickupTimer = player->get_node<Timer>("GunPickupTimer");
	if (gunPickupTimer) {
		GunPickupTimer = gunPickupTimer;

		GunPickupTimer->connect("timeout", callable_mp(this, &PlayerController::PickupTimerTimeout));
		GunPickupTimer->set_wait_time(0.125);
		GunPickupTimer->start();
	}

	Timer* inaccTimer = player->get_node<Timer>("InaccuracyTimer");
	if (inaccTimer) {
		InaccuracyTimer = inaccTimer;
		InaccuracyTimer->set_one_shot(true);
		InaccuracyTimer->connect("timeout", callable_mp(this, &PlayerController::EnableInaccuracyRecovery));
	}

	TextureProgressBar* reloadBar = player->get_node<TextureProgressBar>("VisualNodes/ReloadBar");
	if (reloadBar) {
		ReloadBar = reloadBar;
	}

	player->connect("inc_hit_projectile", callable_mp(this, &PlayerController::OnHitByProjectile));

	GameInstance::GetInstance().RegisterPlayer(ControlledPlayer);

	PlayerHUD->SetHealthMax(ControlledPlayer->MaxHealth);
	PlayerHUD->UpdateHealthCurrent(ControlledPlayer->CurrentHealth);
}

Player* PlayerController::GetPlayer() const {
	return ControlledPlayer;
}

void PlayerController::SetMaxHealth(double max) {
	ControlledPlayer->MaxHealth = max;
	PlayerHUD->SetHealthMax(ControlledPlayer->MaxHealth);
	PlayerHUD->UpdateHealthCurrent(ControlledPlayer->CurrentHealth);
}

Node2D* PlayerController::GetCrosshair() const {
	return PlayerCrosshair;
}

void PlayerController::SetCurrentGunSlot(int32_t slot) {
	CurrentGunSlot = slot;
	ApplyCurrentGun();
	UpdateAmmoLabel();
	PlayerHUD->SetHighlightedWeaponSlot(slot);
}

int32_t PlayerController::GetCurrentGunSlot() const {
	return CurrentGunSlot;
}

void PlayerController::GetStartGun() {
	Gun* newGun = GameInstance::GetInstance().GenerateStarterPistol();
	BindGun(newGun);
	NumEquippedGuns++;

	ControlledPlayer->SetGunInSlot(0, newGun);
	ControlledPlayer->SwitchToGunInSlot(0);
}

void PlayerController::PickUpGunInSlot(int32_t slot) {
	DroppedGunInFocus->CanBePickedUp = false;
	DroppedGunInFocus->InteractibleArea->set_monitorable(false);

	Gun* newGun = GameInstance::GetInstance().CopyDroppedGunToEquip(DroppedGunInFocus);
	DroppedGunInFocus->queue_free();
	DroppedGunInFocus = nullptr;

	BindGun(newGun);

	ControlledPlayer->SetGunInSlot(slot, newGun);

	if (slot == GetCurrentGunSlot()) {
		ControlledPlayer->SwitchToGunInSlot(GetCurrentGunSlot());
	}
}

void PlayerController::SwapGunOnGround() {
	DroppedGunInFocus->CanBePickedUp = false;
	DroppedGunInFocus->InteractibleArea->set_monitorable(false);

	// Presence tested before this is called, so we can probably assume it exists, barring immeasurably tiny time differences create a gap
	Gun* oldGun = GetPlayer()->GetCurrentGun();

	if (IsReloading) {
		oldGun->ReloadTimer->stop();
		GunReloadEnd();
	}

	// Pick up new gun
	Gun* newGun = GameInstance::GetInstance().CopyDroppedGunToEquip(DroppedGunInFocus);
	DroppedGunInFocus->queue_free();
	DroppedGunInFocus = nullptr;

	BindGun(newGun);

	ControlledPlayer->SetGunInSlot(GetCurrentGunSlot(), newGun);
	ControlledPlayer->SwitchToGunInSlot(GetCurrentGunSlot());

	// Drop gun and clean up gun instance
	GameInstance::GetInstance().CopyEquippedGunToDrop(oldGun, GetPlayer()->get_global_position());
	//oldGun->queue_free();
	oldGun->FreeGun();
}

void PlayerController::BindGun(Gun* gun) {
	gun->connect("gun_fired", callable_mp(this, &PlayerController::OnGunFired));
	gun->connect("gun_reload_ended", callable_mp(this, &PlayerController::GunReloadEnd));

	switch (gun->GunDef->GunAmmoType) {
		case EAmmoType::Pistol:
			gun->OwnerReserveAmmo = &ControlledPlayer->PistolAmmo;
			break;

		case EAmmoType::Revolver:
			gun->OwnerReserveAmmo = &ControlledPlayer->RevolverAmmo;
			break;

		case EAmmoType::SMG:
			gun->OwnerReserveAmmo = &ControlledPlayer->SMGAmmo;
			break;

		case EAmmoType::Rifle:
			gun->OwnerReserveAmmo = &ControlledPlayer->ARAmmo;
			break;

		case EAmmoType::Shotgun:
			gun->OwnerReserveAmmo = &ControlledPlayer->ShotgunAmmo;
			break;

		case EAmmoType::Sniper:
			gun->OwnerReserveAmmo = &ControlledPlayer->SniperAmmo;
			break;

		case EAmmoType::Launcher:
			gun->OwnerReserveAmmo = &ControlledPlayer->LauncherAmmo;
			break;

		default:
			gun->OwnerReserveAmmo = &ControlledPlayer->PistolAmmo;
			break;
	}
}

void PlayerController::UnbindGun(Gun* gun) {
	gun->disconnect("gun_fired", callable_mp(this, &PlayerController::OnGunFired));
	gun->disconnect("gun_reload_ended", callable_mp(this, &PlayerController::GunReloadEnd));
	gun->OwnerReserveAmmo = nullptr;
}

void PlayerController::ApplyCurrentGun() {
	Gun* gun = ControlledPlayer->GetCurrentGun();

	ControlledPlayer->Recoil = gun->GunDef->Recoil;
	ControlledPlayer->MinInaccuracy = gun->GunDef->MinInaccuracy;
	ControlledPlayer->MaxInaccuracy = gun->GunDef->MaxInaccuracy;
	ControlledPlayer->InaccuracyRegen = gun->GunDef->InaccuracyRegen;
	ControlledPlayer->InaccuracyRegenDelay = gun->GunDef->InaccuracyRegenDelay;
	ControlledPlayer->Inaccuracy = ControlledPlayer->MinInaccuracy;
	IsFullyAccurate = true;

	if (ControlledPlayer->GetCurrentGun()) {
		PlayerHUD->SetAmmoDisplayType(ControlledPlayer->GetCurrentGun()->GunDef->GunAmmoType);

		if (ControlledPlayer->GetCurrentGun()->MagAmmo > *ControlledPlayer->GetCurrentGun()->OwnerReserveAmmo) {
			ControlledPlayer->GetCurrentGun()->MagAmmo = *ControlledPlayer->GetCurrentGun()->OwnerReserveAmmo;
		}
	}

	UpdateGunHeldType(*gun);
}

void PlayerController::GunReloadStart() {
	CharacterController::GunReloadStart();

	Gun* gun = ControlledPlayer->GetCurrentGun();

	CurReloadTime = 0.0;
	ReloadBar->set_value(0.0);
	ReloadBar->set_max(gun->GunDef->ReloadTime);
	ReloadBar->set_visible(true);
}

void PlayerController::ProcessReload(double delta) {
	CurReloadTime += delta;
	ReloadBar->set_value(CurReloadTime);
}

void PlayerController::GunReloadEnd() {
	CharacterController::GunReloadEnd();

	ReloadBar->set_visible(false);
	UpdateAmmoLabel();
}

void PlayerController::OnGunFired() {
	CharacterController::OnGunFired();
	UpdateAmmoLabel();
}

void PlayerController::EnableInaccuracyRecovery() {
	CharacterController::EnableInaccuracyRecovery();
}

void PlayerController::ApplyRecoil() {
	CharacterController::ApplyRecoil();

	InaccuracyTimer->start((float)ControlledPlayer->InaccuracyRegenDelay);
}

// Temp
void PlayerController::UpdateAmmoLabel() {
	if (!ControlledPlayer->GetCurrentGun()) {
		PlayerHUD->ClearAmmoDisplay();
		return;
	}

	PlayerHUD->SetAmmoDisplayValues(ControlledPlayer->GetCurrentGun()->MagAmmo, ControlledPlayer->GetCurrentGun()->GunDef->MagSize, *ControlledPlayer->GetCurrentGun()->OwnerReserveAmmo);
}

void PlayerController::PickupAreaEntered(Area2D* area) {
	if (area->is_in_group("AmmoPickup")) {
		AmmoPickup* ammo = static_cast<AmmoPickup*>(area);

		// gross, fix later when ammo is redone
		switch ((EAmmoType)ammo->GetAmmoType()) {
			case EAmmoType::Pistol:
				ControlledPlayer->PistolAmmo += ammo->GetAmmoCount();
				break;

			case EAmmoType::Revolver:
				ControlledPlayer->RevolverAmmo += ammo->GetAmmoCount();
				break;

			case EAmmoType::SMG:
				ControlledPlayer->SMGAmmo += ammo->GetAmmoCount();
				break;

			case EAmmoType::Rifle:
				ControlledPlayer->ARAmmo += ammo->GetAmmoCount();
				break;

			case EAmmoType::Shotgun:
				ControlledPlayer->ShotgunAmmo += ammo->GetAmmoCount();
				break;

			case EAmmoType::Sniper:
				ControlledPlayer->SniperAmmo += ammo->GetAmmoCount();
				break;

			case EAmmoType::Launcher:
				ControlledPlayer->LauncherAmmo += ammo->GetAmmoCount();
				break;

			default:
				break;
		}

		print_line(vformat("Picked up %d %s ammo!", ammo->GetAmmoCount(), GetAmmoTypeName((EAmmoType)ammo->GetAmmoType())));

		//ammo->Disable();
		ammo->queue_free();

		UpdateAmmoLabel();
	}
}

void PlayerController::PickupAreaExited(Area2D* area) {
	
}

void PlayerController::InteractibleAreaEntered(Area2D* area) {
	if (area->is_in_group("Interactible")) {
		Interactible* inter = static_cast<Interactible*>(area);
		InteractiblesInRadius.push_back(inter);
		ScanForGuns();
	}

	/*
	Node* parent = area->get_parent();

	if (parent && parent->is_in_group("GunDropped")) {
		GunDropped* dGun = static_cast<GunDropped*>(parent);

		DroppedGunsInRadius.push_back(dGun);
		ScanForGuns();
	}
	*/
}

void PlayerController::InteractibleAreaExited(Area2D* area) {
	if (area->is_in_group("Interactible")) {
		Interactible* inter = static_cast<Interactible*>(area);

		const std::vector<Interactible*>::iterator index = std::find(InteractiblesInRadius.begin(), InteractiblesInRadius.end(), inter);

		if (InteractibleInFocus && inter == InteractibleInFocus) {
			if (InteractibleInFocus->get_parent() && InteractibleInFocus->get_parent()->is_in_group("ItemChest")) {
				ItemChest* focIC = static_cast<ItemChest*>(InteractibleInFocus->get_parent());

				focIC->SetTextVisibility(false);
			}
		}

		if (index != InteractiblesInRadius.end()) {
			InteractiblesInRadius.erase(index);
			ScanForGuns();
		}
	}

	/*
	Node* parent = area->get_parent();

	if (parent && parent->is_in_group("GunDropped")) {
		GunDropped* dGun = static_cast<GunDropped*>(parent);
		const std::vector<GunDropped*>::iterator index = std::find(DroppedGunsInRadius.begin(), DroppedGunsInRadius.end(), dGun);

		if (index != DroppedGunsInRadius.end()) {
			DroppedGunsInRadius.erase(index);
			ScanForGuns();
		}
	}
	*/
}

void PlayerController::PickupTimerTimeout() {
	ScanForGuns();

	/* opdaterer den ikke ordentligt, når man kun går imellem ticks
	if (ControlledPlayer->get_velocity().length() > 0.f) {
		
	}
	*/
}

void PlayerController::ScanForGuns() {
	/*
	GunDropped* dgun = GetClosestGunDropped();

	if (dgun) {
		if (!DroppedGunInFocus || dgun != DroppedGunInFocus) {
			PlayerHUD->GetPriItemCard()->UseGunDef(*dgun->GunDef);
			PlayerHUD->ShowItemCard();
		}

		DroppedGunInFocus = dgun;
	}
	else {
		DroppedGunInFocus = nullptr;
		PlayerHUD->HideItemCard();
	}
	*/

	Interactible* inter = GetClosestInteractible();

	if (inter) {
		Node* parent = inter->get_parent();

		if (parent) {
			if (parent->is_in_group("GunDropped")) {
				GunDropped* dgun = static_cast<GunDropped*>(parent);

				if (!DroppedGunInFocus || dgun != DroppedGunInFocus) {
					if (!dgun->ItemCardPivot->get_child_count()) {
						dgun->CreateItemCard();
					}
					
					//PlayerHUD->MovePriItemCardPivot(dgun->get_global_position());
					//PlayerHUD->GetPriItemCard()->UseGunDef(*dgun->GunDef);
					//PlayerHUD->ShowItemCard();
				}

				if (DroppedGunInFocus && dgun != DroppedGunInFocus) {
					DroppedGunInFocus->DestroyItemCard();
				}

				DroppedGunInFocus = dgun;
			}
			else {
				if (DroppedGunInFocus) {
					DroppedGunInFocus->DestroyItemCard();
				}

				DroppedGunInFocus = nullptr;
				//PlayerHUD->HideItemCard();
			}

			if (parent->is_in_group("ItemChest")) {
				ItemChest* ic = static_cast<ItemChest*>(parent);

				if (!InteractibleInFocus || inter != InteractibleInFocus) {
					ic->SetTextVisibility(true);
				}

				if (InteractibleInFocus && inter != InteractibleInFocus) {
					if (InteractibleInFocus->get_parent() && InteractibleInFocus->get_parent()->is_in_group("ItemChest")) {
						ItemChest* focIC = static_cast<ItemChest*>(InteractibleInFocus->get_parent());

						focIC->SetTextVisibility(false);
					}
				}
			}
			else {
				if (InteractibleInFocus && inter != InteractibleInFocus) {
					if (InteractibleInFocus->get_parent() && InteractibleInFocus->get_parent()->is_in_group("ItemChest")) {
						ItemChest* focIC = static_cast<ItemChest*>(InteractibleInFocus->get_parent());

						focIC->SetTextVisibility(false);
					}
				}
			}
		}

		InteractibleInFocus = inter;
	}
	else {
		if (DroppedGunInFocus) {
			DroppedGunInFocus->DestroyItemCard();
		}

		InteractibleInFocus = nullptr;
		DroppedGunInFocus = nullptr;
		//PlayerHUD->HideItemCard();
	}
}

GunDropped* PlayerController::GetClosestGunDropped() {
	if (DroppedGunsInRadius.empty()) {
		return nullptr;
	}

	if (DroppedGunsInRadius.size() == 1) {
		return DroppedGunsInRadius[0];
	}

	float shortestDist = 100.f;
	int32_t shortestIndex = 0;

	for (size_t i = 0; i < DroppedGunsInRadius.size(); i++) {
		const GunDropped* element = DroppedGunsInRadius[i];

		if (!element) {
			continue;
		}

		const float dist = ControlledPlayer->get_global_position().distance_to(element->get_global_position());

		if (shortestDist > dist) {
			shortestDist = dist;
			shortestIndex = i;
		}
	}

	return DroppedGunsInRadius[shortestIndex];
}

Interactible* PlayerController::GetClosestInteractible() {
	if (InteractiblesInRadius.empty()) {
		return nullptr;
	}

	if (InteractiblesInRadius.size() == 1) {
		return InteractiblesInRadius[0];
	}

	float shortestDist = 100.f;
	int32_t shortestIndex = 0;

	for (size_t i = 0; i < InteractiblesInRadius.size(); i++) {
		const Interactible* element = InteractiblesInRadius[i];

		if (!element) {
			continue;
		}

		const float dist = ControlledPlayer->get_global_position().distance_to(element->get_global_position());

		if (shortestDist > dist) {
			shortestDist = dist;
			shortestIndex = i;
		}
	}

	return InteractiblesInRadius[shortestIndex];
}

void PlayerController::GiveExperience(double exp) {
	if (!ControlledPlayer) {
		print_error("No attached player");
		return;
	}

	ControlledPlayer->Experience += exp;

	if (ControlledPlayer->Level < MaxLevel) {
		if (ControlledPlayer->Experience >= ExperienceThresholds[ControlledPlayer->Level]) {
			LevelUp();

			while (true) {
				if (ControlledPlayer->Experience >= ExperienceThresholds[ControlledPlayer->Level] && ControlledPlayer->Level < MaxLevel) {
					LevelUp();
				}
				else {
					break;
				}
			}

			PlayerHUD->UpdateLevel(ControlledPlayer->Level);
		}
	}

	PlayerHUD->UpdateEXP(ControlledPlayer->Experience, ExperienceThresholds[ControlledPlayer->Level - 1], ExperienceThresholds[ControlledPlayer->Level]);
}

double PlayerController::GetExperience() const {
	if (ControlledPlayer) {
		return ControlledPlayer->Experience;
	}

	return 0.0;
}

void PlayerController::LevelUp() {
	if (ControlledPlayer) {
		ControlledPlayer->Level++;

		//SetMaxHealth(85 + (15 * ControlledPlayer->Level));
		ControlledPlayer->MaxHealth = 85 + (15 * ControlledPlayer->Level); // Will be replaced when other factors exist
		ControlledPlayer->CurrentHealth = ControlledPlayer->MaxHealth; // might be removed later, who knows
		PlayerHUD->SetHealthMax(ControlledPlayer->MaxHealth);
		PlayerHUD->UpdateHealthCurrent(ControlledPlayer->CurrentHealth);
	}
}

void PlayerController::UpdateGunHeldType(const Gun& heldGun) {
	if (!GunSprite) {
		print_error("No gun sprite, aborting changing the atlas sheet");
		return;
	}

	Rect2 region { Point2(0, 0), Size2(GunSpriteAtlasStepX, GunSpriteAtlasStepY) };
	EGunSubType type = heldGun.GunDef->GunSubType;

	switch (type) {
		case EGunSubType::Repeater:
		case EGunSubType::MachinePistol:
			region.set_position(Vector2(0, 0));
			break;

		case EGunSubType::SMG:
			region.set_position(Vector2(GunSpriteAtlasStepX, 0));
			break;

		case EGunSubType::CombatRifle:
		case EGunSubType::MachineGun:
			region.set_position(Vector2(GunSpriteAtlasStepX * 2, 0));
			break;

		default:
			region.set_position(Vector2(0, 0));
			break;
	}

	AtlasTexture* atlas = static_cast<AtlasTexture*>(GunSprite->get_texture().ptr());
	atlas->set_region(region);
}
