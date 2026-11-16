#include "interactible/interactible.h"

void Interactible::_bind_methods() {
	ClassDB::bind_method(D_METHOD("IntSetRepeatable", "p_Repeatable"), &Interactible::SetRepeatable);
	ClassDB::bind_method(D_METHOD("IntGetRepeatable"), &Interactible::GetRepeatable);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "repeatable", PROPERTY_HINT_NONE), "IntSetRepeatable", "IntGetRepeatable");

	ADD_SIGNAL(MethodInfo("activated"));
}

void Interactible::_ready() {
	add_to_group("Interactible");
}

void Interactible::Activate() {
	emit_signal("activated");
}

void Interactible::SetRepeatable(const bool repeatable) {
	Repeatable = repeatable;
}

bool Interactible::GetRepeatable() const {
	return Repeatable;
}
