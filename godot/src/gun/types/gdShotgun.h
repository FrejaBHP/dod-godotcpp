#pragma once

#include "gun/gunDefinition.h"

class GDShotgun : public GunDefinition {
public:
	GDShotgun();
	void AssembleRandomGun() override;

protected:
	std::unique_ptr<PrefixComponent> GetEligiblePrefix() override;
	std::unique_ptr<TitleComponent> GetEligibleTitle() override;
};
