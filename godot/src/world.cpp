#include "world.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "map/mapBase.h"
#include "player/playerChar.h"


using namespace godot;

void World::_bind_methods() {

}

World::World() {

}

void World::_ready() {
	MapNode = get_node<Node2D>("Map");

	GameInstance& gi = GameInstance::GetInstance();

	gi.Init();
	gi.RegisterWorld(this);
	gi.HideCursor();

	ResetTestMap();
}

void World::_physics_process(double delta) {

}

// Relegate to run manager class later, whenever it will cease to not exist
void World::ResetTestMap() {
	if (MapNode->get_child_count() > 0) {
		MapBase* oldMap = static_cast<MapBase*>(MapNode->get_child(0));
		GameInstance::GetInstance().GetPlayer()->set_global_position(oldMap->PlayerStartMarker->get_global_position());
		oldMap->queue_free();
	}

	Ref<PackedScene> testmapScene = ResourceLoader::get_singleton()->load("res://scenes/maps/map_test.tscn");
	if (testmapScene->can_instantiate()) {
		MapBase* map = static_cast<MapBase*>(testmapScene->instantiate());

		//MapNode->add_child(map);
		MapNode->call_deferred("add_child", map);
		
	}
}
