#pragma once

#include "gun/gunDefinition.h"

class GDRevolver : public GunDefinition {
public:
	GDRevolver();
	void AssembleRandomGun() override;

protected:
	std::unique_ptr<PrefixComponent> GetEligiblePrefix() override;
	std::unique_ptr<TitleComponent> GetEligibleTitle() override;
};
