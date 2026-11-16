#include "character.h"
#include <projectiles/projectile.h>
#include "gun/gun.h"

using namespace godot;

void Character::_bind_methods() {
	ClassDB::bind_method(D_METHOD("CharSetMaxSpeed", "p_MaxSpeed"), &Character::SetMaxSpeed);
	ClassDB::bind_method(D_METHOD("CharGetMaxSpeed"), &Character::GetMaxSpeed);
	ClassDB::bind_method(D_METHOD("CharApplyMovement"), &Character::ApplyMovement);
	ClassDB::bind_method(D_METHOD("CharDie"), &Character::Die);
	ClassDB::bind_method(D_METHOD("CharOnDeath"), &Character::OnDeath);

	ADD_SIGNAL(MethodInfo("inc_hit_projectile", PropertyInfo(Variant::OBJECT, "proj")));
	//ADD_SIGNAL(MethodInfo("inc_hit_projectile"));
}

void Character::_ready() {
	
}

void Character::_physics_process(double delta) {

}

void Character::ApplyMovement(Vector2 movement) {
	Vector2 velocity = Vector2(movement.x * MaxSpeed, movement.y * MaxSpeed);
	set_velocity(velocity);
	move_and_slide();
}

void Character::HitWithProjectile(Projectile* proj) {
	//print_line(vformat("Hit! %X", (uintptr_t)proj));
	emit_signal("inc_hit_projectile", proj);
}

void Character::Die() {
	IsDead = true;
	call_deferred("CharOnDeath");
}

void Character::OnDeath() {

}

void Character::SetMaxSpeed(const double newMax) {
	MaxSpeed = newMax;
}

double Character::GetMaxSpeed() const {
	return MaxSpeed;
}
