#include "room/roomBase.h"
#include "gameInstance.h"
#include "world.h"
#include "runManager.h"
#include "enemies/enemyController.h"
#include "enemies/ai/enemyAIComponent.h"

#include <godot_cpp/classes/timer.hpp>

void RoomBase::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetHasExits", "p_HasExits"), &RoomBase::SetHasExits);
	ClassDB::bind_method(D_METHOD("GetHasExits"), &RoomBase::GetHasExits);
	ClassDB::bind_method(D_METHOD("SetPreExitLayers", "p_preExitLayers"), &RoomBase::SetPreExitLayers);
	ClassDB::bind_method(D_METHOD("GetPreExitLayers"), &RoomBase::GetPreExitLayers);
	ClassDB::bind_method(D_METHOD("SetPostExitLayers", "p_postExitLayers"), &RoomBase::SetPostExitLayers);
	ClassDB::bind_method(D_METHOD("GetPostExitLayers"), &RoomBase::GetPostExitLayers);
	ClassDB::bind_method(D_METHOD("SetInstant", "p_Instant"), &RoomBase::SetFinishesInstantly);
	ClassDB::bind_method(D_METHOD("GetInstant"), &RoomBase::GetFinishesInstantly);
	ClassDB::bind_method(D_METHOD("OnEnemyDied"), &RoomBase::OnEnemyDied);
	ClassDB::bind_method(D_METHOD("OnRoomFinished"), &RoomBase::OnRoomFinished);
	ClassDB::bind_method(D_METHOD("OnExitEntered"), &RoomBase::OnExitEntered);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "hasExits"), "SetHasExits", "GetHasExits");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "finishes_instantly"), "SetInstant", "GetInstant");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "preExitLayers", PROPERTY_HINT_ARRAY_TYPE, "NodePath"), "SetPreExitLayers", "GetPreExitLayers");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "postExitLayers", PROPERTY_HINT_ARRAY_TYPE, "NodePath"), "SetPostExitLayers", "GetPostExitLayers");

	// For when the room has run its _ready() routine. Allows for deferred calls, such as instantiation, to happen first
	ADD_SIGNAL(MethodInfo("room_initialised", PropertyInfo(Variant::OBJECT, "room")));
	// When the objective of a room is complete. Tied to opening exits and rolling future rewards
	ADD_SIGNAL(MethodInfo("room_finished", PropertyInfo(Variant::OBJECT, "room")));
	// When an exit has been taken. Tied to reward paths, game progression and cleanup
	ADD_SIGNAL(MethodInfo("room_exited", PropertyInfo(Variant::OBJECT, "room"), PropertyInfo(Variant::OBJECT, "exit")));
}

void RoomBase::_ready() {
	TileMapLayers = get_node<Node2D>("TileMapLayers");
	NavRegion = TileMapLayers->get_node<NavigationRegion2D>("TMNavRegion");

	ItemsContainerNode = get_node<Node2D>("Items");

	EnemiesNode = get_node<Node2D>("Enemies");
	EnemyCount = EnemiesNode->get_child_count();

	for (size_t i = 0; i < EnemiesNode->get_child_count(); i++) {
		Enemy* enemy = static_cast<Enemy*>(EnemiesNode->get_child(i));
		enemy->connect("enemy_died", callable_mp(this, &RoomBase::OnEnemyDied));

		//EnemyAIComponent* comp = enemy->Controller->GetAIComponent();
		//comp->Disable();
	}

	ExitsNode = get_node<Node2D>("Exits");

	for (size_t i = 0; i < ExitsNode->get_child_count(); i++) {
		RoomExit* exit = static_cast<RoomExit*>(ExitsNode->get_child(i));
		exit->add_to_group(vformat("exit%d", i));
		exit->connect("body_entered", callable_mp(this, &RoomBase::OnExitEntered).bind(exit));

		Exits.append(exit);
	}

	PlayerStartMarker = get_node<Node2D>("PlayerStartMarker");
	CentreMarker = get_node<Node2D>("CentreMarker");

	Timer* timer = get_node<Timer>("Timer");
	timer->connect("timeout", callable_mp(this, &RoomBase::OnRoomFinished));

	GameInstance::GetInstance().GetRunManager()->BindRoom(this);

	emit_signal("room_initialised", this);

	if (FinishesInstantly) {
		emit_signal("room_finished", this);
	}
}

void RoomBase::OnEnemyDied(Enemy* enemy) {
	--EnemyCount;

	if (!FinishesInstantly && EnemyCount == 0) {
		//OnMapFinished();
		emit_signal("room_finished", this);
	}
}

void RoomBase::OnRoomFinished() {
	if (HasExits) {
		OpenExits();
	}
}

void RoomBase::OpenExits() {
	for (size_t i = 0; i < PreExitLayers.size(); i++) {
		TileMapLayer* layer = get_node<TileMapLayer>(PreExitLayers[i]);
		layer->set_enabled(false);
	}

	for (size_t i = 0; i < PostExitLayers.size(); i++) {
		TileMapLayer* layer = get_node<TileMapLayer>(PostExitLayers[i]);
		layer->set_enabled(true);
	}

	for (size_t i = 0; i < Exits.size(); i++) {
		Exits[i]->set_monitoring(true);
	}
}

void RoomBase::OnExitEntered(Node2D* body, RoomExit* exit) {
	//print_line(vformat(exit->get_name()));
	emit_signal("room_exited", this, exit);

	//GameInstance::GetInstance().GetWorld()->ResetTestMap();
}

void RoomBase::SetHasExits(const bool hasExits) {
	HasExits = hasExits;
}

bool RoomBase::GetHasExits() const {
	return HasExits;
}

Node2D* const RoomBase::GetExitsNode() const {
	return ExitsNode;
}

void RoomBase::SetPreExitLayers(const TypedArray<NodePath>& preExitLayers) {
	PreExitLayers = preExitLayers;
}

TypedArray<NodePath> RoomBase::GetPreExitLayers() const {
	return PreExitLayers;
}

void RoomBase::SetPostExitLayers(const TypedArray<NodePath>& postExitLayers) {
	PostExitLayers = postExitLayers;
}

TypedArray<NodePath> RoomBase::GetPostExitLayers() const {
	return PostExitLayers;
}

NavigationRegion2D* const RoomBase::GetNavRegion() const {
	return NavRegion;
}

Node2D* const RoomBase::GetItemsNode() const {
	return ItemsContainerNode;
}

void RoomBase::SetFinishesInstantly(const bool instant) {
	FinishesInstantly = instant;
}

bool RoomBase::GetFinishesInstantly() const {
	return FinishesInstantly;
}
