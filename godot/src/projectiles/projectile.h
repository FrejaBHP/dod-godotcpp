#pragma once

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include "shared/enums.h"

using namespace godot;

class Projectile : public Area2D {
	GDCLASS(Projectile, Area2D)

public:
	Projectile();
	~Projectile() = default;

	void _ready() override;
	void _physics_process(double delta) override;
	void SetSpeed(float speed);
	void UpdateMasks(EAlignment alignment);

protected:
	static void _bind_methods();
	void BodyEntered(Node2D* body);
	void Remove();

	Timer* LifeTimer = nullptr;
	float Speed { 0.f };

private:

};
