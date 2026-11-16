#include "ui/inventorySlot.h"

void InventorySlot::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetSlotType", "p_SlotType"), &InventorySlot::SetSlotType);
	ClassDB::bind_method(D_METHOD("GetSlotType"), &InventorySlot::GetSlotType);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "slot_type", PROPERTY_HINT_ENUM, "Inventory,Weapon,Spell,Mod"), "SetSlotType", "GetSlotType");
}

void InventorySlot::_ready() {

}

Variant InventorySlot::_get_drag_data(const Vector2& p_at_position) {
	if (ContainedItem) {
		return ContainedItem;
	}

	return nullptr;
}

bool InventorySlot::_can_drop_data(const Vector2& p_at_position, const Variant& p_data) const {
	if (p_data.get_type() == Variant::OBJECT) {
		Object* gobj = static_cast<Object*>(p_data);

		if (gobj->get_class() == "InventoryItem") {
			print_line(get_name());
			InventoryItem* item = static_cast<InventoryItem*>(gobj);

			return GetDragEligibility(SlotType, (EInventoryItemType)item->GetItemType());
		}
	}

	return false;
}

void InventorySlot::_drop_data(const Vector2& p_at_position, const Variant& p_data) {
	InventoryItem* item = static_cast<InventoryItem*>((Object*)p_data);

	InventorySlot* oldSlot = static_cast<InventorySlot*>(item->get_parent());

	if (oldSlot == this) {
		return;
	}

	if (!ContainedItem) {
		item->reparent(this);
		oldSlot->ContainedItem = nullptr;
		ContainedItem = item;
	}
}

bool InventorySlot::GetDragEligibility(EInventorySlotType slotType, EInventoryItemType itemType) const {
	switch (slotType) {
		case EInventorySlotType::Inventory:
			return true;

		case EInventorySlotType::EquipmentWeapon:
			if (itemType == EInventoryItemType::Weapon) {
				return true;
			}
			break;

		case EInventorySlotType::EquipmentSpell:
			if (itemType == EInventoryItemType::Spell) {
				return true;
			}
			break;

		case EInventorySlotType::EquipmentMod:
			if (itemType == EInventoryItemType::Mod) {
				return true;
			}
			break;

		default:
			break;
	}

	return false;
}

void InventorySlot::SetSlotType(const int type) {
	SlotType = (EInventorySlotType)type;
}

int InventorySlot::GetSlotType() const {
	return (int)SlotType;
}
