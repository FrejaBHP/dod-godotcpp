#pragma once

#include "gun/gunDefinition.h"

class GDSMG : public GunDefinition {
public:
	GDSMG();
	void AssembleRandomGun() override;

protected:
	std::unique_ptr<TitleComponent> GetEligibleTitle() override;
};
