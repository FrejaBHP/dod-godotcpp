#include "ui/inventory.h"

void Inventory::_bind_methods() {

}

void Inventory::_ready() {
	Control* eqGrid = get_node<Control>("VBoxContainer/EquipmentMargin/EquipmentGrid");
	Control* invGrid = get_node<Control>("VBoxContainer/InventoryMargin/InventoryGrid");

	WeaponSlots[0] = eqGrid->get_node<InventorySlot>("WeaponSlot1");
	WeaponSlots[1] = eqGrid->get_node<InventorySlot>("WeaponSlot2");
	WeaponSlots[2] = eqGrid->get_node<InventorySlot>("WeaponSlot3");

	SpellSlot = eqGrid->get_node<InventorySlot>("SpellSlot");
	ModSlot = eqGrid->get_node<InventorySlot>("ModSlot");
	ReservedSlot = eqGrid->get_node<InventorySlot>("NotSureSlot");

	for (size_t i = 0; i < invGrid->get_child_count(); i++) {
		InventorySlots[i] = invGrid->get_node<InventorySlot>("InventorySlot" + String::num_uint64(i + 1));
	}

	// TESTING

	InventorySlots[0]->ContainedItem = InventorySlots[0]->get_node<InventoryItem>("InventoryItem");
	InventorySlots[1]->ContainedItem = InventorySlots[1]->get_node<InventoryItem>("InventoryItem");
}
