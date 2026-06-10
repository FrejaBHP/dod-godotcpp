#pragma once

#include <cstdint>
#include "shared/enums.h"

class Attribute {

public:
	EAttributeType AttrType;
	int32_t Flat;
	double ScalePos;
	double ScaleNeg;

	Attribute operator+(const Attribute& b) {
		Attribute c;

		c.Flat = this->Flat + b.Flat;
		c.ScalePos = this->ScalePos + b.ScalePos;
		c.ScaleNeg = this->ScaleNeg + b.ScaleNeg;

		return c;
	}

	Attribute operator-(const Attribute& b) {
		Attribute c;

		c.Flat = this->Flat - b.Flat;
		c.ScalePos = this->ScalePos - b.ScalePos;
		c.ScaleNeg = this->ScaleNeg - b.ScaleNeg;

		return c;
	}
};
