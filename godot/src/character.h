#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include "shared/enums.h"

using namespace godot;

class Gun;

class Character : public CharacterBody2D {
	GDCLASS(Character, CharacterBody2D)

public:
	void _ready() override;
	void _physics_process(double delta) override;

	EAlignment Alignment;

	virtual void ApplyMovement(Vector2 movement);
	virtual void OnHitByProjectile();
	virtual void Die();
	double GetMaxSpeed() const;

	double Inaccuracy { 0 };
	double Recoil { 0 };
	double MinInaccuracy { 0 };
	double MaxInaccuracy { 0 };
	double InaccuracyRegen { 0 };
	double InaccuracyRegenDelay { 0.2 };

	int32_t PistolAmmo { 48 };
	int32_t SMGAmmo { 192 };
	int32_t ARAmmo { 120 };

	bool IsDead = false;

protected:
	static void _bind_methods();
	virtual void OnDeath();

	Gun* CurrentGun = nullptr;

	float MaxSpeed;

private:
};
