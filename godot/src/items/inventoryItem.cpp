#include "items/inventoryItem.h"

void InventoryItem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetItemType", "p_ItemType"), &InventoryItem::SetItemType);
	ClassDB::bind_method(D_METHOD("GetItemType"), &InventoryItem::GetItemType);
	ClassDB::bind_method(D_METHOD("SetUsable", "p_Usable"), &InventoryItem::SetUsable);
	ClassDB::bind_method(D_METHOD("GetUsable"), &InventoryItem::GetUsable);
	ClassDB::bind_method(D_METHOD("SetDescription", "p_Desc"), &InventoryItem::SetDescription);
	ClassDB::bind_method(D_METHOD("GetDescription"), &InventoryItem::GetDescription);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_type", PROPERTY_HINT_ENUM, "Generic,Consumable,Weapon,Shield,Spell,Mod"), "SetItemType", "GetItemType");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_usable", PROPERTY_HINT_NONE), "SetUsable", "GetUsable");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "item_description", PROPERTY_HINT_NONE), "SetDescription", "GetDescription");
}

void InventoryItem::_ready() {
	ItemTextureRect = get_node<TextureRect>("ItemTexture");
	CardAnchor = get_node<Control>("Control/CardAnchor");

	add_to_group("InventoryItem");
}

void InventoryItem::OnPickedUp() {

}

void InventoryItem::CreateItemCard() {

}

void InventoryItem::DestroyItemCard() {

}

TextureRect* const InventoryItem::GetTextureRect() const {
	return ItemTextureRect;
}

void InventoryItem::SetItemType(const int type) {
	ItemType = (EInventoryItemType)type;
}

int InventoryItem::GetItemType() const {
	return (int)ItemType;
}

void InventoryItem::SetUsable(const bool usable) {
	IsUsable = usable;
}

bool InventoryItem::GetUsable() const {
	return IsUsable;
}

void InventoryItem::SetDescription(const String desc) {
	Description = desc;
}

String InventoryItem::GetDescription() const {
	return Description;
}
