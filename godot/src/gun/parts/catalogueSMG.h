#pragma once

#include <memory>
#include "gun/gunpart.h"

std::unique_ptr<BodyComponent> GetRandomSMGBody();
std::unique_ptr<BarrelComponent> GetRandomSMGBarrel();
std::unique_ptr<MagazineComponent> GetRandomSMGMag();
std::unique_ptr<StockComponent> GetRandomSMGStock();
std::unique_ptr<AccessoryComponent> GetRandomSMGAccessory();

class SMGBody1 : public BodyComponent {
public:
	SMGBody1();
};

class SMGBody2 : public BodyComponent {
public:
	SMGBody2();
};

class SMGBody3 : public BodyComponent {
public:
	SMGBody3();
};

class SMGBody4 : public BodyComponent {
public:
	SMGBody4();
};

class SMGBody5 : public BodyComponent {
public:
	SMGBody5();
};


class SMGBarrel1 : public BarrelComponent {
public:
	SMGBarrel1();
};

class SMGBarrel2 : public BarrelComponent {
public:
	SMGBarrel2();
};

class SMGBarrel3 : public BarrelComponent {
public:
	SMGBarrel3();
};

class SMGBarrel4 : public BarrelComponent {
public:
	SMGBarrel4();
};

class SMGBarrel5 : public BarrelComponent {
public:
	SMGBarrel5();
};


class SMGMag1Thumper : public MagazineComponent {
public:
	SMGMag1Thumper();
};

class SMGMag2 : public MagazineComponent {
public:
	SMGMag2();
};

class SMGMag3 : public MagazineComponent {
public:
	SMGMag3();
};

class SMGMag4 : public MagazineComponent {
public:
	SMGMag4();
};

class SMGMag5 : public MagazineComponent {
public:
	SMGMag5();
};


class SMGStock0None : public StockComponent {
public:
	SMGStock0None();
};

class SMGStock1 : public StockComponent {
public:
	SMGStock1();
};

class SMGStock2 : public StockComponent {
public:
	SMGStock2();
};

class SMGStock3 : public StockComponent {
public:
	SMGStock3();
};

class SMGStock4 : public StockComponent {
public:
	SMGStock4();
};

class SMGStock5 : public StockComponent {
public:
	SMGStock5();
};


class SMGAcc0None : public AccessoryComponent {
public:
	SMGAcc0None();
};

class SMGAcc1Relentless : public AccessoryComponent {
public:
	SMGAcc1Relentless();
};

class SMGAcc2Ruthless : public AccessoryComponent {
public:
	SMGAcc2Ruthless();
};

class SMGAcc3Vector : public AccessoryComponent {
public:
	SMGAcc3Vector();
};

class SMGAcc4Double : public AccessoryComponent {
public:
	SMGAcc4Double();
};
