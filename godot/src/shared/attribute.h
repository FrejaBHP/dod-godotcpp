#pragma once

#include <cstdint>
#include "shared/enums.h"

class Attribute {

public:
	EAttributeType AttrType;
	int32_t Flat;
	double Scale;

	static double GetAdjustedScale(double scale) {
		if (scale >= 0) {
			return 1 + scale;
		}
		else {
			return 1 / (1 - scale);
		}
	}

	Attribute operator+(const Attribute& b) {
		Attribute c;

		c.Flat = this->Flat + b.Flat;
		c.Scale = this->Scale + b.Scale;

		return c;
	}

	void operator+=(const Attribute& b) {
		this->Flat += b.Flat;
		this->Scale += b.Scale;
	}

	Attribute operator-(const Attribute& b) {
		Attribute c;

		c.Flat = this->Flat - b.Flat;
		c.Scale = this->Scale - b.Scale;

		return c;
	}

	void operator-=(const Attribute& b) {
		this->Flat -= b.Flat;
		this->Scale -= b.Scale;
	}
};
