#include "enemies/ai/enemyAIComponent.h"
#include "enemies/enemyController.h"
#include "character.h"

void EnemyAIComponent::_bind_methods() {
	
}

void EnemyAIComponent::_ready() {
	
}

void EnemyAIComponent::_physics_process(double delta) {
	if (!AIEnabled) {
		return;
	}
}

void EnemyAIComponent::SetController(EnemyController* ec) {
	Controller = ec;
}

const EnemyController* EnemyAIComponent::GetController() const {
	return Controller;
}

void EnemyAIComponent::SetState(EAIState state) {
	AIState = state;
}

const EAIState EnemyAIComponent::GetState() const {
	return AIState;
}

void EnemyAIComponent::AISlowUpdate() {

}

void EnemyAIComponent::ExecuteIdle() {

}

void EnemyAIComponent::ExecuteSearch() {

}

void EnemyAIComponent::ExecuteChase() {

}

void EnemyAIComponent::Enable() {
	AIEnabled = true;
}

void EnemyAIComponent::Disable() {
	AIEnabled = false;
}

godot::real_t EnemyAIComponent::GetDotTarget() {
	if (Controller->ControlledChar) {
		Vector2 facingDir = Controller->ControlledChar->get_global_position().direction_to(Controller->Target->get_global_position());

		return facingDir.dot(Controller->ControlledChar->get_global_transform().columns[0]);
	}
	else {
		return -1.f;
	}
}

