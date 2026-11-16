#pragma once

#include "characterController.h"
#include "ui/crosshair.h"
#include "interactible/interactible.h"

#include <godot_cpp/classes/node2d.hpp>
//#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

using namespace godot;

class Player;
class Gun;
class GunDropped;
class HUD;

class PlayerController : public CharacterController {
	GDCLASS(PlayerController, CharacterController)

public:
	PlayerController();
	~PlayerController() = default;

	void _unhandled_input(const Ref<InputEvent>& p_event) override;
	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	Vector2 ProcessMovementInput();

	void SetPlayer(Player* player);
	Player* GetPlayer() const;

	// Updates HUD values, do not set MaxHealth directly
	void SetMaxHealth(double max);

	void OnHitByProjectile(Projectile* proj) override;
	void TakeDamage(DamageInfo& di) override;

	Node2D* GetCrosshair() const;

	void UpdateGunHeldType(const Gun& heldGun);

	void GetStartGun(); // Only use this for starting pistol for a new character
	// Sets the current gun in Controller. Is also responsible for calls to update HUD with the new gun.
	void SetCurrentGunSlot(int32_t slot);
	int32_t GetCurrentGunSlot() const;
	void UpdateAmmoLabel();

	void GiveExperience(double exp);
	double GetExperience() const;

protected:
	Player* ControlledPlayer { nullptr };
	Sprite2D* GunSprite { nullptr };
	Crosshair* PlayerCrosshair { nullptr };
	Label* DebugLabel { nullptr };
	Camera2D* PlayerCamera { nullptr };
	Area2D* PickupRadius { nullptr };
	Area2D* GunPickupRadius { nullptr };
	Timer* GunPickupTimer { nullptr };
	HUD* PlayerHUD { nullptr };
	Timer* InaccuracyTimer { nullptr };
	TextureProgressBar* ReloadBar { nullptr };

	std::vector<GunDropped*> DroppedGunsInRadius;
	GunDropped* DroppedGunInFocus { nullptr };

	std::vector<Interactible*> InteractiblesInRadius;
	Interactible* InteractibleInFocus { nullptr };

	bool isLMBHeld = false;
	bool isRMBHeld = false;

	double CurReloadTime = 0.0;

	int32_t NumEquippedGuns { 0 };
	int32_t CurrentGunSlot { 0 };

	static void _bind_methods();

	// When a pickup, like ammo, comes within PickupRadius' area
	void PickupAreaEntered(Area2D* area);
	void PickupAreaExited(Area2D* area);

	// When a GunDropped object comes within DroppedGunRadius' area
	void InteractibleAreaEntered(Area2D* area);
	void InteractibleAreaExited(Area2D* area);

	void PickupTimerTimeout();
	void ScanForGuns();
	GunDropped* GetClosestGunDropped();
	Interactible* GetClosestInteractible();

	void Interact();
	void PickUpGunInSlot(int32_t slot);
	void SwapGunOnGround();

	void SwitchGun(int32_t slot);
	// Sets up gun that is switched to
	void ApplyCurrentGun();

	void GunReloadStart() override;
	void GunReloadEnd() override;
	void ProcessReload(double delta);

	void OnGunFired();
	void ApplyRecoil() override;
	void EnableInaccuracyRecovery() override;

	void BindGun(Gun* gun);
	void UnbindGun(Gun* gun);

	void LevelUp();

private:

};
