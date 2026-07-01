#include "enemies/enemyController.h"
#include "character.h"
#include "gameInstance.h"

//temp
#include "gun/gun.h"
#include "enemies/enemyGun.h"

using namespace godot;

// Ville give god mening at lave mere defineret opførselsmodul/-komponent, som bliver kørt, i stedet for at lave en masse generelt her, men det må vente til senere

void EnemyController::_bind_methods() {
	
}

void EnemyController::_ready() {
	Target = (Character*)GameInstance::GetInstance().GetPlayer();
}

void EnemyController::_physics_process(double delta) {
	if (ControlledChar) {
		if (ControlledChar->IsDead) {
			return;
		}

		if (Target) {
			ControlledChar->look_at(Target->get_global_position());

			ControlledChar->ApplyMovement(ControlledChar->get_global_transform().columns[0]);

			if (UsesGun) {
				EnemyGun* eg = static_cast<EnemyGun*>(ControlledChar);

				if (CanRecoverInaccuracy) {
					RecoverInaccuracy(delta);
				}

				if (eg->CurrentGun) {
					if (eg->CurrentGun->MagAmmo > 0) {
						eg->CurrentGun->TryPrimaryFire(eg->get_global_position(), Target->get_global_position());
					}
					else if (!IsReloading) {
						if (eg->CurrentGun->TryReload()) {
							GunReloadStart();
						}
					}
				}
			}
		}
	}
}

void EnemyController::SetCharacter(Character* ch) {
	ControlledChar = ch;
	
	if (ControlledChar->is_in_group("EnemyGun")) {
		UsesGun = true;

		InaccuracyTimer = ControlledChar->get_node<Timer>("InaccuracyTimer");
		InaccuracyTimer->set_one_shot(true);
		InaccuracyTimer->connect("timeout", callable_mp(this, &EnemyController::EnableInaccuracyRecovery));
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
