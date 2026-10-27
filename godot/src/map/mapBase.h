#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/navigation_region2d.hpp>
#include <godot_cpp/classes/tile_map_layer.hpp>

#include "enemies/enemyGun.h"

using namespace godot;

class MapBase : public Node2D {
	GDCLASS(MapBase, Node2D)

public:
	Node2D* PlayerStartMarker { nullptr };

	virtual void _ready() override;

	void SetHasExits(const bool hasExits);
	bool GetHasExits() const;

	void SetPreExitLayers(const TypedArray<NodePath>& preExitLayers);
	TypedArray<NodePath> GetPreExitLayers() const;

	void SetPostExitLayers(const TypedArray<NodePath>& postExitLayers);
	TypedArray<NodePath> GetPostExitLayers() const;

	NavigationRegion2D* const GetNavRegion() const;

protected:
	Node2D* TileMapLayers { nullptr };
	NavigationRegion2D* NavRegion { nullptr };

	Node2D* EnemiesNode { nullptr };
	int EnemyCount { 0 };

	bool HasExits { true };
	Node2D* ExitsNode { nullptr };
	Vector<Area2D*> Exits;

	TypedArray<NodePath> PreExitLayers;
	TypedArray<NodePath> PostExitLayers;

	static void _bind_methods();
	void OnEnemyDied(EnemyGun* enemy);
	void OnMapFinished();
	void OpenExits();
	void OnExitEntered(Node2D* body, Area2D* exit);

private:

};
