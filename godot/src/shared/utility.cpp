#include "shared/utility.h"

std::random_device rnd;
std::mt19937 gen(rnd());

int GetRandomInt(int min, int max) {
	std::uniform_int_distribution<std::mt19937::result_type> distr(min, max);

	return distr(gen);
}

double GetRandomDouble(double min, double max) {
	std::uniform_real_distribution<> distr(min, max);

	return distr(gen);
}

std::string GetManufacturerName(EManufacturer manufacturer) {
	switch (manufacturer) {
		case EManufacturer::Mars:
			return "Mars";
		case EManufacturer::Prism:
			return "Prism";
		case EManufacturer::Bozboz:
			return "Bozboz";
		case EManufacturer::Weaver:
			return "Weaver";
		case EManufacturer::Smitherson:
			return "Smitherson";
		case EManufacturer::Violet:
			return "Violet";
		case EManufacturer::Prometheus:
			return "Prometheus";
		case EManufacturer::Bjorn:
			return "Bjorn";
		default:
			return "???";
	}
}

std::string GetGunTypeName(EGunType guntype) {
	switch (guntype) {
		case EGunType::None:
			return "None";
		case EGunType::Pistol:
			return "Pistol";
		case EGunType::Revolver:
			return "Revolver";
		case EGunType::SMG:
			return "SMG";
		case EGunType::Rifle:
			return "Rifle";
		case EGunType::Shotgun:
			return "Shotgun";
		case EGunType::Sniper:
			return "Sniper";
		case EGunType::Launcher:
			return "Launcher";
		default:
			return "???";
	}
}

std::string GetGunSubTypeName(EGunSubType subtype) {
	switch (subtype) {
		case EGunSubType::None:
			return "None";
		case EGunSubType::Repeater:
			return "Repeater";
		case EGunSubType::MachinePistol:
			return "Machine Pistol";
		case EGunSubType::AssaultRifle:
			return "Assault Rifle";
		case EGunSubType::MachineGun:
			return "Machine Gun";
		case EGunSubType::CombatShotgun:
			return "Combat Shotgun";
		case EGunSubType::AssaultShotgun:
			return "Assault Shotgun";
		case EGunSubType::DoubleBarrel:
			return "Double Barrel Shotgun";
		case EGunSubType::SniperSemiAuto:
			return "Semi-Auto Sniper";
		case EGunSubType::SniperBoltAction:
			return "Bolt Action Sniper";
		default:
			return "???";
	}
}

std::string GetElementName(EElement element) {
	switch (element) {
		case EElement::None:
			return "None";
		case EElement::Fire:
			return "Incendiary";
		case EElement::Shock:
			return "Shock";
		case EElement::Corrosive:
			return "Corrosive";
		case EElement::Cryo:
			return "Cryo";
		default:
			return "???";
	}
}
