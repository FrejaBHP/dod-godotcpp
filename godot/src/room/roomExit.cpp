#include "room/roomExit.h"

void RoomExit::_bind_methods() {

}

void RoomExit::_ready() {
	ExitSign = get_node<Control>("ControlPivot/ExitSign");
	SignTitle = ExitSign->get_node<RichTextLabel>("VBoxContainer/SignTitle");
	SignDesc = ExitSign->get_node<RichTextLabel>("VBoxContainer/SignDesc");
}

void RoomExit::UpdateExitSign() {
	switch (RewardsInfo.RewardClass) {
		case ERewardClass::Chest:
			switch (RewardsInfo.ChestRewardClass) {
				case EChestRewardClass::AmmoCrate:
					SignTitle->push_color(ColourItemAmmoCrate);
					SignTitle->append_text("Ammo Crate");
					SignTitle->pop();

					SignDesc->append_text("Contains ammunition");
					break;

				case EChestRewardClass::EquipmentChest:
					SignTitle->push_color(ColourItemWeaponsChest);
					SignTitle->append_text("Weapons Chest");
					SignTitle->pop();

					SignDesc->append_text("Contains weapons");
					break;

				default:
					break;
			}
			break;

		default:
			SignTitle->append_text("Default");
			SignDesc->append_text("Sorry nothing");
			break;
	}

	ExitSign->set_visible(true);
}

void RoomExit::SetRewardsInfo(const RoomRewardsInfo info) {
	RewardsInfo = info;

	UpdateExitSign();
}

RoomRewardsInfo RoomExit::GetRewardsInfo() const {
	return RewardsInfo;
}
