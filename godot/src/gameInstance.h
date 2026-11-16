#pragma once

#include <cstdint>
#include <memory>

#include <godot_cpp/classes/resource_loader.hpp>

#include "gun/gunDefinition.h"
#include "gun/gunDropped.h"

using namespace godot;

class World;
class RunManager;
class Player;
class Gun;
class Enemy;

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

	void RegisterWorld(World* world, RunManager* rm);
	void RegisterPlayer(Player* player);
	Gun* GenerateNakedGun(int type, int level);
	Gun* GenerateStarterPistol();
	void CopyEquippedGunToDrop(Gun* gun, Vector2 position);
	Gun* CopyDroppedGunToEquip(GunDropped* dgun);

	std::shared_ptr<GunDefinition> GenerateGunDef(int type, int level) const;
	void GenerateAndDropGun(int type, int level, Node2D* parent);

	void TestSpawnEnemy();
	void TestSpawnWave(int num);

	void ShowCursor();
	void HideCursor();

	void SpawnDamageText(Vector2 position, double damage, EElement element);

	void EnemyDeath(Enemy* enemy);
	void SpawnRandomAmmoPickup(Vector2 position);

	World* const GetWorld() const;
	RunManager* const GetRunManager() const;
	Player* const GetPlayer() const;

protected:
	bool HasBeenInitialised { false };

	World* GWorld { nullptr };
	RunManager* GRunManager { nullptr };
	Player* GPlayer { nullptr };
	ResourceLoader* ResLoader { nullptr };

private:
	GameInstance() {}

};
