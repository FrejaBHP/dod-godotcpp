#include "items/invItemGun.h"
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <ui/itemCard.h>

void ItemGun::_bind_methods() {

}

ItemGun::ItemGun() {
	ItemType = EInventoryItemType::Weapon;
}

void ItemGun::_ready() {
	InventoryItem::_ready();

	add_to_group("ItemGun");
}

void ItemGun::OnPickedUp() {
	Ref<Texture2D> texture;
	ResourceLoader* loader = ResourceLoader::get_singleton();

	if (GunDef->GunType == EGunType::Pistol) {
		texture = loader->load("res://assets/pistol.png");
		/*
		if (GunDef->GunSubType == EGunSubType::Repeater) {
			texture = loader->load("res://assets/pistol.png");
		}
		*/
	}
	else if (GunDef->GunType == EGunType::SMG) {
		texture = loader->load("res://assets/mp5.png");
	}
	else {
		texture = loader->load("res://assets/scarh.png");
	}

	ItemTextureRect->set_texture(texture);
}

void ItemGun::CreateItemCard() {
	HasActiveCard = true;

	Ref<PackedScene> icScene = ResourceLoader::get_singleton()->load("res://scenes/ui/item_card_gun.tscn");

	if (icScene->can_instantiate()) {
		ItemCard* card = static_cast<ItemCard*>(icScene->instantiate());

		CardAnchor->add_child(card);
		card->UseGunDef(*GunDef);
		card->set_visible(true);
	}
}

void ItemGun::DestroyItemCard() {
	HasActiveCard = false;

	if (CardAnchor->get_child_count()) {
		CardAnchor->get_child(0)->queue_free();
	}
}
