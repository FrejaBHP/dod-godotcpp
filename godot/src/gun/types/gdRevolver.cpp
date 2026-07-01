#include "gun/types/gdRevolver.h"
#include "gun/parts/catalogueRevolver.h"

GDRevolver::GDRevolver() {
	GunType = EGunType::Pistol;
	GunSubType = EGunSubType::Revolver;
	FireMode = EFireMode::Semi;
	DamageModifier = 2.4;

	BaseFireTime = 800;
	BaseMagSize = 6;
	BaseReloadTime = 2.5;

	BaseSpread = 1.0;
	BaseRecoil = 3.0;
	BaseMinInaccuracy = 1.5;
	BaseMaxInaccuracy = 12;
	BaseInaccuracyRegen = 7.0;

	// Critical Damage +1
}

void GDRevolver::AssembleRandomGun() {
	Barrel = GetRandomRevolverBarrel();
	Body = GetRandomRevolverBody();
	Magazine = GetRandomRevolverMagazine();
	Stock = GetRandomRevolverStock();
	Accessory = GetRandomRevolverAccessory();

	ApplyPartsBonuses();

	Prefix = GetEligiblePrefix();
	Title = GetEligibleTitle();
}

std::unique_ptr<PrefixComponent> GDRevolver::GetEligiblePrefix() {
	PrefixComponent* prefix;

	if (FireTime <= 600) {
		prefix = new RevolverPrefixSwift();
	}
	else if (AttrBonuses[EAttributeType::Damage].Scale >= 0.33) {
		prefix = new RevolverPrefixBloody();
	}
	else if (Spread >= 1.5 && ProjectileCount == 1) {
		prefix = new RevolverPrefixRaw();
	}
	else if (Accessory->PartNum == 2) {
		prefix = new RevolverPrefixStabilised();
	}
	else if (RarityScore >= PrefixQ3Min) {
		prefix = new RevolverPrefixQ3();
	}
	else if (RarityScore >= PrefixQ2Min) {
		prefix = new RevolverPrefixQ2();
	}
	else if (RarityScore >= PrefixQ1Min) {
		prefix = new RevolverPrefixQ1();
	}
	else {
		prefix = new RevolverPrefixQ0();
	}

	return std::unique_ptr<PrefixComponent>(prefix);
}

std::unique_ptr<TitleComponent> GDRevolver::GetEligibleTitle() {
	TitleComponent* title;

	if (Accessory->PartNum == 1) {
		title = new RevolverTitleMasher();
	}
	else if (AttrBonuses[EAttributeType::Damage].Scale >= 0.15) {
		title = new RevolverTitleJustice();
	}
	else if (Accuracy >= 95.0) {
		title = new RevolverTitleViper();
	}
	else if (FireTime <= 625) {
		title = new RevolverTitleLaw();
	}
	else {
		title = new RevolverTitleDefault();
	}

	return std::unique_ptr<TitleComponent>(title);
}
