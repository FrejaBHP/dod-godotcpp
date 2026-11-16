#include "runManager.h"
#include "gameInstance.h"
#include "world.h"
#include "player/playerChar.h"
#include "shared/utility.h"
#include "interactible/itemChest.h"

#include <godot_cpp/classes/packed_scene.hpp>

void RunManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("RollNextRoomRewards"), &RunManager::RollNextRoomRewards);
	ClassDB::bind_method(D_METHOD("SetNextRoomReward"), &RunManager::SetNextRoomReward);
	ClassDB::bind_method(D_METHOD("OnRoomFinished", "room"), &RunManager::OnRoomFinished);
	ClassDB::bind_method(D_METHOD("OnRoomExited", "room", "exit"), &RunManager::OnRoomExited);
}

void RunManager::_ready() {

}

void RunManager::StartRun() {
	CreateFloorStartRoom();
}

void RunManager::CreateFloorStartRoom() {
	Ref<PackedScene> startRoomScene = ResourceLoader::get_singleton()->load("res://scenes/rooms/room_start.tscn");
	World* world = GameInstance::GetInstance().GetWorld();

	if (startRoomScene->can_instantiate()) {
		RoomBase* room = static_cast<RoomBase*>(startRoomScene->instantiate());

		world->GetRoomContainerNode()->call_deferred("add_child", room);
		world->call_deferred("SetCurrentRoom", room);

		//GameInstance::GetInstance().GetPlayer()->set_global_position(room->PlayerStartMarker->get_global_position());
		//GameInstance::GetInstance().GetPlayer()->call_deferred("set_global_position", room->PlayerStartMarker->get_global_position());
	}
}

void RunManager::RollNextRoomRewards(RoomBase* room) {
	for (size_t i = 0; i < room->GetExitsNode()->get_child_count(); i++) {
		RoomRewardsInfo rInfo;
		RoomExit* exit = static_cast<RoomExit*>(room->GetExitsNode()->get_child(i));

		if (!NextRoomIsBoss) {
			rInfo.RewardClass = (ERewardClass)GetRandomInt(0, 1);
			
			if (rInfo.RewardClass == ERewardClass::Chest) {
				rInfo.ChestRewardClass = (EChestRewardClass)GetRandomInt(0, 1);
			}
		}
		else {
			rInfo.RewardClass = ERewardClass::Boss;
		}

		exit->SetRewardsInfo(rInfo);
	}
}

void RunManager::SetNextRoomReward(RoomExit* exit) {
	RewardsInfo = exit->GetRewardsInfo();
}

void RunManager::SpawnRoomRewards(RoomBase* room) {
	if (RewardsInfo.RewardClass == ERewardClass::Chest) {
		Ref<PackedScene> chestScene;
		ItemChest* ic;

		if (RewardsInfo.ChestRewardClass == EChestRewardClass::AmmoCrate) {
			chestScene = ResourceLoader::get_singleton()->load("res://scenes/obj/ammo_crate.tscn");
		}
		else if (RewardsInfo.ChestRewardClass == EChestRewardClass::EquipmentChest) { // temp
			chestScene = ResourceLoader::get_singleton()->load("res://scenes/obj/weapons_chest.tscn");
		}

		if (chestScene->can_instantiate()) {
			ic = static_cast<ItemChest*>(chestScene->instantiate());
			room->GetItemsNode()->add_child(ic);
			ic->set_global_position(room->CentreMarker->get_global_position());
		}
	}
}

void RunManager::BindRoom(RoomBase* room) {
	if (!room) {
		print_error("Can't bind room: room is null");
		return;
	}

	room->connect("room_initialised", callable_mp(this, &RunManager::OnRoomInitialised));
	room->connect("room_finished", callable_mp(this, &RunManager::OnRoomFinished));
	room->connect("room_exited", callable_mp(this, &RunManager::OnRoomExited));
}

void RunManager::OnRoomInitialised(RoomBase* room) {
	GameInstance::GetInstance().GetPlayer()->set_global_position(room->PlayerStartMarker->get_global_position());
}

void RunManager::OnRoomFinished(RoomBase* room) {
	//World* world = GameInstance::GetInstance().GetWorld();
	//MapBase* room = world->GetCurrentMap();

	if (room->GetHasExits()) {
		room->OpenExits();
		SpawnRoomRewards(room);
		RollNextRoomRewards(room);
	}
}

void RunManager::OnRoomExited(RoomBase* room, RoomExit* exit) {
	SetNextRoomReward(exit);

	World* world = GameInstance::GetInstance().GetWorld();
	//MapBase* room = world->GetCurrentMap();

	++CurrentAreaLevel;

	world->ResetTestRoom();
}
