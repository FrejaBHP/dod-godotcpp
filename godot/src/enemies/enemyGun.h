#pragma once

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

	void GiveGun(std::shared_ptr<GunDefinition> gundef);

	EnemyController* Controller = nullptr;
	Gun* CurrentGun = nullptr;

protected:
	static void _bind_methods();

private:

};
