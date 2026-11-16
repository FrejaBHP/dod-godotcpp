#include "ui/itemCard.h"
#include "shared/utility.h"
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>

using namespace godot;

void ItemCard::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("GetRowValueLabel"), &ItemCard::GetRowValueLabel);
}

void ItemCard::_ready() {
	CardRows.reserve(8);

	LName = get_node<Label>("VCardContainer/VHeadContainer/LName");
	LGunType = get_node<RichTextLabel>("VCardContainer/VHeadContainer/LGunType");
	LManufacturer = get_node<Label>("VCardContainer/VHeadContainer/LManufacturer");

	CardRows[0] = get_node<HBoxContainer>("VCardContainer/VRowContainer/RDamage");
	CardRows[1] = get_node<HBoxContainer>("VCardContainer/VRowContainer/RAccuracy");
	CardRows[2] = get_node<HBoxContainer>("VCardContainer/VRowContainer/RFireRate");
	CardRows[3] = get_node<HBoxContainer>("VCardContainer/VRowContainer/RReload");
	CardRows[4] = get_node<HBoxContainer>("VCardContainer/VRowContainer/RMagazine");
	CardRows[5] = get_node<HBoxContainer>("VCardContainer/VRowContainer/RElement");
	CardRows[6] = get_node<HBoxContainer>("VCardContainer/VRowContainer/REleParam1");
	CardRows[7] = get_node<HBoxContainer>("VCardContainer/VRowContainer/REleParam2");
}

HBoxContainer* ItemCard::GetRowByName(ECardRow row) {
	return CardRows[(size_t)row];
}

Label* ItemCard::GetRowNameLabel(size_t index) {
	return CardRows[index]->get_node<Label>("NameMargin/StatName");
}

Label* ItemCard::GetRowValueLabel(size_t index) {
	return CardRows[index]->get_node<Label>("ValueMargin/StatValue");
}

Label* ItemCard::GetRowValueLabelByName(ECardRow row) {
	return GetRowByName(row)->get_node<Label>("ValueMargin/StatValue");
}

TextureRect* ItemCard::GetRowTextureRect(size_t index) {
	return CardRows[index]->get_node<TextureRect>("IconMargin/StatIcon");
}

void ItemCard::UseGunDef(const GunDefinition& gundef) {
	const Color rarityColour = GetRarityColour(gundef.RarityScore);

	// override card's border colour to match item rarity
	Ref<StyleBoxFlat> sb = static_cast<Ref<StyleBoxFlat>>(get_theme_stylebox("panel")->duplicate());
	sb->set_border_color(rarityColour);
	add_theme_stylebox_override("panel", sb);

	LName->add_theme_color_override("font_color", rarityColour);
	LName->set_text(vformat("%s", gundef.GunName.c_str()));

	//LGunType->set_text(vformat("%s :: %s", GetGunTypeName(gundef.GunType).c_str(), GetGunSubTypeName(gundef.GunSubType).c_str()));
	LGunType->set_text("");
	LGunType->push_color(rarityColour);
	LGunType->append_text(GetRarityName(gundef.GunRarity));
	LGunType->pop();
	LGunType->append_text(" " + GetGunSubTypeName(gundef.GunSubType));

	LManufacturer->set_text(GetManufacturerName(gundef.Manufacturer));

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
			GetRowValueLabel(5)->set_text(GetElementName(gundef.Element->Element));
			GetRowValueLabel(5)->add_theme_color_override("font_color", GetElementColour(gundef.Element->Element));
			CardRows[5]->set_visible(true);

			EElement e = gundef.Element->Element;
			Ref<Texture2D> eleRes = nullptr;

			switch (e) {
				case EElement::Fire:
					eleRes = ResourceLoader::get_singleton()->load("res://assets/interface/icon_incendiary.png");
					break;

				case EElement::Shock:
					eleRes = ResourceLoader::get_singleton()->load("res://assets/interface/icon_shock.png");
					break;

				case EElement::Corrosive:
					eleRes = ResourceLoader::get_singleton()->load("res://assets/interface/icon_corrosive.png");
					break;

				case EElement::Cryo:
					eleRes = ResourceLoader::get_singleton()->load("res://assets/interface/icon_cryo.png");
					break;

				case EElement::Explosive:
					break;

				default:
					break;
			}

			TextureRect* tr = GetRowTextureRect((size_t)ECardRow::Element);
			tr->set_texture(eleRes);

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
