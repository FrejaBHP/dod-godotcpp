#pragma once

#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include "shared/enums.h"

using namespace godot;

class InventoryItem : public MarginContainer {
	GDCLASS(InventoryItem, MarginContainer)

public:
	bool HasActiveCard { false };

	virtual void _ready() override;

	virtual void OnPickedUp();

	virtual void CreateItemCard();
	virtual void DestroyItemCard();

	TextureRect* const GetTextureRect() const;

	void SetItemType(const int type);
	int GetItemType() const;

	void SetUsable(const bool usable);
	bool GetUsable() const;

	void SetDescription(const String desc);
	String GetDescription() const;

protected:
	TextureRect* ItemTextureRect { nullptr };
	Control* CardAnchor { nullptr };

	EInventoryItemType ItemType { EInventoryItemType::Generic };
	bool IsUsable { false };
	String Description { "" };

	static void _bind_methods();

private:

};
