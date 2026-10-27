#include "ui/itemCard.h"
#include "shared/utility.h"

using namespace godot;

void ItemCard::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("GetRowValueLabel"), &ItemCard::GetRowValueLabel);
}

void ItemCard::_ready() {
	CardRows.reserve(8);

	LName = get_node<Label>("CardContainer/VTextContainer/LName");
	LGunType = get_node<Label>("CardContainer/VTextContainer/LGunType");
	LManufacturer = get_node<Label>("CardContainer/VTextContainer/LManufacturer");

	CardRows[0] = get_node<HBoxContainer>("CardContainer/VTextContainer/RDamage");
	CardRows[1] = get_node<HBoxContainer>("CardContainer/VTextContainer/RAccuracy");
	CardRows[2] = get_node<HBoxContainer>("CardContainer/VTextContainer/RFireRate");
	CardRows[3] = get_node<HBoxContainer>("CardContainer/VTextContainer/RReload");
	CardRows[4] = get_node<HBoxContainer>("CardContainer/VTextContainer/RMagazine");
	CardRows[5] = get_node<HBoxContainer>("CardContainer/VTextContainer/RElement");
	CardRows[6] = get_node<HBoxContainer>("CardContainer/VTextContainer/REleParam1");
	CardRows[7] = get_node<HBoxContainer>("CardContainer/VTextContainer/REleParam2");
}

HBoxContainer* ItemCard::GetRowByName(ECardRow row) {
	return CardRows[(size_t)row];
}

Label* ItemCard::GetRowNameLabel(size_t index) {
	return CardRows[index]->get_node<Label>("StatName");
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

	if (gundef.Element) {
		if (gundef.Element->Element != EElement::None) {
			GetRowValueLabel(5)->set_text(GetElementName(gundef.Element->Element).c_str());
			GetRowValueLabel(5)->add_theme_color_override("font_color", GetElementColour(gundef.Element->Element));
			CardRows[5]->set_visible(true);

			EElement e = gundef.Element->Element;
			if (e == EElement::Cryo) {
				GetRowNameLabel(6)->set_text("EFrzFactor:");
				GetRowValueLabel(6)->set_text(vformat("0"));

				CardRows[6]->set_visible(true);
				CardRows[7]->set_visible(false);
			}
			else if (e == EElement::Explosive) {
				GetRowNameLabel(6)->set_text("EExpRadius:");
				GetRowValueLabel(6)->set_text(vformat("0"));

				CardRows[6]->set_visible(true);
				CardRows[7]->set_visible(false);
			}
			else {
				GetRowNameLabel(6)->set_text("EChance:");
				GetRowValueLabel(6)->set_text("0%");

				GetRowNameLabel(7)->set_text("EDamage:");

				if (gundef.Element->BL1Style) {
					GetRowValueLabel(7)->set_text("0%");
				}
				else {
					GetRowValueLabel(7)->set_text(vformat("0"));
				}

				CardRows[6]->set_visible(true);
				CardRows[7]->set_visible(true);
			}
		}
		else {
			CardRows[5]->set_visible(false);
			CardRows[6]->set_visible(false);
			CardRows[7]->set_visible(false);
		}
	}
	else {
		CardRows[5]->set_visible(false);
		CardRows[6]->set_visible(false);
		CardRows[7]->set_visible(false);
	}
}
