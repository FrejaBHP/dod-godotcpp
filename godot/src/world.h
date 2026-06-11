#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include "gameInstance.h"

using namespace godot;

class World : public Node2D {
	GDCLASS(World, Node2D)

public:
	World();
	~World() = default;

	void _ready() override;
	void _physics_process(double delta) override;

protected:
	static void _bind_methods();

private:

};
