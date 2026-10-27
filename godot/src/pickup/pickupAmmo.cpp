#include "pickup/pickupAmmo.h"

#include <godot_cpp/classes/atlas_texture.hpp>

constexpr int AtlasStep { 16 };

constexpr int PistolAmmoCount { 18 };
constexpr int SMGAmmoCount { 32 };
constexpr int RifleAmmoCount { 24 };
constexpr int RevolverAmmoCount { 6 };
constexpr int ShotgunAmmoCount { 8 };
constexpr int SniperAmmoCount { 6 };
constexpr int LauncherAmmoCount { 2 };

void AmmoPickup::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetAmmoType", "p_AmmoType"), &AmmoPickup::SetAmmoType);
	ClassDB::bind_method(D_METHOD("GetAmmoType"), &AmmoPickup::GetAmmoType);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "ammoType", PROPERTY_HINT_ENUM, "Pistol,Revolver,SMG,Rifle,Shotgun,Sniper,Launcher,NONE"), "SetAmmoType", "GetAmmoType");
}

void AmmoPickup::_ready() {
	AmmoSprite = get_node<Sprite2D>("AmmoSprite");
	add_to_group("AmmoPickup");
}

void AmmoPickup::SetAmmoType(const int ammoType) {
	AmmoType = (EAmmoType)ammoType;

	Rect2 region { Point2(0, 0), Size2(AtlasStep, AtlasStep) };

	switch (AmmoType) {
		case EAmmoType::Pistol:
			region.set_position(Vector2(0, 0));
			AmmoCount = PistolAmmoCount;
			break;

		case EAmmoType::Revolver:
			region.set_position(Vector2(AtlasStep, 0));
			AmmoCount = RevolverAmmoCount;
			break;

		case EAmmoType::SMG:
			region.set_position(Vector2(AtlasStep * 2, 0));
			AmmoCount = SMGAmmoCount;
			break;

		case EAmmoType::Rifle:
			region.set_position(Vector2(AtlasStep * 3, 0));
			AmmoCount = RifleAmmoCount;
			break;

		case EAmmoType::Shotgun:
			region.set_position(Vector2(AtlasStep, AtlasStep));
			AmmoCount = ShotgunAmmoCount;
			break;

		case EAmmoType::Sniper:
			region.set_position(Vector2(0, AtlasStep));
			AmmoCount = SniperAmmoCount;
			break;

		case EAmmoType::Launcher:
			region.set_position(Vector2(AtlasStep * 2, AtlasStep));
			AmmoCount = LauncherAmmoCount;
			break;

		default:
			region.set_position(Vector2(AtlasStep * 3, AtlasStep));
			break;
	}

	AtlasTexture* atlas = static_cast<AtlasTexture*>(AmmoSprite->get_texture().ptr());
	atlas->set_region(region);

	if (!is_monitorable()) {
		set_deferred("monitorable", true);
	}
}

int AmmoPickup::GetAmmoType() const {
	return (int)AmmoType;
}

int AmmoPickup::GetAmmoCount() const {
	return AmmoCount;
}

void AmmoPickup::Disable() {
	IsPickedUp = true;
	set_deferred("monitorable", false);
}
