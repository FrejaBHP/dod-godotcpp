#include "enemies/enemyGun.h"
#include "enemies/enemyController.h"
#include "gun/gun.h"
#include "gameInstance.h"

using namespace godot;

void EnemyGun::_bind_methods() {

}

void EnemyGun::_ready() {
	Alignment = EAlignment::Enemies;
	add_to_group("Character");
	add_to_group("EnemyGun");

	MaxSpeed = 150.f;

	PistolAmmo = -1;
	SMGAmmo = -1;
	ARAmmo = -1;

	EnemyController* newController = memnew(EnemyController);

	if (newController) {
		add_child(newController);
		Controller = newController;
		Controller->SetCharacter(this);
	}

	PlayerCast = get_node<RayCast2D>("PlayerCast");

	InitGunUse();
}

void EnemyGun::_physics_process(double delta) {

}

void EnemyGun::OnHitByProjectile() {
	Die();
}

void EnemyGun::Die() {
	Character::Die();
}

void EnemyGun::OnDeath() {
	GameInstance::GetInstance().CopyEquippedGunToDrop(CurrentGun, get_global_position());
	queue_free();
}

void EnemyGun::InitGunUse() {
	Gun* newGun = GameInstance::GetInstance().GenerateNakedGun(-1);

	if (newGun) {
		add_child(newGun);
		newGun->OwningCharacter = this;
		CurrentGun = newGun;
		Controller->ApplyCurrentGun();

		print_line(vformat("Given gun %s", CurrentGun->GunDef->GunName.c_str()));
	}
}
