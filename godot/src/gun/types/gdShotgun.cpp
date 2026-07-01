#include "gun/types/gdShotgun.h"
#include "gun/parts/catalogueShotgun.h"

GDShotgun::GDShotgun() {
	GunType = EGunType::Shotgun;
	FireMode = EFireMode::Semi;
}

void GDShotgun::AssembleRandomGun() {
	int32_t subtype = GetRandomInt(0, 1);

	Body = GetRandomShotgunBody();
	Stock = GetRandomShotgunStock();

	if (subtype == 0) {
		GunSubType = EGunSubType::CombatShotgun;
		DamageModifier = 0.8;

		BaseProjectileCount = 9;
		BaseFireTime = 1150; // 1350 default
		BaseMagSize = 6;
		BaseReloadTime = 4.0;

		BaseSpread = 6.5;
		BaseRecoil = 8.0;
		BaseMinInaccuracy = 2.0;
		BaseMaxInaccuracy = 12.0;
		BaseInaccuracyRegen = 8.0;

		Barrel = GetRandomCSBarrel();
		Magazine = GetRandomCSMag();
		Accessory = GetRandomCSAccessory();
	}
	else {
		GunSubType = EGunSubType::AssaultShotgun;
		DamageModifier = 0.75;

		BaseProjectileCount = 7;
		BaseFireTime = 750; // 800 default
		BaseMagSize = 5;
		BaseReloadTime = 3.5;

		BaseSpread = 7.0;
		BaseRecoil = 7.0;
		BaseMinInaccuracy = 2.0;
		BaseMaxInaccuracy = 12.0;
		BaseInaccuracyRegen = 8.0;

		Barrel = GetRandomASBarrel();
		Magazine = GetRandomASMag();
		Accessory = GetRandomASAccessory();
	}

	ApplyPartsBonuses();

	Prefix = GetEligiblePrefix();
	Title = GetEligibleTitle();
}

std::unique_ptr<PrefixComponent> GDShotgun::GetEligiblePrefix() {
	PrefixComponent* prefix;

	if (GunSubType == EGunSubType::CombatShotgun) {
		if (Spread < 4.0) {
			prefix = new CSPrefixHunter();
		}
		else if (FireTime <= 1000 && MagSize >= 3) {
			prefix = new CSPrefixRiot();
		}
		else if (Accessory->PartNum == 2) {
			prefix = new CSPrefixTerrible();
		}
		else if (Accessory->PartNum == 1) {
			prefix = new CSPrefixFrenzied();
		}
		else if (RarityScore >= PrefixQ3Min) {
			prefix = new CSPrefixQ3();
		}
		else if (RarityScore >= PrefixQ2Min) {
			prefix = new CSPrefixQ2();
		}
		else if (RarityScore >= PrefixQ1Min) {
			prefix = new CSPrefixQ1();
		}
		else {
			prefix = new CSPrefixQ0();
		}
	}
	else {
		if (ReloadTime <= 2.5) {
			prefix = new ASPrefixAngry();
		}
		else if (Accessory->PartNum == 2) {
			prefix = new ASPrefixPainful();
		}
		else if (Accessory->PartNum == 1) {
			prefix = new ASPrefixRaging();
		}
		else if (RarityScore >= PrefixQ3Min) {
			prefix = new ASPrefixQ3();
		}
		else if (RarityScore >= PrefixQ2Min) {
			prefix = new ASPrefixQ2();
		}
		else if (RarityScore >= PrefixQ1Min) {
			prefix = new ASPrefixQ1();
		}
		else {
			prefix = new ASPrefixQ0();
		}
	}

	return std::unique_ptr<PrefixComponent>(prefix);
}

std::unique_ptr<TitleComponent> GDShotgun::GetEligibleTitle() {
	TitleComponent* title;

	if (GunSubType == EGunSubType::CombatShotgun) {
		if (Barrel->PartNum == 6) {
			title = new CSTitleShredder();
		}
		else if (Barrel->PartNum == 7) {
			title = new CSTitleCarnage();
		}
		else if (Accuracy <= 33.3 && RarityScore >= 8) {
			title = new CSTitleMatador();
		}
		else if (Accuracy <= 33.3 && RarityScore < 8) {
			title = new CSTitleScattergun();
		}
		else {
			title = new ShotgunTitleDefault();
		}
	}
	else {
		if (AttrBonuses[EAttributeType::Damage].Scale >= 0.45) {
			title = new ASTitleBrute();
		}
		else if (Accuracy >= 67) {
			title = new ASTitleDeath();
		}
		else if (Accuracy <= 25) {
			title = new ASTitleSweeper();
		}
		else {
			title = new ShotgunTitleDefault();
		}
	}

	return std::unique_ptr<TitleComponent>(title);
}
