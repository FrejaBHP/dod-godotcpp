#include "shared/utility.h"

std::random_device rnd;
std::mt19937 gen(rnd());

int GetRandomInt(int min, int max) {
	std::uniform_int_distribution<std::mt19937::result_type> distr(min, max);

	return distr(gen);
}

float GetRandomFloat(float min, float max) {
	std::uniform_real_distribution<> distr(min, max);

	return distr(gen);
}

double GetRandomDouble(double min, double max) {
	std::uniform_real_distribution<> distr(min, max);

	return distr(gen);
}

double GetBaseScaled(int32_t level) {
	// 0.8 * (( Level ^ 1.3) + 9)
	double base = 0.8 * (pow(level, 1.3) + 9);

	return base;
}

godot::Color GetRarityColour(int32_t rarity) {
	godot::Color rarityColour;

	// 0 - 5: White/Common
	if (rarity < RarityMinUncommon) {
		rarityColour = godot::Color(0.6f, 0.6f, 0.6f, 1.f);
	}
	// 6 - 12: Green/Uncommon
	else if (rarity < RarityMinRare) {
		rarityColour = godot::Color(0.25f, 0.85f, 0.05f, 1.f);
	}
	// 13 - 19: Blue/Rare
	else if (rarity < RarityMinEpic) {
		rarityColour = godot::Color(0.2f, 0.45f, 1.f, 1.f);
	}
	// 20 - 49: Purple/Epic
	else if (rarity < RarityMinLegendaryLow) {
		rarityColour = godot::Color(0.67f, 0.25f, 1.f, 1.f);
	}
	// 50 - 62: Yellow/Unique
	else if (rarity < RarityMinLegendaryMid) {
		rarityColour = godot::Color(1.f, 1.f, 0.25f, 1.f);
	}
	// 63 - 69: Orange/Legendary
	else if (rarity < RarityMinLegendaryHigh) {
		rarityColour = godot::Color(1.f, 0.6f, 0.f, 1.f);
	}
	// 70 - 100: Dark Orange/Higher tier legendary
	else if (rarity < RarityMinPearlescent) {
		rarityColour = godot::Color(0.85f, 0.45f, 0.f, 1.f);
	}
	// 101+: Pearlescent
	else {
		rarityColour = godot::Color(0.f, 1.f, 1.f, 1.f);
	}

	return rarityColour;
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
			return "Placeholder";
	}
}

std::string GetGunTypeName(EGunType guntype) {
	switch (guntype) {
		case EGunType::None:
			return "None";
		case EGunType::Pistol:
			return "Pistol";
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
		case EGunSubType::Revolver:
			return "Revolver";
		case EGunSubType::CombatRifle:
			return "Combat Rifle";
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
