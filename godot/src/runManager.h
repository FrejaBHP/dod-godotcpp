#pragma once

#include <godot_cpp/classes/node.hpp>
#include "room/roomBase.h"
#include "room/roomExit.h"

using namespace godot;

class RunManager : public Node {
	GDCLASS(RunManager, Node)

public:
	RoomRewardsInfo RewardsInfo;

	int CurrentRoomNumber { 0 };
	int CurrentFloorNumber { 0 };
	int CurrentAreaLevel { 1 };

	void _ready() override;

	void StartRun();
	void CreateFloorStartRoom();

	void RollNextRoomRewards(RoomBase* room);
	void SetNextRoomReward(RoomExit* exit);
	void SpawnRoomRewards(RoomBase* room);

	void BindRoom(RoomBase* room);
	void OnRoomInitialised(RoomBase* room);
	void OnRoomFinished(RoomBase* room);
	void OnRoomExited(RoomBase* room, RoomExit* exit);

protected:
	bool NextRoomIsBoss { false };

	static void _bind_methods();

private:


};
