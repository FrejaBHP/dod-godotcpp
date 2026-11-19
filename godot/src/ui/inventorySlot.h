#pragma once

#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include "items/inventoryItem.h"
#include "shared/enums.h"

using namespace godot;

class InventorySlot : public PanelContainer {
	GDCLASS(InventorySlot, PanelContainer)

public:
	int SlotNumber { -1 };

	void _ready() override;

	virtual void _gui_input(const Ref<InputEvent>& p_event) override;

	void OnMouseEntered();
	void OnMouseExited();

	void SetBGVisibility(const bool visible);
	void SetContainedItem(InventoryItem* item);
	InventoryItem* const GetContainedItem() const;
	bool ContainsItem();

	void SetSlotType(const int type);
	int GetSlotType() const;

protected:
	EInventorySlotType SlotType { EInventorySlotType::Inventory };
	TextureRect* BGTexture { nullptr };

	InventoryItem* ContainedItem { nullptr };

	static void _bind_methods();

private:

};
