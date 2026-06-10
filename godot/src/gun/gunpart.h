#pragma once

#include "shared/enums.h"
#include "shared/attribute.h"
#include <vector>

class GunPart {
public:
	EManufacturer Manufacturer { EManufacturer::Placeholder };
	int32_t PartRarity { 0 };
	std::vector<Attribute> Attributes;

	GunPart() {}
	GunPart(std::vector<Attribute> attributes) : Attributes(attributes) {}

protected:

private:

};

class MaterialComponent : public GunPart {

};

class BodyComponent : public GunPart {

};

class BarrelComponent : public GunPart {

};

class StockComponent : public GunPart {

};

class MagazineComponent : public GunPart {

};

class GripComponent : public GunPart {

};

class AccessoryComponent : public GunPart {

};
