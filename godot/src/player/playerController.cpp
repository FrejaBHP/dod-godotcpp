// #include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/viewport.hpp>

// temp
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

//#include <godot_cpp/variant/utility_functions.hpp>
#include <algorithm>

#include "player/playerController.h"
#include "player/playerChar.h"
#include "gameInstance.h"
#include "gun/gun.h"
#include "gun/gunDropped.h"
#include "shared/utility.h"
#include "ui/hud.h"

using namespace godot;
using namespace std::chrono;

void PlayerController::_bind_methods() {
	ClassDB::bind_method(D_METHOD("ProcessMovementInput"), &PlayerController::ProcessMovementInput);
	ClassDB::bind_method(D_METHOD("SetPlayer"), &PlayerController::SetPlayer);
	ClassDB::bind_method(D_METHOD("GetPlayer"), &PlayerController::GetPlayer);
	ClassDB::bind_method(D_METHOD("GetCrosshair"), &PlayerController::GetCrosshair);
	ClassDB::bind_method(D_METHOD("SetCurrentGunSlot"), &PlayerController::SetCurrentGunSlot);
	ClassDB::bind_method(D_METHOD("GetCurrentGunSlot"), &PlayerController::GetCurrentGunSlot);
	ClassDB::bind_method(D_METHOD("UpdateAmmoLabel"), &PlayerController::UpdateAmmoLabel);
	ClassDB::bind_method(D_METHOD("PickupAreaEntered"), &PlayerController::PickupAreaEntered);
	ClassDB::bind_method(D_METHOD("PickupAreaExited"), &PlayerController::PickupAreaExited);
	ClassDB::bind_method(D_METHOD("Interact"), &PlayerController::Interact);
	ClassDB::bind_method(D_METHOD("SwapGunOnGround"), &PlayerController::SwapGunOnGround);
	ClassDB::bind_method(D_METHOD("PickupTimerTimeout"), &PlayerController::PickupTimerTimeout);
	ClassDB::bind_method(D_METHOD("ScanForGuns"), &PlayerController::ScanForGuns);
	ClassDB::bind_method(D_METHOD("GetClosestGunDropped"), &PlayerController::GetClosestGunDropped);

	ClassDB::bind_method(D_METHOD("ApplyRecoil"), &PlayerController::ApplyRecoil);
	ClassDB::bind_method(D_METHOD("OnGunFired"), &PlayerController::OnGunFired);
	ClassDB::bind_method(D_METHOD("ReloadEnd"), &PlayerController::GunReloadEnd);
}

PlayerController::PlayerController() {
	DroppedGunsInRadius.reserve(8);
}

void PlayerController::_ready() {
	InputMap::get_singleton()->load_from_project_settings();
}

void PlayerController::_input(const Ref<InputEvent>& p_event) {
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
				GunReloadStart(gun);
			}
		}

		if (p_event.ptr()->is_action_pressed("interact")) {
			Interact();
		}

		if (p_event.ptr()->is_action_pressed("debug0")) {
			GameInstance::GetInstance().GenerateAndDropGun(-1);
		}

		if (p_event.ptr()->is_action_pressed("debug1")) {
			for (size_t i = 0; i < PlayerNumGunSlots; i++) {
				Gun* gun = GetPlayer()->GetGunInSlot(i);

				if (gun) {
					print_line((int32_t)gun->GunDef.use_count());
				}
			}
		}

		if (p_event.ptr()->is_action_pressed("debug2")) {
			GameInstance::GetInstance().TestSpawnEnemy();
		}

		if (p_event.ptr()->is_action_pressed("debug3")) {
			
		}

		if (p_event.ptr()->is_action_pressed("debug4")) {
			GameInstance::GetInstance().GenerateAndDropGun(0);
		}

		if (p_event.ptr()->is_action_pressed("debug5")) {
			GameInstance::GetInstance().GenerateAndDropGun(1);
		}

		if (p_event.ptr()->is_action_pressed("debug6")) {
			GameInstance::GetInstance().GenerateAndDropGun(2);
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
	}
}

void PlayerController::_physics_process(double delta) {
	if (ControlledPlayer) {
		Vector2 movement = ProcessMovementInput();
		ControlledPlayer->ApplyMovement(movement);

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

		/*
		double spread = 0;

		if (ControlledPlayer->GetCurrentGun()) {
			spread = ControlledPlayer->GetCurrentGun()->GunDef->Spread;
		}

		DebugLabel->set_text(vformat("%.2f + %.2f, %.2f, %d", spread, ControlledPlayer->Inaccuracy, InaccuracyTimer->get_time_left(), int(CanRecoverInaccuracy)));
		*/
	}
}

Vector2 PlayerController::ProcessMovementInput() {
	Vector2 movementInput = Input::get_singleton()->get_vector("move_left", "move_right", "move_up", "move_down");
	return movementInput;
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
}

void PlayerController::SetPlayer(Player* player) {
	ControlledPlayer = player;

	HUD* hud = player->get_node<HUD>("CanvasLayer/PlayerHUD");
	if (hud) {
		PlayerHUD = hud;
	}

	Node2D* crosshair = player->get_node<Node2D>("Crosshair");
	if (crosshair) {
		PlayerCrosshair = crosshair;
	}

	Label* label = player->get_node<Label>("Label");
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

		// Note to self: Du kan spare 2 timer i fremtiden ved ikke at sætte CALLABLE_DEFERRED og skabe interne race conditions
		PickupRadius->connect("area_entered", callable_mp(this, &PlayerController::PickupAreaEntered));
		PickupRadius->connect("area_exited", callable_mp(this, &PlayerController::PickupAreaExited));
	}

	Timer* pickupTimer = player->get_node<Timer>("PickupTimer");
	if (pickupTimer) {
		PickupTimer = pickupTimer;

		PickupTimer->connect("timeout", callable_mp(this, &PlayerController::PickupTimerTimeout));
		PickupTimer->set_wait_time(0.125);
		PickupTimer->start();
	}

	Timer* inaccTimer = player->get_node<Timer>("InaccuracyTimer");
	if (inaccTimer) {
		InaccuracyTimer = inaccTimer;
		InaccuracyTimer->set_one_shot(true);
		InaccuracyTimer->connect("timeout", callable_mp(this, &PlayerController::EnableInaccuracyRecovery));
	}

	TextureProgressBar* reloadBar = player->get_node<TextureProgressBar>("ReloadBar");
	if (reloadBar) {
		ReloadBar = reloadBar;
	}

	GameInstance::GetInstance().RegisterPlayer(ControlledPlayer);
}

Player* PlayerController::GetPlayer() const {
	return ControlledPlayer;
}

Node2D* PlayerController::GetCrosshair() const {
	return PlayerCrosshair;
}

void PlayerController::SetCurrentGunSlot(int32_t slot) {
	CurrentGunSlot = slot;
	ApplyCurrentGun();
	UpdateAmmoLabel();
}

int32_t PlayerController::GetCurrentGunSlot() const {
	return CurrentGunSlot;
}

void PlayerController::PickUpGunInSlot(int32_t slot) {
	DroppedGunInFocus->CanBePickedUp = false;
	DroppedGunInFocus->PickupArea->set_monitorable(false);

	Gun* newGun = GameInstance::GetInstance().CopyDroppedGunToEquip(DroppedGunInFocus);
	DroppedGunInFocus->queue_free();
	DroppedGunInFocus = nullptr;

	BindGun(newGun);

	ControlledPlayer->SetGunInSlot(slot, newGun);

	if (slot == GetCurrentGunSlot()) {
		ControlledPlayer->SwitchToGunInSlot(GetCurrentGunSlot());

		UpdateAmmoLabel();
	}
}

void PlayerController::SwapGunOnGround() {
	DroppedGunInFocus->CanBePickedUp = false;
	DroppedGunInFocus->PickupArea->set_monitorable(false);

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
	oldGun->queue_free();

	UpdateAmmoLabel();
}

void PlayerController::BindGun(Gun* gun) {
	gun->connect("gun_fired", callable_mp(this, &PlayerController::OnGunFired));
	gun->connect("gun_reload_ended", callable_mp(this, &PlayerController::GunReloadEnd));
}

void PlayerController::UnbindGun(Gun* gun) {
	gun->disconnect("gun_fired", callable_mp(this, &PlayerController::OnGunFired));
	gun->disconnect("gun_reload_ended", callable_mp(this, &PlayerController::GunReloadEnd));
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
}

void PlayerController::GunReloadStart(Gun* gun) {
	IsReloading = true;
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
	IsReloading = false;
	ReloadBar->set_visible(false);
	UpdateAmmoLabel();
}

void PlayerController::OnGunFired() {
	ApplyRecoil();
	UpdateAmmoLabel();
}

void PlayerController::ApplyRecoil() {
	CanRecoverInaccuracy = false;
	IsFullyAccurate = false;

	double newInaccuracy = ControlledPlayer->Inaccuracy + ControlledPlayer->Recoil;
	if (newInaccuracy > ControlledPlayer->MaxInaccuracy) {
		newInaccuracy = ControlledPlayer->MaxInaccuracy;
	}

	ControlledPlayer->Inaccuracy = newInaccuracy;

	InaccuracyTimer->start((float)ControlledPlayer->InaccuracyRegenDelay);
}

void PlayerController::EnableInaccuracyRecovery() {
	CanRecoverInaccuracy = true;
}

void PlayerController::RecoverInaccuracy(double delta) {
	double regenStep = ControlledPlayer->InaccuracyRegen * delta;
	double newInaccuracy = ControlledPlayer->Inaccuracy - regenStep;

	if (ControlledPlayer->MinInaccuracy > newInaccuracy) {
		newInaccuracy = ControlledPlayer->MinInaccuracy;
		CanRecoverInaccuracy = false;
		IsFullyAccurate = true;
	}

	ControlledPlayer->Inaccuracy = newInaccuracy;
}

// Temp
void PlayerController::UpdateAmmoLabel() {
	if (!ControlledPlayer->GetCurrentGun()) {
		PlayerHUD->ClearAmmoDisplay();
		return;
	}

	int32_t ammo;
	if (ControlledPlayer->GetCurrentGun()->GunDef->GunType == EGunType::Pistol) {
		ammo = ControlledPlayer->PistolAmmo;
	}
	else if (ControlledPlayer->GetCurrentGun()->GunDef->GunType == EGunType::SMG) {
		ammo = ControlledPlayer->SMGAmmo;
	}
	else {
		ammo = ControlledPlayer->ARAmmo;
	}

	PlayerHUD->SetAmmoDisplayValues(ControlledPlayer->GetCurrentGun()->MagAmmo, ammo);
}

void PlayerController::PickupAreaEntered(Area2D* area) {
	Node* parent = area->get_parent();

	if (parent && parent->is_in_group("GunDropped")) {
		GunDropped* dGun = static_cast<GunDropped*>(parent);

		DroppedGunsInRadius.push_back(dGun);
		ScanForGuns();
	}
}

void PlayerController::PickupAreaExited(Area2D* area) {
	Node* parent = area->get_parent();

	if (parent && parent->is_in_group("GunDropped")) {
		GunDropped* dGun = static_cast<GunDropped*>(parent);
		const std::vector<GunDropped*>::iterator index = std::find(DroppedGunsInRadius.begin(), DroppedGunsInRadius.end(), dGun);

		if (index != DroppedGunsInRadius.end()) {
			DroppedGunsInRadius.erase(index);
			ScanForGuns();
		}
	}
}

void PlayerController::PickupTimerTimeout() {
	ScanForGuns();

	/* opdaterer den ikke ordentligt, når man kun går imellem ticks
	if (ControlledPlayer->get_velocity().length() > 0.f) {
		
	}
	*/
}

void PlayerController::ScanForGuns() {
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
