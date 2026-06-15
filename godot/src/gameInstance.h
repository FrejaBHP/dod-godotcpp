#pragma once

#include <cstdint>
#include <memory>

#include <godot_cpp/classes/resource_loader.hpp>

#include "gun/gunDefinition.h"
#include "gun/gunDropped.h"

using namespace godot;

class World;
class Player;
class Gun;

// https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern

class GameInstance {
public:
	static GameInstance& GetInstance() {
		static GameInstance instance;
		return instance;
	}

	GameInstance(GameInstance const&) = delete;
	void operator=(GameInstance const&) = delete;

	void Init();

	void RegisterWorld(World* world);
	void RegisterPlayer(Player* player);
	void DebugSpawnGun(int32_t type);
	void CopyEquippedGunToDrop(Gun* gun, Vector2 position);
	Gun* CopyDroppedGunToEquip(GunDropped* dgun);

	void GenerateAndDropGun(int32_t type);

	void ShowCursor();
	void HideCursor();

	World* GetWorld();
	Player* GetPlayer();

protected:
	World* GWorld = nullptr;
	Player* GPlayer = nullptr;
	ResourceLoader* ResLoader = nullptr;

	bool HasBeenInitialised { false };

private:
	GameInstance() {}

};
