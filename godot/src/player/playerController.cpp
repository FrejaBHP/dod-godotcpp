// #include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/viewport.hpp>

// temp
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

#include "player/playerController.h"
#include "player/playerChar.h"
#include "gun/gun.h"
#include "gun/gunDropped.h"

using namespace godot;
using namespace std::chrono;

void PlayerController::_bind_methods() {
	ClassDB::bind_method(D_METHOD("ProcessMovementInput"), &PlayerController::ProcessMovementInput);
	ClassDB::bind_method(D_METHOD("SetPlayer"), &PlayerController::SetPlayer);
	ClassDB::bind_method(D_METHOD("GetPlayer"), &PlayerController::GetPlayer);
	ClassDB::bind_method(D_METHOD("GetCrosshair"), &PlayerController::GetCrosshair);
	ClassDB::bind_method(D_METHOD("SetCurrentGunSlot"), &PlayerController::SetCurrentGunSlot);
	ClassDB::bind_method(D_METHOD("UpdateAmmoLabel"), &PlayerController::UpdateAmmoLabel);
	ClassDB::bind_method(D_METHOD("DebugSpawnGun"), &PlayerController::DebugSpawnGun);
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
			DebugSpawnGun(0);
		}

		if (p_event.ptr()->is_action_pressed("debug5")) {
			DebugSpawnGun(1);
		}

		if (p_event.ptr()->is_action_pressed("debug6")) {
			DebugSpawnGun(2);
		}
	}
}

void PlayerController::DebugSpawnGun(int32_t type) {
	std::shared_ptr<GunDefinition> gundef = std::make_shared<GunDefinition>();

	if (type == 0) {
		gundef->SetPistolStats();
	}
	else if (type == 1) {
		gundef->SetSMGStats();
	}
	else {
		gundef->SetARStats();
	}

	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> droppedScene = loader->load("res://gun_dropped.tscn");

	if (droppedScene->can_instantiate()) {
		Node2D* world = get_tree()->get_root()->get_node<Node2D>("World");

		if (world) {
			GunDropped* dGun = static_cast<GunDropped*>(droppedScene->instantiate());
			world->add_child(dGun);
			dGun->SetupDroppedGun(gundef);

			dGun->set_global_position(GetPlayer()->get_global_position());
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
	}
}

Vector2 PlayerController::ProcessMovementInput() {
	Vector2 movementInput = Input::get_singleton()->get_vector("move_left", "move_right", "move_up", "move_down");
	return movementInput;
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
}

Player* PlayerController::GetPlayer() const {
	return ControlledPlayer;
}

Node2D* PlayerController::GetCrosshair() {
	return PlayerCrosshair;
}

void PlayerController::SetCurrentGunSlot(int32_t slot) {
	CurrentGunSlot = slot;
	UpdateAmmoLabel();
}

// Temp
void PlayerController::UpdateAmmoLabel() {
	if (!ControlledPlayer->GetCurrentGun()) {
		AmmoLabel->set_text("");
		return;
	}

	int32_t ammo;
	if (ControlledPlayer->GetCurrentGun()->GunDef->GunType == EGunType::PistolRepeater) {
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
