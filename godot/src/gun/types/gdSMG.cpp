#include "gun/types/gdSMG.h"
#include "gun/parts/catalogueSMG.h"

GDSMG::GDSMG() {
	GunType = EGunType::SMG;
	GunSubType = EGunSubType::None;
	FireMode = EFireMode::Automatic;
	DamageModifier = 0.8;

	BaseFireTime = 120;
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

	Prefix = GetEligiblePrefix();
	Title = GetEligibleTitle();
}

std::unique_ptr<PrefixComponent> GDSMG::GetEligiblePrefix() {
	PrefixComponent* prefix;

	if (Accessory->PartNum == 4) {
		prefix = new SMGPrefixDouble();
	}
	else if (Accessory->PartNum == 2) {
		prefix = new SMGPrefixRuthless();
	}
	else if (Accessory->PartNum == 1) {
		prefix = new SMGPrefixRelentless();
	}
	else if (RarityScore >= PrefixQ3Min) {
		prefix = new SMGPrefixQ3();
	}
	else if (RarityScore >= PrefixQ2Min) {
		prefix = new SMGPrefixQ2();
	}
	else if (RarityScore >= PrefixQ1Min) {
		prefix = new SMGPrefixQ1();
	}
	else {
		prefix = new SMGPrefixQ0();
	}

	return std::unique_ptr<PrefixComponent>(prefix);
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
