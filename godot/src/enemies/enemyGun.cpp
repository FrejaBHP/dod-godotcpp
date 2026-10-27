#include "enemies/enemyGun.h"
#include "enemies/enemyController.h"
#include "enemies/ai/basicRangedAIComponent.h"
#include "combat/healthComponent.h"
#include "gun/gun.h"
#include "gameInstance.h"

using namespace godot;

void EnemyGun::_bind_methods() {
	ADD_SIGNAL(MethodInfo("enemy_died", PropertyInfo(Variant::OBJECT, "enemy")));
}

void EnemyGun::_ready() {
	Alignment = EAlignment::Enemies;
	add_to_group("Character");
	add_to_group("EnemyGun");

	MaxSpeed = 100.f;
	FireRateMod = 0.80;

	PistolAmmo = -1;
	SMGAmmo = -1;
	ARAmmo = -1;
	RevolverAmmo = -1;
	ShotgunAmmo = -1;
	SniperAmmo = -1;
	LauncherAmmo = -1;

	Ref<PackedScene> ecScene = ResourceLoader::get_singleton()->load("res://scenes/enemy_controller.tscn");

	if (ecScene->can_instantiate()) {
		EnemyController* newController = static_cast<EnemyController*>(ecScene->instantiate());

		if (newController) {
			add_child(newController);
			Controller = newController;
			Controller->SetCharacter(this);

			BasicRangedEAIComponent* ai = memnew(BasicRangedEAIComponent);

			if (ai) {
				newController->add_child(ai);
				newController->SetAIComponent(ai);
				ai->SetController(newController);
			}

			Ref<PackedScene> hcScene = ResourceLoader::get_singleton()->load("res://scenes/health_component.tscn");

			if (hcScene->can_instantiate()) {
				HealthComponent* newHealthComponent = static_cast<HealthComponent*>(hcScene->instantiate());

				if (newHealthComponent) {
					newController->add_child(newHealthComponent);
					newController->SetHealthComponent(newHealthComponent);

					//newHealthComponent->AddHealthBar(25, EHealthType::Shield);
					//newHealthComponent->AddHealthBar(25, EHealthType::Armour);
					newHealthComponent->AddHealthBar(25, EHealthType::Flesh);
				}
			}
		}
	}
	
	PlayerCast = get_node<RayCast2D>("PlayerCast");

	InitGunUse();
}

void EnemyGun::_physics_process(double delta) {

}

void EnemyGun::Die() {
	Character::Die();
}

void EnemyGun::OnDeath() {
	emit_signal("enemy_died", this);

	CurrentGun->MagAmmo = CurrentGun->GunDef->MagSize;
	GameInstance::GetInstance().CopyEquippedGunToDrop(CurrentGun, get_global_position());
	CurrentGun->FreeGun();

	GameInstance::GetInstance().EnemyDeath(this);

	queue_free();
}

void EnemyGun::InitGunUse() {
	Gun* newGun = GameInstance::GetInstance().GenerateNakedGun(-1);

	if (newGun) {
		add_child(newGun);
		newGun->OwningCharacter = this;
		CurrentGun = newGun;
		Controller->ApplyCurrentGun();

		//print_line(vformat("Given gun %s", CurrentGun->GunDef->GunName.c_str()));
	}
}
