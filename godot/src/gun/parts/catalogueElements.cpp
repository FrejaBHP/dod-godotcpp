#include "gun/parts/catalogueElements.h"
#include "shared/utility.h"

//constexpr int32_t NumElementTypes = (int32_t)EElement::COUNT;

std::unique_ptr<ElementComponent> GetRandomElement() {
	//int32_t eleIndex = GetRandomInt(0, NumElementTypes);
	int32_t random = GetRandomInt(0, 30);
	ElementComponent* elem;

	if (random < 3) { // 0 - 2
		elem = new EleCryo();
	}
	else if (random < 5) { // 3 - 4
		elem = new EleExplosiveNormal();
	}
	else if (random < 6) { // 5 - 5
		elem = new EleExplosiveBlast();
	}
	else if (random < 8) { // 6 - 7
		elem = new EleIncendiaryDoT();
	}
	else if (random < 9) { // 8 - 8
		elem = new EleIncendiaryBlast();
	}
	else if (random < 11) { // 9 - 10
		elem = new EleShockDoT();
	}
	else if (random < 12) { // 11 - 11
		elem = new EleShockBlast();
	}
	else if (random < 14) { // 12 - 13
		elem = new EleCorrosiveDoT();
	}
	else if (random < 15) { // 14 - 14
		elem = new EleCorrosiveBlast();
	}
	else {
		elem = new EleNone();
	}

	return std::unique_ptr<ElementComponent>(elem);
}

std::unique_ptr<ElementComponent> GetElementOfType(EElementCompType type) {
	ElementComponent* elem;

	switch (type) {
		case EElementCompType::Cryo:
			elem = new EleCryo();
			break;

		case EElementCompType::ExplosiveNormal:
			elem = new EleExplosiveNormal();
			break;

		case EElementCompType::ExplosiveBlast:
			elem = new EleExplosiveBlast();
			break;

		case EElementCompType::IncendiaryDoT:
			elem = new EleIncendiaryDoT();
			break;

		case EElementCompType::IncendiaryBlast:
			elem = new EleIncendiaryBlast();
			break;

		case EElementCompType::ShockDoT:
			elem = new EleShockDoT();
			break;

		case EElementCompType::ShockBlast:
			elem = new EleShockBlast();
			break;

		case EElementCompType::CorrosiveDoT:
			elem = new EleCorrosiveDoT();
			break;

		case EElementCompType::CorrosiveBlast:
			elem = new EleCorrosiveBlast();
			break;

		default: // None
			elem = new EleNone();
			break;
	}

	return std::unique_ptr<ElementComponent>(elem);
}

EleNone::EleNone() {
	Element = EElement::None;

	Bonuses = {};
}

EleCryo::EleCryo() {
	Element = EElement::Cryo;

	Bonuses = {
		{ EAttributeType::Damage, 0, -0.3 }
	};
}

EleExplosiveNormal::EleExplosiveNormal() {
	Element = EElement::Explosive;
	BL1Style = false;

	Bonuses = {};
}

EleDoTComponent::EleDoTComponent() {
	BL1Style = false;
}

EleBlastComponent::EleBlastComponent() {
	BL1Style = true;
}

EleExplosiveBlast::EleExplosiveBlast() {
	Element = EElement::Explosive;

	Bonuses = {
		{ EAttributeType::Damage, 0, -0.3 }
	};
}

EleIncendiaryDoT::EleIncendiaryDoT() {
	Element = EElement::Fire;

	Bonuses = {
		{ EAttributeType::Damage, 0, -0.3 }
	};
}

EleIncendiaryBlast::EleIncendiaryBlast() {
	Element = EElement::Fire;

	Bonuses = {
		{ EAttributeType::Damage, 0, -0.3 }
	};
}

EleShockDoT::EleShockDoT() {
	Element = EElement::Shock;

	Bonuses = {
		{ EAttributeType::Damage, 0, -0.3 }
	};
}

EleShockBlast::EleShockBlast() {
	Element = EElement::Shock;

	Bonuses = {
		{ EAttributeType::Damage, 0, -0.3 }
	};
}

EleCorrosiveDoT::EleCorrosiveDoT() {
	Element = EElement::Corrosive;

	Bonuses = {
		{ EAttributeType::Damage, 0, -0.3 }
	};
}

EleCorrosiveBlast::EleCorrosiveBlast() {
	Element = EElement::Corrosive;

	Bonuses = {
		{ EAttributeType::Damage, 0, -0.3 }
	};
}
