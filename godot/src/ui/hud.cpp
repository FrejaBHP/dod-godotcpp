#include "ui/hud.h"

using namespace godot;

void HUD::_bind_methods() {
	ClassDB::bind_method(D_METHOD("GetPriItemCard"), &HUD::GetPriItemCard);
	ClassDB::bind_method(D_METHOD("ShowItemCard"), &HUD::ShowItemCard);
	ClassDB::bind_method(D_METHOD("HideItemCard"), &HUD::HideItemCard);
	ClassDB::bind_method(D_METHOD("ClearAmmoDisplay"), &HUD::ClearAmmoDisplay);
	ClassDB::bind_method(D_METHOD("SetAmmoDisplayValues"), &HUD::SetAmmoDisplayValues);
}

HUD::HUD() {

}

void HUD::_ready() {
	PriItemCard = get_node<ItemCard>("ItemCard");

	AmmoLabel = get_node<Label>("AmmoLabel");
}

void HUD::_process(double delta) {

}

void HUD::_physics_process(double delta) {

}

ItemCard* HUD::GetPriItemCard() const {
	return PriItemCard;
}

void HUD::ShowItemCard() {
	PriItemCard->set_visible(true);
}

void HUD::HideItemCard() {
	PriItemCard->set_visible(false);
}

void HUD::ClearAmmoDisplay() {
	AmmoLabel->set_text("");
}

void HUD::SetAmmoDisplayValues(int32_t cur, int32_t res) {
	AmmoLabel->set_text(itos(cur) + " / " + itos(res));
}
