#pragma once

#include <memory>
#include "gun/gunpart.h"
#include "gun/gunDefinition.h"

std::unique_ptr<BodyComponent> GetRandomCRBody();
std::unique_ptr<BodyComponent> GetRandomMGBody();
std::unique_ptr<StockComponent> GetRandomCRStock();
std::unique_ptr<StockComponent> GetRandomMGStock();
std::unique_ptr<MagazineComponent> GetRandomCRMag();
std::unique_ptr<MagazineComponent> GetRandomMGMag();

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



class CRTitleDefault : public TitleComponent {
public:
	CRTitleDefault();
};

class CRTitlePounder : public TitleComponent {
public:
	CRTitlePounder();
};

class MGTitleDefault : public TitleComponent {
public:
	MGTitleDefault();
};
