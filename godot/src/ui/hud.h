#pragma once

#include <godot_cpp/classes/control.hpp>
#include "ui/itemCard.h"

using namespace godot;

class HUD : public Control {
	GDCLASS(HUD, Control)

public:
	HUD();
	~HUD() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void ClearAmmoDisplay();
	void SetAmmoDisplayValues(int32_t cur, int32_t res);

	void ShowItemCard();
	void HideItemCard();

	ItemCard* GetPriItemCard() const;

protected:
	static void _bind_methods();

	ItemCard* PriItemCard = nullptr;

	// Temp
	Label* AmmoLabel = nullptr;

private:

};
