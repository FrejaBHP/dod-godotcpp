#pragma once

#include "characterController.h"

#include <godot_cpp/classes/timer.hpp>

using namespace godot;

class Character;
class Gun;

class EnemyController : public CharacterController {
	GDCLASS(EnemyController, CharacterController)

public:
	void _ready() override;
	void _physics_process(double delta) override;

	void SetCharacter(Character* ch);
	void ApplyCurrentGun();

	Character* Target = nullptr;
	Timer* InaccuracyTimer = nullptr;

protected:
	static void _bind_methods();

	// Temp
	virtual void OnGunFired() override;
	virtual void GunReloadStart() override;
	virtual void GunReloadEnd() override;

	void ApplyRecoil() override;
	void EnableInaccuracyRecovery() override;

	void BindGun(Gun* gun);

	bool UsesGun = false;

private:

};
