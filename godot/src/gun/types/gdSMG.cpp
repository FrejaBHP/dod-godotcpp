#include "gun/types/gdSMG.h"
#include "gun/parts/catalogueSMG.h"

GDSMG::GDSMG() {
	GunType = EGunType::SMG;
	GunSubType = EGunSubType::None;
	FireMode = EFireMode::Automatic;
	DefaultPrefix = "Patrol";

	BaseDamage = 3.0;
	BaseFireTime = 150;
	BaseMagSize = 28;
	BaseReloadTime = 2.2;

	BaseSpread = 2.0;
	BaseRecoil = 1.5;
	BaseMinInaccuracy = 2;
	BaseMaxInaccuracy = 10;
	BaseInaccuracyRegen = 10;
}

void GDSMG::AssembleRandomGun() {
	Barrel = GetRandomSMGBarrel();
	Body = GetRandomSMGBody();
	Magazine = GetRandomSMGMag();
	Stock = GetRandomSMGStock();
	Accessory = GetRandomSMGAccessory();

	ApplyPartsBonuses();

	Title = GetEligibleTitle();
}

std::unique_ptr<TitleComponent> GDSMG::GetEligibleTitle() {
	TitleComponent* title;

	if (Magazine->PartNum == 1) {
		title = new SMGTitleThumper();
	}
	else if (Accessory->PartNum == 4 && Accuracy <= 70.0) {
		title = new SMGTitleAnarchy();
	}
	else if (FireTime <= 83) {
		title = new SMGTitleStinger();
	}
	else if (AttrBonuses[EAttributeType::Damage].Scale >= 0.33) {
		title = new SMGTitleBruiser();
	}
	else {
		title = new SMGTitleDefault();
	}

	return std::unique_ptr<TitleComponent>(title);
}
