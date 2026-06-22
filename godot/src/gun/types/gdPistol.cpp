#include "gun/types/gdPistol.h"
#include "gun/parts/cataloguePistol.h"

GDPistol::GDPistol() {
	GunType = EGunType::Pistol;
	DefaultPrefix = "Bad";

	BaseDamage = 6.0;
	BaseFireTime = 275;
	BaseMagSize = 12;
	BaseReloadTime = 2.0;

	BaseSpread = 2.0;
	BaseRecoil = 2.0;
	BaseMinInaccuracy = 1.5;
	BaseMaxInaccuracy = 8;
	BaseInaccuracyRegen = 12;
}

void GDPistol::AssembleRandomGun() {
	Body = GetRandomPistolBody();

	if (Body->PartNum == 5) {
		GunSubType = EGunSubType::MachinePistol;
		FireMode = EFireMode::Automatic;

		BaseDamage = 6.0;
		BaseFireTime = 120;
		BaseMagSize = 16;
		BaseReloadTime = 2.25;

		BaseSpread = 2.0;
		BaseRecoil = 1.5;
		BaseMinInaccuracy = 2;
		BaseMaxInaccuracy = 12;
		BaseInaccuracyRegen = 8;

		Magazine = GetRandomMPMag();
		Accessory = GetRandomMPAccessory();
	}
	else {
		GunSubType = EGunSubType::Repeater;
		FireMode = EFireMode::Semi;

		BaseDamage = 6.0;
		BaseFireTime = 275;
		BaseMagSize = 12;
		BaseReloadTime = 2.0;

		BaseSpread = 2.0;
		BaseRecoil = 2.0;
		BaseMinInaccuracy = 1.5;
		BaseMaxInaccuracy = 8;
		BaseInaccuracyRegen = 12;

		Magazine = GetRandomRepeaterMag();
		Accessory = GetRandomRepeaterAccessory();
	}

	Barrel = GetRandomPistolBarrel();
	Action = GetRandomPistolAction();
	
	ApplyPartsBonuses();

	Title = GetEligibleTitle();
}

void GDPistol::ApplyPartsBonuses() {
	GunDefinition::ApplyPartsBonuses();

	if (Action.get() != nullptr) {
		for (size_t i = 0; i < Action->Bonuses.size(); i++) {
			AttrBonuses[Action->Bonuses[i].AttrType] += Action->Bonuses[i];
		}
		RarityScore += Action->PartRarity;
	}

	// FIXME: Skal fjernes senere
	CalculateStats();
}

std::unique_ptr<TitleComponent> GDPistol::GetEligibleTitle() {
	TitleComponent* title;

	if (GunSubType == EGunSubType::Repeater) {
		if (FireTime <= 180) {
			title = new RepeaterTitleNeedler();
		}
		else if (Accuracy >= 91.0) {
			title = new RepeaterTitleSwatter();
		}
		else if (Accuracy >= 85.0 && FireTime > 180) {
			title = new RepeaterTitleRaptor();
		}
		else {
			title = new RepeaterTitleDefault();
		}
	}
	else {
		if (Accessory->PartNum == 4) {
			title = new MPTitleRage();
		}
		else if (AttrBonuses[EAttributeType::Damage].Scale > 0.25) {
			title = new MPTitleTorment();
		}
		else if (Accuracy <= 79 && FireTime <= 100) { // 75
			title = new MPTitleFury();
		}
		else {
			title = new MPTitleDefault();
		}
	}
	
	return std::unique_ptr<TitleComponent>(title);
}
