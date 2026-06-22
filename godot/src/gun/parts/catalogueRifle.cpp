#include "gun/parts/catalogueRifle.h"
#include "shared/utility.h"

constexpr int32_t NumCRBodies = 4;
constexpr int32_t NumMGBodies = 4;
constexpr int32_t NumCRBarrels = 4;
constexpr int32_t NumMGBarrels = 4;
constexpr int32_t NumCRStocks = 5;
constexpr int32_t NumMGStocks = 4;
constexpr int32_t NumCRMags = 3;
constexpr int32_t NumMGMags = 3;
constexpr int32_t NumCRAccs = 3;
constexpr int32_t NumMGAccs = 4;

std::unique_ptr<BodyComponent> GetRandomCRBody() {
	int32_t bodyIndex = GetRandomInt(0, NumCRBodies - 1);
	BodyComponent* body;

	switch (bodyIndex) {
		case 1:
			body = new ARBody1CR();
			break;

		case 2:
			body = new ARBody2();
			break;

		case 3:
			body = new ARBody3();
			break;

		default:
			body = new ARBody4();
			break;
	}

	return std::unique_ptr<BodyComponent>(body);
}

std::unique_ptr<BodyComponent> GetRandomMGBody() {
	int32_t bodyIndex = GetRandomInt(0, NumMGBodies - 1);
	BodyComponent* body;

	switch (bodyIndex) {
		case 1:
			body = new ARBody1MG();
			break;

		case 2:
			body = new ARBody2();
			break;

		case 3:
			body = new ARBody3();
			break;

		default:
			body = new ARBody4();
			break;
	}

	return std::unique_ptr<BodyComponent>(body);
}

std::unique_ptr<BarrelComponent> GetRandomCRBarrel() {
	int32_t barrelIndex = GetRandomInt(0, NumCRBarrels - 1);
	BarrelComponent* barrel;

	switch (barrelIndex) {
		case 1:
			barrel = new ARBarrel1CR();
			break;

		case 2:
			barrel = new ARBarrel2();
			break;

		case 3:
			barrel = new ARBarrel3();
			break;

		default:
			barrel = new ARBarrel4();
			break;
	}

	return std::unique_ptr<BarrelComponent>(barrel);
}

std::unique_ptr<BarrelComponent> GetRandomMGBarrel() {
	int32_t barrelIndex = GetRandomInt(0, NumMGBarrels - 1);
	BarrelComponent* barrel;

	switch (barrelIndex) {
		case 1:
			barrel = new ARBarrel1MG();
			break;

		case 2:
			barrel = new ARBarrel2();
			break;

		case 3:
			barrel = new ARBarrel3();
			break;

		default:
			barrel = new ARBarrel4();
			break;
	}

	return std::unique_ptr<BarrelComponent>(barrel);
}

std::unique_ptr<StockComponent> GetRandomCRStock() {
	int32_t stockIndex = GetRandomInt(0, NumCRStocks - 1);
	StockComponent* stock;

	switch (stockIndex) {
		case 1:
			stock = new ARStock1CR();
			break;

		case 2:
			stock = new ARStock2();
			break;

		case 3:
			stock = new ARStock3();
			break;

		case 4:
			stock = new ARStock4();
			break;

		default:
			stock = new ARStock0CRNone();
			break;
	}

	return std::unique_ptr<StockComponent>(stock);
}

std::unique_ptr<StockComponent> GetRandomMGStock() {
	int32_t stockIndex = GetRandomInt(0, NumMGStocks - 1);
	StockComponent* stock;

	switch (stockIndex) {
		case 1:
			stock = new ARStock1MG();
			break;

		case 2:
			stock = new ARStock2();
			break;

		case 3:
			stock = new ARStock3();
			break;

		default:
			stock = new ARStock4();
			break;
	}

	return std::unique_ptr<StockComponent>(stock);
}

std::unique_ptr<MagazineComponent> GetRandomCRMag() {
	int32_t magIndex = GetRandomInt(0, NumCRMags - 1);
	MagazineComponent* mag;

	switch (magIndex) {
		case 1:
			mag = new CRMag1();
			break;

		case 2:
			mag = new CRMag2Pounder();
			break;

		default:
			mag = new CRMag3();
			break;
	}

	return std::unique_ptr<MagazineComponent>(mag);
}

std::unique_ptr<MagazineComponent> GetRandomMGMag() {
	int32_t magIndex = GetRandomInt(0, NumMGMags - 1);
	MagazineComponent* mag;

	switch (magIndex) {
		case 1:
			mag = new MGMag1();
			break;

		case 2:
			mag = new MGMag2();
			break;

		default:
			mag = new MGMag3();
			break;
	}

	return std::unique_ptr<MagazineComponent>(mag);
}

std::unique_ptr<AccessoryComponent> GetRandomCRAcc() {
	int32_t accIndex = GetRandomInt(0, NumCRAccs - 1);
	AccessoryComponent* acc;

	switch (accIndex) {
		case 1:
			acc = new ARAcc1Deathly();
			break;

		case 2:
			acc = new CRAcc2Intense();
			break;

		default:
			acc = new ARAcc0None();
			break;
	}

	return std::unique_ptr<AccessoryComponent>(acc);
}

std::unique_ptr<AccessoryComponent> GetRandomMGAcc() {
	int32_t accIndex = GetRandomInt(0, NumMGAccs - 1);
	AccessoryComponent* acc;

	switch (accIndex) {
		case 1:
			acc = new ARAcc1Deathly();
			break;

		case 2:
			acc = new MGAcc2Frantic();
			break;

		case 3:
			acc = new MGAcc3Shattering();
			break;

		default:
			acc = new ARAcc0None();
			break;
	}

	return std::unique_ptr<AccessoryComponent>(acc);
}


ARBody1CR::ARBody1CR() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.08 }
	};
}

ARBody1MG::ARBody1MG() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::FireRate, 0, -0.17 },
		{ EAttributeType::Recoil, 0, 0.3 },
	};
}

ARBody2::ARBody2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.15 },
		{ EAttributeType::FireRate, 0, 0.3 },
		{ EAttributeType::Recoil, 0, -0.3 },
	};
}

ARBody3::ARBody3() {
	PartNum = 3;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, -0.23 },
		{ EAttributeType::Recoil, 0, 0.5 },
	};
}

ARBody4::ARBody4() {
	PartNum = 4;
	PartRarity = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, 0.5 },
		{ EAttributeType::Recoil, 0, -0.2 },
	};
}


ARBarrel1CR::ARBarrel1CR() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, -0.04 },
	};
}

ARBarrel1MG::ARBarrel1MG() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, 0.28 },
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, 0.2 },
		{ EAttributeType::Recoil, 0, 0.2 },
	};
}

ARBarrel2::ARBarrel2() {
	PartNum = 2;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, -0.5 },
		{ EAttributeType::InaccuracyMin, 0, -0.3 },
		{ EAttributeType::InaccuracyMax, 0, -0.3 },
	};
}

ARBarrel3::ARBarrel3() {
	PartNum = 3;
	PartRarity = 4;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.3 },
		{ EAttributeType::Spread, 0, -0.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.4 },
		{ EAttributeType::Recoil, 0, 0.35 },
	};
}

ARBarrel4::ARBarrel4() {
	PartNum = 4;
	PartRarity = 5;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, -1.3 },
		{ EAttributeType::InaccuracyMin, 0, -0.4 },
		{ EAttributeType::InaccuracyMax, 0, -1.5 },
		{ EAttributeType::Recoil, 0, -0.5 },
	};
}


ARStock0CRNone::ARStock0CRNone() {
	PartNum = 0;
	PartRarity = 0;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, 0.5 },
		{ EAttributeType::InaccuracyMax, 0, -0.2 },
		{ EAttributeType::InaccuracyRegen, 0, 1.0 },
		{ EAttributeType::Recoil, 0, 0.4 },
		{ EAttributeType::ReloadSpeed, 0, 0.3 },
	};
}

ARStock1CR::ARStock1CR() {
	PartNum = 1;
	PartRarity = 0;
	Bonuses = {
		{ EAttributeType::InaccuracyRegen, 0, 0.2 },
	};
}

ARStock1MG::ARStock1MG() {
	PartNum = 1;
	PartRarity = 0;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.1 },
		{ EAttributeType::InaccuracyMax, 0, -0.1 },
		{ EAttributeType::InaccuracyRegen, 0, 0.2 },
		{ EAttributeType::Recoil, 0, -0.4 },
		{ EAttributeType::ReloadSpeed, 0, -0.3 },
	};
}

ARStock2::ARStock2() {
	PartNum = 2;
	PartRarity = 1;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.2 },
		{ EAttributeType::InaccuracyMax, 0, -0.2 },
		{ EAttributeType::InaccuracyRegen, 0, 0.4 },
		{ EAttributeType::Recoil, 0, -0.3 },
	};
}

ARStock3::ARStock3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.3 },
		{ EAttributeType::InaccuracyMax, 0, -0.3 },
		{ EAttributeType::InaccuracyRegen, 0, 0.6 },
		{ EAttributeType::Recoil, 0, -0.8 },
		{ EAttributeType::ReloadSpeed, 0, -0.2 },
	};
}

ARStock4::ARStock4() {
	PartNum = 4;
	PartRarity = 4;
	Bonuses = {
		{ EAttributeType::InaccuracyMin, 0, -0.4 },
		{ EAttributeType::InaccuracyMax, 0, -0.4 },
		{ EAttributeType::InaccuracyRegen, 0, 0.8 },
		{ EAttributeType::Recoil, 0, -1.0 },
	};
}


CRMag1::CRMag1() {
	PartNum = 1;
	Bonuses = {};
}

CRMag2Pounder::CRMag2Pounder() {
	PartNum = 2;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.52 },
		{ EAttributeType::FireRate, 0, -0.67 },
		{ EAttributeType::ReloadSpeed, 0, 0.4 },
		{ EAttributeType::MagSize, -6, 0.0 },
	};
}

CRMag3::CRMag3() {
	PartNum = 3;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::MagSize, 6, 0.0 },
	};
}

MGMag1::MGMag1() {
	PartNum = 1;
	Bonuses = {
		{ EAttributeType::ReloadSpeed, 0, 0.15 },
	};
}

MGMag2::MGMag2() {
	PartNum = 2;
	PartRarity = 2;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::ReloadSpeed, 0, -0.25 },
		{ EAttributeType::MagSize, 12, 0.0 },
	};
}

MGMag3::MGMag3() {
	PartNum = 3;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.18 },
		{ EAttributeType::ReloadSpeed, 0, -0.35 },
		{ EAttributeType::MagSize, 24, 0.0 },
	};
}


ARAcc0None::ARAcc0None() {
	PartNum = 0;
	Bonuses = {};
}

ARAcc1Deathly::ARAcc1Deathly() {
	Name = "Deathly";
	PartNum = 1;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::Recoil, 0, -0.25 },
		{ EAttributeType::InaccuracyRegen, 0, -0.25 },
	};
}

CRAcc2Intense::CRAcc2Intense() {
	Name = "Intense";
	PartNum = 2;
	PartRarity = 3;
	Bonuses = {
		// +50% Crit Damage, midlertidigt erstattet med damage
		// +2 Tech
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::Spread, 0, -0.15 },
		{ EAttributeType::InaccuracyMin, 0, -0.4 },
		{ EAttributeType::InaccuracyMax, 0, -0.4 },
	};
}

MGAcc2Frantic::MGAcc2Frantic() {
	Name = "Frantic";
	PartNum = 2;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::FireRate, 0, 0.3 },
		{ EAttributeType::ReloadSpeed, 0, 0.6 },
	};
}

MGAcc3Shattering::MGAcc3Shattering() {
	Name = "Shattering";
	PartNum = 3;
	PartRarity = 3;
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.3 },
		{ EAttributeType::ReloadSpeed, 0, 0.6 },
	};
}


CRTitleDefault::CRTitleDefault() {
	Title = "Rifle";
	Bonuses = {};
}

CRTitlePounder::CRTitlePounder() {
	Title = "Pounder";
	Bonuses = {};
}

CRTitleCobra::CRTitleCobra() {
	Title = "Cobra";
	Bonuses = {
		{ EAttributeType::Recoil, 0, -0.4 }
	};
}

CRTitleStomper::CRTitleStomper() {
	Title = "Stomper";
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.5 },
		{ EAttributeType::ProjectileSpeed, 0, -2.0 }
	};
}

MGTitleDefault::MGTitleDefault() {
	Title = "Machine Gun";
	Bonuses = {};
}

MGTitleMauler::MGTitleMauler() {
	Title = "Mauler";
	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 }
	};
}

MGTitleHavoc::MGTitleHavoc() {
	Title = "Havoc";
	Bonuses = {
		{ EAttributeType::MagSize, 0, 0.2 }
	};
}

MGTitleMassacre::MGTitleMassacre() {
	Title = "Massacre";
	Bonuses = {
		{ EAttributeType::Recoil, 0, -0.4 }
	};
}
