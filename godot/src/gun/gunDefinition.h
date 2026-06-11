#pragma once

#include <cstdint>
#include "shared/enums.h"

// using namespace godot;

class GunDefinition {
public:
	GunDefinition();
	~GunDefinition();

	void SetPistolStats();
	void SetSMGStats();
	void SetARStats();

	EManufacturer Manufacturer { EManufacturer::Placeholder };
	EGunType GunType { EGunType::None };
	EGunSubType GunSubType { EGunSubType::None };
	EGunRarity GunRarity { EGunRarity::Common };

	double BaseDamage { 0 };
	int32_t BaseProjectileCount { 1 };
	int32_t BaseShotCost { 1 };
	double BaseFireTime { 1 };
	int32_t BaseMagSize { 0 };
	double BaseReloadTime { 0 };

	double Damage { 0 };
	int32_t ProjectileCount { 1 };
	int32_t ShotCost { 1 };
	double FireTime { 1 };
	int32_t MagSize { 0 };
	double ReloadTime { 0 };

	int32_t RarityScore { 0 };

	// Metadata
	int32_t MetaMagAmmo { 0 };

protected:

private:
};
