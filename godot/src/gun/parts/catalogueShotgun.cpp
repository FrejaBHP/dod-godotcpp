#include "gun/parts/catalogueShotgun.h"
#include "shared/utility.h"

constexpr int32_t NumBodies = 5;
constexpr int32_t NumCSBarrels = 7;
constexpr int32_t NumASBarrels = 5;
constexpr int32_t NumStocks = 4;
constexpr int32_t NumCSMags = 4;
constexpr int32_t NumASMags = 2;
constexpr int32_t NumCSAccs = 2;
constexpr int32_t NumASAccs = 2;

std::unique_ptr<BodyComponent> GetRandomShotgunBody() {
	int32_t bodyIndex = GetRandomInt(0, NumBodies - 1);
	BodyComponent* body;

	switch (bodyIndex) {
		case 1:
			body = new ShotgunBody1();
			break;

		case 2:
			body = new ShotgunBody2();
			break;

		case 3:
			body = new ShotgunBody3();
			break;

		case 4:
			body = new ShotgunBody4();
			break;

		default:
			body = new ShotgunBody5();
			break;
	}

	return std::unique_ptr<BodyComponent>(body);
}
std::unique_ptr<BarrelComponent> GetRandomCSBarrel() {
	int32_t index = GetRandomInt(0, NumCSBarrels - 1);
	BarrelComponent* barrel;

	switch (index) {
		case 1:
			barrel = new ShotgunBarrel1();
			break;

		case 2:
			barrel = new ShotgunBarrel2();
			break;

		case 3:
			barrel = new ShotgunBarrel3();
			break;

		case 4:
			barrel = new ShotgunBarrel4();
			break;

		case 5:
			barrel = new ShotgunBarrel5();
			break;

		case 6:
			barrel = new CSBarrel6Shredder();
			break;

		default:
			barrel = new CSBarrel7Carnage();
			break;
	}

	return std::unique_ptr<BarrelComponent>(barrel);
}

std::unique_ptr<BarrelComponent> GetRandomASBarrel() {
	int32_t index = GetRandomInt(0, NumASBarrels - 1);
	BarrelComponent* barrel;

	switch (index) {
		case 1:
			barrel = new ShotgunBarrel1();
			break;

		case 2:
			barrel = new ShotgunBarrel2();
			break;

		case 3:
			barrel = new ShotgunBarrel3();
			break;

		case 4:
			barrel = new ShotgunBarrel4();
			break;

		default:
			barrel = new ShotgunBarrel5();
			break;
	}

	return std::unique_ptr<BarrelComponent>(barrel);
}

std::unique_ptr<StockComponent> GetRandomShotgunStock() {
	int32_t index = GetRandomInt(0, NumStocks - 1);
	StockComponent* stock;

	switch (index) {
		case 1:
			stock = new ShotgunStock1();
			break;

		case 2:
			stock = new ShotgunStock2();
			break;

		case 3:
			stock = new ShotgunStock3();
			break;

		default:
			stock = new ShotgunStock0None();
			break;
	}

	return std::unique_ptr<StockComponent>(stock);
}

std::unique_ptr<MagazineComponent> GetRandomCSMag() {
	int32_t index = GetRandomInt(0, NumCSMags - 1);
	MagazineComponent* mag;

	switch (index) {
		case 1:
			mag = new CSMag1();
			break;

		case 2:
			mag = new CSMag2();
			break;

		case 3:
			mag = new CSMag3();
			break;

		default:
			mag = new CSMag4();
			break;
	}

	return std::unique_ptr<MagazineComponent>(mag);
}

std::unique_ptr<MagazineComponent> GetRandomASMag() {
	int32_t index = GetRandomInt(0, NumASMags - 1);
	MagazineComponent* mag;

	switch (index) {
		case 1:
			mag = new ASMag1();
			break;

		default:
			mag = new ASMag2();
			break;
	}

	return std::unique_ptr<MagazineComponent>(mag);
}

std::unique_ptr<AccessoryComponent> GetRandomCSAccessory() {
	int32_t index = GetRandomInt(0, NumCSAccs - 1);
	AccessoryComponent* acc;

	switch (index) {
		case 1:
			acc = new CSAcc1Frenzied();
			break;

		default:
			acc = new CSAcc2Terrible();
			break;
	}

	return std::unique_ptr<AccessoryComponent>(acc);
}

std::unique_ptr<AccessoryComponent> GetRandomASAccessory() {
	int32_t index = GetRandomInt(0, NumASAccs - 1);
	AccessoryComponent* acc;

	switch (index) {
		case 1:
			acc = new ASAcc1Raging();
			break;

		default:
			acc = new ASAcc2Painful();
			break;
	}

	return std::unique_ptr<AccessoryComponent>(acc);
}


ShotgunBody1::ShotgunBody1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.08 }
	};
}

ShotgunBody2::ShotgunBody2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::FireRate, 0, -0.17 },
		{ EAttributeType::Recoil, 0, 0.3 }
	};
}

ShotgunBody3::ShotgunBody3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		// Tech +3
		{ EAttributeType::Damage, 0, -0.15 },
		{ EAttributeType::FireRate, 0, 0.3 },
		{ EAttributeType::Recoil, 0, -0.3 }
	};
}

ShotgunBody4::ShotgunBody4() {
	PartNum = 4;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, -0.23 },
		{ EAttributeType::Recoil, 0, 0.5 }
	};
}

ShotgunBody5::ShotgunBody5() {
	PartNum = 5;
	PartRarity = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, 0.5 },
		{ EAttributeType::Recoil, 0, -0.2 }
	};
}


ShotgunBarrel1::ShotgunBarrel1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.04 }
	};
}

ShotgunBarrel2::ShotgunBarrel2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, 0.28 },
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, 0.2 },
		{ EAttributeType::Recoil, 0, 0.2 }
	};
}

ShotgunBarrel3::ShotgunBarrel3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		// Tech +2
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, -0.5 },
		{ EAttributeType::InaccuracyMin, 0, -0.5 },
		{ EAttributeType::InaccuracyMax, 0, -0.3 }
	};
}

ShotgunBarrel4::ShotgunBarrel4() {
	PartNum = 4;
	PartRarity = 4;
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.3 },
		{ EAttributeType::Spread, 0, -0.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.4 },
		{ EAttributeType::Recoil, 0, 0.35 }
	};
}

ShotgunBarrel5::ShotgunBarrel5() {
	PartNum = 5;
	PartRarity = 5;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, -1.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.4 },
		{ EAttributeType::InaccuracyMax, 0, -1.5 },
		{ EAttributeType::Recoil, 0, -0.5 }
	};
}

CSBarrel6Shredder::CSBarrel6Shredder() {
	PartNum = 6;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, 0.28 },
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, 0.2 },
		{ EAttributeType::Recoil, 0, 0.2 }
	};
}

CSBarrel7Carnage::CSBarrel7Carnage() {
	PartNum = 7;
	PartRarity = 1;
	Bonuses = {
		// Tech -500 ???
		{ EAttributeType::Damage, 0, 5.0 },
		{ EAttributeType::ProjectileCount, -99, 0.0 },
		{ EAttributeType::Spread, 0, -0.5 },
		{ EAttributeType::InaccuracyMin, 0, -0.3 },
		{ EAttributeType::InaccuracyMax, 0, -0.3 }
	};
}


ShotgunStock0None::ShotgunStock0None() {
	PartNum = 0;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyRegen, 0, 1.0 },
		{ EAttributeType::Recoil, 0, 0.4 },
		{ EAttributeType::ReloadSpeed, 0, 0.3 }
	};
}

ShotgunStock1::ShotgunStock1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::InaccuracyRegen, 0, 0.2 }
	};
}

ShotgunStock2::ShotgunStock2() {
	PartNum = 2;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.1 },
		{ EAttributeType::InaccuracyRegen, 0, 0.2 },
		{ EAttributeType::Recoil, 0, -0.4 },
		{ EAttributeType::ReloadSpeed, 0, -0.3 }
	};
}

ShotgunStock3::ShotgunStock3() {
	PartNum = 3;
	PartRarity = 4;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, -0.2 },
		{ EAttributeType::InaccuracyRegen, 0, 0.4 },
		{ EAttributeType::Recoil, 0, -0.3 }
	};
}


CSMag1::CSMag1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.18 },
		{ EAttributeType::ReloadSpeed, 0, 0.4 }
	};
}

CSMag2::CSMag2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::MagSize, 6, 0.0 },
		{ EAttributeType::ReloadSpeed, 0, -0.6 }
	};
}

CSMag3::CSMag3() {
	PartNum = 3;
	PartRarity = 1;
	Bonuses = {};
}

CSMag4::CSMag4() {
	PartNum = 4;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, 1.02 },
		{ EAttributeType::MagSize, -4, 0.0 },
		{ EAttributeType::ReloadSpeed, 0, 0.5 }
	};
}

ASMag1::ASMag1() {
	PartNum = 1;
	Bonuses = {};
}

ASMag2::ASMag2() {
	PartNum = 2;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::MagSize, 2, 0.0 }
	};
}


ShotgunAcc0None::ShotgunAcc0None() {
	PartNum = 0;
	Bonuses = {};
}

CSAcc1Frenzied::CSAcc1Frenzied() {
	Name = "Frenzied";
	PartNum = 1;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.4 }
	};
}

CSAcc2Terrible::CSAcc2Terrible() {
	Name = "Terrible";
	PartNum = 2;
	PartRarity = 2;
	Bonuses = {
		// 23% knockback
		{ EAttributeType::Damage, 0, 0.13 }
	};
}

ASAcc1Raging::ASAcc1Raging() {
	Name = "Raging";
	PartNum = 1;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.2 },
		{ EAttributeType::ReloadSpeed, 0, 0.2 }
	};
}

ASAcc2Painful::ASAcc2Painful() {
	Name = "Painful";
	PartNum = 2;
	PartRarity = 2;
	Bonuses = {
		// 23% knockback
		{ EAttributeType::Damage, 0, 0.13 }
	};
}


CSPrefixQ0::CSPrefixQ0() {
	Name = "Combat";
	Bonuses = {};
}

CSPrefixQ1::CSPrefixQ1() {
	Name = "Battle";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.06 }
	};
}

CSPrefixQ2::CSPrefixQ2() {
	Name = "War";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.09 }
	};
}

CSPrefixQ3::CSPrefixQ3() {
	Name = "Atrocity";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.12 }
	};
}

CSPrefixTerrible::CSPrefixTerrible() {
	Name = "Terrible";
	Bonuses = {};
}

CSPrefixFrenzied::CSPrefixFrenzied() {
	Name = "Frenzied";
	Bonuses = {};
}

CSPrefixHunter::CSPrefixHunter() {
	Name = "Hunter's";
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::InaccuracyMin, 0, -0.15 },
		{ EAttributeType::ProjectileCount, 0, -0.2 }
	};
}

CSPrefixRiot::CSPrefixRiot() {
	Name = "Riot";
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.15 },
		{ EAttributeType::Spread, 0, 0.2 },
		{ EAttributeType::ProjectileCount, 1, 0.0 }
	};
}

ASPrefixQ0::ASPrefixQ0() {
	Name = "Assault";
	Bonuses = {};
}

ASPrefixQ1::ASPrefixQ1() {
	Name = "Grievous";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.06 }
	};
}

ASPrefixQ2::ASPrefixQ2() {
	Name = "Lethal";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.09 }
	};
}

ASPrefixQ3::ASPrefixQ3() {
	Name = "Fatal";
	Bonuses = {
		// Tech +1
		{ EAttributeType::Damage, 0, 0.12 }
	};
}

ASPrefixRaging::ASPrefixRaging() {
	Name = "Raging";
	Bonuses = {};
}

ASPrefixPainful::ASPrefixPainful() {
	Name = "Raging";
	Bonuses = {};
}

ASPrefixAngry::ASPrefixAngry() {
	Name = "Angry";
	PartRarity = 2;
	Bonuses = {
		// Swap Speed +30%
		{ EAttributeType::FireRate, 0, 0.2 },
		{ EAttributeType::ReloadSpeed, 0, 0.3 },
	};
}


ShotgunTitleDefault::ShotgunTitleDefault() {
	Name = "Shotgun";
	Bonuses = {};
}

CSTitleMatador::CSTitleMatador() {
	Name = "Matador";
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.25 },
		{ EAttributeType::ProjectileCount, 0, 0.35 }
	};
}

CSTitleScattergun::CSTitleScattergun() {
	Name = "Scattergun";
	Bonuses = {
		{ EAttributeType::ProjectileCount, 0, 0.3 }
	};
}

CSTitleShredder::CSTitleShredder() {
	Name = "Shredder";
	Bonuses = {
		{ EAttributeType::ProjectileCount, 2, 0.0 },
		{ EAttributeType::Spread, 0, 0.15 }
	};
}

CSTitleCarnage::CSTitleCarnage() {
	Name = "Carnage";
	Bonuses = {};
}

ASTitleBrute::ASTitleBrute() {
	Name = "Brute";
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.22 }
	};
}

ASTitleDeath::ASTitleDeath() {
	Name = "Death";
	PartRarity = 1;
	Bonuses = {
		// Crit Damage +15%
		// Tech +2
		{ EAttributeType::Damage, 0, 0.05 }, // midlertidig crit damage erstatning
		{ EAttributeType::InaccuracyMin, 0, -0.25 }
	};
}

ASTitleSweeper::ASTitleSweeper() {
	Name = "Sweeper";
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::ProjectileCount, 1, 0.0 }
	};
}
