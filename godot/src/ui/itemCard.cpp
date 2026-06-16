#include "ui/itemCard.h"
#include "shared/utility.h"

using namespace godot;

void ItemCard::_bind_methods() {
	ClassDB::bind_method(D_METHOD("GetRowValueLabel"), &ItemCard::GetRowValueLabel);
}

void ItemCard::_ready() {
	LName = get_node<Label>("CardContainer/VTextContainer/LName");
	LGunType = get_node<Label>("CardContainer/VTextContainer/LGunType");
	LManufacturer = get_node<Label>("CardContainer/VTextContainer/LManufacturer");
	CardRows[0] = get_node<HBoxContainer>("CardContainer/VTextContainer/RDamage");
	CardRows[1] = get_node<HBoxContainer>("CardContainer/VTextContainer/RAccuracy");
	CardRows[2] = get_node<HBoxContainer>("CardContainer/VTextContainer/RFireRate");
	CardRows[3] = get_node<HBoxContainer>("CardContainer/VTextContainer/RReload");
	CardRows[4] = get_node<HBoxContainer>("CardContainer/VTextContainer/RMagazine");
}

HBoxContainer* ItemCard::GetRowByName(ECardRow row) {
	return CardRows[(size_t)row];
}

Label* ItemCard::GetRowValueLabel(size_t index) {
	return CardRows[index]->get_node<Label>("StatValue");
}

Label* ItemCard::GetRowValueLabelByName(ECardRow row) {
	return GetRowByName(row)->get_node<Label>("StatValue");
}

void ItemCard::UseGunDef(const GunDefinition& gundef) {
	LName->add_theme_color_override("font_color", GetRarityColour(gundef.RarityScore));
	LName->set_text(vformat("%s", gundef.GunName.c_str()));

	LGunType->set_text(vformat("%s :: %s", GetGunTypeName(gundef.GunType).c_str(), GetGunSubTypeName(gundef.GunSubType).c_str()));
	LManufacturer->set_text(GetManufacturerName(gundef.Manufacturer).c_str());

	if (gundef.ProjectileCount > 1) {
		GetRowValueLabelByName(Damage)->set_text(vformat("%.0fx%.0d", gundef.Damage, gundef.ProjectileCount));
	}
	else {
		GetRowValueLabelByName(Damage)->set_text(vformat("%.0f", gundef.Damage));
	}
	
	GetRowValueLabelByName(Accuracy)->set_text(vformat("%.1f", gundef.Accuracy));
	GetRowValueLabelByName(FireRate)->set_text(vformat("%.1f", 1000 / gundef.FireTime));
	GetRowValueLabelByName(Reload)->set_text(vformat("%.1f", gundef.ReloadTime));
	GetRowValueLabelByName(Magazine)->set_text(vformat("%.0d", gundef.MagSize));
}
