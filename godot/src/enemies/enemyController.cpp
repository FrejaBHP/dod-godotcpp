#include "enemies/enemyController.h"
#include "enemies/ai/enemyAIComponent.h"
#include "character.h"
#include "gameInstance.h"

#include <godot_cpp/classes/navigation_server2d.hpp>
#include <godot_cpp/classes/world2d.hpp>

//temp
#include "gun/gun.h"
#include "enemies/enemyGun.h"

using namespace godot;

// Ville give god mening at lave mere defineret opførselsmodul/-komponent, som bliver kørt, i stedet for at lave en masse generelt her, men det må vente til senere

void EnemyController::_bind_methods() {
	ADD_SIGNAL(MethodInfo("gun_fired_aic", PropertyInfo(Variant::FLOAT, "fireTime")));
	ADD_SIGNAL(MethodInfo("register_gun_aic"));

	ClassDB::bind_method(D_METHOD("OnHitByProjectile"), &EnemyController::OnHitByProjectile);
	ClassDB::bind_method(D_METHOD("OnHealthDepleted"), &EnemyController::OnHealthDepleted);
	ClassDB::bind_method(D_METHOD("OnVelocityComputed"), &EnemyController::OnVelocityComputed);
}

void EnemyController::_ready() {
	Target = (Character*)GameInstance::GetInstance().GetPlayer();

	NavAgent = get_node<NavigationAgent2D>("NavigationAgent2D");
	NavAgent->connect("velocity_computed", callable_mp(this, &EnemyController::OnVelocityComputed));
	NavAgent->set_navigation_map(get_world_2d()->get_navigation_map());
}

void EnemyController::_physics_process(double delta) {
	if (ControlledChar) {
		if (ControlledChar->IsDead) {
			return;
		}

		if (UsesGun && CanRecoverInaccuracy) {
			RecoverInaccuracy(delta);
		}
	}
}

void EnemyController::OnVelocityComputed(Vector2 safeVelocity) {
	//ControlledChar->set_velocity(safeVelocity);
	ControlledChar->ApplyMovement(safeVelocity);
}

void EnemyController::SetCharacter(Character* ch) {
	ControlledChar = ch;
	ch->connect("inc_hit_projectile", callable_mp(this, &EnemyController::OnHitByProjectile));
	
	if (ControlledChar->is_in_group("EnemyGun")) {
		UsesGun = true;

		InaccuracyTimer = ControlledChar->get_node<Timer>("InaccuracyTimer");
		InaccuracyTimer->set_one_shot(true);
		InaccuracyTimer->connect("timeout", callable_mp(this, &EnemyController::EnableInaccuracyRecovery));
	}
}

void EnemyController::SetAIComponent(EnemyAIComponent* ai) {
	AIComp = ai;
}

EnemyAIComponent* const EnemyController::GetAIComponent() const {
	return AIComp;
}

void EnemyController::SetHealthComponent(HealthComponent* hc) {
	HealthComp = hc;
	HealthComp->connect("health_depleted", callable_mp(this, &EnemyController::OnHealthDepleted));
}

void EnemyController::OnHitByProjectile(Projectile* proj) {
	//print_line(vformat("Hit! %X", (uintptr_t)proj));
	if (!ControlledChar->IsDead) {
		if (HealthComp) {
			HealthComp->TakeDamage(proj->DmgInfo);
		}
		//TakeDamage(proj->DmgInfo);
	}
}

// Health kan laves om til et component med sit eget system. Placeholder her
void EnemyController::TakeDamage(DamageInfo& di) {
	/*
	double totalDamage { 0 };
	double biggestDamage = di.DamageInstances[0].Damage;
	EElement biggestElement = di.DamageInstances[0].Element;

	for (size_t i = 0; i < di.DamageInstances.size(); i++) {
		totalDamage += di.DamageInstances[i].Damage;

		if (di.DamageInstances[i].Damage > biggestDamage) {
			biggestDamage = di.DamageInstances[i].Damage;
			biggestElement = di.DamageInstances[i].Element;
		}
	}

	ControlledChar->CurrentHealth -= totalDamage;

	// Burde samle skaden her og så lave én tekstinstans for al skade taget på ét tick
	GameInstance::GetInstance().SpawnDamageText(ControlledChar->get_global_position(), totalDamage, biggestElement);

	if (ControlledChar->CurrentHealth <= 0.0) {
		ControlledChar->Die();
	}
	else {
		UpdateHealthBar();
	}
	*/
}

void EnemyController::OnHealthDepleted() {
	ControlledChar->Die();

	/*
	if (HealthComp) {
		if (HealthComp->HealthBars.size() < 32) {
			EHealthType thingy = (EHealthType)GetRandomInt(0, 4);
			HealthComp->AddHealthBar(25, thingy);

			if (HealthComp->HealthBars[HealthComp->HealthBars.size() - 1]->GetHealthType() != EHealthType::Flesh) {
				HealthComp->HealthBars[HealthComp->HealthBars.size() - 1]->SetBarStats(25, EHealthType::Flesh);
			}
		}
		else {
			ControlledChar->Die();
		}
	}
	*/
}

void EnemyController::UpdateHealthBar() {
	if (ControlledChar) {
		
	}
}

void EnemyController::ApplyCurrentGun() {
	if (UsesGun) {
		EnemyGun* eg = static_cast<EnemyGun*>(ControlledChar);
		Gun* gun = eg->CurrentGun;

		if (gun) {
			ControlledChar->Recoil = gun->GunDef->Recoil;
			ControlledChar->MinInaccuracy = gun->GunDef->MinInaccuracy;
			ControlledChar->MaxInaccuracy = gun->GunDef->MaxInaccuracy;
			ControlledChar->InaccuracyRegen = gun->GunDef->InaccuracyRegen;
			ControlledChar->InaccuracyRegenDelay = gun->GunDef->InaccuracyRegenDelay;
			ControlledChar->Inaccuracy = ControlledChar->MinInaccuracy;
			IsFullyAccurate = true;

			BindGun(gun);
			emit_signal("register_gun_aic");
		}
	}
}

void EnemyController::EnableInaccuracyRecovery() {
	CharacterController::EnableInaccuracyRecovery();
}

void EnemyController::ApplyRecoil() {
	CharacterController::ApplyRecoil();

	InaccuracyTimer->start((float)ControlledChar->InaccuracyRegenDelay);
}

void EnemyController::OnGunFired() {
	CharacterController::OnGunFired();
	EnemyGun* eg = static_cast<EnemyGun*>(ControlledChar);

	emit_signal("gun_fired_aic", eg->CurrentGun->GunDef->FireTime / eg->FireRateMod);
}

void EnemyController::GunReloadStart() {
	CharacterController::GunReloadStart();
}

void EnemyController::GunReloadEnd() {
	CharacterController::GunReloadEnd();
}

void EnemyController::BindGun(Gun* gun) {
	gun->connect("gun_fired", callable_mp(this, &EnemyController::OnGunFired));
	gun->connect("gun_reload_ended", callable_mp(this, &EnemyController::GunReloadEnd));
}

NavigationAgent2D* EnemyController::GetNavAgent() const {
	return NavAgent;
}
