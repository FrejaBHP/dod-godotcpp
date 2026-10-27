#include "ui/damageText.h"
#include <godot_cpp/classes/property_tweener.hpp>

void DamageText::_bind_methods() {
	ClassDB::bind_method(D_METHOD("TweenUpwardsFinished"), &DamageText::UpwardsFinished);
}

void DamageText::Start() {
	upwardsTween = this->create_tween();
	upwardsTween->connect("finished", callable_mp(this, &DamageText::UpwardsFinished));
	upwardsTween->set_parallel(true);

	upwardsTween->tween_property(this, "position", uptVec, uptDur)->as_relative()->set_ease(Tween::EASE_OUT);
	upwardsTween->tween_property(this, "modulate", uptCol, uptDur)->as_relative()->set_ease(Tween::EASE_IN)->set_trans(Tween::TRANS_CUBIC);

	upwardsTween->play();
}

void DamageText::SetDamageValue(double damage) {
	DamageValue = damage;

	//set_modulate(Color(1.0f, 0.3f, 0.3f, 1.0f));

	String text = vformat("%0.0f", DamageValue);

	set_text(text);
}

void DamageText::SetTextColour(Color colour) {
	set_modulate(colour);
}

void DamageText::UpwardsFinished() {
	queue_free();
}
