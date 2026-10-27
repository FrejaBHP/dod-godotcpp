#include "ui/crosshair.h"


const Vector2 CHUpBasePos { -2.0f, 0.0f };
const Vector2 CHDownBasePos { -2.0f, 8.0f };
const Vector2 CHRightBasePos { 0.0f, -2.0f };
const Vector2 CHLeftBasePos { -8.0f, -2.0f };

void Crosshair::_bind_methods() {

}

void Crosshair::_ready() {
	CHUp = get_node<TextureRect>("CHUp");
	CHDown = get_node<TextureRect>("CHDown");
	CHRight = get_node<TextureRect>("CHRight");
	CHLeft = get_node<TextureRect>("CHLeft");
}

void Crosshair::_process(double delta) {
	const float deltaS = (float)delta * 5;

	const Vector2 chup { CHUpBasePos.x, CHUpBasePos.y - SpreadTarget };
	CHUp->set_position(CHUp->get_position().lerp(chup, deltaS));

	const Vector2 chdown { CHDownBasePos.x, CHDownBasePos.y + SpreadTarget };
	CHDown->set_position(CHDown->get_position().lerp(chdown, deltaS));

	const Vector2 chright { CHRightBasePos.x + SpreadTarget, CHRightBasePos.y };
	CHRight->set_position(CHRight->get_position().lerp(chright, deltaS));

	const Vector2 chleft { CHLeftBasePos.x - SpreadTarget, CHLeftBasePos.y };
	CHLeft->set_position(CHLeft->get_position().lerp(chleft, deltaS));
}

void Crosshair::_physics_process(double delta) {
	
}

void Crosshair::UpdateCrosshairSpreadTarget(double spread) {
	SpreadTarget = (float)spread * 2;
}
