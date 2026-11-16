#pragma once

// https://forum.godotengine.org/t/creating-navigationregion2d-from-tilemap-data/40969/4

#include <chrono>

#include "enemies/ai/enemyAIComponent.h"

using namespace std::chrono;

class EnemyController;
class Enemy;

constexpr double PrefBaseRangeFar { 768.0 };
constexpr double PrefBaseRangeNormal { 384.0 };
constexpr double PrefBaseRangeNear { 192.0 };

class BasicRangedEAIComponent : public EnemyAIComponent {
	GDCLASS(BasicRangedEAIComponent, EnemyAIComponent)

public:
	void _ready() override;
	void _physics_process(double delta) override;

	void SetController(EnemyController* ec) override;
	void RegisterGun();

protected:
	Enemy* CtrlEGun = nullptr; // For ease of access to derived class and to prevent repeated casting. Might be removed or changed later

	/*
		Shooting behaviour stuff for guns
		Salvo refers to how many shots should be fired from an automatic weapon before a pause
		Refire refers to the chance for a semi-automatic weapon to be fired again as soon as possible, ignoring the pause
	*/

	bool CanGunRefire { false };
	bool CanGunSalvo { false };
	int SalvoRemaining { 0 };

	/*
		This timestamp is used by the AI to tell it when it's allowed to start shooting again if next shot is further delayed.
		The delay is independent from the gun itself, but can not override the gun's fire rate and make it shoot faster than the gun and owner's fire rate mods allow.
	*/
	steady_clock::time_point NextShot;
	bool IsNextShotDelayed { false };

	double PreferredRange { PrefBaseRangeNormal };

	static void _bind_methods();

	virtual void AISlowUpdate() override;

	virtual void ExecuteIdle() override;
	virtual void ExecuteSearch() override;
	virtual void ExecuteChase() override;

	virtual void GunFired(double fireTimeMS);
	virtual int GetNewSalvoCount();
	virtual bool RefireCheck();
	virtual void FireAtTarget();

private:

};
