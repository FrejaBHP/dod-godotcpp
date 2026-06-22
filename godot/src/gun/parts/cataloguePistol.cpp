#include "gun/parts/cataloguePistol.h"
#include "shared/utility.h"

constexpr int32_t NumBodies = 5;
constexpr int32_t NumBarrels = 5;
constexpr int32_t NumActions = 5;
constexpr int32_t NumRepeaterMags = 3;
constexpr int32_t NumMPMags = 2;
constexpr int32_t NumRepeaterAccs = 4;
constexpr int32_t NumMPAccs = 6;

std::unique_ptr<BodyComponent> GetRandomPistolBody() {
	int32_t bodyIndex = GetRandomInt(0, NumBodies - 1);
	BodyComponent* body;

	switch (bodyIndex) {
		case 1:
			body = new PistolBody1();
			break;

		case 2:
			body = new PistolBody2();
			break;

		case 3:
			body = new PistolBody3();
			break;

		case 4:
			body = new PistolBody4();
			break;

		default:
			body = new PistolBody5MP();
			break;
	}

	return std::unique_ptr<BodyComponent>(body);
}

std::unique_ptr<BarrelComponent> GetRandomPistolBarrel() {
	int32_t index = GetRandomInt(0, NumBodies - 1);
	BarrelComponent* barrel;

	switch (index) {
		case 1:
			barrel = new PistolBarrel1();
			break;

		case 2:
			barrel = new PistolBarrel2();
			break;

		case 3:
			barrel = new PistolBarrel3();
			break;

		case 4:
			barrel = new PistolBarrel4();
			break;

		default:
			barrel = new PistolBarrel5();
			break;
	}

	return std::unique_ptr<BarrelComponent>(barrel);
}

std::unique_ptr<ActionComponent> GetRandomPistolAction() {
	int32_t index = GetRandomInt(0, NumActions - 1);
	ActionComponent* action;

	switch (index) {
		case 1:
			action = new PistolAction1();
			break;

		case 2:
			action = new PistolAction2();
			break;

		case 3:
			action = new PistolAction3();
			break;

		case 4:
			action = new PistolAction4();
			break;

		default:
			action = new PistolAction5();
			break;
	}

	return std::unique_ptr<ActionComponent>(action);
}

std::unique_ptr<MagazineComponent> GetRandomRepeaterMag() {
	int32_t index = GetRandomInt(0, NumRepeaterMags - 1);
	MagazineComponent* mag;

	switch (index) {
		case 1:
			mag = new RepeaterMag1();
			break;

		case 2:
			mag = new RepeaterMag2();
			break;

		default:
			mag = new RepeaterMag3();
			break;
	}

	return std::unique_ptr<MagazineComponent>(mag);
}

std::unique_ptr<MagazineComponent> GetRandomMPMag() {
	int32_t index = GetRandomInt(0, NumMPMags - 1);
	MagazineComponent* mag;

	switch (index) {
		case 1:
			mag = new MPMag1();
			break;

		default:
			mag = new MPMag2();
			break;
	}

	return std::unique_ptr<MagazineComponent>(mag);
}

std::unique_ptr<AccessoryComponent> GetRandomRepeaterAccessory() {
	int32_t index = GetRandomInt(0, NumRepeaterAccs - 1);
	AccessoryComponent* acc;

	switch (index) {
		case 1:
			acc = new PistolAcc1Stabilised();
			break;

		case 2:
			acc = new PistolAcc2Laser();
			break;

		case 3:
			acc = new PistolAcc3Double();
			break;

		default:
			acc = new PistolAcc0None();
			break;
	}

	return std::unique_ptr<AccessoryComponent>(acc);
}

std::unique_ptr<AccessoryComponent> GetRandomMPAccessory() {
	int32_t index = GetRandomInt(0, NumMPAccs - 1);
	AccessoryComponent* acc;

	switch (index) {
		case 1:
			acc = new PistolAcc1Stabilised();
			break;

		case 2:
			acc = new PistolAcc2Laser();
			break;

		case 3:
			acc = new PistolAcc3Double();
			break;

		case 4:
			acc = new MPAcc4Rage();
			break;

		case 5:
			acc = new MPAcc5Cold();
			break;

		default:
			acc = new PistolAcc0None();
			break;
	}

	return std::unique_ptr<AccessoryComponent>(acc);
}


PistolBody1::PistolBody1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.08 }
	};
}

PistolBody2::PistolBody2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::FireRate, 0, -0.17 },
		{ EAttributeType::Recoil, 0, 0.3 },
	};
}

PistolBody3::PistolBody3() {
	PartNum = 3;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.15 },
		{ EAttributeType::FireRate, 0, 0.3 },
		{ EAttributeType::Recoil, 0, -0.3 },
	};
}

PistolBody4::PistolBody4() {
	PartNum = 4;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, -0.23 },
		{ EAttributeType::Recoil, 0, 0.5 },
	};
}

PistolBody5MP::PistolBody5MP() {
	PartNum = 5;
	PartRarity = 1;
	Bonuses = {};
}


PistolBarrel1::PistolBarrel1() {
	PartNum = 1;
	PartRarity = 0;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.04 },
	};
}

PistolBarrel2::PistolBarrel2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, 0.28 },
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, 0.2 },
		{ EAttributeType::Recoil, 0, 0.2 },
	};
}

PistolBarrel3::PistolBarrel3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, -0.5 },
		{ EAttributeType::InaccuracyMin, 0, -0.3 },
		{ EAttributeType::InaccuracyMax, 0, -0.3 },
	};
}

PistolBarrel4::PistolBarrel4() {
	PartNum = 4;
	PartRarity = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.3 },
		{ EAttributeType::Spread, 0, -0.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.4 },
		{ EAttributeType::Recoil, 0, 0.35 },
	};
}

PistolBarrel5::PistolBarrel5() {
	PartNum = 5;
	PartRarity = 5;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, -1.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.4 },
		{ EAttributeType::InaccuracyMax, 0, -1.5 },
		{ EAttributeType::Recoil, 0, -0.5 },
	};
}


PistolAction1::PistolAction1() {
	PartNum = 1;
	PartRarity = 0;
	Bonuses = {};
}

PistolAction2::PistolAction2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.08 },
		{ EAttributeType::Recoil, 0, 0.05 },
	};
}

PistolAction3::PistolAction3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.12 },
		{ EAttributeType::Recoil, 0, -0.2 },
	};
}

PistolAction4::PistolAction4() {
	PartNum = 4;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.11 },
		{ EAttributeType::FireRate, 0, -0.08 },
		{ EAttributeType::Recoil, 0, 0.45 },
	};
}

PistolAction5::PistolAction5() {
	PartNum = 5;
	PartRarity = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.06 },
		{ EAttributeType::FireRate, 0, 0.36 },
	};
}


RepeaterMag1::RepeaterMag1() {
	PartNum = 1;
	PartRarity = 0;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, 0.3 },
	};
}

RepeaterMag2::RepeaterMag2() {
	PartNum = 2;
	PartRarity = 0;
	Bonuses = {
		{ EAttributeType::MagSize, 4, 0.0 },
	};
}

RepeaterMag3::RepeaterMag3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::MagSize, 6, 0.0 },
		{ EAttributeType::ReloadSpeed, 0, 0.5 },
	};
}

MPMag1::MPMag1() {
	PartNum = 1;
	PartRarity = 0;
	Bonuses = {};
}

MPMag2::MPMag2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::MagSize, 10, 0.0 },
	};
}

PistolAcc0None::PistolAcc0None() {
	PartNum = 0;
	PartRarity = 0;
	Bonuses = {};
}

PistolAcc1Stabilised::PistolAcc1Stabilised() {
	Name = "Stabilised";
	PartNum = 1;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Recoil, 0, -1.0 },
		{ EAttributeType::InaccuracyRegen, 0, 1.0 },
	};
}

PistolAcc2Laser::PistolAcc2Laser() {
	Name = "Laser";
	PartNum = 2;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Spread, 0, -0.25 },
		{ EAttributeType::InaccuracyMin, 0, -1.2 },
		{ EAttributeType::InaccuracyRegen, 0, 0.1 },
	};
}

PistolAcc3Double::PistolAcc3Double() {
	Name = "Double";
	PartNum = 3;
	PartRarity = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.18 },
		{ EAttributeType::MagSize, 0, 0.2 },
		{ EAttributeType::ProjectileCount, 1, 0.0 },
		{ EAttributeType::ShotCost, 1, 0.0 },
		{ EAttributeType::Spread, 0, 0.75 },
	};
}

MPAcc4Rage::MPAcc4Rage() {
	PartNum = 4;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 1.0 },
		{ EAttributeType::Recoil, 0, 1.0 },
	};
}

MPAcc5Cold::MPAcc5Cold() {
	Name = "Cold";
	PartNum = 5;
	PartRarity = 3;
	Bonuses = {
		// +4 Tech
		// +200% knockback
		{ EAttributeType::Damage, 0, 0.7 },
		{ EAttributeType::Recoil, 0, -1.0 },
		{ EAttributeType::InaccuracyRegen, 0, 1.0 },
		{ EAttributeType::ProjectileSpeed, 0, -3.0 },
	};
}


RepeaterTitleDefault::RepeaterTitleDefault() {
	Title = "Repeater";
	Bonuses = {};
}

RepeaterTitleNeedler::RepeaterTitleNeedler() {
	Title = "Needler";
	Bonuses = {
		{ EAttributeType::MagSize, 2, 0.0 },
		{ EAttributeType::Recoil, 0, -0.2 },
	};
}

RepeaterTitleSwatter::RepeaterTitleSwatter() {
	Title = "Swatter";
	Bonuses = {};
}

RepeaterTitleRaptor::RepeaterTitleRaptor() {
	Title = "Raptor";
	Bonuses = {};
}

MPTitleDefault::MPTitleDefault() {
	Title = "Machine Pistol";
	Bonuses = {};
}

MPTitleTorment::MPTitleTorment() {
	Title = "Torment";
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::MagSize, 2, 0.0 },
	};
}

MPTitleFury::MPTitleFury() {
	Title = "Fury";
	Bonuses = {
		{ EAttributeType::Spread, 0, -0.6 },
		{ EAttributeType::FireRate, 0, 0.25 },
		{ EAttributeType::MagSize, 0, 0.3 },
	};
}

MPTitleRage::MPTitleRage() {
	Title = "Rage";
	Bonuses = {};
}
