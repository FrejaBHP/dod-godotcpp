#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

#include "gun/gun.h"
#include "player/playerChar.h"
#include "player/playerController.h"
#include "projectiles/projectile.h"
#include "shared/utility.h"

using namespace godot;

void Gun::_bind_methods() {
	ClassDB::bind_method(D_METHOD("TryPrimaryFire"), &Gun::TryPrimaryFire);
	ClassDB::bind_method(D_METHOD("PrimaryFire"), &Gun::PrimaryFire);
	ClassDB::bind_method(D_METHOD("TryReload"), &Gun::TryReload);
	ClassDB::bind_method(D_METHOD("Reload"), &Gun::Reload);
}

Gun::Gun() {

}

void Gun::_ready() {
	LastFired = high_resolution_clock::now();

	ResourceLoader* loader = ResourceLoader::get_singleton();
	ProjectileScene = loader->load("res://projectile.tscn");
}

void Gun::_process(double delta) {

}

void Gun::_physics_process(double delta) {

}

void Gun::BuildGun(std::shared_ptr<GunDefinition> gundef) {
	GunDef = gundef;
	MagAmmo = GunDef->MagSize;
}


bool Gun::TryPrimaryFire() {
	if (MagAmmo < 1) {
		return false;
	}

	steady_clock::time_point now = high_resolution_clock::now();

	long long difference = duration_cast<milliseconds>(now - LastFired).count();

	if (difference > GunDef->FireTime) {
		PrimaryFire();
		LastFired = now;
		return true;
	}
}

void Gun::PrimaryFire() {
	if (ProjectileScene->can_instantiate()) {
		Node2D* world = get_tree()->get_root()->get_node<Node2D>("World");

		if (world) {
			for (size_t i = 0; i < GunDef->ProjectileCount; i++) {
				Projectile* proj = static_cast<Projectile*>(ProjectileScene->instantiate());
				world->add_child(proj);

				proj->set_global_position(OwningPlayer->get_global_position());
				proj->look_at(OwningPlayer->GetController()->GetCrosshair()->get_global_position());

				AdjustFiringAngle(proj);
			}
			
			MagAmmo -= GunDef->ShotCost;

			OwningPlayer->GetController()->ApplyRecoil();
			OwningPlayer->GetController()->UpdateAmmoLabel();
		}
	}
}

void Gun::AdjustFiringAngle(Node2D* node) {
	double maxAngle = OwningPlayer->Inaccuracy + GunDef->Spread;
	double randomAngle = GetRandomDouble(-maxAngle, maxAngle);

	double rad = godot::Math::deg_to_rad(randomAngle);
	node->rotate((float)rad);
}

bool Gun::TryReload() {
	// Dirty hacky stuff
	int32_t reserveAmmo;
	if (GunDef->GunType == EGunType::Pistol) {
		reserveAmmo = OwningPlayer->PistolAmmo;
	}
	else if (GunDef->GunType == EGunType::SMG) {
		reserveAmmo = OwningPlayer->SMGAmmo;
	}
	else {
		reserveAmmo = OwningPlayer->ARAmmo;
	}


	if (MagAmmo == GunDef->MagSize) {
		return false;
	}

	if (reserveAmmo > 0) {
		Reload();
		return true;
	}
	else {
		return false;
	}
}


void Gun::Reload() {
	// Dirty hacky stuff
	int32_t* reserveAmmo;
	if (GunDef->GunType == EGunType::Pistol) {
		reserveAmmo = &OwningPlayer->PistolAmmo;
	}
	else if (GunDef->GunType == EGunType::SMG) {
		reserveAmmo = &OwningPlayer->SMGAmmo;
	}
	else {
		reserveAmmo = &OwningPlayer->ARAmmo;
	}

	// When there is enough ammo for a full reload
	if (*reserveAmmo >= GunDef->MagSize) {
		int32_t prevAmmo = MagAmmo;

		MagAmmo = GunDef->MagSize;
		*reserveAmmo -= (GunDef->MagSize - prevAmmo);
	}
	// When there is less than a magazine left of reserve ammo
	else if (*reserveAmmo > 0) {
		MagAmmo = *reserveAmmo;
		*reserveAmmo = 0;
	}

	OwningPlayer->GetController()->UpdateAmmoLabel();
}
