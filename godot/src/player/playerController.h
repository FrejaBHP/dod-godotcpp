#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

using namespace godot;

class Player;
class Gun;

class PlayerController : public Node {
	GDCLASS(PlayerController, Node)

public:
	PlayerController();
	~PlayerController() = default;

	void _input(const Ref<InputEvent>& p_event) override;
	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	Vector2 ProcessMovementInput();

	void SetPlayer(Player* player);
	Player* GetPlayer() const;

	Node2D* GetCrosshair();

	void SetCurrentGunSlot(int32_t slot);
	void UpdateAmmoLabel();

protected:
	static void _bind_methods();

	Player* ControlledPlayer = nullptr;
	Node2D* PlayerCrosshair = nullptr;
	Label* DebugLabel = nullptr;
	Camera2D* PlayerCamera = nullptr;

	// Temp
	Label* AmmoLabel = nullptr;

	bool isLMBHeld = false;
	bool isRMBHeld = false;

	int32_t CurrentGunSlot { 0 };

private:

};
