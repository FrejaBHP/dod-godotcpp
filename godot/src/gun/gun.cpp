#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

#include "gun/gun.h"
#include "player/playerChar.h"
#include "player/playerController.h"
#include "projectiles/projectile.h"

using namespace godot;

void Gun::_bind_methods() {
	ClassDB::bind_method(D_METHOD("TryPrimaryFire"), &Gun::TryPrimaryFire);
	ClassDB::bind_method(D_METHOD("PrimaryFire"), &Gun::PrimaryFire);
	ClassDB::bind_method(D_METHOD("TryReload"), &Gun::TryReload);
	ClassDB::bind_method(D_METHOD("Reload"), &Gun::Reload);
	ClassDB::bind_method(D_METHOD("PartialReload"), &Gun::PartialReload);
}

Gun::Gun() {

}

void Gun::_ready() {
	LastFired = high_resolution_clock::now();

	ResourceLoader* loader = ResourceLoader::get_singleton();
	ProjectileScene = loader->load("res://projectile.tscn");

	MagSize = 8;
	MagAmmo = MagSize;

	MaxAmmo = 32;
	ReserveAmmo = MaxAmmo;
}

void Gun::_process(double delta) {

}

void Gun::_physics_process(double delta) {

}

bool Gun::TryPrimaryFire() {
	if (MagAmmo < 1) {
		return false;
	}

	steady_clock::time_point now = high_resolution_clock::now();

	long long difference = duration_cast<milliseconds>(now - LastFired).count();

	if (difference > 100) {
		PrimaryFire();
		LastFired = now;
		return true;
	}
}

void Gun::PrimaryFire() {
	if (ProjectileScene->can_instantiate()) {
		Node2D* world = get_tree()->get_root()->get_node<Node2D>("World");

		if (world) {
			Projectile* proj = static_cast<Projectile*>(ProjectileScene->instantiate());
			world->add_child(proj);

			proj->set_global_position(OwningPlayer->get_global_position());
			proj->look_at(OwningPlayer->GetController()->GetCrosshair()->get_global_position());

			MagAmmo -= 1;

			OwningPlayer->GetController()->UpdateAmmoLabel();
		}
	}
}

bool Gun::TryReload() {
	if (MagAmmo == MagSize) {
		return false;
	}

	if (ReserveAmmo >= MagSize) {
		Reload();
		return true;
	}
	else if (ReserveAmmo > 0) {
		PartialReload();
		return true;
	}
	else {
		return false;
	}
}

void Gun::Reload() {
	MagAmmo = MagSize;
	ReserveAmmo -= MagSize;
	OwningPlayer->GetController()->UpdateAmmoLabel();
}

void Gun::PartialReload() {
	MagAmmo = ReserveAmmo;
	ReserveAmmo = 0;
	OwningPlayer->GetController()->UpdateAmmoLabel();
}
