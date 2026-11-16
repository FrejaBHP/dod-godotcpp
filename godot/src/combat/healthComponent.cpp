#include "combat/healthComponent.h"
#include "characterController.h"
#include "character.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "gameInstance.h"


void HealthComponent::_bind_methods() {
	ADD_SIGNAL(MethodInfo("health_depleted"));
}

void HealthComponent::_ready() {
	Controller = static_cast<CharacterController*>(get_parent());
	BarContainer = get_node<VBoxContainer>("UIAnchor/BarContainer");
}

void HealthComponent::InitHealthBars() {
	int addedBars { 0 };

	for (size_t i = 0; i < BarContainer->get_child_count(); i++) {
		if (BarContainer->get_child(i)->is_in_group("HealthBar")) {
			HealthBar* hb = static_cast<HealthBar*>(BarContainer->get_child(i));
			HealthBars.append(hb);

			hb->FinaliseHealthBar(GetEnemyBaseHealth(Controller->ControlledChar->Level));
			TotalMaxHealth += hb->GetMaxHealth();
			TotalCurrentHealth += hb->GetCurrentHealth();

			++addedBars;
		}
	}

	if (addedBars > 0) {
		Vector2 pos = BarContainer->get_position();
		pos.y -= 6.f * addedBars;
		BarContainer->set_position(pos);
	}
}

void HealthComponent::_physics_process(double delta) {
	
}

HealthBar* HealthComponent::AddHealthBar(double max, EHealthType type) {
	return AddHealthBar(max, max, type);
}

HealthBar* HealthComponent::AddHealthBar(double max, double current, EHealthType type) {
	Ref<PackedScene> hbScene = ResourceLoader::get_singleton()->load("res://scenes/health_bar.tscn");

	if (hbScene->can_instantiate()) {
		HealthBar* newHealthBar = static_cast<HealthBar*>(hbScene->instantiate());

		if (newHealthBar) {
			BarContainer->add_child(newHealthBar);

			newHealthBar->BarNumber = HealthBars.size();
			HealthBars.append(newHealthBar);

			newHealthBar->SetBarStats(max, current, type);
			
			TotalMaxHealth += max;
			TotalCurrentHealth += current;

			Vector2 pos = BarContainer->get_position();
			pos.y -= 6.f;
			BarContainer->set_position(pos);

			return newHealthBar;
		}
	}

	return nullptr;
}

void HealthComponent::TakeDamage(DamageInfo& di) {
	double biggestDamage = di.DamageInstances[0].Damage;
	EElement biggestElement = di.DamageInstances[0].Element;

	for (size_t i = 0; i < di.DamageInstances.size(); i++) {
		if (di.DamageInstances[i].Damage > biggestDamage) {
			biggestDamage = di.DamageInstances[i].Damage;
			biggestElement = di.DamageInstances[i].Element;
		}
	}

	// Out parameter, accumulates total damage dealt to bars
	double damageDealt { 0.0 };

	for (size_t i = 0; i < HealthBars.size(); i++) {
		if (HealthBars[i]->GetCurrentHealth() <= 0.0) {
			continue;
		}

		double overkillFraction = HealthBars[i]->ApplyDamageInfo(di, damageDealt);

		if (overkillFraction == 0.0) {
			break;
		}
		else {
			di *= overkillFraction;
		}
	}

	double barsCurHealth = 0.0;
	for (size_t i = 0; i < HealthBars.size(); i++) {
		barsCurHealth += HealthBars[i]->GetCurrentHealth();
	}

	TotalCurrentHealth = barsCurHealth;

	//print_line(vformat("TCH: %0.2f / 150", TotalCurrentHealth));

	GameInstance::GetInstance().SpawnDamageText(get_global_position(), damageDealt, biggestElement);

	if (TotalCurrentHealth <= 0.0) {
		emit_signal("health_depleted");
	}
}
