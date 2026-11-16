#include "combat/healthBar.h"


void HealthBar::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetHealthType", "p_HealthType"), &HealthBar::SetHealthType);
	ClassDB::bind_method(D_METHOD("GetHealthType"), &HealthBar::GetHealthType);
	ClassDB::bind_method(D_METHOD("SetHealthRatio", "p_HealthRatio"), &HealthBar::SetHealthRatio);
	ClassDB::bind_method(D_METHOD("GetHealthRatio"), &HealthBar::GetHealthRatio);
	ClassDB::bind_method(D_METHOD("SetInitialHealthPercentage", "p_InitHealthPct"), &HealthBar::SetInitialHealthPercentage);
	ClassDB::bind_method(D_METHOD("GetInitialHealthPercentage"), &HealthBar::GetInitialHealthPercentage);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "healthType", PROPERTY_HINT_ENUM, "Neutral,Flesh,Shield,Armour,Energy"), "SetHealthType", "GetHealthType");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "healthRatio", PROPERTY_HINT_NONE, ""), "SetHealthRatio", "GetHealthRatio");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "initialHealthPercentage", PROPERTY_HINT_NONE, ""), "SetInitialHealthPercentage", "GetInitialHealthPercentage");

	ADD_SIGNAL(MethodInfo("healthbar_depleted", PropertyInfo(Variant::INT, "barNum")));
}

void HealthBar::_ready() {
	add_to_group("HealthBar");
}

void HealthBar::_physics_process(double delta) {

}

void HealthBar::FinaliseHealthBar(double maxHealth) {
	HealthMax = maxHealth * HealthRatio;
	HealthCurrent = HealthMax * InitialHealthPercentage;

	UpdateBarValue();
	set_tint_progress(GetHealthColour(HealthType));
	set_visible(true);
}

void HealthBar::SetBarStats(double max, EHealthType type) {
	SetBarStats(max, max, type);
}

void HealthBar::SetBarStats(double max, double current, EHealthType type) {
	HealthMax = max;
	HealthCurrent = current;

	UpdateBarValue();

	SetHealthType((int)type);

	set_visible(true);
}

/*
void HealthBar::SetHealthType(EHealthType type) {
	HealthType = type;

	set_tint_progress(GetHealthColour(type));
}
*/

void HealthBar::SetHealthType(const int type) {
	HealthType = (EHealthType)type;

	set_tint_progress(GetHealthColour(HealthType));
}

int HealthBar::GetHealthType() const {
	return (int)HealthType;
}

void HealthBar::SetHealthRatio(const double ratio) {
	HealthRatio = ratio;
}

double HealthBar::GetHealthRatio() const {
	return HealthRatio;
}

void HealthBar::SetInitialHealthPercentage(const double pct) {
	InitialHealthPercentage = pct;
}

double HealthBar::GetInitialHealthPercentage() const {
	return InitialHealthPercentage;
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

double HealthBar::GetMaxHealth() const {
	return HealthMax;
}

double HealthBar::GetCurrentHealth() const {
	return HealthCurrent;
}
