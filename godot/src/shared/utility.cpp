#include "shared/utility.h"
#include <godot_cpp/classes/resource_loader.hpp>

std::random_device rnd;
std::mt19937 gen(rnd());

const godot::Color ColourItemAmmoCrate { 0.3f, 0.5f, 0.0f, 1.0f };
const godot::Color ColourItemWeaponsChest { 0.75f, 0.0f, 0.0f, 1.0f };

const double DamageEffectiveness[6][5] = {
	/*			Neutral	 Flesh   Shield  Armour  Energy			*/
	/*None*/	{ 1.0,    1.0,    1.0,    0.9,    0.9 },
	/*Incen*/	{ 1.0,    1.5,    0.75,   0.6,    0.75 },
	/*Shock*/	{ 1.0,    0.6,    1.5,    0.75,   0.9 },
	/*Corro*/	{ 1.0,    0.75,   0.6,    1.5,    0.75 },
	/*Cryo*/	{ 1.0,    1.25,   0.9,    0.9,    1.5 },
	/*Explo*/	{ 1.0,    1.0,    0.9,    1.25,   0.9 }
};

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

double GetWeaponBaseDamage(int level) {
	// 0.8 * (( Level ^ 1.3) + 9)
	//double base = 0.8 * (pow(level, 1.3) + 9);

	double base = 8 * pow(1.06, level - 1);

	return base;
}

double GetShieldBaseCapacity(int level) {
	double base = 50 * pow(1.06, level - 1);

	return base;
}

double GetEnemyBaseHealth(int level) {
	double base = 50 * pow(1.074, level - 1);

	return base;
}

double GetDamageEffectiveness(EElement damageType, EHealthType healthType) {
	if (damageType == EElement::COUNT) {
		return 0.0;
	}

	return DamageEffectiveness[(int)damageType][(int)healthType];
}

godot::Ref<godot::AudioStream> GetAudio(godot::String name) {
	godot::ResourceLoader* loader = godot::ResourceLoader::get_singleton();

	godot::Ref<godot::AudioStream> audio = loader->load("res://assets/sounds/" + name);
	return audio;
}

EItemRarity GetItemRarity(int32_t rarity) {
	if (rarity < RarityMinUncommon) {
		return EItemRarity::Common;
	}
	// 6 - 12: Green/Uncommon
	else if (rarity < RarityMinRare) {
		return EItemRarity::Uncommon;
	}
	// 13 - 19: Blue/Rare
	else if (rarity < RarityMinEpic) {
		return EItemRarity::Rare;
	}
	// 20 - 49: Purple/Epic
	else if (rarity < RarityMinLegendaryLow) {
		return EItemRarity::Epic;
	}
	// 50 - 62: Yellow/Unique
	else if (rarity < RarityMinLegendaryMid) {
		return EItemRarity::SemiLegendary;
	}
	// 63 - 100: Orange/Legendary
	else if (rarity < RarityMinPearlescent) {
		return EItemRarity::Legendary;
	}
	// 101+: Pearlescent
	else {
		return EItemRarity::Pearlescent;
	}
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

godot::Color GetElementColour(EElement element) {
	godot::Color elementColour;

	switch (element) {
		case EElement::Fire:
			elementColour = godot::Color(0.85f, 0.3f, 0.0f, 1.f);
			break;

		case EElement::Shock:
			elementColour = godot::Color(0.1f, 0.1f, 1.0f, 1.f);
			break;

		case EElement::Corrosive:
			elementColour = godot::Color(0.1f, 1.0f, 0.1f, 1.f);
			break;

		case EElement::Cryo:
			elementColour = godot::Color(0.3f, 0.8f, 1.0f, 1.f);
			break;

		case EElement::Explosive:
			elementColour = godot::Color(1.0f, 0.8f, 0.0f, 1.f);
			break;

		default: // Non-elemental
			elementColour = godot::Color(0.7f, 0.7f, 0.7f, 1.f);
			break;
	}

	return elementColour;
}

godot::Color GetHealthColour(EHealthType type) {
	godot::Color healthColour;

	switch (type) {
		case EHealthType::Neutral:
			healthColour = godot::Color(0.7f, 0.7f, 0.7f, 1.0f);
			break;

		case EHealthType::Flesh:
			healthColour = godot::Color(1.0f, 0.0f, 0.0f, 1.0f);
			break;

		case EHealthType::Shield:
			healthColour = godot::Color(0.3f, 0.3f, 1.0f, 1.0f);
			break;

		case EHealthType::Armour:
			healthColour = godot::Color(0.95f, 0.95f, 0.1f, 1.0f);
			break;

		case EHealthType::Energy:
			healthColour = godot::Color(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		default:
			healthColour = godot::Color(0.7f, 0.7f, 0.7f, 1.0f);
			break;
	}

	return healthColour;
}

godot::String GetManufacturerName(EManufacturer manufacturer) {
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

godot::String GetGunTypeName(EGunType guntype) {
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

godot::String GetGunSubTypeName(EGunSubType subtype) {
	switch (subtype) {
		case EGunSubType::None:
			return "None";
		case EGunSubType::Repeater:
			return "Repeater";
		case EGunSubType::MachinePistol:
			return "Machine Pistol";
		case EGunSubType::Revolver:
			return "Revolver";
		case EGunSubType::SMG:
			return "SMG";
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
		case EGunSubType::Launcher:
			return "Launcher";
		default:
			return "???";
	}
}

godot::String GetElementName(EElement element) {
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
		case EElement::Explosive:
			return "Explosive";
		default:
			return "???";
	}
}

godot::String GetAmmoTypeName(EAmmoType ammotype) {
	switch (ammotype) {
		case EAmmoType::Pistol:
			return "Pistol";
		case EAmmoType::Revolver:
			return "Revolver";
		case EAmmoType::SMG:
			return "SMG";
		case EAmmoType::Rifle:
			return "Rifle";
		case EAmmoType::Shotgun:
			return "Shotgun";
		case EAmmoType::Sniper:
			return "Sniper";
		case EAmmoType::Launcher:
			return "Launcher";
		default:
			return "???";
	}
}

godot::String GetRarityName(EItemRarity rarity) {
	switch (rarity) {
		case EItemRarity::Common:
			return "Common";

		case EItemRarity::Uncommon:
			return "Uncommon";

		case EItemRarity::Rare:
			return "Rare";

		case EItemRarity::Epic:
			return "Epic";

		case EItemRarity::SemiLegendary:
			return "Not Sure Yet";

		case EItemRarity::Legendary:
			return "Legendary";

		case EItemRarity::Pearlescent:
			return "Pearlescent";

		default:
			return "???";
	}
}
