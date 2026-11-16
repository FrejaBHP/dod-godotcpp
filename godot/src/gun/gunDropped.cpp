#include "gun/gunDropped.h"
#include "ui/itemCard.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

void GunDropped::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("SetupDroppedGun"), &GunDropped::SetupDroppedGun);
	//ClassDB::bind_method(D_METHOD("BodyEntered"), &GunDropped::BodyEntered);
}

GunDropped::GunDropped() {

}

void GunDropped::_ready() {
	Sprite = get_node<Sprite2D>("GunSprite");
	ItemCardPivot = get_node<Node2D>("ItemCardPivot");
	InteractibleArea = get_node<Interactible>("Interactible");

	CanBePickedUp = true;

	add_to_group("GunDropped");

	//PickupArea->connect("body_entered", callable_mp(this, &GunDropped::BodyEntered), CONNECT_DEFERRED);
}

void GunDropped::_physics_process(double delta) {

}

void GunDropped::SetupDroppedGun(std::shared_ptr<GunDefinition> gundef) {
	GunDef = gundef;

	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<Texture2D> texture;

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

	Sprite->set_texture(texture);
}

void GunDropped::CreateItemCard() {
	Ref<PackedScene> icScene = ResourceLoader::get_singleton()->load("res://scenes/ui/item_card.tscn");

	if (icScene->can_instantiate()) {
		ItemCard* card = static_cast<ItemCard*>(icScene->instantiate());

		ItemCardPivot->add_child(card);
		card->UseGunDef(*GunDef);
		card->set_visible(true);
	}
}

void GunDropped::DestroyItemCard() {
	if (ItemCardPivot->get_child_count()) {
		ItemCardPivot->get_child(0)->queue_free();
	}
}
