#include "characterController.h"
#include "character.h"

#include "gun/gun.h"

void CharacterController::_bind_methods() {
	ClassDB::bind_method(D_METHOD("ApplyRecoil"), &CharacterController::ApplyRecoil);
	ClassDB::bind_method(D_METHOD("EnableInaccuracyRecovery"), &CharacterController::EnableInaccuracyRecovery);
	ClassDB::bind_method(D_METHOD("OnGunFired"), &CharacterController::OnGunFired);
	ClassDB::bind_method(D_METHOD("ReloadEnd"), &CharacterController::GunReloadEnd);
}

void CharacterController::OnGunFired() {
	ApplyRecoil();
}

void CharacterController::ApplyRecoil() {
	CanRecoverInaccuracy = false;
	IsFullyAccurate = false;

	double newInaccuracy = ControlledChar->Inaccuracy + ControlledChar->Recoil;
	if (newInaccuracy > ControlledChar->MaxInaccuracy) {
		newInaccuracy = ControlledChar->MaxInaccuracy;
	}

	ControlledChar->Inaccuracy = newInaccuracy;
}

void CharacterController::EnableInaccuracyRecovery() {
	CanRecoverInaccuracy = true;
}

void CharacterController::RecoverInaccuracy(double delta) {
	double regenStep = ControlledChar->InaccuracyRegen * delta;
	double newInaccuracy = ControlledChar->Inaccuracy - regenStep;

	if (ControlledChar->MinInaccuracy > newInaccuracy) {
		newInaccuracy = ControlledChar->MinInaccuracy;
		CanRecoverInaccuracy = false;
		IsFullyAccurate = true;
	}

	ControlledChar->Inaccuracy = newInaccuracy;
}

void CharacterController::GunReloadStart() {
	IsReloading = true;
}

void CharacterController::GunReloadEnd() {
	IsReloading = false;
}
