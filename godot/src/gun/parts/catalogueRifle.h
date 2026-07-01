#pragma once

#include <memory>
#include "gun/gunpart.h"
#include "gun/gunDefinition.h"

std::unique_ptr<BodyComponent> GetRandomCRBody();
std::unique_ptr<BodyComponent> GetRandomMGBody();
std::unique_ptr<BarrelComponent> GetRandomCRBarrel();
std::unique_ptr<BarrelComponent> GetRandomMGBarrel();
std::unique_ptr<StockComponent> GetRandomCRStock();
std::unique_ptr<StockComponent> GetRandomMGStock();
std::unique_ptr<MagazineComponent> GetRandomCRMag();
std::unique_ptr<MagazineComponent> GetRandomMGMag();
std::unique_ptr<AccessoryComponent> GetRandomCRAcc();
std::unique_ptr<AccessoryComponent> GetRandomMGAcc();

class ARBody1CR : public BodyComponent {
public:
	ARBody1CR();
};

class ARBody1MG : public BodyComponent {
public:
	ARBody1MG();
};

class ARBody2 : public BodyComponent {
public:
	ARBody2();
};

class ARBody3 : public BodyComponent {
public:
	ARBody3();
};

class ARBody4 : public BodyComponent {
public:
	ARBody4();
};


class ARBarrel1CR : public BarrelComponent {
public:
	ARBarrel1CR();
};

class ARBarrel1MG : public BarrelComponent {
public:
	ARBarrel1MG();
};

class ARBarrel2 : public BarrelComponent {
public:
	ARBarrel2();
};

class ARBarrel3 : public BarrelComponent {
public:
	ARBarrel3();
};

class ARBarrel4 : public BarrelComponent {
public:
	ARBarrel4();
};


class ARStock0CRNone : public StockComponent {
public:
	ARStock0CRNone();
};

class ARStock1CR : public StockComponent {
public:
	ARStock1CR();
};

class ARStock1MG : public StockComponent {
public:
	ARStock1MG();
};

class ARStock2 : public StockComponent {
public:
	ARStock2();
};

class ARStock3 : public StockComponent {
public:
	ARStock3();
};

class ARStock4 : public StockComponent {
public:
	ARStock4();
};


class CRMag1 : public MagazineComponent {
public:
	CRMag1();
};

class CRMag2Pounder : public MagazineComponent {
public:
	CRMag2Pounder();
};

class CRMag3 : public MagazineComponent {
public:
	CRMag3();
};

class MGMag1 : public MagazineComponent {
public:
	MGMag1();
};

class MGMag2 : public MagazineComponent {
public:
	MGMag2();
};

class MGMag3 : public MagazineComponent {
public:
	MGMag3();
};


class ARAcc0None : public AccessoryComponent {
public:
	ARAcc0None();
};

class ARAcc1Deathly : public AccessoryComponent {
public:
	ARAcc1Deathly();
};

class CRAcc2Intense : public AccessoryComponent {
public:
	CRAcc2Intense();
};

class MGAcc2Frantic : public AccessoryComponent {
public:
	MGAcc2Frantic();
};

class MGAcc3Shattering : public AccessoryComponent {
public:
	MGAcc3Shattering();
};


class CRPrefixQ0 : public PrefixComponent {
public:
	CRPrefixQ0();
};

class CRPrefixQ1 : public PrefixComponent {
public:
	CRPrefixQ1();
};

class CRPrefixQ2 : public PrefixComponent {
public:
	CRPrefixQ2();
};

class CRPrefixQ3 : public PrefixComponent {
public:
	CRPrefixQ3();
};

class CRPrefixShort : public PrefixComponent {
public:
	CRPrefixShort();
};

class CRPrefixPunishing : public PrefixComponent {
public:
	CRPrefixPunishing();
};

class MGPrefixQ0 : public PrefixComponent {
public:
	MGPrefixQ0();
};

class MGPrefixQ1 : public PrefixComponent {
public:
	MGPrefixQ1();
};

class MGPrefixQ2 : public PrefixComponent {
public:
	MGPrefixQ2();
};

class MGPrefixQ3 : public PrefixComponent {
public:
	MGPrefixQ3();
};

class MGPrefixRowdy : public PrefixComponent {
public:
	MGPrefixRowdy();
};

class MGPrefixShattering : public PrefixComponent {
public:
	MGPrefixShattering();
};

class MGPrefixFrantic : public PrefixComponent {
public:
	MGPrefixFrantic();
};

class MGPrefixGlorious : public PrefixComponent {
public:
	MGPrefixGlorious();
};




class CRTitleDefault : public TitleComponent {
public:
	CRTitleDefault();
};

class CRTitlePounder : public TitleComponent {
public:
	CRTitlePounder();
};

class CRTitleCobra : public TitleComponent {
public:
	CRTitleCobra();
};

class CRTitleStomper : public TitleComponent {
public:
	CRTitleStomper();
};

class MGTitleDefault : public TitleComponent {
public:
	MGTitleDefault();
};

class MGTitleMauler : public TitleComponent {
public:
	MGTitleMauler();
};

class MGTitleHavoc : public TitleComponent {
public:
	MGTitleHavoc();
};

class MGTitleMassacre : public TitleComponent {
public:
	MGTitleMassacre();
};
