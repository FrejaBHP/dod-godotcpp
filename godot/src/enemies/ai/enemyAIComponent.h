#pragma once

#include <godot_cpp/classes/node.hpp>
#include "shared/enums.h"

using namespace godot;

class EnemyController;

class EnemyAIComponent : public Node {
	GDCLASS(EnemyAIComponent, Node)

public:
	void _ready() override;
	void _physics_process(double delta) override;

	virtual void SetController(EnemyController* ec);
	const EnemyController* GetController() const;

	void SetState(EAIState state);
	const EAIState GetState() const;

	void Enable();
	void Disable();

protected:
	EnemyController* Controller = nullptr;
	EAIState AIState { EAIState::Idle };
	int SlowUpdateCounter { 0 };
	int SlowUpdateDelay { 12 };

	bool IsTargetInFront { false };

	bool CanSeeTarget { false };
	bool IsFacingTarget { false };

	bool AIEnabled { true };

	static void _bind_methods();

	virtual void AISlowUpdate(); // For running operations and updates that don't need to be run every frame.
	godot::real_t GetDotTarget(); // Gets the dot product for the facing angle towards the target. > 0 means within 90 degrees to either side

	virtual void ExecuteIdle();
	virtual void ExecuteSearch();
	virtual void ExecuteChase();

private:

};
