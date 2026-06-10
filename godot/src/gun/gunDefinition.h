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
	double Damage { 0 };
	int32_t ProjectileCount { 1 };
	int32_t ShotCost { 1 };
	double FireTime { 1 };
	int32_t MagSize { 0 };
	double ReloadTime { 0 };

	// Metadata
	int32_t MagAmmo { 0 };

protected:

private:
};
