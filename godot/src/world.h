#pragma once

#include <godot_cpp/classes/node2d.hpp>

using namespace godot;

class World : public Node2D {
	GDCLASS(World, Node2D)

public:
	World();
	~World() = default;

protected:
	static void _bind_methods();

private:

};
