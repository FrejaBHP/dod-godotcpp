#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include "gun/gunDefinition.h"

using namespace godot;

class ItemCard : public Control {
	GDCLASS(ItemCard, Control)

public:
	ItemCard() = default;
	~ItemCard() = default;

	void _ready() override;

	void UseGunDef(const GunDefinition& gundef);

protected:
	enum ECardRow {
		Damage,
		Accuracy,
		FireRate,
		Reload,
		Magazine,
		Element,
		ElementChance,
		ElementDamage
	};

	Label* LName = nullptr;
	Label* LGunType = nullptr;
	Label* LManufacturer = nullptr;
	std::vector<HBoxContainer*> CardRows;

	static void _bind_methods();

	HBoxContainer* GetRowByName(ECardRow row);
	Label* GetRowNameLabel(size_t index);
	Label* GetRowValueLabel(size_t index);
	Label* GetRowValueLabelByName(ECardRow row);

private:

};
