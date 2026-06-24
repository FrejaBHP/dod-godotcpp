#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/timer.hpp>

using namespace godot;

class Character;
class Gun;

class EnemyController : public Node {
	GDCLASS(EnemyController, Node)

public:
	void _ready() override;
	void _physics_process(double delta) override;

	void SetCharacter(Character* ch);
	void ApplyCurrentGun();

	Character* ControlledChar = nullptr;
	Character* Target = nullptr;
	Timer* InaccuracyTimer = nullptr;

protected:
	static void _bind_methods();

	// Temp
	void EnableInaccuracyRecovery();
	void RecoverInaccuracy(double delta);
	
	void OnGunFired();
	void ApplyRecoil();
	void GunReloadStart();
	void GunReloadEnd();
	void BindGun(Gun* gun);

	bool IsReloading = false;
	bool UsesGun = false;
	bool IsFullyAccurate = false;
	bool CanRecoverInaccuracy = false;

private:

};
