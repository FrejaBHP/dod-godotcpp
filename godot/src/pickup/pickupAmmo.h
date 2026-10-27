#pragma once

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

#include "shared/enums.h"

using namespace godot;

class AmmoPickup : public Area2D {
	GDCLASS(AmmoPickup, Area2D)

public:
	bool IsPickedUp { false };

	void _ready() override;

	void SetAmmoType(const int ammoType);
	int GetAmmoType() const;

	int GetAmmoCount() const;

	void Disable();

protected:
	Sprite2D* AmmoSprite { nullptr };
	EAmmoType AmmoType { EAmmoType::NONE };
	int AmmoCount { 0 };

	static void _bind_methods();

private:

};
