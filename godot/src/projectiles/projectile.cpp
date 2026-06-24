#include "projectiles/projectile.h"
#include "character.h"

using namespace godot;

void Projectile::_bind_methods() {
	ClassDB::bind_method(D_METHOD("BodyEntered"), &Projectile::BodyEntered);
	ClassDB::bind_method(D_METHOD("Remove"), &Projectile::Remove);
	ClassDB::bind_method(D_METHOD("SetSpeed"), &Projectile::SetSpeed);
}

Projectile::Projectile() {
	
}

void Projectile::_ready() {
	Timer* timer = get_node<Timer>("Timer");
	if (timer) {
		LifeTimer = timer;
		LifeTimer->connect("timeout", callable_mp(this, &Projectile::Remove));

		LifeTimer->set_wait_time(2.5);
		LifeTimer->start();
	}

	connect("body_entered", callable_mp(this, &Projectile::BodyEntered));
}

void Projectile::_physics_process(double delta) {
	Vector2 curGPos = get_global_position();
	Vector2 newGPos = curGPos + (get_global_transform().columns[0] * (Speed * delta));
	set_global_position(newGPos);
}

void Projectile::BodyEntered(Node2D* body) {
	LifeTimer->stop();

	if (body->is_in_group("Character")) {
		Character* ch = static_cast<Character*>(body);
		ch->OnHitByProjectile();
	}

	Remove();
}

void Projectile::SetSpeed(float speed) {
	Speed = speed;
}

void Projectile::UpdateMasks(EAlignment alignment) {
	if (alignment == EAlignment::Player) {
		set_collision_mask_value(5, true);
	}
	else if (alignment == EAlignment::Enemies) {
		set_collision_mask_value(1, true);
	}
	else {
		set_collision_mask_value(1, true);
		set_collision_mask_value(5, true);
	}
}

void Projectile::Remove() {
	queue_free();
}
