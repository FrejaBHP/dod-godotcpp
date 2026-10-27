#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/atlas_texture.hpp>
#include <godot_cpp/classes/texture_progress_bar.hpp>
#include "ui/itemCard.h"
#include "shared/enums.h"

using namespace godot;

class HUD : public Control {
	GDCLASS(HUD, Control)

public:
	HUD();
	~HUD() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void ShowItemCard();
	void HideItemCard();

	void SetHighlightedWeaponSlot(int slot);

	void ClearAmmoDisplay();
	void SetAmmoDisplayValues(int32_t cur, int32_t max, int32_t res);
	void SetAmmoDisplayType(EAmmoType ammoType);

	void UpdateEXP(double xp, double prevThresh, double nextThresh);
	void UpdateLevel(int level);

	ItemCard* GetPriItemCard() const;

protected:
	ItemCard* PriItemCard { nullptr };

	Control* ExperienceLevel { nullptr };
	TextureProgressBar* ExpBar { nullptr };
	Label* LevelLabel { nullptr };

	Control* WeaponBar { nullptr };

	Label* CurAmmoLabel { nullptr };
	Label* ReserveAmmoLabel { nullptr };
	TextureProgressBar* CurAmmoBar { nullptr };
	TextureRect* CurAmmoTypeRect { nullptr };
	AtlasTexture* CurAmmoTypeAtlas { nullptr };

	static void _bind_methods();

private:

};
