#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include "gun/gunDefinition.h"

using namespace godot;

class GunDropped : public Node2D {
	GDCLASS(GunDropped, Node2D)

public:
	GunDropped();
	~GunDropped() = default;

	void _ready() override;
	void _physics_process(double delta) override;

	GunDefinition* GunDef = nullptr;

protected:
	static void _bind_methods();

private:
};
