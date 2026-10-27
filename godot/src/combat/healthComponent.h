#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <vector>
#include "shared/enums.h"
#include "combat/healthBar.h"

using namespace godot;

class HealthComponent : public Node2D {
	GDCLASS(HealthComponent, Node2D)

public:
	Vector<HealthBar*> HealthBars;

	void _ready() override;
	void _physics_process(double delta) override;

	HealthBar* AddHealthBar(double max, EHealthType type);
	HealthBar* AddHealthBar(double max, double current, EHealthType type);

	void TakeDamage(DamageInfo& di);

protected:
	VBoxContainer* BarContainer { nullptr };

	double TotalMaxHealth { 0 };
	double TotalCurrentHealth { 0 };

	static void _bind_methods();

private:


};
