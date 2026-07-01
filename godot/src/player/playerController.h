#pragma once

#include "characterController.h"

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/texture_progress_bar.hpp>

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

	void _input(const Ref<InputEvent>& p_event) override;
	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	Vector2 ProcessMovementInput();

	void SetPlayer(Player* player);
	Player* GetPlayer() const;

	Node2D* GetCrosshair() const;

	void SetCurrentGunSlot(int32_t slot);
	int32_t GetCurrentGunSlot() const;
	void UpdateAmmoLabel();
	

protected:
	static void _bind_methods();

	void PickupAreaEntered(Area2D* area);
	void PickupAreaExited(Area2D* area);
	void PickupTimerTimeout();
	void ScanForGuns();
	GunDropped* GetClosestGunDropped();

	void Interact();
	void PickUpGunInSlot(int32_t slot);
	void SwapGunOnGround();

	void SwitchGun(int32_t slot);
	void ApplyCurrentGun();

	void GunReloadStart() override;
	void GunReloadEnd() override;
	void ProcessReload(double delta);

	void OnGunFired();
	void ApplyRecoil() override;
	void EnableInaccuracyRecovery() override;

	void BindGun(Gun* gun);
	void UnbindGun(Gun* gun);

	Player* ControlledPlayer = nullptr;
	Node2D* PlayerCrosshair = nullptr;
	Label* DebugLabel = nullptr;
	Camera2D* PlayerCamera = nullptr;
	Area2D* PickupRadius = nullptr;
	Timer* PickupTimer = nullptr;
	HUD* PlayerHUD = nullptr;
	Timer* InaccuracyTimer = nullptr;
	TextureProgressBar* ReloadBar = nullptr;

	std::vector<GunDropped*> DroppedGunsInRadius;
	GunDropped* DroppedGunInFocus = nullptr;

	bool isLMBHeld = false;
	bool isRMBHeld = false;

	double CurReloadTime = 0.0;

	int32_t NumEquippedGuns { 0 };
	int32_t CurrentGunSlot { 0 };

private:

};
