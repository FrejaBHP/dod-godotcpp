#pragma once

#include <godot_cpp/classes/static_body2d.hpp>
#include <godot_cpp/classes/control.hpp>
#include "interactible/interactible.h"

using namespace godot;

class ItemChest : public StaticBody2D {
	GDCLASS(ItemChest, StaticBody2D)

public:
	enum EItemChestType {
		WeaponsCrate,
		WeaponsCrateQuality,
		AmmoCrate,
		AmmoCrateSmall
	};

	virtual void _ready() override;

	void OnActivated();

	void SetTextVisibility(bool visible);

	void SetItemChestType(const int type);
	int GetItemChestType() const;

protected:
	Interactible* InteractibleArea { nullptr };
	Control* ChestControls { nullptr };

	EItemChestType ChestType { EItemChestType::WeaponsCrate };
	bool Used { false };

	static void _bind_methods();

private:

};
