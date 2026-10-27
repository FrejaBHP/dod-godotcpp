#include "gun/gun.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include <godot_cpp/classes/audio_stream_randomizer.hpp>

#include "character.h"
#include "player/playerController.h"
#include "projectiles/projectile.h"
#include "gameInstance.h"
#include "world.h"
#include "shared/utility.h"


void Gun::_bind_methods() {
	ADD_SIGNAL(MethodInfo("gun_fired"));
	ADD_SIGNAL(MethodInfo("gun_reload_ended"));

	ClassDB::bind_method(D_METHOD("TryPrimaryFire"), &Gun::TryPrimaryFire);
	ClassDB::bind_method(D_METHOD("PrimaryFire"), &Gun::PrimaryFireSingle);
	ClassDB::bind_method(D_METHOD("TryReload"), &Gun::TryReload);
	ClassDB::bind_method(D_METHOD("Reload"), &Gun::FinishReload);
}

// Finished kaldes, når én lyd er færdig med at spille. Det gælder ikke, når lyd bliver overskrevet
// Kan bruge is_playing() til at se, om der stadig er andre lyde i gang med polyphony - returnerer 0 ved slut på sidste lyd
void Gun::TestFunction() {
	print_line(vformat("Stream finished. Still playing? %d", (int)StreamPlayer->is_playing()));
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

	// Audio
	StreamPlayer = get_node<AudioStreamPlayer2D>("GunAudioStream");
	StreamPlayer->set_max_polyphony(5);
	//StreamPlayer->connect("finished", callable_mp(this, &Gun::TestFunction));

	StreamRandomiser.instantiate();
	StreamPlayer->set_stream(StreamRandomiser);

	StreamRandomiser->set_random_pitch(1.05f);
	StreamRandomiser.ptr()->add_stream(0, GunDef->GetPriFireAudio());
}

void Gun::_process(double delta) {

}

void Gun::_physics_process(double delta) {
	if (MarkedForDeletion) {
		if (!StreamPlayer->is_playing()) {
			queue_free();
		}

		return;
	}
	
	if (IsFiringBurst) {

	}
}

void Gun::BuildGun(std::shared_ptr<GunDefinition> gundef) {
	GunDef = gundef;
	MagAmmo = GunDef->MagSize;
}

bool Gun::IsReadyToFire(steady_clock::time_point now) const {
	long long difference = duration_cast<milliseconds>(now - LastFired).count();

	if (difference > (GunDef->FireTime / OwningCharacter->FireRateMod)) {
		return true;
	}
	else {
		return false;
	}
}

bool Gun::TryPrimaryFire(const Vector2 from, const Vector2 towards) {
	if (MagAmmo < 1) {
		return false;
	}

	//steady_clock::time_point now = high_resolution_clock::now();
	steady_clock::time_point now = steady_clock::now();


	if (IsReadyToFire(now)) {
		LastFired = now;
		PrimaryFireSingle(from, towards);

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
		World* world = GameInstance::GetInstance().GetWorld();

		if (world) {
			for (size_t i = 0; i < GunDef->ProjectileCount; i++) {
				Projectile* proj = static_cast<Projectile*>(ProjectileScene->instantiate());
				// Only one until multiple sources exist
				proj->DmgInfo.DamageInstances.push_back({ GunDef->Element->Element, GunDef->Damage });
				proj->SetSpeed((float)GunDef->ProjectileSpeed);
				world->add_child(proj);

				proj->UpdateMasks(OwningCharacter->Alignment);

				proj->set_global_position(from);
				proj->look_at(towards);

				AdjustFiringAngle(proj);
			}

			if (StreamRandomiser->get_streams_count() > 0) {
				StreamPlayer->play();
			}

			if (GunDef->ShotCost > MagAmmo) {
				if (OwnerReserveAmmo) {
					*OwnerReserveAmmo -= MagAmmo;
				}
				
				MagAmmo = 0;
			}
			else {
				if (OwnerReserveAmmo) {
					*OwnerReserveAmmo -= GunDef->ShotCost;
				}

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
		World* world = GameInstance::GetInstance().GetWorld();

		if (world) {
			for (size_t b = 0; b < GunDef->BurstCount; b++) {
				if (MagAmmo == 0) {
					break;
				}

				for (size_t i = 0; i < GunDef->ProjectileCount; i++) {
					Projectile* proj = static_cast<Projectile*>(ProjectileScene->instantiate());
					proj->Damage = GunDef->Damage;
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
	if (MagAmmo == GunDef->MagSize) {
		return false;
	}

	if (OwnerReserveAmmo && (*OwnerReserveAmmo > 0 || *OwnerReserveAmmo == -1) && *OwnerReserveAmmo > MagAmmo) {
		StartReload();
		return true;
	}
	else if (!OwnerReserveAmmo) { // Special case for NPCs, as they don't use from their ammo pool. Temporary
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
	if (OwnerReserveAmmo) {
		// When there is enough ammo for a full reload
		if (*OwnerReserveAmmo >= GunDef->MagSize) {
			int32_t prevAmmo = MagAmmo;

			MagAmmo = GunDef->MagSize;
			//*reserveAmmo -= (GunDef->MagSize - prevAmmo);
		}
		// When there is less than a magazine left of reserve ammo
		else if (*OwnerReserveAmmo > 0) {
			MagAmmo = *OwnerReserveAmmo;
			//*reserveAmmo = 0;
		}
		else if (*OwnerReserveAmmo == -1) {
			MagAmmo = GunDef->MagSize;
		}
	}
	else {
		MagAmmo = GunDef->MagSize;
	}

	emit_signal("gun_reload_ended");
}

steady_clock::time_point Gun::GetLastFired() const {
	return LastFired;
}

// Queues the Gun object for freeing when ready. This includes when sounds are no longer playing
void Gun::FreeGun() {
	if (get_parent()) {
		//get_parent()->remove_child(this);
		reparent(GameInstance::GetInstance().GetWorld(), false);
	}
	MarkedForDeletion = true;
}
