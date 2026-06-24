#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/marker2d.hpp>

#include "gameInstance.h"
#include "player/playerChar.h"
#include "player/playerController.h"
#include "shared/utility.h"
#include "world.h"
#include "gun/gun.h"

#include "gun/types/gdSMG.h"
#include "gun/types/gdPistol.h"
#include "gun/types/gdRifle.h"

#include "gun/parts/catalogueMaterials.h"

#include "enemies/enemyGun.h"

using namespace godot;

void GameInstance::Init() {
	if (HasBeenInitialised) {
		return;
	}

	ResLoader = ResourceLoader::get_singleton();
}

std::shared_ptr<GunDefinition> GameInstance::GenerateGunDef(int32_t type) {
	std::shared_ptr<GunDefinition> gundef;

	if (type == -1) {
		type = GetRandomInt(0, 2);
	}

	if (type == 0) {
		gundef = std::make_shared<GDPistol>();
	}
	else if (type == 1) {
		gundef = std::make_shared<GDSMG>();
	}
	else {
		gundef = std::make_shared<GDRifle>();
	}

	int32_t manuIndex = GetRandomInt(0, (int32_t)EManufacturer::COUNT - 1);
	EManufacturer manufacturer = (EManufacturer)manuIndex;

	gundef->Material = GetRandomMaterial(manufacturer);
	gundef->Manufacturer = gundef->Material->Manufacturer;

	gundef->AssembleRandomGun();
	gundef->FinaliseGun();

	return gundef;
}

Gun* GameInstance::GenerateNakedGun(int32_t type) {
	std::shared_ptr<GunDefinition> gundef = GenerateGunDef(type);

	Ref<PackedScene> gunScene = ResLoader->load("res://gun.tscn");

	if (gunScene->can_instantiate()) {
		Gun* newGun = static_cast<Gun*>(gunScene->instantiate());
		newGun->BuildGun(gundef);
		newGun->MagAmmo = newGun->GunDef->MetaMagAmmo;

		return newGun;
	}

	return nullptr;
}

void GameInstance::GenerateAndDropGun(int32_t type) {
	std::shared_ptr<GunDefinition> gundef = GenerateGunDef(type);

	Ref<PackedScene> droppedScene = ResLoader->load("res://gun_dropped.tscn");

	if (droppedScene->can_instantiate()) {
		if (GWorld && GPlayer) {
			GunDropped* dGun = static_cast<GunDropped*>(droppedScene->instantiate());
			GWorld->add_child(dGun);
			dGun->SetupDroppedGun(gundef);

			dGun->set_global_position(GPlayer->get_global_position());
		}
	}
}

void GameInstance::CopyEquippedGunToDrop(Gun* gun, Vector2 position) {
	gun->GunDef->MetaMagAmmo = gun->MagAmmo;

	Ref<PackedScene> droppedScene = ResLoader->load("res://gun_dropped.tscn");

	if (droppedScene->can_instantiate()) {
		if (GWorld && GPlayer) {
			GunDropped* dGun = static_cast<GunDropped*>(droppedScene->instantiate());
			GWorld->add_child(dGun);
			dGun->SetupDroppedGun(gun->GunDef);

			dGun->set_global_position(position);
		}
	}
}

Gun* GameInstance::CopyDroppedGunToEquip(GunDropped* dgun) {
	Ref<PackedScene> gunScene = ResLoader->load("res://gun.tscn");

	if (gunScene->can_instantiate()) {
		if (GWorld && GPlayer) {
			Gun* newGun = static_cast<Gun*>(gunScene->instantiate());
			newGun->BuildGun(dgun->GunDef);
			newGun->MagAmmo = newGun->GunDef->MetaMagAmmo;
			GPlayer->add_child(newGun);

			return newGun;
		}
	}

	//FIXME: Lav bedre error handling
	print_error("Failed to instantiate Gun");

	return nullptr;
}

void GameInstance::TestSpawnEnemy() {
	if (!GWorld) {
		return;
	}

	Marker2D* testmarker = GWorld->get_node<Marker2D>("TestSpawnMarker");

	Ref<PackedScene> egScene = ResLoader->load("res://enemy_gun.tscn");

	if (egScene->can_instantiate()) {
		EnemyGun* eg = static_cast<EnemyGun*>(egScene->instantiate());
		GWorld->add_child(eg);
	}
}

void GameInstance::RegisterWorld(World* world) {
	GWorld = world;
}

void GameInstance::RegisterPlayer(Player* player) {
	GPlayer = player;
}

World* GameInstance::GetWorld() {
	return GWorld;
}

Player* GameInstance::GetPlayer() {
	return GPlayer;
}

void GameInstance::ShowCursor() {
	Input::get_singleton()->set_mouse_mode(Input::MouseMode::MOUSE_MODE_VISIBLE);
}

void GameInstance::HideCursor() {
	Input::get_singleton()->set_mouse_mode(Input::MouseMode::MOUSE_MODE_HIDDEN);
}
