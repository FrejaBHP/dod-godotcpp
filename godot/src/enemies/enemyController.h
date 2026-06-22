#pragma once

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Character;

class EnemyController : public Node {
	GDCLASS(EnemyController, Node)

public:
	void _ready() override;
	void _physics_process(double delta) override;

	void SetCharacter(Character* ch);

	Character* ControlledChar = nullptr;
	Character* Target = nullptr;

protected:
	static void _bind_methods();

private:

};
