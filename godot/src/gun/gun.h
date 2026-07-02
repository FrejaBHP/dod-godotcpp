#pragma once

#include "gun/gunDefinition.h"

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <chrono>

using namespace godot;
using namespace std::chrono;

class Character;

namespace godot {
	class AudioStreamRandomizer;
	class AudioStreamPlayer2D;
}

class Gun : public Node2D {
	GDCLASS(Gun, Node2D)

public:
	Gun();
	~Gun() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void TestFunction();

	virtual void BuildGun(std::shared_ptr<GunDefinition> gundef);

	bool TryPrimaryFire(const Vector2 from, const Vector2 towards);
	bool TryReload();

	// Burde måske være en shared ptr
	std::shared_ptr<GunDefinition> GunDef = nullptr;

	Character* OwningCharacter = nullptr;
	Timer* ReloadTimer = nullptr;
	AudioStreamPlayer2D* StreamPlayer = nullptr;
	Ref<AudioStreamRandomizer> StreamRandomiser;

	int32_t MagAmmo { 0 };

protected:
	static void _bind_methods();
	virtual void PrimaryFireSingle(const Vector2 from, const Vector2 towards);
	virtual void PrimaryFireBurst(const Vector2 from, const Vector2 towards);
	virtual void StartReload();
	virtual void FinishReload();
	void AdjustFiringAngle(Node2D* node) const;
	void ReloadTimerTimeout();

	steady_clock::time_point LastFired;
	Ref<PackedScene> ProjectileScene = nullptr;
	bool IsFiringBurst = false;
	int32_t RemainingBurstCount = 0;

private:

};
