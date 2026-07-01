#pragma once

#include "gun/gunDefinition.h"

class FireModeComponent : public GunPart {

};

class GDRifle : public GunDefinition {
public:
	GDRifle();
	void AssembleRandomGun() override;
	void ApplyPartsBonuses() override;

protected:
	std::unique_ptr<PrefixComponent> GetEligiblePrefix() override;
	std::unique_ptr<TitleComponent> GetEligibleTitle() override;
};
