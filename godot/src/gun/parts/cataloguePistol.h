#pragma once

#include <memory>
#include "gun/gunpart.h"
#include "gun/gunDefinition.h"
#include "gun/types/gdPistol.h"

std::unique_ptr<BodyComponent> GetRandomPistolBody();
std::unique_ptr<BarrelComponent> GetRandomPistolBarrel();
std::unique_ptr<MagazineComponent> GetRandomRepeaterMag();
std::unique_ptr<MagazineComponent> GetRandomMPMag();
std::unique_ptr<AccessoryComponent> GetRandomRepeaterAccessory();
std::unique_ptr<AccessoryComponent> GetRandomMPAccessory();
std::unique_ptr<ActionComponent> GetRandomPistolAction();

class PistolBody1 : public BodyComponent {
public:
	PistolBody1();
};

class PistolBody2 : public BodyComponent {
public:
	PistolBody2();
};

class PistolBody3 : public BodyComponent {
public:
	PistolBody3();
};

class PistolBody4 : public BodyComponent {
public:
	PistolBody4();
};

class PistolBody5MP : public BodyComponent {
public:
	PistolBody5MP();
};


class PistolBarrel1 : public BarrelComponent {
public:
	PistolBarrel1();
};

class PistolBarrel2 : public BarrelComponent {
public:
	PistolBarrel2();
};

class PistolBarrel3 : public BarrelComponent {
public:
	PistolBarrel3();
};

class PistolBarrel4 : public BarrelComponent {
public:
	PistolBarrel4();
};

class PistolBarrel5 : public BarrelComponent {
public:
	PistolBarrel5();
};


class PistolAction1 : public ActionComponent {
public:
	PistolAction1();
};

class PistolAction2 : public ActionComponent {
public:
	PistolAction2();
};

class PistolAction3 : public ActionComponent {
public:
	PistolAction3();
};

class PistolAction4 : public ActionComponent {
public:
	PistolAction4();
};

class PistolAction5 : public ActionComponent {
public:
	PistolAction5();
};


class RepeaterMag1 : public MagazineComponent {
public:
	RepeaterMag1();
};

class RepeaterMag2 : public MagazineComponent {
public:
	RepeaterMag2();
};

class RepeaterMag3 : public MagazineComponent {
public:
	RepeaterMag3();
};

class MPMag1 : public MagazineComponent {
public:
	MPMag1();
};

class MPMag2 : public MagazineComponent {
public:
	MPMag2();
};


class PistolAcc0None : public AccessoryComponent {
public:
	PistolAcc0None();
};

class PistolAcc1Stabilised : public AccessoryComponent {
public:
	PistolAcc1Stabilised();
};

class PistolAcc2Laser : public AccessoryComponent {
public:
	PistolAcc2Laser();
};

class PistolAcc3Double : public AccessoryComponent {
public:
	PistolAcc3Double();
};

class MPAcc4Rage : public AccessoryComponent {
public:
	MPAcc4Rage();
};


class RepeaterTitleDefault : public TitleComponent {
public:
	RepeaterTitleDefault();
};

class RepeaterTitleNeedler : public TitleComponent {
public:
	RepeaterTitleNeedler();
};

class RepeaterTitleSwatter : public TitleComponent {
public:
	RepeaterTitleSwatter();
};

class RepeaterTitleRaptor : public TitleComponent {
public:
	RepeaterTitleRaptor();
};

class MPTitleDefault : public TitleComponent {
public:
	MPTitleDefault();
};

class MPTitleTorment : public TitleComponent {
public:
	MPTitleTorment();
};

class MPTitleFury : public TitleComponent {
public:
	MPTitleFury();
};

class MPTitleRage : public TitleComponent {
public:
	MPTitleRage();
};
