#include "projectiles/projectile.h"

using namespace godot;

void Projectile::_bind_methods() {
	ClassDB::bind_method(D_METHOD("BodyEntered"), &Projectile::BodyEntered);
	ClassDB::bind_method(D_METHOD("Remove"), &Projectile::Remove);
}

Projectile::Projectile() {
	Speed = 500.f;
}

void Projectile::_ready() {
	Timer* timer = get_node<Timer>("Timer");
	if (timer) {
		LifeTimer = timer;
		LifeTimer->connect("timeout", callable_mp(this, &Projectile::Remove), CONNECT_DEFERRED);

		LifeTimer->set_wait_time(1);
		LifeTimer->start();
	}

	connect("body_entered", callable_mp(this, &Projectile::BodyEntered), CONNECT_DEFERRED);
}

void Projectile::_physics_process(double delta) {
	Vector2 curGPos = get_global_position();
	Vector2 newGPos = curGPos + (get_global_transform().columns[0] * (Speed * delta));
	set_global_position(newGPos);
}

void Projectile::BodyEntered(Node2D* body) {
	LifeTimer->stop();
	Remove();
}

void Projectile::Remove() {
	queue_free();
}
