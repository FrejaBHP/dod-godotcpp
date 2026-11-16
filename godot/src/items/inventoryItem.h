#pragma once

#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include "shared/enums.h"

using namespace godot;

class InventoryItem : public MarginContainer {
	GDCLASS(InventoryItem, MarginContainer)

public:
	virtual void _ready() override;

	//virtual Variant _get_drag_data(const Vector2 &p_at_position) override;

	void SetItemType(const int type);
	int GetItemType() const;

protected:
	TextureRect* ItemTextureRect { nullptr };

	EInventoryItemType ItemType { EInventoryItemType::Generic };

	static void _bind_methods();

private:

};
