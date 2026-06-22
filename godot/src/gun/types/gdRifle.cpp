#include "gun/types/gdRifle.h"
#include "gun/parts/catalogueRifle.h"
#include "shared/utility.h"

GDRifle::GDRifle() {
	GunType = EGunType::Rifle;
}

void GDRifle::AssembleRandomGun() {
	int32_t subtype = GetRandomInt(0, 1);

	if (subtype == 0) {
		GunSubType = EGunSubType::CombatRifle;
		FireMode = EFireMode::Burst;
		DefaultPrefix = "Combat";

		BaseDamage = 6.0;
		BaseFireTime = 100;
		BaseMagSize = 12;
		BaseReloadTime = 2.4;

		BaseSpread = 1.3;
		BaseRecoil = 3.5;
		BaseMinInaccuracy = 1.5;
		BaseMaxInaccuracy = 12.0;
		BaseInaccuracyRegen = 8.0;

		Body = GetRandomCRBody();
		Barrel = GetRandomCRBarrel();
		Stock = GetRandomCRStock();
		Magazine = GetRandomCRMag();
		Accessory = GetRandomCRAcc();

		if (Magazine->PartNum == 2) {
			FireMode = EFireMode::Semi;
		}
	}
	else {
		GunSubType = EGunSubType::MachineGun;
		FireMode = EFireMode::Automatic;
		DefaultPrefix = "Combat";

		BaseDamage = 6.0;
		BaseFireTime = 167;
		BaseMagSize = 24;
		BaseReloadTime = 3.0;

		BaseSpread = 2.4;
		BaseRecoil = 2.2;
		BaseMinInaccuracy = 2.0;
		BaseMaxInaccuracy = 14.0;
		BaseInaccuracyRegen = 8.0;

		Body = GetRandomMGBody();
		Barrel = GetRandomMGBarrel();
		Stock = GetRandomMGStock();
		Magazine = GetRandomMGMag();
		Accessory = GetRandomMGAcc();
	}

	ApplyPartsBonuses();

	Title = GetEligibleTitle();
}

void GDRifle::ApplyPartsBonuses() {
	GunDefinition::ApplyPartsBonuses();

	// FIXME: Skal fjernes senere
	CalculateStats();
}

std::unique_ptr<TitleComponent> GDRifle::GetEligibleTitle() {
	TitleComponent* title;

	if (GunSubType == EGunSubType::CombatRifle) {
		if (Magazine->PartNum == 2) {
			title = new CRTitlePounder();
		}
		else if (Accuracy >= 93.0) {
			title = new CRTitleCobra();
		}
		else if (AttrBonuses[EAttributeType::Damage].Scale > 0.45) {
			title = new CRTitleStomper();
		}
		else {
			title = new CRTitleDefault();
		}
	}
	else {
		if (FireTime <= 100) {
			title = new MGTitleHavoc();
		}
		else if (Accuracy >= 91.3) {
			title = new MGTitleMassacre();
		}
		else if (AttrBonuses[EAttributeType::Damage].Scale > 0.8) {
			title = new MGTitleMauler();
		}
		else {
			title = new MGTitleDefault();
		}
	}

	return std::unique_ptr<TitleComponent>(title);
}
