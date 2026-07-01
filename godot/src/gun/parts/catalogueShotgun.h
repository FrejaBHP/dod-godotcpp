#pragma once

#include <memory>
#include "gun/gunpart.h"
#include "gun/gunDefinition.h"
#include "gun/types/gdShotgun.h"

std::unique_ptr<BodyComponent> GetRandomShotgunBody();
std::unique_ptr<BarrelComponent> GetRandomCSBarrel();
std::unique_ptr<BarrelComponent> GetRandomASBarrel();
std::unique_ptr<StockComponent> GetRandomShotgunStock();
std::unique_ptr<MagazineComponent> GetRandomCSMag();
std::unique_ptr<MagazineComponent> GetRandomASMag();
std::unique_ptr<AccessoryComponent> GetRandomCSAccessory();
std::unique_ptr<AccessoryComponent> GetRandomASAccessory();


class ShotgunBody1 : public BodyComponent {
public:
	ShotgunBody1();
};

class ShotgunBody2 : public BodyComponent {
public:
	ShotgunBody2();
};

class ShotgunBody3 : public BodyComponent {
public:
	ShotgunBody3();
};

class ShotgunBody4 : public BodyComponent {
public:
	ShotgunBody4();
};

class ShotgunBody5 : public BodyComponent {
public:
	ShotgunBody5();
};


class ShotgunBarrel1 : public BarrelComponent {
public:
	ShotgunBarrel1();
};

class ShotgunBarrel2 : public BarrelComponent {
public:
	ShotgunBarrel2();
};

class ShotgunBarrel3 : public BarrelComponent {
public:
	ShotgunBarrel3();
};

class ShotgunBarrel4 : public BarrelComponent {
public:
	ShotgunBarrel4();
};

class ShotgunBarrel5 : public BarrelComponent {
public:
	ShotgunBarrel5();
};

class CSBarrel6Shredder : public BarrelComponent {
public:
	CSBarrel6Shredder();
};

class CSBarrel7Carnage : public BarrelComponent {
public:
	CSBarrel7Carnage();
};


class ShotgunStock0None : public StockComponent {
public:
	ShotgunStock0None();
};

class ShotgunStock1 : public StockComponent {
public:
	ShotgunStock1();
};

class ShotgunStock2 : public StockComponent {
public:
	ShotgunStock2();
};

class ShotgunStock3 : public StockComponent {
public:
	ShotgunStock3();
};


class CSMag1 : public MagazineComponent {
public:
	CSMag1();
};

class CSMag2 : public MagazineComponent {
public:
	CSMag2();
};

class CSMag3 : public MagazineComponent {
public:
	CSMag3();
};

class CSMag4 : public MagazineComponent {
public:
	CSMag4();
};

class ASMag1 : public MagazineComponent {
public:
	ASMag1();
};

class ASMag2 : public MagazineComponent {
public:
	ASMag2();
};


class ShotgunAcc0None : public AccessoryComponent {
public:
	ShotgunAcc0None();
};

class CSAcc1Frenzied : public AccessoryComponent {
public:
	CSAcc1Frenzied();
};

class CSAcc2Terrible : public AccessoryComponent {
public:
	CSAcc2Terrible();
};

class ASAcc1Raging : public AccessoryComponent {
public:
	ASAcc1Raging();
};

class ASAcc2Painful : public AccessoryComponent {
public:
	ASAcc2Painful();
};


class CSPrefixQ0 : public PrefixComponent {
public:
	CSPrefixQ0();
};

class CSPrefixQ1 : public PrefixComponent {
public:
	CSPrefixQ1();
};

class CSPrefixQ2 : public PrefixComponent {
public:
	CSPrefixQ2();
};

class CSPrefixQ3 : public PrefixComponent {
public:
	CSPrefixQ3();
};

class CSPrefixTerrible : public PrefixComponent {
public:
	CSPrefixTerrible();
};

class CSPrefixFrenzied : public PrefixComponent {
public:
	CSPrefixFrenzied();
};

class CSPrefixHunter : public PrefixComponent {
public:
	CSPrefixHunter();
};

class CSPrefixRiot : public PrefixComponent {
public:
	CSPrefixRiot();
};

class ASPrefixQ0 : public PrefixComponent {
public:
	ASPrefixQ0();
};

class ASPrefixQ1 : public PrefixComponent {
public:
	ASPrefixQ1();
};

class ASPrefixQ2 : public PrefixComponent {
public:
	ASPrefixQ2();
};

class ASPrefixQ3 : public PrefixComponent {
public:
	ASPrefixQ3();
};

class ASPrefixRaging : public PrefixComponent {
public:
	ASPrefixRaging();
};

class ASPrefixPainful : public PrefixComponent {
public:
	ASPrefixPainful();
};

class ASPrefixAngry : public PrefixComponent {
public:
	ASPrefixAngry();
};


class ShotgunTitleDefault : public TitleComponent {
public:
	ShotgunTitleDefault();
};

class CSTitleMatador : public TitleComponent {
public:
	CSTitleMatador();
};

class CSTitleScattergun : public TitleComponent {
public:
	CSTitleScattergun();
};

class CSTitleShredder : public TitleComponent {
public:
	CSTitleShredder();
};

class CSTitleCarnage : public TitleComponent {
public:
	CSTitleCarnage();
};

class ASTitleBrute : public TitleComponent {
public:
	ASTitleBrute();
};

class ASTitleDeath : public TitleComponent {
public:
	ASTitleDeath();
};

class ASTitleSweeper : public TitleComponent {
public:
	ASTitleSweeper();
};
