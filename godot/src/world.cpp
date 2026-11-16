#include "world.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "runManager.h"
#include "player/playerChar.h"

using namespace godot;


void World::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetCurrentRoom", "p_Room"), &World::SetCurrentRoom);
	ClassDB::bind_method(D_METHOD("GetCurrentRoom"), &World::GetCurrentRoom);
}

World::World() {

}

void World::_ready() {
	WRunManager = get_node<RunManager>("RunManager");
	RoomContainerNode = get_node<Node2D>("RoomConNode");

	GameInstance& gi = GameInstance::GetInstance();

	gi.Init();
	gi.RegisterWorld(this, WRunManager);
	gi.HideCursor();

	//ResetTestRoom();
	WRunManager->StartRun();
}

void World::_physics_process(double delta) {

}

// Relegate to run manager class later, whenever it will cease to not exist
void World::ResetTestRoom() {
	if (RoomContainerNode->get_child_count() > 0) {
		RoomBase* oldRoom = static_cast<RoomBase*>(RoomContainerNode->get_child(0));
		GameInstance::GetInstance().GetPlayer()->set_global_position(oldRoom->PlayerStartMarker->get_global_position());

		CurrentRoom = nullptr;
		oldRoom->queue_free();
	}

	Ref<PackedScene> testRoomScene = ResourceLoader::get_singleton()->load("res://scenes/rooms/room_test.tscn");
	if (testRoomScene->can_instantiate()) {
		RoomBase* room = static_cast<RoomBase*>(testRoomScene->instantiate());

		RoomContainerNode->call_deferred("add_child", room);
		call_deferred("SetCurrentRoom", room);
	}
}

void World::SetCurrentRoom(RoomBase* room) {
	CurrentRoom = room;
}

RoomBase* World::GetCurrentRoom() const {
	return CurrentRoom;
}

Node2D* const World::GetRoomContainerNode() const {
	return RoomContainerNode;
}
