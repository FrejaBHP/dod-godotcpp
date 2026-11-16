#pragma once

#include "characterController.h"

#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>

using namespace godot;

class Character;
class Gun;
class EnemyAIComponent;
class HealthComponent;

class EnemyController : public CharacterController {
	GDCLASS(EnemyController, CharacterController)

public:
	Character* Target = nullptr;

	void _ready() override;
	void _physics_process(double delta) override;

	void SetCharacter(Character* ch);
	void SetAIComponent(EnemyAIComponent* ai);
	EnemyAIComponent* const GetAIComponent() const;
	void SetHealthComponent(HealthComponent* hc);
	void ApplyCurrentGun();

	void OnHitByProjectile(Projectile* proj) override;
	void TakeDamage(DamageInfo& di) override;
	void OnHealthDepleted();

	NavigationAgent2D* GetNavAgent() const;
	// Despite saying Velocity, this is actually the direction. Speed multiplier is added to the direction Character's ApplyMovement(Vector2) function
	void OnVelocityComputed(Vector2 safeVelocity);

	virtual void GunReloadStart() override;

protected:
	Timer* InaccuracyTimer = nullptr;
	NavigationAgent2D* NavAgent = nullptr;
	EnemyAIComponent* AIComp = nullptr;
	HealthComponent* HealthComp = nullptr;

	bool UsesGun = false;

	static void _bind_methods();

	void UpdateHealthBar();
	
	// Temp
	virtual void OnGunFired() override;
	
	virtual void GunReloadEnd() override;

	void ApplyRecoil() override;
	void EnableInaccuracyRecovery() override;

	void BindGun(Gun* gun);

private:

};
