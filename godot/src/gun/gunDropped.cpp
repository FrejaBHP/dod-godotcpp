#include <godot_cpp/classes/resource_loader.hpp>

#include "gun/gunDropped.h"

using namespace godot;

void GunDropped::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("SetupDroppedGun"), &GunDropped::SetupDroppedGun);
	//ClassDB::bind_method(D_METHOD("BodyEntered"), &GunDropped::BodyEntered);
}

GunDropped::GunDropped() {

}

void GunDropped::_ready() {
	Sprite = get_node<Sprite2D>("GunSprite");
	PickupArea = get_node<Area2D>("PickupArea");

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
		if (GunDef->GunSubType == EGunSubType::Repeater) {
			texture = loader->load("res://assets/pistol.png");
		}
	}
	else if (GunDef->GunType == EGunType::SMG) {
		texture = loader->load("res://assets/mp5.png");
	}
	else {
		texture = loader->load("res://assets/scarh.png");
	}

	Sprite->set_texture(texture);
}
