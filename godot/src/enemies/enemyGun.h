#pragma once

#include <godot_cpp/classes/ray_cast2d.hpp>
#include "character.h"

using namespace godot;

class EnemyController;
class Gun;
class GunDefinition;

class EnemyGun : public Character {
	GDCLASS(EnemyGun, Character)

public:
	void _ready() override;
	void _physics_process(double delta) override;

	void OnHitByProjectile() override;
	void Die() override;
	void OnDeath() override;

	EnemyController* Controller = nullptr;
	Gun* CurrentGun = nullptr;

	RayCast2D* PlayerCast = nullptr;

protected:
	static void _bind_methods();
	void InitGunUse();

private:

};
