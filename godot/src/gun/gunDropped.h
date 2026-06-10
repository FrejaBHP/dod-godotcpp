#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include "gun/gunDefinition.h"

using namespace godot;

class GunDropped : public Node2D {
	GDCLASS(GunDropped, Node2D)

public:
	GunDropped();
	~GunDropped() = default;

	void _ready() override;
	void _physics_process(double delta) override;

	virtual void SetupDroppedGun(std::shared_ptr<GunDefinition> gundef);

	std::shared_ptr<GunDefinition> GunDef = nullptr;

	Sprite2D* Sprite = nullptr;
	Area2D* PickupArea = nullptr;

protected:
	static void _bind_methods();
	//void BodyEntered(Node2D* body);

private:
};
