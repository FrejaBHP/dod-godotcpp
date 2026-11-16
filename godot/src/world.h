#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include "gameInstance.h"
#include "room/roomBase.h"

using namespace godot;

class RunManager;

class World : public Node2D {
	GDCLASS(World, Node2D)

public:
	World();
	~World() = default;

	void _ready() override;
	void _physics_process(double delta) override;

	void ResetTestRoom();
	void SetCurrentRoom(RoomBase* room);
	RoomBase* GetCurrentRoom() const;
	Node2D* const GetRoomContainerNode() const;

protected:
	RunManager* WRunManager { nullptr };
	Node2D* RoomContainerNode { nullptr };
	RoomBase* CurrentRoom { nullptr };

	static void _bind_methods();

private:

};
