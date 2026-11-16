#pragma once

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include "shared/utility.h"

using namespace godot;

class RoomExit : public Area2D {
	GDCLASS(RoomExit, Area2D)

public:
	void SetRewardsInfo(const RoomRewardsInfo info);
	RoomRewardsInfo GetRewardsInfo() const;

	void _ready() override;

protected:
	Control* ExitSign { nullptr };
	RichTextLabel* SignTitle { nullptr };
	RichTextLabel* SignDesc { nullptr };
	RoomRewardsInfo RewardsInfo;

	void UpdateExitSign();

	static void _bind_methods();

private:

};
