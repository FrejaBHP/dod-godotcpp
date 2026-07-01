#pragma once

#include <memory>
#include "gun/gunpart.h"
#include "gun/gunDefinition.h"
#include "gun/types/gdRevolver.h"

std::unique_ptr<BodyComponent> GetRandomRevolverBody();
std::unique_ptr<BarrelComponent> GetRandomRevolverBarrel();
std::unique_ptr<MagazineComponent> GetRandomRevolverMagazine();
std::unique_ptr<AccessoryComponent> GetRandomRevolverAccessory();
std::unique_ptr<StockComponent> GetRandomRevolverStock();

class RevolverBody1 : public BodyComponent {
public:
	RevolverBody1();
};

class RevolverBody2 : public BodyComponent {
public:
	RevolverBody2();
};

class RevolverBody3 : public BodyComponent {
public:
	RevolverBody3();
};

class RevolverBody4 : public BodyComponent {
public:
	RevolverBody4();
};

class RevolverBody5 : public BodyComponent {
public:
	RevolverBody5();
};


class RevolverBarrel1 : public BarrelComponent {
public:
	RevolverBarrel1();
};

class RevolverBarrel2 : public BarrelComponent {
public:
	RevolverBarrel2();
};

class RevolverBarrel3 : public BarrelComponent {
public:
	RevolverBarrel3();
};

class RevolverBarrel4 : public BarrelComponent {
public:
	RevolverBarrel4();
};

class RevolverBarrel5 : public BarrelComponent {
public:
	RevolverBarrel5();
};


class RevolverMag1 : public MagazineComponent {
public:
	RevolverMag1();
};

class RevolverMag2 : public MagazineComponent {
public:
	RevolverMag2();
};

class RevolverMag3 : public MagazineComponent {
public:
	RevolverMag3();
};

class RevolverMag4 : public MagazineComponent {
public:
	RevolverMag4();
};

class RevolverMag5 : public MagazineComponent {
public:
	RevolverMag5();
};


class RevolverStock0None : public StockComponent {
public:
	RevolverStock0None();
};

class RevolverStock1 : public StockComponent {
public:
	RevolverStock1();
};

class RevolverStock2 : public StockComponent {
public:
	RevolverStock2();
};

class RevolverStock3 : public StockComponent {
public:
	RevolverStock3();
};


class RevolverAcc0None : public AccessoryComponent {
public:
	RevolverAcc0None();
};

class RevolverAcc1Masher : public AccessoryComponent {
public:
	RevolverAcc1Masher();
};

class RevolverAcc2Stabilised : public AccessoryComponent {
public:
	RevolverAcc2Stabilised();
};


class RevolverPrefixQ0 : public PrefixComponent {
public:
	RevolverPrefixQ0();
};

class RevolverPrefixQ1 : public PrefixComponent {
public:
	RevolverPrefixQ1();
};

class RevolverPrefixQ2 : public PrefixComponent {
public:
	RevolverPrefixQ2();
};

class RevolverPrefixQ3 : public PrefixComponent {
public:
	RevolverPrefixQ3();
};

class RevolverPrefixStabilised : public PrefixComponent {
public:
	RevolverPrefixStabilised();
};

class RevolverPrefixBloody : public PrefixComponent {
public:
	RevolverPrefixBloody();
};

class RevolverPrefixSwift : public PrefixComponent {
public:
	RevolverPrefixSwift();
};

class RevolverPrefixRaw : public PrefixComponent {
public:
	RevolverPrefixRaw();
};


class RevolverTitleDefault : public TitleComponent {
public:
	RevolverTitleDefault();
};

class RevolverTitleMasher : public TitleComponent {
public:
	RevolverTitleMasher();
};

class RevolverTitleJustice : public TitleComponent {
public:
	RevolverTitleJustice();
};

class RevolverTitleLaw : public TitleComponent {
public:
	RevolverTitleLaw();
};

class RevolverTitleViper : public TitleComponent {
public:
	RevolverTitleViper();
};
