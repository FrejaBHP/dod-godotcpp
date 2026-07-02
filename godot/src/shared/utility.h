#pragma once

#include <memory>
#include <vector>
#include <random>
#include <string.h>

#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

#include "shared/enums.h"
#include "shared/attribute.h"
//#include "element.h"

constexpr int32_t RarityMinUncommon = 6;
constexpr int32_t RarityMinRare = 13;
constexpr int32_t RarityMinEpic = 20;
constexpr int32_t RarityMinLegendaryLow = 50;
constexpr int32_t RarityMinLegendaryMid = RarityMinLegendaryLow + RarityMinRare;
constexpr int32_t RarityMinLegendaryHigh = RarityMinLegendaryLow + RarityMinEpic;
constexpr int32_t RarityMinPearlescent = 101;

constexpr int32_t PrefixQ1Min = 5;
constexpr int32_t PrefixQ2Min = 8;
constexpr int32_t PrefixQ3Min = 12;

extern std::random_device rnd;
extern std::mt19937 gen;

int GetRandomInt(int min, int max);
float GetRandomFloat(float min, float max);
double GetRandomDouble(double min, double max);

double GetBaseScaled(int32_t level);

godot::Color GetRarityColour(int32_t rarity);
godot::Ref<godot::AudioStream> GetAudio(godot::String name);

std::string GetManufacturerName(EManufacturer manufacturer);
std::string GetGunTypeName(EGunType guntype);
std::string GetGunSubTypeName(EGunSubType subtype);
std::string GetElementName(EElement element);
