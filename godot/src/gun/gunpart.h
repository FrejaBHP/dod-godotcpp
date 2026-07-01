#pragma once

#include "shared/enums.h"
#include "shared/attribute.h"
#include <vector>
#include <string>

class GunPart {
public:
	std::string Name { "" };
	int32_t PartRarity { 0 };
	int32_t PartNum { 0 };
	std::vector<Attribute> Bonuses;

	GunPart() {}
	GunPart(std::vector<Attribute> bonuses) : Bonuses(bonuses) {}

protected:

private:

};

class MaterialComponent : public GunPart {
public:
	EManufacturer Manufacturer { EManufacturer::Placeholder };
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

class PrefixComponent : public GunPart {

};

class TitleComponent : public GunPart {

};
