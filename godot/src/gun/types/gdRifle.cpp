#include "gun/types/gdRifle.h"
#include "gun/parts/catalogueRifle.h"

GDRifle::GDRifle() {
	GunType = EGunType::Rifle;
}

void GDRifle::AssembleRandomGun() {
	int32_t subtype = GetRandomInt(0, 1);

	if (subtype == 0) {
		GunSubType = EGunSubType::CombatRifle;
		FireMode = EFireMode::Burst;
		DamageModifier = 1.2;

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

		BaseFireTime = 170;
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

	Prefix = GetEligiblePrefix();
	Title = GetEligibleTitle();
}

void GDRifle::ApplyPartsBonuses() {
	GunDefinition::ApplyPartsBonuses();

	// FIXME: Skal fjernes senere
	CalculateStats();
}

std::unique_ptr<PrefixComponent> GDRifle::GetEligiblePrefix() {
	PrefixComponent* prefix;

	if (GunSubType == EGunSubType::CombatRifle) {
		if (AttrBonuses[EAttributeType::Damage].Scale >= 0.67) {
			prefix = new CRPrefixPunishing();
		}
		else if (AttrBonuses[EAttributeType::Damage].Scale < -0.08) {
			prefix = new CRPrefixShort();
		}
		else if (RarityScore >= PrefixQ3Min) {
			prefix = new CRPrefixQ3();
		}
		else if (RarityScore >= PrefixQ2Min) {
			prefix = new CRPrefixQ2();
		}
		else if (RarityScore >= PrefixQ1Min) {
			prefix = new CRPrefixQ1();
		}
		else {
			prefix = new CRPrefixQ0();
		}
	}
	else {
		if (Recoil <= 1.85 && RarityScore >= PrefixQ1Min) {
			prefix = new MGPrefixGlorious();
		}
		else if (Accessory->PartNum == 3) {
			prefix = new MGPrefixShattering();
		}
		else if (RarityScore >= PrefixQ3Min) {
			prefix = new MGPrefixQ3();
		}
		else if (Spread >= 3.0) {
			prefix = new MGPrefixRowdy();
		}
		else if (RarityScore >= PrefixQ2Min) {
			prefix = new MGPrefixQ2();
		}
		else if (RarityScore >= PrefixQ1Min) {
			prefix = new MGPrefixQ1();
		}
		else {
			prefix = new MGPrefixQ0();
		}
	}

	return std::unique_ptr<PrefixComponent>(prefix);
}

std::unique_ptr<TitleComponent> GDRifle::GetEligibleTitle() {
	TitleComponent* title;

	if (GunSubType == EGunSubType::CombatRifle) {
		if (Magazine->PartNum == 2) {
			title = new CRTitlePounder();
			PriFireAudio = GetAudio("guns/rifle_cr_pounder.mp3");
		}
		else if (Accuracy >= 93.0) {
			title = new CRTitleCobra();
			PriFireAudio = GetAudio("guns/rifle_cr_cobra.mp3");
		}
		else if (AttrBonuses[EAttributeType::Damage].Scale > 0.45) {
			title = new CRTitleStomper();
			PriFireAudio = GetAudio("guns/rifle_cr_stomper.mp3");
		}
		else {
			title = new CRTitleDefault();
			PriFireAudio = GetAudio("guns/rifle_cr_def.mp3");
		}
	}
	else {
		if (FireTime <= 100) {
			title = new MGTitleHavoc();
			PriFireAudio = GetAudio("guns/rifle_mg_havoc.mp3");
		}
		else if (Accuracy >= 91.3) {
			title = new MGTitleMassacre();
			PriFireAudio = GetAudio("guns/rifle_mg_massacre.mp3");
		}
		else if (AttrBonuses[EAttributeType::Damage].Scale > 0.8) {
			title = new MGTitleMauler();
			PriFireAudio = GetAudio("guns/rifle_mg_mauler.mp3");
		}
		else {
			title = new MGTitleDefault();
			PriFireAudio = GetAudio("guns/rifle_mg_def.mp3");
		}
	}

	return std::unique_ptr<TitleComponent>(title);
}
