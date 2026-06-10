#pragma once

#include <godot_cpp/classes/character_body2d.hpp>

using namespace godot;

class PlayerController;
class Gun;

constexpr int32_t PlayerNumGunSlots = 3;

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)

public:
	Player();
	~Player() = default;

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void ApplyMovement(Vector2 movement);

	double GetMaxSpeed() const;

	void SetController(PlayerController* controller);
	PlayerController* GetController() const;

	void SetGunInSlot(int32_t slot, Gun* gun);
	Gun* GetGunInSlot(int32_t slot);
	void SetCurrentGun(Gun* gun);
	Gun* GetCurrentGun();

	void SwitchToGunInSlot(int32_t slot);

	int32_t PistolAmmo { 48 };
	int32_t SMGAmmo { 192 };
	int32_t ARAmmo { 120 };
	
protected:
	static void _bind_methods();

	PlayerController* Controller = nullptr;

	Gun* GunSlots[PlayerNumGunSlots];
	Gun* CurrentGun = nullptr;

	float MaxSpeed;

private:

};
