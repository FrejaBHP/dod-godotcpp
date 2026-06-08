#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <chrono>

using namespace godot;
using namespace std::chrono;

class Player;

class Gun : public Node2D {
	GDCLASS(Gun, Node2D)

private:


protected:
	static void _bind_methods();
	virtual void PrimaryFire();
	virtual void Reload();
	virtual void PartialReload();

	steady_clock::time_point LastFired;
	Ref<PackedScene> ProjectileScene = nullptr;

public:
	Gun();
	~Gun() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	bool TryPrimaryFire();
	bool TryReload();

	Player* OwningPlayer = nullptr;

	int32_t MagSize { 0 };
	int32_t MagAmmo { 0 };
	int32_t ReserveAmmo { 0 };
	int32_t MaxAmmo { 0 };
};
