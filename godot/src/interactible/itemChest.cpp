#include "interactible/itemChest.h"
#include "gameInstance.h"
#include "runManager.h"

#include <godot_cpp/classes/atlas_texture.hpp>

void ItemChest::_bind_methods() {
	ClassDB::bind_method(D_METHOD("ICOnActivated"), &ItemChest::OnActivated);
	ClassDB::bind_method(D_METHOD("ICSetItemChestType", "p_ChestType"), &ItemChest::SetItemChestType);
	ClassDB::bind_method(D_METHOD("ICGetItemChestType"), &ItemChest::GetItemChestType);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "chestType", PROPERTY_HINT_ENUM, "WeaponsChest,WeaponsChestQuality,AmmoCrate,AmmoCrateSmall"), "ICSetItemChestType", "ICGetItemChestType");
}

void ItemChest::_ready() {
	InteractibleArea = get_node<Interactible>("Interactible");
	InteractibleArea->connect("activated", callable_mp(this, &ItemChest::OnActivated));

	ChestControls = get_node<Control>("TextPivot/VBoxContainer");

	add_to_group("ItemChest");
}

void ItemChest::OnActivated() {
	if (Used) {
		return;
	}

	Used = true;

	if (!InteractibleArea->GetRepeatable()) {
		InteractibleArea->set_deferred("monitorable", false);
	}

	SetTextVisibility(false);

	switch (ChestType) {
		case EItemChestType::WeaponsCrate: {
			Node2D* wpnAP = get_node<Node2D>("WeaponAttachmentPoints");

			for (size_t i = 0; i < wpnAP->get_child_count(); i++) {
				Node2D* point = static_cast<Node2D*>(wpnAP->get_child(i));
				GameInstance::GetInstance().GenerateAndDropGun(-1, GameInstance::GetInstance().GetRunManager()->CurrentAreaLevel, point);
			}

			AtlasTexture* at = static_cast<AtlasTexture*>(get_node<Sprite2D>("Sprite2D")->get_texture().ptr());
			Rect2 reg = at->get_region();
			reg.set_position(Vector2(reg.size.x, 0.f));
			at->set_region(reg);

			break;
		}

		case EItemChestType::AmmoCrate: {
			const Vector2 cratePos = get_global_position();

			for (size_t i = 0; i < 6; i++) {
				Vector2 offset { 0.f, GetRandomFloat(16.f, 48.f) };
				offset = offset.rotated(GetRandomFloat(-0.4f, 0.4f));

				const Vector2 finalPos = cratePos + offset;
				GameInstance::GetInstance().SpawnRandomAmmoPickup(finalPos);
			}

			AtlasTexture* at = static_cast<AtlasTexture*>(get_node<Sprite2D>("Sprite2D")->get_texture().ptr());
			Rect2 reg = at->get_region();
			reg.set_position(Vector2(reg.size.x, 0.f));
			at->set_region(reg);

			break;
		}

		default:
			break;
	}
}

void ItemChest::SetTextVisibility(bool visible) {
	ChestControls->set_visible(visible);
}

void ItemChest::SetItemChestType(const int type) {
	ChestType = (EItemChestType)type;
}

int ItemChest::GetItemChestType() const {
	return (int)ChestType;
}
