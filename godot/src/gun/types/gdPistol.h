#pragma once

#include "gun/gunDefinition.h"

class ActionComponent : public GunPart {

};

class GDPistol : public GunDefinition {
public:
	GDPistol();
	void AssembleRandomGun() override;
	void ApplyPartsBonuses() override;
	virtual std::string GetGunPartsString() override;

	std::unique_ptr<ActionComponent> Action;

protected:
	std::unique_ptr<PrefixComponent> GetEligiblePrefix() override;
	std::unique_ptr<TitleComponent> GetEligibleTitle() override;
};
