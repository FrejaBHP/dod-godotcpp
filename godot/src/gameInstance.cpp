#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/classes/node2d.hpp>

#include "gameInstance.h"
#include "player/playerChar.h"
#include "player/playerController.h"
#include "shared/utility.h"
#include "world.h"
#include "gun/gun.h"

using namespace godot;

void GameInstance::DebugSpawnGun(int32_t type) {
	std::shared_ptr<GunDefinition> gundef = std::make_shared<GunDefinition>();

	if (type == 0) {
		gundef->SetPistolStats();
	}
	else if (type == 1) {
		gundef->SetSMGStats();
	}
	else {
		gundef->SetARStats();
	}

	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> droppedScene = loader->load("res://gun_dropped.tscn");

	if (droppedScene->can_instantiate()) {
		//Node2D* world = get_tree()->get_root()->get_node<Node2D>("World");

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

	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> droppedScene = loader->load("res://gun_dropped.tscn");

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
	// NOTE: Will be replaced with a Gun scene eventually
	Gun* newGun = memnew(Gun);

	if (newGun) {
		newGun->BuildGun(dgun->GunDef);
		newGun->MagAmmo = newGun->GunDef->MetaMagAmmo;
		GPlayer->add_child(newGun);
	}

	return newGun;
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
