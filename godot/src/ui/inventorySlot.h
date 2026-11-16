#pragma once

#include <godot_cpp/classes/panel_container.hpp>
#include "items/inventoryItem.h"
#include "shared/enums.h"

using namespace godot;

class InventorySlot : public PanelContainer {
	GDCLASS(InventorySlot, PanelContainer)

public:
	InventoryItem* ContainedItem { nullptr };

	void _ready() override;

	virtual Variant _get_drag_data(const Vector2& p_at_position) override;
	virtual bool _can_drop_data(const Vector2& p_at_position, const Variant& p_data) const override;
	virtual void _drop_data(const Vector2& p_at_position, const Variant& p_data) override;

	void SetSlotType(const int type);
	int GetSlotType() const;

protected:
	

	EInventorySlotType SlotType { EInventorySlotType::Inventory };

	static void _bind_methods();

	// Const to comply with _can_drop_data
	bool GetDragEligibility(EInventorySlotType slotType, EInventoryItemType itemType) const;

private:

};
