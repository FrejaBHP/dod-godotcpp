#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/texture_progress_bar.hpp>
#include "projectiles/projectile.h"
#include "shared/utility.h"

using namespace godot;

class Character;
class Gun;

class CharacterController : public Node2D {
	GDCLASS(CharacterController, Node2D)

public:
	Character* ControlledChar = nullptr;

	virtual void OnHitByProjectile(Projectile* proj);
	virtual void TakeDamage(DamageInfo& di);
	virtual void GunReloadStart();
	bool IsCharacterReloading() const;

protected:
	bool IsFullyAccurate { false };
	bool CanRecoverInaccuracy { false };
	bool IsReloading { false };

	static void _bind_methods();

	virtual void OnGunFired();

	virtual void ApplyRecoil();
	virtual void EnableInaccuracyRecovery();
	virtual void RecoverInaccuracy(double delta);
	
	virtual void GunReloadEnd();

private:

};
