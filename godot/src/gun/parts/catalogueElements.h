#pragma once

#include <memory>
#include "gun/gunpart.h"
#include "shared/enums.h"

std::unique_ptr<ElementComponent> GetRandomElement();
std::unique_ptr<ElementComponent> GetElementOfType(EElementCompType type);

class EleNone : public ElementComponent {
public:
	EleNone();
};

class EleCryo : public ElementComponent {
public:
	EleCryo();
};

class EleExplosiveNormal : public ElementComponent {
public:
	EleExplosiveNormal();
};

class EleDoTComponent : public ElementComponent {
public:
	EleDoTComponent();
};

class EleBlastComponent : public ElementComponent {
public:
	EleBlastComponent();
};


class EleExplosiveBlast : public EleBlastComponent {
public:
	//EleExplosiveBlast() : EleBlastComponent() {};
	EleExplosiveBlast();
};

class EleIncendiaryDoT : public EleDoTComponent {
public:
	//EleIncendiaryDoT() : EleDoTComponent() {};
	EleIncendiaryDoT();
};

class EleIncendiaryBlast : public EleBlastComponent {
public:
	//EleIncendiaryBlast() : EleBlastComponent() {};
	EleIncendiaryBlast();
};

class EleShockDoT : public EleDoTComponent {
public:
	//EleShockDoT() : EleDoTComponent() {};
	EleShockDoT();
};

class EleShockBlast : public EleBlastComponent {
public:
	//EleShockBlast() : EleBlastComponent() {};
	EleShockBlast();
};

class EleCorrosiveDoT : public EleDoTComponent {
public:
	//EleCorrosiveDoT() : EleDoTComponent() {};
	EleCorrosiveDoT();
};

class EleCorrosiveBlast : public EleBlastComponent {
public:
	//EleCorrosiveBlast() : EleBlastComponent() {};
	EleCorrosiveBlast();
};
