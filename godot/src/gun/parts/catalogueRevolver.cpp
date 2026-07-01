#include "gun/parts/catalogueRevolver.h"
#include "shared/utility.h"

constexpr int32_t NumBodies = 5;
constexpr int32_t NumBarrels = 5;
constexpr int32_t NumMags = 5;
constexpr int32_t NumStocks = 4;
constexpr int32_t NumAccs = 3;

std::unique_ptr<BodyComponent> GetRandomRevolverBody() {
	int32_t bodyIndex = GetRandomInt(0, NumBodies - 1);
	BodyComponent* body;

	switch (bodyIndex) {
		case 1:
			body = new RevolverBody1();
			break;

		case 2:
			body = new RevolverBody2();
			break;

		case 3:
			body = new RevolverBody3();
			break;

		case 4:
			body = new RevolverBody4();
			break;

		default:
			body = new RevolverBody5();
			break;
	}

	return std::unique_ptr<BodyComponent>(body);
}

std::unique_ptr<BarrelComponent> GetRandomRevolverBarrel() {
	int32_t index = GetRandomInt(0, NumBarrels - 1);
	BarrelComponent* barrel;

	switch (index) {
		case 1:
			barrel = new RevolverBarrel1();
			break;

		case 2:
			barrel = new RevolverBarrel2();
			break;

		case 3:
			barrel = new RevolverBarrel3();
			break;

		case 4:
			barrel = new RevolverBarrel4();
			break;

		default:
			barrel = new RevolverBarrel5();
			break;
	}

	return std::unique_ptr<BarrelComponent>(barrel);
}

std::unique_ptr<MagazineComponent> GetRandomRevolverMagazine() {
	int32_t index = GetRandomInt(0, NumMags - 1);
	MagazineComponent* mag;

	switch (index) {
		case 1:
			mag = new RevolverMag1();
			break;

		case 2:
			mag = new RevolverMag2();
			break;

		case 3:
			mag = new RevolverMag3();
			break;

		case 4:
			mag = new RevolverMag4();
			break;

		default:
			mag = new RevolverMag5();
			break;
	}

	return std::unique_ptr<MagazineComponent>(mag);
}

std::unique_ptr<StockComponent> GetRandomRevolverStock() {
	int32_t index = GetRandomInt(0, NumStocks - 1);
	StockComponent* stock;

	switch (index) {
		case 1:
			stock = new RevolverStock1();
			break;

		case 2:
			stock = new RevolverStock2();
			break;

		case 3:
			stock = new RevolverStock3();
			break;

		default:
			stock = new RevolverStock0None();
			break;
	}

	return std::unique_ptr<StockComponent>(stock);
}

std::unique_ptr<AccessoryComponent> GetRandomRevolverAccessory() {
	int32_t index = GetRandomInt(0, NumAccs - 1);
	AccessoryComponent* acc;

	switch (index) {
		case 1:
			acc = new RevolverAcc1Masher();
			break;

		case 2:
			acc = new RevolverAcc2Stabilised();
			break;

		default:
			acc = new RevolverAcc0None();
			break;
	}

	return std::unique_ptr<AccessoryComponent>(acc);
}


RevolverBody1::RevolverBody1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.08 }
	};
}

RevolverBody2::RevolverBody2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::FireRate, 0, -0.2 },
		{ EAttributeType::Recoil, 0, 0.3 },
	};
}

RevolverBody3::RevolverBody3() {
	PartNum = 3;
	PartRarity = 1;
	Bonuses = {
		// Tech +3
		{ EAttributeType::Damage, 0, -0.15 },
		{ EAttributeType::FireRate, 0, 0.3 },
		{ EAttributeType::Recoil, 0, -0.3 },
	};
}

RevolverBody4::RevolverBody4() {
	PartNum = 4;
	PartRarity = 3;
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, -0.3 },
		{ EAttributeType::Recoil, 0, 0.5 },
	};
}

RevolverBody5::RevolverBody5() {
	PartNum = 5;
	PartRarity = 5;
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, 0.5 },
		{ EAttributeType::Recoil, 0, -0.2 },
	};
}


RevolverBarrel1::RevolverBarrel1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.04 }
	};
}

RevolverBarrel2::RevolverBarrel2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, 0.28 },
		{ EAttributeType::Recoil, 0, 0.2 },
		{ EAttributeType::InaccuracyMin, 0, 0.2 },
		{ EAttributeType::InaccuracyMax, 0, -0.2 },
	};
}

RevolverBarrel3::RevolverBarrel3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, -0.5 },
		{ EAttributeType::InaccuracyMin, 0, -0.3 },
		{ EAttributeType::InaccuracyMax, 0, -0.3 },
	};
}

RevolverBarrel4::RevolverBarrel4() {
	PartNum = 4;
	PartRarity = 3;
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.3 },
		{ EAttributeType::Spread, 0, -0.3 },
		{ EAttributeType::Recoil, 0, 0.35 },
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.4 },
	};
}

RevolverBarrel5::RevolverBarrel5() {
	PartNum = 5;
	PartRarity = 5;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, -1.3 },
		{ EAttributeType::Recoil, 0, -0.5 },
		{ EAttributeType::InaccuracyMin, 0, -0.4 },
		{ EAttributeType::InaccuracyMax, 0, -1.5 },
	};
}


RevolverMag1::RevolverMag1() {
	PartNum = 1;
	Bonuses = {};
}

RevolverMag2::RevolverMag2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.18 },
		{ EAttributeType::ReloadSpeed, 0, 0.3 }
	};
}

RevolverMag3::RevolverMag3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		// Tech +3
		{ EAttributeType::MagSize, -3, 0.0 },
		{ EAttributeType::ReloadSpeed, 0, 0.15 }
	};
}

RevolverMag4::RevolverMag4() {
	PartNum = 4;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.21 },
		{ EAttributeType::ReloadSpeed, 0, 0.1 }
	};
}

RevolverMag5::RevolverMag5() {
	PartNum = 5;
	PartRarity = 5;
	Bonuses = {
		// Tech +2
		{ EAttributeType::Damage, 0, 1.02 },
		{ EAttributeType::MagSize, -4, 0.0 },
		{ EAttributeType::ReloadSpeed, 0, 0.5 }
	};
}


RevolverStock0None::RevolverStock0None() {
	PartNum = 0;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, 0.3 },
		{ EAttributeType::Recoil, 0, 0.4 },
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, 0.5 },
		{ EAttributeType::InaccuracyRegen, 0, 1.0 }
	};
}

RevolverStock1::RevolverStock1() {
	PartNum = 1;
	Bonuses = {};
}

RevolverStock2::RevolverStock2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, -0.3 },
		{ EAttributeType::Recoil, 0, -0.4 },
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.1 },
		{ EAttributeType::InaccuracyRegen, 0, 0.2 }
	};
}

RevolverStock3::RevolverStock3() {
	PartNum = 2;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Recoil, 0, -0.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, -0.2 },
		{ EAttributeType::InaccuracyRegen, 0, 0.4 }
	};
}


RevolverAcc0None::RevolverAcc0None() {
	PartNum = 0;
	Bonuses = {};
}

RevolverAcc1Masher::RevolverAcc1Masher() {
	Name = "Masher";
	PartNum = 1;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, -2.0 },
		{ EAttributeType::ProjectileCount, 6, 0.0 },
		{ EAttributeType::Spread, 0, 2.0 },
		{ EAttributeType::Recoil, 0, 1.0 }		
	};
}

RevolverAcc2Stabilised::RevolverAcc2Stabilised() {
	Name = "Stabilised";
	PartNum = 2;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Recoil, 0, -0.2 },
		{ EAttributeType::InaccuracyRegen, 0, 0.5 }
	};
}


RevolverPrefixQ0::RevolverPrefixQ0() {
	Name = "Brutal";
	Bonuses = {};
}

RevolverPrefixQ1::RevolverPrefixQ1() {
	Name = "Primal";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.06 }
	};
}

RevolverPrefixQ2::RevolverPrefixQ2() {
	Name = "Savage";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.09 }
	};
}

RevolverPrefixQ3::RevolverPrefixQ3() {
	Name = "Feral";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.12 }
	};
}

RevolverPrefixStabilised::RevolverPrefixStabilised() {
	Name = "Stabilised";
	Bonuses = {};
}

RevolverPrefixBloody::RevolverPrefixBloody() {
	Name = "Feral";
	PartRarity = 1;
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.12 }
	};
}

RevolverPrefixSwift::RevolverPrefixSwift() {
	Name = "Swift";
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Recoil, 0, -0.3 },
		{ EAttributeType::InaccuracyRegen, 0, 0.2 }
	};
}

RevolverPrefixRaw::RevolverPrefixRaw() {
	Name = "Raw";
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.16 },
		{ EAttributeType::FireRate, 0, 0.2 },
		{ EAttributeType::Spread, 0, 0.3 }
	};
}


RevolverTitleDefault::RevolverTitleDefault() {
	Name = "Revolver";
	Bonuses = {};
}

RevolverTitleMasher::RevolverTitleMasher() {
	Name = "Masher";
	Bonuses = {};
}

RevolverTitleJustice::RevolverTitleJustice() {
	Name = "Justice";
	Bonuses = {};
}

RevolverTitleLaw::RevolverTitleLaw() {
	Name = "Law";
	Bonuses = {};
}

RevolverTitleViper::RevolverTitleViper() {
	Name = "Viper";
	Bonuses = {};
}
