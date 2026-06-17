#pragma once

#include "gun/gunDefinition.h"

class GDPistol : public GunDefinition {
public:
	GDPistol();
	void AssembleRandomGun() override;
	void ApplyPartsBonuses() override;

	std::unique_ptr<ActionComponent> Action;

protected:
	std::unique_ptr<TitleComponent> GetEligibleTitle() override;
};
