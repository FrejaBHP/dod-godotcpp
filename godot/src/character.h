#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include "shared/enums.h"

using namespace godot;

class Gun;
class Projectile;

class Character : public CharacterBody2D {
	GDCLASS(Character, CharacterBody2D)

public:
	void _ready() override;
	void _physics_process(double delta) override;

	EAlignment Alignment;

	virtual void ApplyMovement(Vector2 movement);
	virtual void HitWithProjectile(Projectile* proj);
	virtual void Die();
	double GetMaxSpeed() const;

	double FireRateMod { 1. };

	int Level { 1 };

	double Inaccuracy { 0 };
	double Recoil { 0 };
	double MinInaccuracy { 0 };
	double MaxInaccuracy { 0 };
	double InaccuracyRegen { 0 };
	double InaccuracyRegenDelay { 0.2 };

	int PistolAmmo { 72 };
	int RevolverAmmo { 24 };
	int SMGAmmo { 192 };
	int ARAmmo { 120 };
	int ShotgunAmmo { 40 };
	int SniperAmmo { 18 };
	int LauncherAmmo { 8 };

	bool IsDead = false;

protected:
	static void _bind_methods();
	virtual void OnDeath();

	Gun* CurrentGun = nullptr;

	float MaxSpeed { 100.f };

private:
};
