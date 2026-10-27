#include "map/mapBase.h"
#include "gameInstance.h"
#include "world.h"
#include "enemies/enemyController.h"
#include "enemies/ai/enemyAIComponent.h"

#include <godot_cpp/classes/timer.hpp>

void MapBase::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetHasExits", "p_HasExits"), &MapBase::SetHasExits);
	ClassDB::bind_method(D_METHOD("GetHasExits"), &MapBase::GetHasExits);
	ClassDB::bind_method(D_METHOD("SetPreExitLayers", "p_preExitLayers"), &MapBase::SetPreExitLayers);
	ClassDB::bind_method(D_METHOD("GetPreExitLayers"), &MapBase::GetPreExitLayers);
	ClassDB::bind_method(D_METHOD("SetPostExitLayers", "p_postExitLayers"), &MapBase::SetPostExitLayers);
	ClassDB::bind_method(D_METHOD("GetPostExitLayers"), &MapBase::GetPostExitLayers);
	ClassDB::bind_method(D_METHOD("OnEnemyDied"), &MapBase::OnEnemyDied);
	ClassDB::bind_method(D_METHOD("OnMapFinished"), &MapBase::OnMapFinished);
	ClassDB::bind_method(D_METHOD("OnExitEntered"), &MapBase::OnExitEntered);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "hasExits"), "SetHasExits", "GetHasExits");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "preExitLayers", PROPERTY_HINT_ARRAY_TYPE, "NodePath"), "SetPreExitLayers", "GetPreExitLayers");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "postExitLayers", PROPERTY_HINT_ARRAY_TYPE, "NodePath"), "SetPostExitLayers", "GetPostExitLayers");
	ADD_SIGNAL(MethodInfo("map_finished"));
}

void MapBase::_ready() {
	TileMapLayers = get_node<Node2D>("TileMapLayers");
	NavRegion = TileMapLayers->get_node<NavigationRegion2D>("TMNavRegion");

	EnemiesNode = get_node<Node2D>("Enemies");
	EnemyCount = EnemiesNode->get_child_count();

	for (size_t i = 0; i < EnemiesNode->get_child_count(); i++) {
		EnemyGun* enemy = static_cast<EnemyGun*>(EnemiesNode->get_child(i));
		enemy->connect("enemy_died", callable_mp(this, &MapBase::OnEnemyDied));

		//EnemyAIComponent* comp = enemy->Controller->GetAIComponent();
		//comp->Disable();
	}

	ExitsNode = get_node<Node2D>("Exits");

	for (size_t i = 0; i < ExitsNode->get_child_count(); i++) {
		Area2D* exit = static_cast<Area2D*>(ExitsNode->get_child(i));
		exit->add_to_group(vformat("exit%d", i));
		exit->connect("body_entered", callable_mp(this, &MapBase::OnExitEntered).bind(exit));

		Exits.append(exit);
	}

	PlayerStartMarker = get_node<Node2D>("PlayerStartMarker");

	Timer* timer = get_node<Timer>("Timer");
	timer->connect("timeout", callable_mp(this, &MapBase::OnMapFinished));
}

void MapBase::SetHasExits(const bool hasExits) {
	HasExits = hasExits;
}

bool MapBase::GetHasExits() const {
	return HasExits;
}

void MapBase::SetPreExitLayers(const TypedArray<NodePath>& preExitLayers) {
	PreExitLayers = preExitLayers;
}

TypedArray<NodePath> MapBase::GetPreExitLayers() const {
	return PreExitLayers;
}

void MapBase::SetPostExitLayers(const TypedArray<NodePath>& postExitLayers) {
	PostExitLayers = postExitLayers;
}

TypedArray<NodePath> MapBase::GetPostExitLayers() const {
	return PostExitLayers;
}

NavigationRegion2D* const MapBase::GetNavRegion() const {
	return NavRegion;
}

void MapBase::OnEnemyDied(EnemyGun* enemy) {
	--EnemyCount;

	if (EnemyCount == 0) {
		OnMapFinished();
	}
}

void MapBase::OnMapFinished() {
	if (HasExits) {
		OpenExits();
	}
}

void MapBase::OpenExits() {
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

void MapBase::OnExitEntered(Node2D* body, Area2D* exit) {
	print_line(vformat(exit->get_name()));

	GameInstance::GetInstance().GetWorld()->ResetTestMap();
}
