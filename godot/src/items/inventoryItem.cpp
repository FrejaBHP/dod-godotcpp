#include "items/inventoryItem.h"

void InventoryItem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetItemType", "p_ItemType"), &InventoryItem::SetItemType);
	ClassDB::bind_method(D_METHOD("GetItemType"), &InventoryItem::GetItemType);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_type", PROPERTY_HINT_ENUM, "Generic,Consumable,Weapon,Spell,Mod"), "SetItemType", "GetItemType");
}

void InventoryItem::_ready() {
	ItemTextureRect = get_node<TextureRect>("ItemTexture");

	add_to_group("InventoryItem");
}

/*
Variant InventoryItem::_get_drag_data(const Vector2& p_at_position) {
	return this;
}
*/

void InventoryItem::SetItemType(const int type) {
	ItemType = (EInventoryItemType)type;
}

int InventoryItem::GetItemType() const {
	return (int)ItemType;
}
