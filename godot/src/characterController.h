#pragma once

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Character;
class Gun;

class CharacterController : public Node {
	GDCLASS(CharacterController, Node)

public:
	Character* ControlledChar = nullptr;

protected:
	static void _bind_methods();

	virtual void OnGunFired();

	virtual void ApplyRecoil();
	virtual void EnableInaccuracyRecovery();
	virtual void RecoverInaccuracy(double delta);

	virtual void GunReloadStart();
	virtual void GunReloadEnd();

	bool IsFullyAccurate { false };
	bool CanRecoverInaccuracy { false };
	bool IsReloading = false;

private:

};
