#include "gun/gunDefinition.h"

// using namespace godot;

GunDefinition::GunDefinition() {

}

void GunDefinition::SetPistolStats() {
	GunType = EGunType::Pistol;
	GunSubType = EGunSubType::Repeater;
	BaseDamage = 6.0;
	BaseFireTime = 225;
	BaseMagSize = 12;
	BaseReloadTime = 2.0;

	BaseSpread = 2.0;
	BaseRecoil = 2.0;
	BaseMinInaccuracy = 1.5;
	BaseMaxInaccuracy = 8;
	BaseInaccuracyRegen = 12;
}

void GunDefinition::SetSMGStats() {
	GunType = EGunType::SMG;
	GunSubType = EGunSubType::None;
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

void GunDefinition::SetARStats() {
	GunType = EGunType::Rifle;
	GunSubType = EGunSubType::AssaultRifle;
	BaseDamage = 5.0;
	BaseFireTime = 200;
	BaseMagSize = 15;
	BaseReloadTime = 2.4;

	BaseSpread = 1.3;
	BaseRecoil = 3.5;
	BaseMinInaccuracy = 1.5;
	BaseMaxInaccuracy = 12;
	BaseInaccuracyRegen = 8;
}

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

	Damage = (BaseDamage + AttrBonuses[EAttributeType::Damage].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::Damage].Scale);

	double fireRate = (1000 / BaseFireTime) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::FireRate].Scale);
	FireTime = (1 / fireRate) * 1000;

	MagSize = (BaseMagSize + AttrBonuses[EAttributeType::MagSize].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::MagSize].Scale);

	double reloadSpeed = (1 / BaseReloadTime) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::ReloadSpeed].Scale);
	ReloadTime = 1 / reloadSpeed;

	ProjectileCount = (BaseProjectileCount + AttrBonuses[EAttributeType::ProjectileCount].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::ProjectileCount].Scale);
	ShotCost = (BaseShotCost + AttrBonuses[EAttributeType::ShotCost].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::ShotCost].Scale);

	Spread = (BaseSpread + AttrBonuses[EAttributeType::Spread].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::Spread].Scale);
	Recoil = (BaseRecoil + AttrBonuses[EAttributeType::Recoil].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::Recoil].Scale);
	MinInaccuracy = (BaseMinInaccuracy + AttrBonuses[EAttributeType::InaccuracyMin].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::InaccuracyMin].Scale);
	MaxInaccuracy = (BaseMaxInaccuracy + AttrBonuses[EAttributeType::InaccuracyMax].Flat) * Attribute::GetAdjustedScale(AttrBonuses[EAttributeType::InaccuracyMax].Scale);

	InaccuracyRegen = BaseInaccuracyRegen;
	InaccuracyRegenDelay = BaseInaccuracyRegenDelay;

	Accuracy = 100 - (12 * Spread);

	MetaMagAmmo = MagSize;
}

GunDefinition::~GunDefinition() {

}
