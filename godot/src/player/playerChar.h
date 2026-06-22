#pragma once

// #include <godot_cpp/classes/character_body2d.hpp>
#include "character.h"

using namespace godot;

class PlayerController;
class Gun;

constexpr int32_t PlayerNumGunSlots = 3;

class Player : public Character {
	GDCLASS(Player, Character)

public:
	Player();
	~Player() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void SetController(PlayerController* controller);
	PlayerController* GetController() const;

	void SetGunInSlot(int32_t slot, Gun* gun);
	Gun* GetGunInSlot(int32_t slot) const;
	void SetCurrentGun(Gun* gun);
	Gun* GetCurrentGun();

	void SwitchToGunInSlot(int32_t slot);
	
protected:
	static void _bind_methods();

	PlayerController* Controller = nullptr;

	Gun* GunSlots[PlayerNumGunSlots];

private:

};
