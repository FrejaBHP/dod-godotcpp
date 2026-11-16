#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/navigation_region2d.hpp>
#include <godot_cpp/classes/tile_map_layer.hpp>

#include "room/roomExit.h"
#include "enemies/enemy.h"

using namespace godot;

class RoomBase : public Node2D {
	GDCLASS(RoomBase, Node2D)

public:
	Node2D* PlayerStartMarker { nullptr };
	Node2D* CentreMarker { nullptr };

	virtual void _ready() override;

	void OpenExits();

	Node2D* const GetItemsNode() const;

	void SetFinishesInstantly(const bool instant);
	bool GetFinishesInstantly() const;

	void SetHasExits(const bool hasExits);
	bool GetHasExits() const;
	Node2D* const GetExitsNode() const;

	void SetPreExitLayers(const TypedArray<NodePath>& preExitLayers);
	TypedArray<NodePath> GetPreExitLayers() const;

	void SetPostExitLayers(const TypedArray<NodePath>& postExitLayers);
	TypedArray<NodePath> GetPostExitLayers() const;

	NavigationRegion2D* const GetNavRegion() const;

protected:
	Node2D* TileMapLayers { nullptr };
	NavigationRegion2D* NavRegion { nullptr };

	Node2D* ItemsContainerNode { nullptr };
	Node2D* EnemiesNode { nullptr };

	int EnemyCount { 0 };
	bool FinishesInstantly { false };

	bool HasExits { true };
	Node2D* ExitsNode { nullptr };
	Vector<RoomExit*> Exits;

	TypedArray<NodePath> PreExitLayers;
	TypedArray<NodePath> PostExitLayers;

	static void _bind_methods();
	void OnEnemyDied(Enemy* enemy);
	void OnRoomFinished();
	
	void OnExitEntered(Node2D* body, RoomExit* exit);

private:

};
