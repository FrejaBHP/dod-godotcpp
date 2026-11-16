#pragma once

#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

class Interactible : public Area2D {
	GDCLASS(Interactible, Area2D)

public:
	virtual void _ready() override;

	void Activate();

	void SetRepeatable(const bool repeatable);
	bool GetRepeatable() const;

protected:
	bool Repeatable { false };

	static void _bind_methods();

private:

};
