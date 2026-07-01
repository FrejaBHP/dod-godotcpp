#pragma once

#include "shared/enums.h"
#include "gun/gunpart.h"
#include "shared/utility.h"

#include <cstdint>
#include <memory>
#include <map>
#include <string>

// using namespace godot;

class GunDefinition {
public:
	GunDefinition();
	~GunDefinition();

	virtual void AssembleRandomGun();
	virtual void ApplyPartsBonuses();
	void FinaliseGun();

	virtual std::string GetGunPartsString();

	EManufacturer Manufacturer { EManufacturer::Placeholder };
	EGunType GunType { EGunType::None };
	EGunSubType GunSubType { EGunSubType::None };
	EGunRarity GunRarity { EGunRarity::Common };
	EFireMode FireMode { EFireMode::Automatic };

	std::string GunName { "" };

	int32_t Level { 1 };
	double DamageModifier { 1.0 };

	int32_t BaseProjectileCount { 1 };
	int32_t BaseShotCost { 1 };
	double BaseFireTime { 1000.0 }; // In milliseconds
	int32_t BaseMagSize { 0 };
	double BaseReloadTime { 0.0 }; // In seconds
	double BaseProjectileSpeed { 800.0 };
	int32_t BaseBurstCount { 3 };

	double BaseSpread { 0.0 };
	double BaseRecoil { 0.0 };
	double BaseMinInaccuracy { 0.0 };
	double BaseMaxInaccuracy { 0.0 };
	double BaseInaccuracyRegen { 0.0 };
	double BaseInaccuracyRegenDelay { 0.2 };

	double Damage { 0.0 };
	double Accuracy { 100.0 };

	int32_t ProjectileCount = BaseProjectileCount;
	int32_t ShotCost = BaseShotCost;
	double FireTime = BaseFireTime; // In milliseconds
	int32_t MagSize = BaseMagSize;
	double ReloadTime = BaseReloadTime; // In seconds
	double ProjectileSpeed = BaseProjectileSpeed;
	int32_t BurstCount = BaseBurstCount;

	double Spread = BaseSpread;
	double Recoil = BaseRecoil;
	double MinInaccuracy = BaseMinInaccuracy;
	double MaxInaccuracy = BaseMaxInaccuracy;
	double InaccuracyRegen = BaseInaccuracyRegen;
	double InaccuracyRegenDelay = BaseInaccuracyRegenDelay;

	int32_t RarityScore { 0 };

	std::map<EAttributeType, Attribute> AttrBonuses;

	// Parts
	std::unique_ptr<MaterialComponent> Material;
	std::unique_ptr<BodyComponent> Body;
	std::unique_ptr<BarrelComponent> Barrel;
	std::unique_ptr<GripComponent> Grip;
	std::unique_ptr<MagazineComponent> Magazine;
	std::unique_ptr<StockComponent> Stock;
	std::unique_ptr<AccessoryComponent> Accessory;
	std::unique_ptr<PrefixComponent> Prefix;
	std::unique_ptr<TitleComponent> Title;

	// Metadata
	int32_t MetaMagAmmo { 0 };

protected:
	virtual std::unique_ptr<PrefixComponent> GetEligiblePrefix();
	virtual std::unique_ptr<TitleComponent> GetEligibleTitle();
	void CalculateStats();

private:
};
