#include "ui/inventory.h"
#include "gameInstance.h"
#include "player/playerChar.h"
#include "player/playerController.h"

void Inventory::_bind_methods() {
	ClassDB::bind_method(D_METHOD("OnSlotClicked", "p_Slot", "p_Item"), &Inventory::OnSlotClicked);
	ClassDB::bind_method(D_METHOD("GunEquipped", "p_Gun", "p_Slot"), &Inventory::GunEquipped);
	ClassDB::bind_method(D_METHOD("GunUnequipped", "p_Slot"), &Inventory::GunUnequipped);

	ADD_SIGNAL(MethodInfo("create_preview", PropertyInfo(Variant::OBJECT, "item")));
	ADD_SIGNAL(MethodInfo("destroy_preview"));

	ADD_SIGNAL(MethodInfo("gun_equipped", PropertyInfo(Variant::OBJECT, "gun"), PropertyInfo(Variant::INT, "slot")));
	ADD_SIGNAL(MethodInfo("gun_unequipped", PropertyInfo(Variant::INT, "slot")));

	ADD_SIGNAL(MethodInfo("melee_equipped", PropertyInfo(Variant::OBJECT, "melee"), PropertyInfo(Variant::INT, "slot")));
	ADD_SIGNAL(MethodInfo("melee_unequipped", PropertyInfo(Variant::INT, "slot")));

	ADD_SIGNAL(MethodInfo("shield_equipped", PropertyInfo(Variant::OBJECT, "shield")));
	ADD_SIGNAL(MethodInfo("shield_unequipped"));

	ADD_SIGNAL(MethodInfo("spell_equipped", PropertyInfo(Variant::OBJECT, "spell")));
	ADD_SIGNAL(MethodInfo("spell_unequipped"));

	ADD_SIGNAL(MethodInfo("mod_equipped", PropertyInfo(Variant::OBJECT, "mod")));
	ADD_SIGNAL(MethodInfo("mod_unequipped"));
}

void Inventory::_ready() {
	Control* eqGrid = get_node<Control>("VBoxContainer/EquipmentMargin/EquipmentGrid");
	Control* invGrid = get_node<Control>("VBoxContainer/InventoryMargin/InventoryGrid");

	WeaponSlots[0] = eqGrid->get_node<InventorySlot>("WeaponSlot1");
	WeaponSlots[0]->SlotNumber = 0;
	WeaponSlots[0]->connect("item_equipped", callable_mp(this, &Inventory::GunEquipped));
	WeaponSlots[0]->connect("item_unequipped", callable_mp(this, &Inventory::GunUnequipped));

	WeaponSlots[1] = eqGrid->get_node<InventorySlot>("WeaponSlot2");
	WeaponSlots[1]->SlotNumber = 1;
	WeaponSlots[1]->connect("item_equipped", callable_mp(this, &Inventory::GunEquipped));
	WeaponSlots[1]->connect("item_unequipped", callable_mp(this, &Inventory::GunUnequipped));

	WeaponSlots[2] = eqGrid->get_node<InventorySlot>("WeaponSlot3");
	WeaponSlots[2]->SlotNumber = 2;
	WeaponSlots[2]->connect("item_equipped", callable_mp(this, &Inventory::GunEquipped));
	WeaponSlots[2]->connect("item_unequipped", callable_mp(this, &Inventory::GunUnequipped));

	ShieldSlot = eqGrid->get_node<InventorySlot>("ShieldSlot");
	SpellSlot = eqGrid->get_node<InventorySlot>("SpellSlot");
	ModSlot = eqGrid->get_node<InventorySlot>("ModSlot");

	for (size_t i = 0; i < eqGrid->get_child_count(); i++) {
		InventorySlot* slot = static_cast<InventorySlot*>(eqGrid->get_child(i));
		slot->connect("slot_clicked", callable_mp(this, &Inventory::OnSlotClicked));
		slot->connect("item_use", callable_mp(this, &Inventory::UseItem));
		slot->connect("item_drop", callable_mp(this, &Inventory::DropItem));
	}

	for (size_t i = 0; i < invGrid->get_child_count(); i++) {
		InventorySlots[i] = invGrid->get_node<InventorySlot>("InventorySlot" + String::num_uint64(i + 1));
		InventorySlots[i]->SlotNumber = (int)i;
		InventorySlots[i]->connect("slot_clicked", callable_mp(this, &Inventory::OnSlotClicked));
		InventorySlots[i]->connect("item_use", callable_mp(this, &Inventory::UseItem));
		InventorySlots[i]->connect("item_drop", callable_mp(this, &Inventory::DropItem));
	}

	connect("mouse_entered", callable_mp(this, &Inventory::OnMouseEntered));
	connect("mouse_exited", callable_mp(this, &Inventory::OnMouseExited));
}

bool Inventory::CanAddItem(int& outSlot) {
	bool spaceFound { false };
	int slot { 0 };

	while (!spaceFound) {
		if (!InventorySlots[slot]->ContainsItem()) {
			spaceFound = true;
			outSlot = slot;
			break;
		}

		++slot;

		if (slot > 7) {
			outSlot = -1;
			break;
		}
	}

	return spaceFound;
}

void Inventory::AddItem(InventoryItem* item, int slot) {
	InventorySlots[slot]->add_child(item);
	InventorySlots[slot]->SetContainedItem(item);

	item->OnPickedUp();
}

void Inventory::SetItemInSlot(InventoryItem* item, EInventorySlotType slotType, int slot) {
	switch (slotType) {
		case EInventorySlotType::Inventory:
			if (slot > 7) {
				slot = 7;
			}

			InventorySlots[slot]->add_child(item);
			InventorySlots[slot]->SetContainedItem(item);
			break;

		case EInventorySlotType::EquipmentWeapon:
			if (slot > 2) {
				slot = 2;
			}

			WeaponSlots[slot]->add_child(item);
			WeaponSlots[slot]->SetContainedItem(item);
			break;

		case EInventorySlotType::EquipmentShield:
			ShieldSlot->add_child(item);
			ShieldSlot->SetContainedItem(item);
			break;

		case EInventorySlotType::EquipmentSpell:
			SpellSlot->add_child(item);
			SpellSlot->SetContainedItem(item);
			break;

		case EInventorySlotType::EquipmentMod:
			ModSlot->add_child(item);
			ModSlot->SetContainedItem(item);
			break;

		default:
			InventorySlots[7]->add_child(item);
			InventorySlots[7]->SetContainedItem(item);
			break;
	}

	item->OnPickedUp();
}

void Inventory::UseItem(InventorySlot* slot, InventoryItem* item) {
	// item is already null-checked


}

void Inventory::DropItem(InventorySlot* slot, InventoryItem* item) {
	GameInstance& gi = GameInstance::GetInstance();

	gi.CopyItemFromInventoryToDrop(item, gi.GetPlayer()->get_global_position());

	item->queue_free();
	slot->SetContainedItem(nullptr); // note: behaviour for removing items from equipment slots is already defined by the slots, so don't do anything extra
}

void Inventory::GunEquipped(ItemGun* gun, int slot) {
	emit_signal("gun_equipped", gun, slot);
}

void Inventory::GunUnequipped(int slot) {
	emit_signal("gun_unequipped", slot);
}

void Inventory::OnInventoryClosed() {
	if (IsItemHeld) {
		MovingItem->set_modulate(Color(1.f, 1.f, 1.f, 1.f));

		MovingSlot = nullptr;
		MovingItem = nullptr;
		IsItemHeld = false;

		emit_signal("destroy_preview");
	}
}

void Inventory::OnSlotClicked(InventorySlot* slot, InventoryItem* item) {
	if (!IsItemHeld) {
		// If trying to grab from an empty slot, cancel
		if (!item) {
			return;
		}

		// If no item is already held, register it
		MovingSlot = slot;
		MovingItem = item;
		IsItemHeld = true;

		if (slot->GetContainedItem()->HasActiveCard) {
			slot->GetContainedItem()->DestroyItemCard();
		}

		MovingItem->set_modulate(Color(1.f, 1.f, 1.f, 0.7f));
		emit_signal("create_preview", MovingItem->GetTextureRect());

		//print_line(MovingSlot->get_name());
	}
	// If an item is held, aka item is being released
	else {
		// If the slot is a different one
		if (slot != MovingSlot) {
			// If item can go into slot
			if (GetSlotEligibility((EInventorySlotType)slot->GetSlotType(), (EInventoryItemType)MovingItem->GetItemType())) {
				// If the slot released into is empty, move the item
				if (!item) {
					MovingItem->reparent(slot);
					MovingSlot->SetContainedItem(nullptr);
					slot->SetContainedItem(MovingItem);

					if (!slot->GetContainedItem()->HasActiveCard) {
						slot->GetContainedItem()->CreateItemCard();
					}
					
					//print_line("Moved item to " + slot->get_name());
				}
				// If the slot released into also has an item, swap them if valid
				else {
					if (GetSlotEligibility((EInventorySlotType)MovingSlot->GetSlotType(), (EInventoryItemType)item->GetItemType())) {
						MovingItem->reparent(slot);
						item->reparent(MovingSlot);
						MovingSlot->SetContainedItem(item);
						slot->SetContainedItem(MovingItem);

						if (!slot->GetContainedItem()->HasActiveCard) {
							slot->GetContainedItem()->CreateItemCard();
						}
						if (MovingSlot->GetContainedItem()->HasActiveCard) {
							MovingSlot->GetContainedItem()->DestroyItemCard();
						}

						//print_line("Swapped with " + slot->get_name());
					}
					else {
						//print_line("Failed swapping with " + slot->get_name());
					}
				}
			}
		}

		//cancel the operation and/or reset references
		MovingItem->set_modulate(Color(1.f, 1.f, 1.f, 1.f));

		MovingSlot = nullptr;
		MovingItem = nullptr;
		IsItemHeld = false;

		emit_signal("destroy_preview");
	}
}

bool Inventory::GetSlotEligibility(EInventorySlotType slotType, EInventoryItemType itemType) const {
	switch (slotType) {
		case EInventorySlotType::Inventory:
			return true;

		case EInventorySlotType::EquipmentWeapon:
			if (itemType == EInventoryItemType::Weapon) {
				return true;
			}
			break;

		case EInventorySlotType::EquipmentShield:
			if (itemType == EInventoryItemType::Shield) {
				return true;
			}
			break;

		case EInventorySlotType::EquipmentSpell:
			if (itemType == EInventoryItemType::Spell) {
				return true;
			}
			break;

		case EInventorySlotType::EquipmentMod:
			if (itemType == EInventoryItemType::Mod) {
				return true;
			}
			break;

		default:
			break;
	}

	return false;
}

void Inventory::OnMouseEntered() {
	GameInstance::GetInstance().GetPlayer()->GetController()->SetCrosshairVisibility(false);
	GameInstance::GetInstance().ShowCursor();
}

void Inventory::OnMouseExited() {
	GameInstance::GetInstance().GetPlayer()->GetController()->SetCrosshairVisibility(true);
	GameInstance::GetInstance().HideCursor();
}
