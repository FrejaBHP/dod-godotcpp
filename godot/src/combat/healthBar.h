#pragma once

#include <godot_cpp/classes/texture_progress_bar.hpp>
#include "shared/utility.h"

using namespace godot;

class HealthBar : public TextureProgressBar {
	GDCLASS(HealthBar, TextureProgressBar)

public:
	int BarNumber { 0 };

	void _ready() override;
	void _physics_process(double delta) override;

	void SetBarStats(double max, EHealthType type);
	void SetBarStats(double max, double current, EHealthType type);
	EHealthType GetHealthType() const;

	double ApplyDamage(double damage);
	double ApplyDamageInfo(DamageInfo& di, double& outDmgDealt);
	void UpdateBarValue();
	double GetCurrentHealth() const;

protected:
	EHealthType HealthType { EHealthType::Neutral };
	double HealthMax { 0 };
	double HealthCurrent { 0 };

	static void _bind_methods();

	// Helper function to gather configuration logic in one place
	void SetHealthType(EHealthType type);

private:

};
