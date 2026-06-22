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
		DefaultPrefix = "Combat";

		BaseDamage = 6.0;
		BaseFireTime = 275;
		BaseMagSize = 12;
		BaseReloadTime = 2.0;

		BaseSpread = 1.3;
		BaseRecoil = 3.5;
		BaseMinInaccuracy = 1.5;
		BaseMaxInaccuracy = 12.0;
		BaseInaccuracyRegen = 8.0;

		Body = GetRandomCRBody();
		Stock = GetRandomCRStock();
		Magazine = GetRandomCRMag();
	}
	else {
		GunSubType = EGunSubType::MachineGun;
		DefaultPrefix = "Combat";

		BaseDamage = 6.0;
		BaseFireTime = 275;
		BaseMagSize = 12;
		BaseReloadTime = 2.0;

		BaseSpread = 2.4;
		BaseRecoil = 2.2;
		BaseMinInaccuracy = 2.0;
		BaseMaxInaccuracy = 14.0;
		BaseInaccuracyRegen = 8.0;

		Body = GetRandomMGBody();
		Stock = GetRandomMGStock();
		Magazine = GetRandomMGMag();
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
		else {
			title = new CRTitleDefault();
		}
	}
	else {
		title = new MGTitleDefault();
	}

	return std::unique_ptr<TitleComponent>(title);
}
