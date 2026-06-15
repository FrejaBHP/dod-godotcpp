#pragma once

#include <memory>
#include <vector>
#include <random>
#include <string.h>

#include <godot_cpp/variant/color.hpp>

#include "shared/enums.h"
#include "shared/attribute.h"
//#include "element.h"

extern std::random_device rnd;
extern std::mt19937 gen;

int GetRandomInt(int min, int max);
float GetRandomFloat(float min, float max);
double GetRandomDouble(double min, double max);

godot::Color GetRarityColour(int32_t rarity);

std::string GetManufacturerName(EManufacturer manufacturer);
std::string GetGunTypeName(EGunType guntype);
std::string GetGunSubTypeName(EGunSubType subtype);
std::string GetElementName(EElement element);
