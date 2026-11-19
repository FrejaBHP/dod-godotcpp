#pragma once

#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include "gun/gunDefinition.h"

using namespace godot;

class ItemCard : public PanelContainer {
	GDCLASS(ItemCard, PanelContainer)

public:
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

	Label* LName { nullptr };
	RichTextLabel* LGunType { nullptr };
	Label* LManufacturer { nullptr };
	TextureRect* ManufacturerTexture { nullptr };
	std::vector<HBoxContainer*> CardRows;

	static void _bind_methods();

	HBoxContainer* GetRowByName(ECardRow row);
	Label* GetRowNameLabel(size_t index);
	Label* GetRowValueLabel(size_t index);
	Label* GetRowValueLabelByName(ECardRow row);
	TextureRect* GetRowTextureRect(size_t index);

private:

};
