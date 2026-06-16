#include "gun/parts/catalogueSMG.h"
#include "shared/utility.h"

constexpr int32_t NumBodies = 5;
constexpr int32_t NumBarrels = 5;
constexpr int32_t NumMags = 5;
constexpr int32_t NumStocks = 6;
constexpr int32_t NumAccessories = 5;
constexpr int32_t NumTitles = 5;

std::unique_ptr<BodyComponent> GetRandomSMGBody() {
	int32_t bodyIndex = GetRandomInt(0, NumBodies - 1);
	BodyComponent* body;

	switch (bodyIndex) {
		case 1:
			body = new SMGBody2();
			break;

		case 2:
			body = new SMGBody3();
			break;

		case 3:
			body = new SMGBody4();
			break;

		case 4:
			body = new SMGBody5();
			break;
	
		default:
			body = new SMGBody1();
			break;
	}

	return std::unique_ptr<BodyComponent>(body);
}

std::unique_ptr<BarrelComponent> GetRandomSMGBarrel() {
	int32_t barrelIndex = GetRandomInt(0, NumBarrels - 1);
	BarrelComponent* barrel;

	switch (barrelIndex) {
		case 1:
			barrel = new SMGBarrel2();
			break;

		case 2:
			barrel = new SMGBarrel3();
			break;

		case 3:
			barrel = new SMGBarrel4();
			break;

		case 4:
			barrel = new SMGBarrel5();
			break;

		default:
			barrel = new SMGBarrel1();
			break;
	}

	return std::unique_ptr<BarrelComponent>(barrel);
}

std::unique_ptr<MagazineComponent> GetRandomSMGMag() {
	int32_t magIndex = GetRandomInt(0, NumMags - 1);
	MagazineComponent* mag;

	switch (magIndex) {
		case 1:
			mag = new SMGMag2();
			break;

		case 2:
			mag = new SMGMag3();
			break;

		case 3:
			mag = new SMGMag4();
			break;

		case 4:
			mag = new SMGMag5();
			break;

		default:
			mag = new SMGMag1Thumper();
			break;
	}

	return std::unique_ptr<MagazineComponent>(mag);
}

std::unique_ptr<StockComponent> GetRandomSMGStock() {
	int32_t stockIndex = GetRandomInt(0, NumStocks - 1);
	StockComponent* stock;

	switch (stockIndex) {
		case 1:
			stock = new SMGStock1();
			break;

		case 2:
			stock = new SMGStock2();
			break;

		case 3:
			stock = new SMGStock3();
			break;

		case 4:
			stock = new SMGStock4();
			break;

		case 5:
			stock = new SMGStock5();
			break;

		default:
			stock = new SMGStock0None();
			break;
	}

	return std::unique_ptr<StockComponent>(stock);
}

std::unique_ptr<AccessoryComponent> GetRandomSMGAccessory() {
	int32_t accIndex = GetRandomInt(0, NumAccessories - 1);
	AccessoryComponent* acc;

	switch (accIndex) {
		case 1:
			acc = new SMGAcc1Relentless();
			break;

		case 2:
			acc = new SMGAcc2Ruthless();
			break;

		case 3:
			acc = new SMGAcc3Vector();
			break;

		case 4:
			acc = new SMGAcc4Double();
			break;

		default:
			acc = new SMGAcc0None();
			break;
	}

	return std::unique_ptr<AccessoryComponent>(acc);
}

std::unique_ptr<TitleComponent> GetEligibleSMGTitle(GunDefinition* gundef) {
	TitleComponent* title;

	if (gundef->Magazine->PartNum == 1) {
		title = new SMGTitleThumper();
	}
	else if (gundef->Accessory->PartNum == 4 && gundef->Accuracy <= 70.0) {
		title = new SMGTitleAnarchy();
	}
	else if (gundef->FireTime <= 83) {
		title = new SMGTitleStinger();
	}
	else if (gundef->AttrBonuses[EAttributeType::Damage].Scale >= 0.33) {
		title = new SMGTitleBruiser();
	}
	else {
		title = new SMGTitleDefault();
	}

	return std::unique_ptr<TitleComponent>(title);
}


SMGBody1::SMGBody1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.08 }
	};
}

SMGBody2::SMGBody2() {
	PartRarity = 2;
	PartNum = 2;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::FireRate, 0, -0.17 },
		{ EAttributeType::Recoil, 0, 0.3 },
	};
}

SMGBody3::SMGBody3() {
	PartRarity = 2;
	PartNum = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.15 },
		{ EAttributeType::FireRate, 0, 0.3 },
		{ EAttributeType::Recoil, 0, -0.3 },
	};
}

SMGBody4::SMGBody4() {
	PartRarity = 4;
	PartNum = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, -0.23 },
		{ EAttributeType::Recoil, 0, 0.5 },
	};
}

SMGBody5::SMGBody5() {
	PartRarity = 6;
	PartNum = 5;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, 0.5 },
		{ EAttributeType::Recoil, 0, -0.2 },
	};
}


SMGBarrel1::SMGBarrel1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.04 }
	};
}

SMGBarrel2::SMGBarrel2() {
	PartRarity = 1;
	PartNum = 2;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, 0.28 },
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, 0.2 },
		{ EAttributeType::Recoil, 0, 0.2 },
	};
}

SMGBarrel3::SMGBarrel3() {
	PartRarity = 2;
	PartNum = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, -0.5 },
		{ EAttributeType::InaccuracyMin, 0, -0.3 },
		{ EAttributeType::InaccuracyMax, 0, -0.3 },
	};
}

SMGBarrel4::SMGBarrel4() {
	PartRarity = 4;
	PartNum = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.3 },
		{ EAttributeType::Spread, 0, -0.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.4 },
		{ EAttributeType::Recoil, 0, 0.35 },
	};
}

SMGBarrel5::SMGBarrel5() {
	PartRarity = 4;
	PartNum = 5;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, -1.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.4 },
		{ EAttributeType::InaccuracyMax, 0, -1.5 },
		{ EAttributeType::Recoil, 0, -0.5 },
	};
}


SMGMag1Thumper::SMGMag1Thumper() {
	PartRarity = 2;
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.7 },
		{ EAttributeType::MagSize, -10, 0 },
		{ EAttributeType::FireRate, 0, -0.67 },
		{ EAttributeType::ReloadSpeed, 0, 0.25 }
	};
}

SMGMag2::SMGMag2() {
	PartNum = 2;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, 0.15 }
	};
}

SMGMag3::SMGMag3() {
	PartRarity = 2;
	PartNum = 3;
	Bonuses = {
		{ EAttributeType::MagSize, 8, 0 },
		{ EAttributeType::ReloadSpeed, 0, 0.2 }
	};
}

SMGMag4::SMGMag4() {
	PartRarity = 1;
	PartNum = 4;
	Bonuses = {
		{ EAttributeType::MagSize, 27, 0 },
		{ EAttributeType::ReloadSpeed, 0, -0.6 }
	};
}

SMGMag5::SMGMag5() {
	PartRarity = 1;
	PartNum = 5;
	Bonuses = {
		{ EAttributeType::MagSize, 18, 0 },
		{ EAttributeType::ReloadSpeed, 0, -0.4 }
	};
}


SMGStock0None::SMGStock0None() {
	PartNum = 0;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, 0.3 },
		{ EAttributeType::InaccuracyMin, 0, 0.5 },
		{ EAttributeType::InaccuracyMax, 0, -0.2 },
		{ EAttributeType::InaccuracyRegen, 0, 1.0 },
		{ EAttributeType::Recoil, 0, 0.4 },
	};
}

SMGStock1::SMGStock1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::InaccuracyRegen, 0, 0.2 },
	};
}

SMGStock2::SMGStock2() {
	PartRarity = 1;
	PartNum = 2;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, -0.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.1 },
		{ EAttributeType::InaccuracyRegen, 0, 0.2 },
		{ EAttributeType::Recoil, 0, -0.4 },
	};
}

SMGStock3::SMGStock3() {
	PartRarity = 2;
	PartNum = 3;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, -0.2 },
		{ EAttributeType::InaccuracyRegen, 0, 0.4 },
		{ EAttributeType::Recoil, 0, -0.3 },
	};
}

SMGStock4::SMGStock4() {
	PartRarity = 3;
	PartNum = 4;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, -0.2 },
		{ EAttributeType::InaccuracyMin, 0, -0.3 },
		{ EAttributeType::InaccuracyMax, 0, -0.3 },
		{ EAttributeType::InaccuracyRegen, 0, 0.6 },
		{ EAttributeType::Recoil, 0, -0.8 },
	};
}

SMGStock5::SMGStock5() {
	PartRarity = 4;
	PartNum = 5;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.4 },
		{ EAttributeType::InaccuracyMax, 0, -0.4 },
		{ EAttributeType::InaccuracyRegen, 0, 0.8 },
		{ EAttributeType::Recoil, 0, -1.0 },
	};
}


SMGAcc0None::SMGAcc0None() {
	PartNum = 0;
	Bonuses = {};
}

SMGAcc1Relentless::SMGAcc1Relentless() {
	Name = "Relentless";
	PartRarity = 2;
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.2 },
	};
}

SMGAcc2Ruthless::SMGAcc2Ruthless() {
	Name = "Ruthless";
	PartRarity = 3;
	PartNum = 2;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, 0.53 },
		{ EAttributeType::Recoil, 0, -0.45 },
	};
}

SMGAcc3Vector::SMGAcc3Vector() {
	Name = "Vector";
	PartRarity = 5;
	PartNum = 3;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.45 },
		{ EAttributeType::ReloadSpeed, 0, 0.53 },
		{ EAttributeType::Recoil, 0, -2.0 },
	};
}

SMGAcc4Double::SMGAcc4Double() {
	Name = "Double";
	PartRarity = 4;
	PartNum = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.18 },
		{ EAttributeType::MagSize, 0, 0.2 },
		{ EAttributeType::ProjectileCount, 1, 0 },
		{ EAttributeType::ShotCost, 1, 0 },
		{ EAttributeType::Spread, 0, 0.75 },
	};
}


SMGTitleDefault::SMGTitleDefault() {
	Title = "SMG";
	Bonuses = {};
}

SMGTitleThumper::SMGTitleThumper() {
	Title = "Thumper";
	Bonuses = {};
}

SMGTitleAnarchy::SMGTitleAnarchy() {
	Title = "Anarchy";
	Bonuses = {
		{ EAttributeType::MagSize, 0, 0.3 },
		{ EAttributeType::ProjectileCount, 2, 0 },
		{ EAttributeType::Spread, 0, 2.0 },
	};
}

SMGTitleStinger::SMGTitleStinger() {
	Title = "Stinger";
	Bonuses = {
		{ EAttributeType::Recoil, 0, -0.15 },
		{ EAttributeType::MagSize, 3, 0.0 },
	};
}

SMGTitleBruiser::SMGTitleBruiser() {
	Title = "Bruiser";
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
	};
}
