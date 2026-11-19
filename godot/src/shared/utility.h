#pragma once

#include <memory>
#include <vector>
#include <random>
#include <string.h>

#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/texture2d.hpp>

#include "shared/enums.h"
#include "shared/attribute.h"
//#include "element.h"

struct DIDamage {
	EElement Element;
	double Damage;

	/*
	DIDamage operator*(const double& d) {
		DIDamage b;

		c.Flat = this->Flat + b.Flat;
		c.Scale = this->Scale + b.Scale;

		return c;
	}

	void operator+=(const Attribute& b) {
		this->Flat += b.Flat;
		this->Scale += b.Scale;
	}
	*/
};

struct DamageInfo {
	std::vector<DIDamage> DamageInstances;

	void operator*=(const double& d) {
		for (size_t i = 0; i < DamageInstances.size(); i++) {
			DamageInstances[i].Damage *= d;
		}
	}

	double DamageInfo::GetTotalDamage() {
		double totalDamage { 0.0 };

		for (size_t i = 0; i < DamageInstances.size(); i++) {
			totalDamage += DamageInstances[i].Damage;
		}

		return totalDamage;
	}
};

struct RoomRewardsInfo {
	ERewardClass RewardClass;
	EItemRewardClass ItemRewardClass;
	EChestRewardClass ChestRewardClass;
	ERoomRewardClass RoomRewardClass;
	EEquipmentRewardClass EquipmentRewardClass;
	EReversalRewardClass ReversalRewardClass;
};

constexpr int32_t RarityMinUncommon = 6;
constexpr int32_t RarityMinRare = 13;
constexpr int32_t RarityMinEpic = 20;
constexpr int32_t RarityMinLegendaryLow = 50;
constexpr int32_t RarityMinLegendaryMid = RarityMinLegendaryLow + RarityMinRare;
constexpr int32_t RarityMinLegendaryHigh = RarityMinLegendaryLow + RarityMinEpic;
constexpr int32_t RarityMinPearlescent = 101;

constexpr int32_t PrefixQ1Min = 5;
constexpr int32_t PrefixQ2Min = 8;
constexpr int32_t PrefixQ3Min = 12;

extern std::random_device rnd;
extern std::mt19937 gen;

extern const double DamageEffectiveness[6][5];

extern const godot::Color ColourItemAmmoCrate;
extern const godot::Color ColourItemWeaponsChest;

// Returns a number between [min, max] (inclusive)
int GetRandomInt(int min, int max);
float GetRandomFloat(float min, float max);
double GetRandomDouble(double min, double max);

double GetWeaponBaseDamage(int level);
double GetShieldBaseCapacity(int level);
double GetEnemyBaseHealth(int level);
double GetDamageEffectiveness(EElement damageType, EHealthType healthType);

EItemRarity GetItemRarity(int32_t rarity);

godot::Color GetRarityColour(int32_t rarity);
godot::Ref<godot::AudioStream> GetAudio(godot::String name);
godot::Color GetElementColour(EElement element);

godot::Color GetHealthColour(EHealthType type);

godot::Ref<godot::Texture2D> GetManufacturerIcon(EManufacturer manufacturer);

godot::String GetManufacturerName(EManufacturer manufacturer);
godot::String GetGunTypeName(EGunType guntype);
godot::String GetGunSubTypeName(EGunSubType subtype);
godot::String GetElementName(EElement element);
godot::String GetAmmoTypeName(EAmmoType ammotype);
godot::String GetRarityName(EItemRarity rarity);
