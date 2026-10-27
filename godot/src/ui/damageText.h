#pragma once

#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/tween.hpp>

using namespace godot;

class DamageText : public Label {
	GDCLASS(DamageText, Label)

public:
	void Start();
	void SetDamageValue(double damage);
	void SetTextColour(Color colour);

protected:
	Ref<Tween> upwardsTween;
	const Vector2 uptVec { 0.f, -64.0f };
	//const Color uptCol { 255.0f, 255.0f, 255.0f, 0.0f };
	const Color uptCol { 0.0f, 0.0f, 0.0f, -1.0f };
	const double uptDur { 0.75 };

	double DamageValue { 0.0 };

	static void _bind_methods();
	void UpwardsFinished();

private:

};
