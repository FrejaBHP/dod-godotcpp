#include "ui/hud.h"
#include "player/playerController.h"

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>

using namespace godot;

constexpr int AtlasStep = 24;
const Color WeaponBarEmptyColour { 0.35f, 0.35f, 0.35f, 0.5f };
const Color WeaponBarInactiveColour { 0.38f, 0.34f, 1.0f, 0.5f };
const Color WeaponBarActiveColour { 0.58f, 0.54f, 1.0f, 0.5f };

const Color WeaponBarEmptyBorder { 0.45f, 0.45f, 0.45f, 0.5f };
const Color WeaponBarInactiveBorder { 0.54f, 0.5f, 1.0f, 0.5f };
const Color WeaponBarActiveBorder { 0.74f, 0.7f, 1.0f, 0.5f };

void HUD::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("GetPriItemCard"), &HUD::GetPriItemCard);
	//ClassDB::bind_method(D_METHOD("ShowItemCard"), &HUD::ShowItemCard);
	//ClassDB::bind_method(D_METHOD("HideItemCard"), &HUD::HideItemCard);
	ClassDB::bind_method(D_METHOD("CreatePreview", "p_TRect"), &HUD::CreateHeldItemPreview);
	ClassDB::bind_method(D_METHOD("DestroyPreview"), &HUD::DestroyHeldItemPreview);
	ClassDB::bind_method(D_METHOD("ClearAmmoDisplay"), &HUD::ClearAmmoDisplay);
	ClassDB::bind_method(D_METHOD("SetAmmoDisplayValues"), &HUD::SetAmmoDisplayValues);
}

HUD::HUD() {

}

void HUD::_ready() {
	//PriItemCardPivot = get_node<Node2D>("ItemCardPivot");
	//PriItemCard = PriItemCardPivot->get_node<ItemCard>("ItemCard");

	PInventory = get_node<Inventory>("Inventory");
	PInventory->connect("create_preview", callable_mp(this, &HUD::CreateHeldItemPreview));
	PInventory->connect("destroy_preview", callable_mp(this, &HUD::DestroyHeldItemPreview));

	ExperienceLevel = get_node<Control>("ExperienceLevel");
	ExpBar = ExperienceLevel->get_node<TextureProgressBar>("ExperienceBar");
	LevelLabel = ExperienceLevel->get_node<Label>("MarginContainer/LevelLabel");

	HealthBar = get_node<TextureProgressBar>("PlayerHealth/HealthBar");
	HealthLabel = HealthBar->get_node<Label>("LabelMargin/Label");
	ShieldBar = get_node<TextureProgressBar>("PlayerHealth/Control/ShieldBar");
	ShieldLabel = ShieldBar->get_node<Label>("LabelMargin/Label");

	WeaponBar = get_node<Control>("SelectedWeaponBar");

	CurAmmoBar = get_node<TextureProgressBar>("PlayerHUDAmmo/AmmoRatioBar");
	CurAmmoLabel = CurAmmoBar->get_node<Label>("LabelMargin/Label");
	CurAmmoTypeRect = get_node<TextureRect>("PlayerHUDAmmo/HBoxContainer/IconMargin/AmmoTypeIcon");
	CurAmmoTypeAtlas = static_cast<AtlasTexture*>(CurAmmoTypeRect->get_texture().ptr());
	ReserveAmmoLabel = get_node<Label>("PlayerHUDAmmo/HBoxContainer/LabelMargin/AmmoReserve");
}

void HUD::_process(double delta) {
	if (HeldItemPreview) {
		const Vector2 mousePosition = get_viewport()->get_mouse_position();
		const Vector2 offset = HeldItemPreview->get_rect().get_size() / 2;
		HeldItemPreview->set_global_position(mousePosition - offset);
	}
}

void HUD::_physics_process(double delta) {

}

void HUD::BindController(PlayerController* pc) {
	PController = pc;
}

void HUD::ToggleInventory() {
	PInventory->set_visible(!PInventory->is_visible());

	if (!PInventory->is_visible()) {
		PInventory->OnInventoryClosed();
	}
}

/*
void HUD::MovePriItemCardPivot(Vector2 pos) {
	pos.y += get_viewport_rect().get_size().y;
	PriItemCardPivot->set_global_position(pos);
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
*/

void HUD::CreateHeldItemPreview(TextureRect* tr) {
	// Failsafe
	if (HeldItemPreview) {
		HeldItemPreview->queue_free();
	}

	HeldItemPreview = memnew(TextureRect);
	add_child(HeldItemPreview);
	HeldItemPreview->set_custom_minimum_size(tr->get_custom_minimum_size());
	HeldItemPreview->set_texture_filter(tr->get_texture_filter());
	HeldItemPreview->set_texture(tr->get_texture());
	HeldItemPreview->set_mouse_filter(MouseFilter::MOUSE_FILTER_IGNORE);
	HeldItemPreview->set_stretch_mode(TextureRect::StretchMode::STRETCH_KEEP_ASPECT_CENTERED);
	HeldItemPreview->set_modulate(Color(1.f, 1.f, 1.f, 0.7f));
}

void HUD::DestroyHeldItemPreview() {
	if (HeldItemPreview) {
		HeldItemPreview->queue_free();
		HeldItemPreview = nullptr;
	}
}

void HUD::UpdateHealthCurrent(double current) {
	if (StoredMaxHealth == 0.0) {
		print_error("UPDATE HEALTH: Trying to divide by 0");
		return;
	}

	if (current > StoredMaxHealth) {
		HealthBar->set_value(1.0);
	}
	else {
		HealthBar->set_value(current / StoredMaxHealth);
	}

	HealthLabel->set_text(vformat("%0.f / %0.f", current, StoredMaxHealth));
}

void HUD::UpdateShieldCurrent(double current) {
	if (StoredMaxShield == 0.0) {
		print_error("UPDATE SHIELD: Trying to divide by 0");
		return;
	}

	if (current > StoredMaxShield) {
		ShieldBar->set_value(1.0);
	}
	else {
		ShieldBar->set_value(current / StoredMaxShield);
	}

	ShieldLabel->set_text(vformat("%0.f / %0.f", current, StoredMaxShield));
}

void HUD::SetHighlightedWeaponSlot(int slot) {
	for (size_t i = 0; i < WeaponBar->get_child_count(); i++) {
		Control* swc = static_cast<Control*>(WeaponBar->get_child(i));
		Panel* panel = swc->get_node<Panel>("Panel");
		Ref<StyleBoxFlat> sb = static_cast<Ref<StyleBoxFlat>>(panel->get_theme_stylebox("panel")->duplicate());

		if (slot == i) {
			sb->set_bg_color(WeaponBarActiveColour);
			sb->set_border_color(WeaponBarActiveBorder);
		}
		else {
			sb->set_bg_color(WeaponBarInactiveColour);
			sb->set_border_color(WeaponBarInactiveBorder);
		}

		panel->add_theme_stylebox_override("panel", sb);
	}
}

void HUD::ClearAmmoDisplay() {
	CurAmmoLabel->set_text("");
	ReserveAmmoLabel->set_text("");
	CurAmmoBar->set_value((double)0);
	SetAmmoDisplayType(EAmmoType::NONE);
}

void HUD::SetAmmoDisplayValues(int32_t cur, int32_t max, int32_t res) {
	CurAmmoLabel->set_text(itos(cur) + " / " + itos(max));
	ReserveAmmoLabel->set_text(itos(res));

	if (max > 0) {
		CurAmmoBar->set_value((double)cur / (double)max);
	}
	else {
		CurAmmoBar->set_value((double)0);
	}
}

void HUD::SetAmmoDisplayType(EAmmoType ammoType) {
	Rect2 region { Point2(0, 0), Size2(AtlasStep, AtlasStep) };

	switch (ammoType) {
		case EAmmoType::Pistol:
			region.set_position(Vector2(0, 0));
			break;

		case EAmmoType::Revolver:
			region.set_position(Vector2(AtlasStep, 0));
			break;

		case EAmmoType::SMG:
			region.set_position(Vector2(0, AtlasStep));
			break;

		case EAmmoType::Rifle:
			region.set_position(Vector2(AtlasStep, AtlasStep));
			break;

		case EAmmoType::Shotgun:
			region.set_position(Vector2(AtlasStep * 2, AtlasStep));
			break;

		case EAmmoType::Sniper:
			region.set_position(Vector2(AtlasStep * 2, 0));
			break;

		case EAmmoType::Launcher:
			region.set_position(Vector2(0, AtlasStep * 2));
			break;

		default:
			region.set_position(Vector2(0, 0));
			break;
	}

	CurAmmoTypeAtlas->set_region(region);
}

void HUD::UpdateEXP(double xp, double prevThresh, double nextThresh) {
	double min = xp - prevThresh;
	double max = nextThresh - prevThresh;
	ExpBar->set_value(min / max);
}

void HUD::UpdateLevel(int level) {
	LevelLabel->set_text(vformat("Level %d", level));
}

Inventory* const HUD::GetInventory() const {
	return PInventory;
}

void HUD::ShowShieldBar() {
	IsShieldBarVisible = true;
	ShieldBar->set_visible(true);
}

void HUD::HideShieldBar() {
	IsShieldBarVisible = false;
	ShieldBar->set_visible(false);
}

void HUD::SetHealthMax(double max) {
	StoredMaxHealth = max;
}

void HUD::SetShieldMax(double max) {
	StoredMaxShield = max;
}
