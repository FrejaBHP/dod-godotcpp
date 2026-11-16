#pragma once

#include <godot_cpp/classes/ray_cast2d.hpp>
#include "character.h"

using namespace godot;


class EnemyController;
class Gun;
class GunDefinition;

class Enemy : public Character {
	GDCLASS(Enemy, Character)

public:
	//[Flags]
	enum FAllowedGunTypes : unsigned int {
		Pistol = 1 << 0,
		Revolver = 1 << 1,
		SMG = 1 << 2,
		Rifle = 1 << 3,
		Shotgun = 1 << 4,
		Sniper = 1 << 5,
		Launcher = 1 << 6
	};

	EnemyController* Controller = nullptr;
	Gun* CurrentGun = nullptr;

	RayCast2D* PlayerCast = nullptr;

	void _ready() override;
	void _physics_process(double delta) override;

	void SetEXPBounty(const double bounty);
	double GetEXPBounty() const;

	void SetAllowedWeaponTypes(const unsigned int bitfield);
	unsigned int GetAllowedWeaponTypes() const;

	void SetCanUseShield(const bool bShield);
	bool GetCanUseShield() const;

	/*
	void SetHealthDict(const Dictionary& dict);
	Dictionary GetHealthDict() const;
	*/

	void Die() override;
	void OnDeath() override;

protected:
	FAllowedGunTypes AllowedGunTypes;
	double EXPBounty { 25.0 };
	bool CanUseShield { false };

	//Dictionary HealthDictionary = {};

	static void _bind_methods();
	void InitGunUse();

private:

};
