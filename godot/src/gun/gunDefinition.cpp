#include "gun/gunDefinition.h"

// using namespace godot;

GunDefinition::GunDefinition() {

}

void GunDefinition::SetPistolStats() {
	GunType = EGunType::PistolRepeater;
	FireTime = 400;
	MagSize = 8;
	ReloadTime = 1;
}

void GunDefinition::SetSMGStats() {
	GunType = EGunType::SMG;
	FireTime = 100;
	MagSize = 32;
	ReloadTime = 2;
}

GunDefinition::~GunDefinition() {

}
