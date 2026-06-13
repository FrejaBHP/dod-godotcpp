#include "gun/gunDefinition.h"

// using namespace godot;

GunDefinition::GunDefinition() {

}

void GunDefinition::SetPistolStats() {
	GunType = EGunType::Pistol;
	GunSubType = EGunSubType::Repeater;
	Damage = 6;
	FireTime = 300;
	MagSize = 8;
	ReloadTime = 0.8;

	MetaMagAmmo = MagSize;
}

void GunDefinition::SetSMGStats() {
	GunType = EGunType::SMG;
	GunSubType = EGunSubType::None;
	Damage = 3;
	FireTime = 80;
	MagSize = 32;
	ReloadTime = 1.5;

	MetaMagAmmo = MagSize;
}

void GunDefinition::SetARStats() {
	GunType = EGunType::Rifle;
	GunSubType = EGunSubType::AssaultRifle;
	Damage = 5;
	FireTime = 140;
	MagSize = 20;
	ReloadTime = 2;

	MetaMagAmmo = MagSize;
}

GunDefinition::~GunDefinition() {

}
