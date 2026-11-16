#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/atlas_texture.hpp>
#include <godot_cpp/classes/texture_progress_bar.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include "ui/itemCard.h"
#include "shared/enums.h"

using namespace godot;

class PlayerController;

class HUD : public Control {
	GDCLASS(HUD, Control)

public:
	HUD();
	~HUD() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void BindController(PlayerController* pc);

	void SetHealthMax(double max);
	void SetShieldMax(double max);
	void UpdateHealthCurrent(double current);
	void UpdateShieldCurrent(double current);

	void SetHighlightedWeaponSlot(int slot);

	void ClearAmmoDisplay();
	void SetAmmoDisplayValues(int32_t cur, int32_t max, int32_t res);
	void SetAmmoDisplayType(EAmmoType ammoType);

	void UpdateEXP(double xp, double prevThresh, double nextThresh);
	void UpdateLevel(int level);

	void ShowShieldBar();
	void HideShieldBar();

	//void ShowItemCard();
	//void HideItemCard();

	//void MovePriItemCardPivot(Vector2 pos);
	//ItemCard* GetPriItemCard() const;

protected:
	PlayerController* PController { nullptr };

	//Node2D* PriItemCardPivot { nullptr };
	//ItemCard* PriItemCard { nullptr };

	Control* ExperienceLevel { nullptr };
	TextureProgressBar* ExpBar { nullptr };
	Label* LevelLabel { nullptr };

	TextureProgressBar* HealthBar { nullptr };
	TextureProgressBar* ShieldBar { nullptr };
	Label* HealthLabel { nullptr };
	Label* ShieldLabel { nullptr };

	Control* WeaponBar { nullptr };

	Label* CurAmmoLabel { nullptr };
	Label* ReserveAmmoLabel { nullptr };
	TextureProgressBar* CurAmmoBar { nullptr };
	TextureRect* CurAmmoTypeRect { nullptr };
	AtlasTexture* CurAmmoTypeAtlas { nullptr };

	bool IsShieldBarVisible { false };

	double StoredMaxHealth { 1.0 };
	double StoredMaxShield { 1.0 };

	static void _bind_methods();

private:

};
