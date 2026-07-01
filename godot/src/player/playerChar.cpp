#include "player/playerChar.h"
#include "player/playerController.h"
#include "gun/gun.h"

using namespace godot;

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetController"), &Player::SetController);
	ClassDB::bind_method(D_METHOD("GetController"), &Player::GetController);

	ClassDB::bind_method(D_METHOD("SetGunInSlot"), &Player::SetGunInSlot);
	ClassDB::bind_method(D_METHOD("GetGunInSlot"), &Player::GetGunInSlot);

	ClassDB::bind_method(D_METHOD("SetCurrentGun"), &Player::SetCurrentGun);
	ClassDB::bind_method(D_METHOD("GetCurrentGun"), &Player::GetCurrentGun);

	ClassDB::bind_method(D_METHOD("SwitchToGunInSlot"), &Player::SwitchToGunInSlot);
}

Player::Player() {
	MaxSpeed = 200.f;

	for (size_t i = 0; i < PlayerNumGunSlots; i++) {
		GunSlots[i] = nullptr;
	}
}

void Player::_ready() {
	Alignment = EAlignment::Player;
	add_to_group("Character");
	add_to_group("Player");

	PlayerController* newController = memnew(PlayerController);
	
	if (newController) {
		add_child(newController);
		SetController(newController);
	}
}

void Player::_process(double delta) {

}

void Player::_physics_process(double delta) {
	
}

void Player::SetController(PlayerController* controller) {
	Controller = controller;
	Controller->SetPlayer(this);
}

PlayerController* Player::GetController() const {
	return Controller;
}

void Player::SetGunInSlot(int32_t slot, Gun* gun) {
	GunSlots[slot] = gun;
	gun->OwningCharacter = this;
}

Gun* Player::GetGunInSlot(int32_t slot) const {
	return GunSlots[slot];
}

void Player::SetCurrentGun(Gun* gun) {
	CurrentGun = gun;
}

Gun* Player::GetCurrentGun() {
	return CurrentGun;
}

void Player::SwitchToGunInSlot(int32_t slot) {
	if (GunSlots[slot]) {
		SetCurrentGun(GunSlots[slot]);
		Controller->SetCurrentGunSlot(slot);
	}
}
