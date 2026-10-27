#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

using namespace godot;

class Crosshair : public Node2D {
	GDCLASS(Crosshair, Node2D)

public:
	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void UpdateCrosshairSpreadTarget(double spread);

protected:
	TextureRect* CHUp { nullptr };
	TextureRect* CHDown { nullptr };
	TextureRect* CHRight { nullptr };
	TextureRect* CHLeft { nullptr };

	float SpreadTarget { 0.0f };

	static void _bind_methods();

private:

};
