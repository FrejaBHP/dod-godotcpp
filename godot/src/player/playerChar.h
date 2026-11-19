#pragma once

// #include <godot_cpp/classes/character_body2d.hpp>
#include "character.h"

using namespace godot;

class PlayerController;
class Gun;

constexpr int32_t PlayerNumGunSlots = 3;

class Player : public Character {
	GDCLASS(Player, Character)

friend PlayerController;

public:
	Player();
	~Player() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void SetController(PlayerController* controller);
	PlayerController* GetController() const;

	// Assigns gun to given gun slot and sets gun's reference to the player
	void SetGunInSlot(int32_t slot, Gun* gun);
	Gun* GetGunInSlot(int32_t slot) const;

	// Sets the gun referenced by CurrentGun
	void SetCurrentGun(Gun* gun);
	Gun* GetCurrentGun();

	// If gun exists, sets CurrentGun and swaps the wielded gun to the one in the given slot
	void SwitchToGunInSlot(int32_t slot, bool ignoreNullptr);
	
protected:
	PlayerController* Controller = nullptr;
	Gun* GunSlots[PlayerNumGunSlots];

	double MaxHealth { 0.0 };
	double CurrentHealth { 0.0 };

	double Experience { 0.0 };

	static void _bind_methods();

private:

};
