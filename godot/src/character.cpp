#include "character.h"
#include "gun/gun.h"

using namespace godot;

void Character::_bind_methods() {
	ClassDB::bind_method(D_METHOD("GetMaxSpeed"), &Character::GetMaxSpeed);
	ClassDB::bind_method(D_METHOD("ApplyMovement"), &Character::ApplyMovement);
}

void Character::_ready() {
	MaxSpeed = 300.f;
}

void Character::_physics_process(double delta) {

}

void Character::ApplyMovement(Vector2 movement) {
	Vector2 velocity = Vector2(movement.x * MaxSpeed, movement.y * MaxSpeed);
	set_velocity(velocity);
	move_and_slide();
}

double Character::GetMaxSpeed() const {
	return MaxSpeed;
}
