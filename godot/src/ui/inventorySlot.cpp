#include "ui/inventorySlot.h"

void InventorySlot::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetSlotType", "p_SlotType"), &InventorySlot::SetSlotType);
	ClassDB::bind_method(D_METHOD("GetSlotType"), &InventorySlot::GetSlotType);
	ClassDB::bind_method(D_METHOD("OnMouseEntered"), &InventorySlot::OnMouseEntered);
	ClassDB::bind_method(D_METHOD("OnMouseExited"), &InventorySlot::OnMouseExited);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "slot_type", PROPERTY_HINT_ENUM, "Inventory,Weapon,Shield,Spell,Mod"), "SetSlotType", "GetSlotType");

	ADD_SIGNAL(MethodInfo("slot_clicked", PropertyInfo(Variant::OBJECT, "slot"), PropertyInfo(Variant::OBJECT, "item")));
	ADD_SIGNAL(MethodInfo("slot_released", PropertyInfo(Variant::OBJECT, "slot"), PropertyInfo(Variant::OBJECT, "item")));

	ADD_SIGNAL(MethodInfo("item_equipped", PropertyInfo(Variant::OBJECT, "item"), PropertyInfo(Variant::INT, "slot")));
	ADD_SIGNAL(MethodInfo("item_unequipped", PropertyInfo(Variant::INT, "slot")));

	ADD_SIGNAL(MethodInfo("item_use", PropertyInfo(Variant::OBJECT, "slot"), PropertyInfo(Variant::OBJECT, "item")));
	ADD_SIGNAL(MethodInfo("item_drop", PropertyInfo(Variant::OBJECT, "slot"), PropertyInfo(Variant::OBJECT, "item")));
}

void InventorySlot::_ready() {
	BGTexture = get_node<TextureRect>("BackgroundTexture");

	connect("mouse_entered", callable_mp(this, &InventorySlot::OnMouseEntered));
	connect("mouse_exited", callable_mp(this, &InventorySlot::OnMouseExited));
}

void InventorySlot::_gui_input(const Ref<InputEvent>& p_event) {
	if (p_event->is_action_pressed("lmb")) {
		emit_signal("slot_clicked", this, ContainedItem);
	}
	else if (p_event->is_action_released("lmb")) {
		emit_signal("slot_released", this, ContainedItem);
	}
	else if (p_event->is_action_pressed("item_use")) {
		if (ContainedItem) {
			emit_signal("item_use", this, ContainedItem);
		}
	}
	else if (p_event->is_action_pressed("item_drop")) {
		if (ContainedItem) {
			if (ContainedItem->HasActiveCard) {
				ContainedItem->DestroyItemCard();
			}
			emit_signal("item_drop", this, ContainedItem);
		}
	}
}

void InventorySlot::OnMouseEntered() {
	grab_focus();

	if (ContainsItem()) {
		ContainedItem->CreateItemCard();	
	}
}

void InventorySlot::OnMouseExited() {
	release_focus();

	if (ContainsItem()) {
		ContainedItem->DestroyItemCard();	
	}
}

void InventorySlot::SetBGVisibility(const bool visible) {
	BGTexture->set_visible(visible);
}

void InventorySlot::SetContainedItem(InventoryItem* item) {
	ContainedItem = item;

	if (SlotType != EInventorySlotType::Inventory) {
		SetBGVisibility(!ContainedItem);

		if (ContainedItem) {
			emit_signal("item_equipped", item, SlotNumber);
		}
		else {
			emit_signal("item_unequipped", SlotNumber);
		}
	}
}

InventoryItem* const InventorySlot::GetContainedItem() const {
	return ContainedItem;
}

bool InventorySlot::ContainsItem() {
	if (!ContainedItem) {
		return false;
	}

	return true;
}

void InventorySlot::SetSlotType(const int type) {
	SlotType = (EInventorySlotType)type;
}

int InventorySlot::GetSlotType() const {
	return (int)SlotType;
}
