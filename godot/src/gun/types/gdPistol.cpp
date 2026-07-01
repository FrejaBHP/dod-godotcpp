#include "gun/types/gdPistol.h"
#include "gun/parts/cataloguePistol.h"

GDPistol::GDPistol() {
	GunType = EGunType::Pistol;
}

void GDPistol::AssembleRandomGun() {
	Body = GetRandomPistolBody();

	if (Body->PartNum == 5) {
		GunSubType = EGunSubType::MachinePistol;
		FireMode = EFireMode::Automatic;
		DamageModifier = 0.9;

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
		DamageModifier = 1.0;

		BaseFireTime = 300;
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

	Prefix = GetEligiblePrefix();
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

std::unique_ptr<PrefixComponent> GDPistol::GetEligiblePrefix() {
	PrefixComponent* prefix;

	if (GunSubType == EGunSubType::Repeater) {
		if (AttrBonuses[EAttributeType::Damage].Scale > 0.3 && MagSize > 16) {
			prefix = new RepeaterPrefixNasty();
		}
		else if (AttrBonuses[EAttributeType::Damage].Scale > 0.2 && MagSize > 14) {
			prefix = new RepeaterPrefixNoble();
		}
		else if (Accessory->PartNum == 3) {
			prefix = new PistolPrefixDouble();
		}
		else if (Accessory->PartNum == 1) {
			prefix = new PistolPrefixStabilised();
		}
		else if (RarityScore >= PrefixQ3Min) {
			prefix = new RepeaterPrefixQ3();
		}
		else if (RarityScore >= PrefixQ2Min) {
			prefix = new RepeaterPrefixQ2();
		}
		else if (RarityScore >= PrefixQ1Min) {
			prefix = new RepeaterPrefixQ1();
		}
		else {
			prefix = new RepeaterPrefixQ0();
		}
	}
	else {
		if (Accessory->PartNum == 5) {
			prefix = new MPPrefixCold();
		}
		else if (Accessory->PartNum == 4) {
			prefix = new MPPrefixRaging();
		}
		else if (Accessory->PartNum == 3) {
			prefix = new PistolPrefixDouble();
		}
		else if (Accessory->PartNum == 1) {
			prefix = new PistolPrefixStabilised();
		}
		else if (RarityScore >= PrefixQ3Min) {
			prefix = new MPPrefixQ3();
		}
		else if (RarityScore >= PrefixQ2Min) {
			prefix = new MPPrefixQ2();
		}
		else if (RarityScore >= PrefixQ1Min) {
			prefix = new MPPrefixQ1();
		}
		else {
			prefix = new MPPrefixQ0();
		}
	}

	return std::unique_ptr<PrefixComponent>(prefix);
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

std::string GDPistol::GetGunPartsString() {
	std::string og = GunDefinition::GetGunPartsString();

	char buffer[64];

	int32_t actionNum = -1;
	int32_t actionRar = -1;
	if (Action.get()) {
		actionNum = Action->PartNum;
		actionRar = Action->PartRarity;
	}

	snprintf(buffer, 64, "\nAction: %d/%d", actionNum, actionRar);

	std::string pistolString = og + buffer;

	return pistolString;
}
