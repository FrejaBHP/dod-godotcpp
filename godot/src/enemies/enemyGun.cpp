#include "enemies/enemyGun.h"
#include "enemies/enemyController.h"
#include "gun/gun.h"

using namespace godot;

void EnemyGun::_bind_methods() {

}

void EnemyGun::_ready() {
	Alignment = EAlignment::Enemies;

	PistolAmmo = -1;
	SMGAmmo = -1;
	ARAmmo = -1;

	EnemyController* newController = memnew(EnemyController);

	if (newController) {
		add_child(newController);
		Controller = newController;
		Controller->SetCharacter(this);
	}
}

void EnemyGun::_physics_process(double delta) {

}

void EnemyGun::GiveGun(std::shared_ptr<GunDefinition> gundef) {

}
