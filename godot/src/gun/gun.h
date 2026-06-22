#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <chrono>
#include "gun/gunDefinition.h"

using namespace godot;
using namespace std::chrono;

class Player;

class Gun : public Node2D {
	GDCLASS(Gun, Node2D)

public:
	Gun();
	~Gun() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	virtual void BuildGun(std::shared_ptr<GunDefinition> gundef);

	bool TryPrimaryFire();
	bool TryReload();

	// Burde måske være en shared ptr
	std::shared_ptr<GunDefinition> GunDef = nullptr;

	Player* OwningPlayer = nullptr;
	Timer* ReloadTimer = nullptr;

	int32_t MagAmmo { 0 };

protected:
	static void _bind_methods();
	virtual void PrimaryFire();
	virtual void StartReload();
	virtual void FinishReload();
	void AdjustFiringAngle(Node2D* node) const;
	void ReloadTimerTimeout();

	steady_clock::time_point LastFired;
	Ref<PackedScene> ProjectileScene = nullptr;

private:

};
