#pragma once

#include "items/inventoryItem.h"
#include "gun/gunDefinition.h"

class ItemGun : public InventoryItem {
	GDCLASS(ItemGun, InventoryItem)

public:
	std::shared_ptr<GunDefinition> GunDef { nullptr };

	ItemGun();

	void _ready() override;

	void OnPickedUp() override;

	void CreateItemCard() override;
	void DestroyItemCard() override;

protected:
	static void _bind_methods();

private:

};
