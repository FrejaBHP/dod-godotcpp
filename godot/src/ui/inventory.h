#pragma once

#include <godot_cpp/classes/panel_container.hpp>
#include "ui/inventorySlot.h"
#include "items/inventoryItem.h"

using namespace godot;

class Inventory : public PanelContainer {
	GDCLASS(Inventory, PanelContainer)

public:
	void _ready() override;

protected:
	// Equipment slots

	InventorySlot* WeaponSlots[3];
	InventorySlot* SpellSlot { nullptr };
	InventorySlot* ModSlot { nullptr };
	InventorySlot* ReservedSlot { nullptr };

	InventorySlot* InventorySlots[8];

	static void _bind_methods();

private:

};
