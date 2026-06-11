// #include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/viewport.hpp>

// temp
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

//#include <godot_cpp/variant/utility_functions.hpp>

#include "player/playerController.h"
#include "player/playerChar.h"
#include "gameInstance.h"
#include "gun/gun.h"
#include "gun/gunDropped.h"
#include "shared/utility.h"

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
}

PlayerController::PlayerController() {
	
}

void PlayerController::_ready() {
	InputMap::get_singleton()->load_from_project_settings();
}

void PlayerController::_input(const Ref<InputEvent>& p_event) {
	if (p_event.ptr()->is_action_pressed("lmb")) {
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
			ControlledPlayer->SwitchToGunInSlot(0);
		}
		else if (p_event.ptr()->is_action_pressed("weaponSlot2")) {
			ControlledPlayer->SwitchToGunInSlot(1);
		}
		else if (p_event.ptr()->is_action_pressed("weaponSlot3")) {
			ControlledPlayer->SwitchToGunInSlot(2);
		}

		if (p_event.ptr()->is_action_pressed("reload")) {
			if (ControlledPlayer->GetCurrentGun()) {
				ControlledPlayer->GetCurrentGun()->TryReload();
			}
		}

		if (p_event.ptr()->is_action_pressed("interact")) {
			Interact();
		}

		if (p_event.ptr()->is_action_pressed("debug0")) {

		}

		if (p_event.ptr()->is_action_pressed("debug1")) {
			for (size_t i = 0; i < PlayerNumGunSlots; i++) {
				Gun* gun = GetPlayer()->GetGunInSlot(i);

				if (gun) {
					print_line(gun->GunDef.use_count());
				}
			}
		}

		if (p_event.ptr()->is_action_pressed("debug4")) {
			GameInstance::GetInstance().DebugSpawnGun(0);
		}

		if (p_event.ptr()->is_action_pressed("debug5")) {
			GameInstance::GetInstance().DebugSpawnGun(1);
		}

		if (p_event.ptr()->is_action_pressed("debug6")) {
			GameInstance::GetInstance().DebugSpawnGun(2);
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

			if (currentGun) {
				currentGun->TryPrimaryFire();
			}
		}

		if (DroppedGunInFocus) {
			std::string focus = GetGunTypeName(DroppedGunInFocus->GunDef->GunType) + " : " + GetGunSubTypeName(DroppedGunInFocus->GunDef->GunSubType);
			DebugLabel->set_text(focus.c_str());
		}
		else {
			DebugLabel->set_text("None");
		}
	}
}

Vector2 PlayerController::ProcessMovementInput() {
	Vector2 movementInput = Input::get_singleton()->get_vector("move_left", "move_right", "move_up", "move_down");
	return movementInput;
}

void PlayerController::Interact() {
	if (DroppedGunInFocus && DroppedGunInFocus->CanBePickedUp) {
		Gun* curGun = GetPlayer()->GetCurrentGun();

		if (curGun) {
			SwapGunOnGround();
		}
	}
}

void PlayerController::SetPlayer(Player* player) {
	ControlledPlayer = player;

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

	Label* ammoLabel = player->get_node<Label>("CanvasLayer/Control/Label");
	if (ammoLabel) {
		AmmoLabel = ammoLabel;
	}

	Area2D* pickupRadius = player->get_node<Area2D>("PickupRadius");
	if (pickupRadius) {
		PickupRadius = pickupRadius;

		// Note to self: Du kan spare 2 timer i fremtiden ved ikke at sætte CALLABLE_DEFERRED og skabe interne race conditions
		PickupRadius->connect("area_entered", callable_mp(this, &PlayerController::PickupAreaEntered));
		PickupRadius->connect("area_exited", callable_mp(this, &PlayerController::PickupAreaExited));
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
	UpdateAmmoLabel();
}

int32_t PlayerController::GetCurrentGunSlot() const {
	return CurrentGunSlot;
}

void PlayerController::SwapGunOnGround() {
	DroppedGunInFocus->CanBePickedUp = false;
	DroppedGunInFocus->PickupArea->set_monitorable(false);

	// Presence tested before this is called, so we can probably assume it exists, barring immeasurably tiny time differences create a gap
	Gun* oldGun = GetPlayer()->GetCurrentGun();

	// Pick up new gun
	Gun* newGun = GameInstance::GetInstance().CopyDroppedGunToEquip(DroppedGunInFocus);
	DroppedGunInFocus->queue_free();
	DroppedGunInFocus = nullptr;

	ControlledPlayer->SetGunInSlot(GetCurrentGunSlot(), newGun);
	ControlledPlayer->SwitchToGunInSlot(GetCurrentGunSlot());

	// Drop gun and clean up gun instance
	GameInstance::GetInstance().CopyEquippedGunToDrop(oldGun, GetPlayer()->get_global_position());
	oldGun->queue_free();

	UpdateAmmoLabel();
}

// Temp
void PlayerController::UpdateAmmoLabel() {
	if (!ControlledPlayer->GetCurrentGun()) {
		AmmoLabel->set_text("");
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

	char ammoBuffer[32];
	sprintf(ammoBuffer, "%d / %d", ControlledPlayer->GetCurrentGun()->MagAmmo, ammo);

	AmmoLabel->set_text(ammoBuffer);
}

void PlayerController::PickupAreaEntered(Area2D* area) {
	Node* parent = area->get_parent();

	if (parent && parent->is_in_group("GunDropped")) {
		GunDropped* dGun = static_cast<GunDropped*>(parent);

		//std::string type = GetGunTypeName(dGun->GunDef->GunType) + " : " + GetGunSubTypeName(dGun->GunDef->GunSubType);
		//print_line(type.c_str());

		DroppedGunInFocus = dGun;
	}
}

void PlayerController::PickupAreaExited(Area2D* area) {
	Node* parent = area->get_parent();

	if (parent && parent->is_in_group("GunDropped")) {
		GunDropped* dGun = static_cast<GunDropped*>(parent);

		if (dGun == DroppedGunInFocus) {
			TypedArray<Area2D> overlaps = PickupRadius->get_overlapping_areas();

			if (overlaps.size() == 0) {
				DroppedGunInFocus = nullptr;
			}
			else {
				float shortestDist = 100.f;
				int32_t shortestIndex = 0;

				for (size_t i = 0; i < overlaps.size(); i++) {
					// static_cast virker overhovedet ikke til Variant-typer >.>
					Area2D* element = Object::cast_to<Area2D>(overlaps[i]);

					float dist = ControlledPlayer->get_global_position().distance_squared_to(element->get_global_position());
					if (shortestDist > dist) {
						shortestDist = dist;
						shortestIndex = i;
					}
				}

				Area2D* closest = Object::cast_to<Area2D>(overlaps[shortestIndex]);
				GunDropped* newFocus = static_cast<GunDropped*>(closest->get_parent());
				DroppedGunInFocus = newFocus;
			}
		}
	}
}
