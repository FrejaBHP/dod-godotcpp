#include "gun/gunDefinition.h"

// using namespace godot;

GunDefinition::GunDefinition() {

}

void GunDefinition::SetPistolStats() {
	GunType = EGunType::PistolRepeater;
	FireTime = 330;
	MagSize = 8;
	ReloadTime = 0.8;
}

void GunDefinition::SetSMGStats() {
	GunType = EGunType::SMG;
	FireTime = 80;
	MagSize = 32;
	ReloadTime = 1.5;
}

void GunDefinition::SetARStats() {
	GunType = EGunType::RifleAssault;
	FireTime = 150;
	MagSize = 20;
	ReloadTime = 2;
}

GunDefinition::~GunDefinition() {

}
