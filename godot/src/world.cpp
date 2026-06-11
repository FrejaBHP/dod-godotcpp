#include "world.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

using namespace godot;

void World::_bind_methods() {

}

World::World() {

}

void World::_ready() {
	GameInstance::GetInstance().RegisterWorld(this);
}

void World::_physics_process(double delta) {

}
