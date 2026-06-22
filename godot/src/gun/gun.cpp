#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

#include "gun/gun.h"
#include "character.h"
#include "player/playerController.h"
#include "projectiles/projectile.h"
#include "shared/utility.h"

using namespace godot;

void Gun::_bind_methods() {
	ADD_SIGNAL(MethodInfo("gun_fired"));
	ADD_SIGNAL(MethodInfo("gun_reload_ended"));

	ClassDB::bind_method(D_METHOD("TryPrimaryFire"), &Gun::TryPrimaryFire);
	ClassDB::bind_method(D_METHOD("PrimaryFire"), &Gun::PrimaryFireSingle);
	ClassDB::bind_method(D_METHOD("TryReload"), &Gun::TryReload);
	ClassDB::bind_method(D_METHOD("Reload"), &Gun::FinishReload);
}

Gun::Gun() {

}

void Gun::_ready() {
	LastFired = high_resolution_clock::now();

	ResourceLoader* loader = ResourceLoader::get_singleton();
	ProjectileScene = loader->load("res://projectile.tscn");

	ReloadTimer = get_node<Timer>("ReloadTimer");
	ReloadTimer->connect("timeout", callable_mp(this, &Gun::ReloadTimerTimeout));
	ReloadTimer->set_one_shot(true);
}

void Gun::_process(double delta) {

}

void Gun::_physics_process(double delta) {
	if (IsFiringBurst) {

	}
}

void Gun::BuildGun(std::shared_ptr<GunDefinition> gundef) {
	GunDef = gundef;
	MagAmmo = GunDef->MagSize;
}


bool Gun::TryPrimaryFire(const Vector2 from, const Vector2 towards) {
	if (MagAmmo < 1) {
		return false;
	}

	steady_clock::time_point now = high_resolution_clock::now();

	long long difference = duration_cast<milliseconds>(now - LastFired).count();

	if (difference > GunDef->FireTime) {
		PrimaryFireSingle(from, towards);
		LastFired = now;

		/*
		if (GunDef->FireMode != EFireMode::Burst) {
			PrimaryFireSingle(from, towards);
			LastFired = now;
		}
		else {
			PrimaryFireBurst(from, towards);
		}
		*/
		
		return true;
	}

	return false;
}

void Gun::PrimaryFireSingle(const Vector2 from, const Vector2 towards) {
	if (ProjectileScene->can_instantiate()) {
		Node2D* world = get_tree()->get_root()->get_node<Node2D>("World");

		if (world) {
			for (size_t i = 0; i < GunDef->ProjectileCount; i++) {
				Projectile* proj = static_cast<Projectile*>(ProjectileScene->instantiate());
				proj->SetSpeed((float)GunDef->ProjectileSpeed);
				world->add_child(proj);

				proj->UpdateMasks(OwningCharacter->Alignment);

				proj->set_global_position(from);
				proj->look_at(towards);

				AdjustFiringAngle(proj);
			}

			if (GunDef->ShotCost > MagAmmo) {
				MagAmmo = 0;
			}
			else {
				MagAmmo -= GunDef->ShotCost;
			}

			emit_signal("gun_fired");
		}
	}
}

// Skal omtænkes, brug ikke. Gør måske async?
// Ellers så lav en metode (gerne virtuel) i Character, hvor man kan få position og mål, og så kør logik i physics_process
void Gun::PrimaryFireBurst(const Vector2 from, const Vector2 towards) {
	if (ProjectileScene->can_instantiate()) {
		Node2D* world = get_tree()->get_root()->get_node<Node2D>("World");

		if (world) {
			for (size_t b = 0; b < GunDef->BurstCount; b++) {
				if (MagAmmo == 0) {
					break;
				}

				for (size_t i = 0; i < GunDef->ProjectileCount; i++) {
					Projectile* proj = static_cast<Projectile*>(ProjectileScene->instantiate());
					proj->SetSpeed((float)GunDef->ProjectileSpeed);
					world->add_child(proj);

					proj->UpdateMasks(OwningCharacter->Alignment);

					proj->set_global_position(from);
					proj->look_at(towards);

					AdjustFiringAngle(proj);
				}

				if (GunDef->ShotCost > MagAmmo) {
					MagAmmo = 0;
				}
				else {
					MagAmmo -= GunDef->ShotCost;
				}

				emit_signal("gun_fired");
			}
		}
	}
}

void Gun::AdjustFiringAngle(Node2D* node) const {
	double maxAngle = OwningCharacter->Inaccuracy + GunDef->Spread;
	double randomAngle = GetRandomDouble(-maxAngle, maxAngle);

	double rad = godot::Math::deg_to_rad(randomAngle);
	node->rotate((float)rad);
}

bool Gun::TryReload() {
	// Dirty hacky stuff
	int32_t reserveAmmo;
	if (GunDef->GunType == EGunType::Pistol) {
		reserveAmmo = OwningCharacter->PistolAmmo;
	}
	else if (GunDef->GunType == EGunType::SMG) {
		reserveAmmo = OwningCharacter->SMGAmmo;
	}
	else {
		reserveAmmo = OwningCharacter->ARAmmo;
	}


	if (MagAmmo == GunDef->MagSize) {
		return false;
	}

	if (reserveAmmo > 0 || reserveAmmo == -1) {
		StartReload();
		return true;
	}
	else {
		return false;
	}
}

void Gun::StartReload() {
	ReloadTimer->start(GunDef->ReloadTime);
}

void Gun::ReloadTimerTimeout() {
	FinishReload();
}

void Gun::FinishReload() {
	// Dirty hacky stuff
	int32_t* reserveAmmo;
	if (GunDef->GunType == EGunType::Pistol) {
		reserveAmmo = &OwningCharacter->PistolAmmo;
	}
	else if (GunDef->GunType == EGunType::SMG) {
		reserveAmmo = &OwningCharacter->SMGAmmo;
	}
	else {
		reserveAmmo = &OwningCharacter->ARAmmo;
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
	else if (*reserveAmmo == -1) {
		MagAmmo = GunDef->MagSize;
	}

	emit_signal("gun_reload_ended");
}
