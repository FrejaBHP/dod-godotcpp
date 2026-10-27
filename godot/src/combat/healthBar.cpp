#include "combat/healthBar.h"


void HealthBar::_bind_methods() {
	ADD_SIGNAL(MethodInfo("healthbar_depleted", PropertyInfo(Variant::INT, "barNum")));
}

void HealthBar::_ready() {

}

void HealthBar::_physics_process(double delta) {

}

void HealthBar::SetBarStats(double max, EHealthType type) {
	SetBarStats(max, max, type);
}

void HealthBar::SetBarStats(double max, double current, EHealthType type) {
	HealthMax = max;
	HealthCurrent = current;

	UpdateBarValue();

	SetHealthType(type);

	set_visible(true);
}

void HealthBar::SetHealthType(EHealthType type) {
	HealthType = type;

	set_tint_progress(GetHealthColour(type));
}

EHealthType HealthBar::GetHealthType() const {
	return HealthType;
}

double HealthBar::ApplyDamage(double damage) {
	double overkill { 0.0 };

	if (damage > HealthCurrent) {
		overkill = damage - HealthCurrent;
		HealthCurrent = 0.0;
	}
	else if (damage == HealthCurrent) {
		HealthCurrent = 0.0;
	}
	else {
		HealthCurrent -= damage;
	}

	UpdateBarValue();

	return overkill;
}

double HealthBar::ApplyDamageInfo(DamageInfo& di, double& outDmgDealt) {
	double overkillFraction { 0.0 };
	double totalDamage { 0.0 };

	for (size_t i = 0; i < di.DamageInstances.size(); i++) {
		totalDamage += di.DamageInstances[i].Damage * GetDamageEffectiveness(di.DamageInstances[i].Element, HealthType);
	}

	if (totalDamage > HealthCurrent) {
		double overkill = totalDamage - HealthCurrent;
		overkillFraction = overkill / totalDamage;

		outDmgDealt += HealthCurrent;
		HealthCurrent = 0.0;
	}
	else if (totalDamage == HealthCurrent) {
		outDmgDealt += HealthCurrent;
		HealthCurrent = 0.0;
	}
	else {
		outDmgDealt += totalDamage;
		HealthCurrent -= totalDamage;
	}

	UpdateBarValue();

	return overkillFraction;
}

void HealthBar::UpdateBarValue() {
	set_value(HealthCurrent / HealthMax);
}

double HealthBar::GetCurrentHealth() const {
	return HealthCurrent;
}
