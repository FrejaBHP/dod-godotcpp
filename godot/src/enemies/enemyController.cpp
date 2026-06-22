#include "enemies/enemyController.h"
#include "character.h"
#include "gameInstance.h"

using namespace godot;

void EnemyController::_bind_methods() {

}

void EnemyController::_ready() {
	Target = (Character*)GameInstance::GetInstance().GetPlayer();
}

void EnemyController::_physics_process(double delta) {
	if (ControlledChar) {
		if (Target) {
			ControlledChar->look_at(Target->get_global_position());
		}
	}
}

void EnemyController::SetCharacter(Character* ch) {
	ControlledChar = ch;
}
