#pragma once

#include <godot_cpp/classes/panel_container.hpp>
#include "ui/inventorySlot.h"
#include "items/inventoryItem.h"
#include "items/invItemGun.h"

using namespace godot;

class Inventory : public PanelContainer {
	GDCLASS(Inventory, PanelContainer)

public:
	void _ready() override;

	bool CanAddItem(int& outSlot);
	void AddItem(InventoryItem* item, int slot);
	// Use with caution
	void SetItemInSlot(InventoryItem* item, EInventorySlotType slotType, int slot);

	void UseItem(InventorySlot* slot, InventoryItem* item);
	void DropItem(InventorySlot* slot, InventoryItem* item);

	void GunEquipped(ItemGun* gun, int slot);
	void GunUnequipped(int slot);

	void OnInventoryClosed();
	void OnSlotClicked(InventorySlot* slot, InventoryItem* item);

	void OnMouseEntered();
	void OnMouseExited();

protected:
	bool IsDraggingItem { false };
	bool IsItemHeld { false };
	InventorySlot* MovingSlot { nullptr };
	InventoryItem* MovingItem { nullptr };

	// Equipment slots

	InventorySlot* WeaponSlots[3];
	InventorySlot* ShieldSlot { nullptr };
	InventorySlot* SpellSlot { nullptr };
	InventorySlot* ModSlot { nullptr };

	InventorySlot* InventorySlots[8];

	static void _bind_methods();

	bool GetSlotEligibility(EInventorySlotType slotType, EInventoryItemType itemType) const;

private:

};
