#include "gun/gunDefinition.h"

#include <format>

GunDefinition::GunDefinition() {

}

void GunDefinition::AssembleRandomGun() {}
std::unique_ptr<PrefixComponent> GunDefinition::GetEligiblePrefix() { return nullptr; }
std::unique_ptr<TitleComponent> GunDefinition::GetEligibleTitle() { return nullptr; }

void GunDefinition::ApplyPartsBonuses() {
	if (Material.get() != nullptr) {
		for (size_t i = 0; i < Material->Bonuses.size(); i++) {
			AttrBonuses[Material->Bonuses[i].AttrType] += Material->Bonuses[i];
		}
		RarityScore += Material->PartRarity;
	}

	if (Body.get() != nullptr) {
		for (size_t i = 0; i < Body->Bonuses.size(); i++) {
			AttrBonuses[Body->Bonuses[i].AttrType] += Body->Bonuses[i];
		}
		RarityScore += Body->PartRarity;
	}

	if (Barrel.get() != nullptr) {
		for (size_t i = 0; i < Barrel->Bonuses.size(); i++) {
			AttrBonuses[Barrel->Bonuses[i].AttrType] += Barrel->Bonuses[i];
		}
		RarityScore += Barrel->PartRarity;
	}

	if (Stock.get() != nullptr) {
		for (size_t i = 0; i < Stock->Bonuses.size(); i++) {
			AttrBonuses[Stock->Bonuses[i].AttrType] += Stock->Bonuses[i];
		}
		RarityScore += Stock->PartRarity;
	}

	if (Magazine.get() != nullptr) {
		for (size_t i = 0; i < Magazine->Bonuses.size(); i++) {
			AttrBonuses[Magazine->Bonuses[i].AttrType] += Magazine->Bonuses[i];
		}
		RarityScore += Magazine->PartRarity;
	}

	if (Grip.get() != nullptr) {
		for (size_t i = 0; i < Grip->Bonuses.size(); i++) {
			AttrBonuses[Grip->Bonuses[i].AttrType] += Grip->Bonuses[i];
		}
		RarityScore += Grip->PartRarity;
	}

	if (Accessory.get() != nullptr) {
		for (size_t i = 0; i < Accessory->Bonuses.size(); i++) {
			AttrBonuses[Accessory->Bonuses[i].AttrType] += Accessory->Bonuses[i];
		}
		RarityScore += Accessory->PartRarity;
	}

	// FIXME: Skal fjernes senere
	CalculateStats();
}

void GunDefinition::FinaliseGun() {
	size_t numPrefixBonuses = 0;
	size_t numTitleBonuses = 0;

	if (Prefix.get()) {
		numPrefixBonuses = Prefix->Bonuses.size();

		for (size_t i = 0; i < Prefix->Bonuses.size(); i++) {
			AttrBonuses[Prefix->Bonuses[i].AttrType] += Prefix->Bonuses[i];
		}
		RarityScore += Prefix->PartRarity;
	}

	if (Title.get()) {
		numTitleBonuses = Title->Bonuses.size();

		for (size_t i = 0; i < Title->Bonuses.size(); i++) {
			AttrBonuses[Title->Bonuses[i].AttrType] += Title->Bonuses[i];
		}
		RarityScore += Title->PartRarity;
	}

	if (numPrefixBonuses != 0 || numTitleBonuses != 0) {
		CalculateStats();
	}

	std::string appliedPrefix = "";
	std::string appliedTitle = "";

	if (Prefix.get()) {
		appliedPrefix = Prefix->Name;
	}
	else if (Accessory.get()) {
		appliedPrefix = Accessory->Name;
	}

	if (Title.get()) {
		appliedTitle = Title->Name;
	}

	// If nothing has taken the place of the prefix, report
	if (appliedPrefix == "") {
		appliedPrefix = "PLACEHOLDER";
	}

	GunName = appliedPrefix + " " + appliedTitle;

	MetaMagAmmo = MagSize;
}

void GunDefinition::CalculateStats() {
	Damage = ((GetBaseScaled(Level) + AttrBonuses[EAttributeType::Damage].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::Damage].Scale)) * DamageModifier;

	double fireRate = (1000 / BaseFireTime) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::FireRate].Scale);
	FireTime = (1 / fireRate) * 1000;

	MagSize = (BaseMagSize + AttrBonuses[EAttributeType::MagSize].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::MagSize].Scale);

	ReloadTime = BaseReloadTime * Attribute::GetAdjustedScale(-AttrBonuses[EAttributeType::ReloadSpeed].Scale);

	ProjectileCount = (BaseProjectileCount + AttrBonuses[EAttributeType::ProjectileCount].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::ProjectileCount].Scale);
	if (ProjectileCount < 1) {
		ProjectileCount = 1;
	}

	ShotCost = (BaseShotCost + AttrBonuses[EAttributeType::ShotCost].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::ShotCost].Scale);

	Spread = (BaseSpread + AttrBonuses[EAttributeType::Spread].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::Spread].Scale);
	Recoil = (BaseRecoil + AttrBonuses[EAttributeType::Recoil].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::Recoil].Scale);
	MinInaccuracy = (BaseMinInaccuracy + AttrBonuses[EAttributeType::InaccuracyMin].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::InaccuracyMin].Scale);
	MaxInaccuracy = (BaseMaxInaccuracy + AttrBonuses[EAttributeType::InaccuracyMax].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::InaccuracyMax].Scale);

	InaccuracyRegen = (BaseInaccuracyRegen + AttrBonuses[EAttributeType::InaccuracyRegen].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::InaccuracyRegen].Scale);
	InaccuracyRegenDelay = BaseInaccuracyRegenDelay;

	ProjectileSpeed = (BaseProjectileSpeed + AttrBonuses[EAttributeType::ProjectileSpeed].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::ProjectileSpeed].Scale);
	Accuracy = (1 - (Spread / 12)) * 100;
}

std::string GunDefinition::GetGunPartsString() {
	char buffer[256];

	int32_t matNum = -1;
	int32_t matRar = -1;
	if (Material.get()) {
		matNum = Material->PartNum;
		matRar = Material->PartRarity;
	}

	int32_t bodyNum = -1;
	int32_t bodyRar = -1;
	if (Body.get()) {
		bodyNum = Body->PartNum;
		bodyRar = Body->PartRarity;
	}

	int32_t barrelNum = -1;
	int32_t barrelRar = -1;
	if (Barrel.get()) {
		barrelNum = Barrel->PartNum;
		barrelRar = Barrel->PartRarity;
	}

	int32_t magNum = -1;
	int32_t magRar = -1;
	if (Magazine.get()) {
		magNum = Magazine->PartNum;
		magRar = Magazine->PartRarity;
	}

	int32_t stockNum = -1;
	int32_t stockRar = -1;
	if (Stock.get()) {
		stockNum = Stock->PartNum;
		stockRar = Stock->PartRarity;
	}

	int32_t accNum = -1;
	int32_t accRar = -1;
	if (Accessory.get()) {
		accNum = Accessory->PartNum;
		accRar = Accessory->PartRarity;
	}

	std::snprintf(buffer, 256, "PART NUMBER/RARITY\nMaterial: %d/%d\nBody: %d/%d\nBarrel: %d/%d\nMagazine: %d/%d\nStock: %d/%d\nAccessory %d/%d", matNum, matRar, bodyNum, bodyRar, barrelNum, barrelRar, magNum, magRar, stockNum, stockRar, accNum, accRar);

	std::string gunString = buffer;

	return gunString;
}

GunDefinition::~GunDefinition() {

}
