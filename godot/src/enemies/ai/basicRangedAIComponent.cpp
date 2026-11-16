#include "enemies/ai/basicRangedAIComponent.h"
#include "enemies/enemyController.h"
#include "gun/gun.h"
#include "enemies/enemy.h"

// Salvo min and max counts

constexpr int SalvoMPMin { 4 };
constexpr int SalvoMPMax { 6 };
constexpr int SalvoSMGMin { 4 };
constexpr int SalvoSMGMax { 6 };
constexpr int SalvoMGMin { 3 };
constexpr int SalvoMGMax { 5 };

// Refire min and max delay ratios

constexpr double RefireFastMin { 0.4 };
constexpr double RefireFastMax { 0.8 };
constexpr double RefireSlowMin { 0.2 };
constexpr double RefireSlowMax { 0.5 };

// Refire chances

constexpr double RefireRepeater { 0.333 };
constexpr double RefireRevolver { 0.30 };
constexpr double RefireCR { 0.35 };
constexpr double RefireAShotgun { 0.40 };
constexpr double RefireCShotgun { 0.35 };

// Effective range weapon multipliers

constexpr double PrefRangeMultPistol { 1.25 };

void BasicRangedEAIComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("GunFiredAIC"), &BasicRangedEAIComponent::GunFired);
	ClassDB::bind_method(D_METHOD("RegisterGunAIC"), &BasicRangedEAIComponent::RegisterGun);
}

void BasicRangedEAIComponent::_ready() {
	AIState = EAIState::Chase;
}

void BasicRangedEAIComponent::SetController(EnemyController* ec) {
	Controller = ec;
	CtrlEGun = static_cast<Enemy*>(Controller->ControlledChar);

	Controller->connect("gun_fired_aic", callable_mp(this, &BasicRangedEAIComponent::GunFired));
	Controller->connect("register_gun_aic", callable_mp(this, &BasicRangedEAIComponent::RegisterGun));
}

void BasicRangedEAIComponent::RegisterGun() {
	if (CtrlEGun && CtrlEGun->CurrentGun) {
		EGunSubType gst = CtrlEGun->CurrentGun->GunDef->GunSubType;

		// Salvo/refire setup
		if (gst == EGunSubType::MachinePistol || gst == EGunSubType::SMG || gst == EGunSubType::MachineGun) {
			CanGunSalvo = true;
			SalvoRemaining = GetNewSalvoCount();
		}
		else if (gst != EGunSubType::SniperBoltAction || gst != EGunSubType::Launcher) {
			CanGunRefire = true;
		}

		// Preferred range setup
		if (gst == EGunSubType::AssaultShotgun || gst == EGunSubType::CombatShotgun) {
			PreferredRange = PrefBaseRangeNear;
		}
		else if (gst == EGunSubType::SniperBoltAction || gst == EGunSubType::SniperSemiAuto) {
			PreferredRange = PrefBaseRangeFar;
		}
		else {
			PreferredRange = PrefBaseRangeNormal * (1.0 * (CtrlEGun->CurrentGun->GunDef->Accuracy / 100));
		}

		NextShot = steady_clock::now();
	}
}

void BasicRangedEAIComponent::AISlowUpdate() {
	if (Controller->Target) {
		Controller->GetNavAgent()->set_target_position(Controller->Target->get_global_position());

		if (GetDotTarget() > 0.f) {
			IsTargetInFront = true;
		}
		else {
			IsTargetInFront = false;
		}

		//Vector2 dir = Controller->Target->get_global_position() - CtrlEGun->get_global_position();
		//CtrlEGun->PlayerCast->set_target_position(dir);
		CtrlEGun->PlayerCast->force_raycast_update();

		if (CtrlEGun->PlayerCast->is_colliding()) {
			Node2D* obj = static_cast<Node2D*>(CtrlEGun->PlayerCast->get_collider());

			if (obj && obj->is_in_group("Player")) {
				IsFacingTarget = true;
			}
			else {
				IsFacingTarget = false;
			}
		}
	}
}

void BasicRangedEAIComponent::_physics_process(double delta) {
	if (!AIEnabled || !Controller) {
		return;
	}

	if (Controller->ControlledChar->IsDead) {
		return;
	}

	if (SlowUpdateCounter >= SlowUpdateDelay - 1) {
		SlowUpdateCounter = 0;
		AISlowUpdate();
	}
	else {
		++SlowUpdateCounter;
	}

	NavigationAgent2D* nav = Controller->GetNavAgent();

	if (!nav->is_navigation_finished()) {
		Vector2 nextPathPos = nav->get_next_path_position();
		Vector2 newDirection = Controller->ControlledChar->get_global_position().direction_to(nextPathPos);

		if (nav->get_avoidance_enabled()) {
			nav->set_velocity(newDirection * Controller->ControlledChar->GetMaxSpeed());
		}
		else {
			Controller->OnVelocityComputed(newDirection);
		}
	}

	switch (AIState) {
		case EAIState::NONE:
			break;

		case EAIState::Idle:
			ExecuteIdle();
			break;

		case EAIState::Search:
			ExecuteSearch();
			break;

		case EAIState::Chase:
			ExecuteChase();
			break;

		case EAIState::Hold:
			break;

		case EAIState::Flee:
			break;

		case EAIState::Hide:
			break;

		case EAIState::Panic:
			break;

		case EAIState::Strafe:
			break;

		case EAIState::SeekCover:
			break;

		case EAIState::Reload:
			break;

		default:
			break;
	}
}

void BasicRangedEAIComponent::ExecuteIdle() {

}

void BasicRangedEAIComponent::ExecuteSearch() {

}

void BasicRangedEAIComponent::ExecuteChase() {
	if (Controller->Target) {
		/*
		Vector2 facingDir = Controller->ControlledChar->get_global_position().direction_to(Controller->Target->get_global_position());

		if (facingDir.dot(Controller->ControlledChar->get_global_transform().columns[0]) > 0) {
			
		}
		*/

		Controller->ControlledChar->look_at(Controller->Target->get_global_position());
		if (CtrlEGun->GetCanUseShield()) {
			if (IsFacingTarget && CtrlEGun->get_global_position().distance_to(Controller->Target->get_global_position()) < 32) {
				FireAtTarget();
			}
		}
		else {
			if (IsFacingTarget && CtrlEGun->get_global_position().distance_to(Controller->Target->get_global_position()) < PreferredRange) {
				FireAtTarget();
			}
		}
	}
}

int BasicRangedEAIComponent::GetNewSalvoCount() {
	int newCount;

	switch (CtrlEGun->CurrentGun->GunDef->GunSubType) {
		case EGunSubType::MachinePistol:
			newCount = GetRandomInt(SalvoMPMin, SalvoMPMax);
			break;

		case EGunSubType::SMG:
			newCount = GetRandomInt(SalvoSMGMin, SalvoSMGMax);
			break;

		case EGunSubType::MachineGun:
			newCount = GetRandomInt(SalvoMGMin, SalvoMGMax);
			break;

		default:
			newCount = 0;
			break;
	}

	return newCount;
}

bool BasicRangedEAIComponent::RefireCheck() {
	bool refire;
	double roll = GetRandomDouble(0., 1.);

	switch (CtrlEGun->CurrentGun->GunDef->GunSubType) {
		case EGunSubType::Repeater:
			refire = RefireRepeater >= roll;
			break;

		case EGunSubType::Revolver:
			refire = RefireRevolver >= roll;
			break;

		case EGunSubType::CombatRifle:
			refire = RefireCR >= roll;
			break;

		case EGunSubType::AssaultShotgun:
			refire = RefireAShotgun >= roll;
			break;

		case EGunSubType::CombatShotgun:
			refire = RefireCShotgun >= roll;
			break;

		default:
			refire = false;
			break;
	}

	return refire;
}

void BasicRangedEAIComponent::FireAtTarget() {
	if (CtrlEGun->CurrentGun) {
		if (CtrlEGun->CurrentGun->MagAmmo > 0) {
			if (IsNextShotDelayed) {
				steady_clock::time_point now = steady_clock::now();
				long long difference = duration_cast<milliseconds>(now - NextShot).count();

				//print_line(vformat("FAT Difference: %d", difference));

				if (difference >= 0) {
					CtrlEGun->CurrentGun->TryPrimaryFire(CtrlEGun->get_global_position(), Controller->Target->get_global_position());
				}
			}
			else {
				CtrlEGun->CurrentGun->TryPrimaryFire(CtrlEGun->get_global_position(), Controller->Target->get_global_position());
			}
		}
		else if (!Controller->IsCharacterReloading()) {
			if (CtrlEGun->CurrentGun->TryReload()) {
				Controller->GunReloadStart();
			}
		}
	}
}

void BasicRangedEAIComponent::GunFired(double fireTimeMS) {
	steady_clock::time_point lastFired = CtrlEGun->CurrentGun->GetLastFired();
	milliseconds fireTimeDur = duration_cast<milliseconds>(duration<double, std::ratio<1>>(fireTimeMS / 1000)); // Time it takes for the gun to fire a single shot, cast to a duration
	milliseconds totalDelay = fireTimeDur; // If next shot will be further delayed, this is the value used
	
	if (CanGunSalvo) {
		--SalvoRemaining;

		if (SalvoRemaining < 1 || CtrlEGun->CurrentGun->MagAmmo == 0) { // If salvo is over or magazine is empty
			SalvoRemaining = GetNewSalvoCount();
			double noSalvoDelay = GetRandomDouble(1.0, 1.8); // Wait time until next salvo is allowed to be fired
			
			milliseconds dur = duration_cast<milliseconds>(duration<double, std::ratio<1>>(noSalvoDelay)); // Wait time converted to duration
			totalDelay += dur;

			IsNextShotDelayed = true;
		}
		else {
			IsNextShotDelayed = false;
		}
	}
	else if (CanGunRefire) {
		if (CtrlEGun->CurrentGun->MagAmmo > 0) {
			bool refire = RefireCheck();
			if (!refire) {
				double noRefireDelay; // Wait time until next shot is allowed to be fired

				EGunSubType gst = CtrlEGun->CurrentGun->GunDef->GunSubType;
				if (gst == EGunSubType::Repeater || gst == EGunSubType::CombatRifle) {
					noRefireDelay = GetRandomDouble((fireTimeMS / 1000) * RefireFastMin, (fireTimeMS / 1000) * RefireFastMax);
				}
				else {
					noRefireDelay = GetRandomDouble((fireTimeMS / 1000) * RefireSlowMin, (fireTimeMS / 1000) * RefireSlowMax);
				}

				milliseconds dur = duration_cast<milliseconds>(duration<double, std::ratio<1>>(noRefireDelay)); // Wait time converted to duration
				totalDelay += dur;

				IsNextShotDelayed = true;
			}
			else {
				IsNextShotDelayed = false;
			}
		}
		else {
			IsNextShotDelayed = false;
		}
	}

	NextShot = lastFired + totalDelay;
}
