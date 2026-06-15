#pragma once

#include <cstdint>
#include "shared/enums.h"
#include "gun/gunpart.h"
#include <memory>
#include <map>

// using namespace godot;

class GunDefinition {
public:
	GunDefinition();
	~GunDefinition();

	void SetPistolStats();
	void SetSMGStats();
	void SetARStats();

	void ApplyPartsBonuses();

	EManufacturer Manufacturer { EManufacturer::Placeholder };
	EGunType GunType { EGunType::None };
	EGunSubType GunSubType { EGunSubType::None };
	EGunRarity GunRarity { EGunRarity::Common };

	double BaseDamage { 0 };
	int32_t BaseProjectileCount { 1 };
	int32_t BaseShotCost { 1 };
	double BaseFireTime { 1000 }; // In milliseconds
	int32_t BaseMagSize { 0 };
	double BaseReloadTime { 0 }; // In seconds

	double BaseSpread { 0 };
	double BaseRecoil { 0 };
	double BaseMinInaccuracy { 0 };
	double BaseMaxInaccuracy { 0 };
	double BaseInaccuracyRegen { 0 };
	double BaseInaccuracyRegenDelay { 0.2 };

	double Damage { 0 };
	int32_t ProjectileCount { 1 };
	int32_t ShotCost { 1 };
	double FireTime { 1000 };
	int32_t MagSize { 0 };
	double ReloadTime { 0 };

	double Spread { 0 };
	double Recoil { 0 };
	double MinInaccuracy { 0 };
	double MaxInaccuracy { 0 };
	double InaccuracyRegen { 0 };
	double InaccuracyRegenDelay { 0.2 };

	int32_t RarityScore { 0 };
	double Accuracy { 100 };

	std::map<EAttributeType, Attribute> AttrBonuses;

	// Parts
	std::unique_ptr<MaterialComponent> Material;
	std::unique_ptr<BodyComponent> Body;
	std::unique_ptr<BarrelComponent> Barrel;
	std::unique_ptr<GripComponent> Grip;
	std::unique_ptr<MagazineComponent> Magazine;
	std::unique_ptr<StockComponent> Stock;
	std::unique_ptr<AccessoryComponent> Accessory;

	// Metadata
	int32_t MetaMagAmmo { 0 };

protected:

private:
};
