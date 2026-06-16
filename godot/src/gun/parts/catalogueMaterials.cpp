#include "gun/parts/catalogueMaterials.h"
#include "shared/utility.h"

constexpr int32_t NumBasicMaterialsEach = 3;

std::unique_ptr<MaterialComponent> GetRandomMaterial(EManufacturer manufacturer) {
	int32_t matIndex = GetRandomInt(0, NumBasicMaterialsEach - 1);
	MaterialComponent* mat;

	switch (manufacturer) {
		case EManufacturer::Mars:
			if (matIndex == 0) {
				mat = new MatMars1();
			}
			else if (matIndex == 0) {
				mat = new MatMars2();
			}
			else {
				mat = new MatMars3();
			}
			break;

		case EManufacturer::Prism:
			if (matIndex == 0) {
				mat = new MatPrism1();
			}
			else if (matIndex == 0) {
				mat = new MatPrism2();
			}
			else {
				mat = new MatPrism3();
			}
			break;

		case EManufacturer::Bozboz:
			if (matIndex == 0) {
				mat = new MatBozboz1();
			}
			else if (matIndex == 0) {
				mat = new MatBozboz2();
			}
			else {
				mat = new MatBozboz3();
			}
			break;

		case EManufacturer::Weaver:
			if (matIndex == 0) {
				mat = new MatWeaver1();
			}
			else if (matIndex == 0) {
				mat = new MatWeaver2();
			}
			else {
				mat = new MatWeaver3();
			}
			break;

		case EManufacturer::Smitherson:
			if (matIndex == 0) {
				mat = new MatSmitherson1();
			}
			else if (matIndex == 0) {
				mat = new MatSmitherson2();
			}
			else {
				mat = new MatSmitherson3();
			}
			break;

		case EManufacturer::Violet:
			if (matIndex == 0) {
				mat = new MatViolet1();
			}
			else if (matIndex == 0) {
				mat = new MatViolet2();
			}
			else {
				mat = new MatViolet3();
			}
			break;

		case EManufacturer::Prometheus:
			if (matIndex == 0) {
				mat = new MatPrometheus1();
			}
			else if (matIndex == 0) {
				mat = new MatPrometheus2();
			}
			else {
				mat = new MatPrometheus3();
			}
			break;

		default: // Bjorn
			if (matIndex == 0) {
				mat = new MatBjorn1();
			}
			else if (matIndex == 0) {
				mat = new MatBjorn2();
			}
			else {
				mat = new MatBjorn3();
			}
			break;
	}

	return std::unique_ptr<MaterialComponent>(mat);
}

MatPrometheus1::MatPrometheus1() {
	Manufacturer = EManufacturer::Prometheus;
	PartNum = 1;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::FireRate, 0, -0.05 },
		{ EAttributeType::MagSize, 0, 0.15 }
	};
}

MatPrometheus2::MatPrometheus2() {
	Manufacturer = EManufacturer::Prometheus;
	PartNum = 2;
	PartRarity = 2;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.15 },
		{ EAttributeType::FireRate, 0, -0.05 },
		{ EAttributeType::MagSize, 0, 0.15 }
	};
}

MatPrometheus3::MatPrometheus3() {
	Manufacturer = EManufacturer::Prometheus;
	PartNum = 3;
	PartRarity = 4;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, -0.05 },
		{ EAttributeType::MagSize, 0, 0.15 }
	};
}


MatPrism1::MatPrism1() {
	Manufacturer = EManufacturer::Prism;
	PartNum = 1;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.2 },
		{ EAttributeType::FireRate, 0, 0.16 },
		{ EAttributeType::Spread, 0, 0.35 },
		{ EAttributeType::InaccuracyMin, 0, 0.35 },
		{ EAttributeType::InaccuracyMax, 0, 0.35 }
	};
}

MatPrism2::MatPrism2() {
	Manufacturer = EManufacturer::Prism;
	PartNum = 2;
	PartRarity = 2;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.25 },
		{ EAttributeType::FireRate, 0, 0.16 },
		{ EAttributeType::Spread, 0, 0.35 },
		{ EAttributeType::InaccuracyMin, 0, 0.35 },
		{ EAttributeType::InaccuracyMax, 0, 0.35 }
	};
}

MatPrism3::MatPrism3() {
	Manufacturer = EManufacturer::Prism;
	PartNum = 3;
	PartRarity = 4;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.3 },
		{ EAttributeType::FireRate, 0, 0.16 },
		{ EAttributeType::Spread, 0, 0.35 },
		{ EAttributeType::InaccuracyMin, 0, 0.35 },
		{ EAttributeType::InaccuracyMax, 0, 0.35 }
	};
}

MatMars1::MatMars1() {
	Manufacturer = EManufacturer::Mars;
	PartNum = 1;

	Bonuses = {
		{ EAttributeType::Spread, 0, 0.2 },
		{ EAttributeType::InaccuracyMin, 0, 0.2 },
		{ EAttributeType::InaccuracyMax, 0, 0.2 }
	};
}

MatMars2::MatMars2() {
	Manufacturer = EManufacturer::Mars;
	PartNum = 2;
	PartRarity = 2;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.05 },
		{ EAttributeType::Spread, 0, 0.15 },
		{ EAttributeType::InaccuracyMin, 0, 0.15 },
		{ EAttributeType::InaccuracyMax, 0, 0.15 },
		{ EAttributeType::ReloadSpeed, 0, 0.24 }
	};
}

MatMars3::MatMars3() {
	Manufacturer = EManufacturer::Mars;
	PartNum = 3;
	PartRarity = 4;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, 0.15 },
		{ EAttributeType::InaccuracyMin, 0, 0.15 },
		{ EAttributeType::InaccuracyMax, 0, 0.15 },
	};
}


MatWeaver1::MatWeaver1() {
	Manufacturer = EManufacturer::Weaver;
	PartNum = 1;

	Bonuses = {
		{ EAttributeType::Spread, 0, -0.7 },
		{ EAttributeType::InaccuracyMin, 0, -0.7 },
		{ EAttributeType::InaccuracyMax, 0, -0.7 },
	};
}

MatWeaver2::MatWeaver2() {
	Manufacturer = EManufacturer::Weaver;
	PartNum = 2;
	PartRarity = 2;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.05 },
		{ EAttributeType::Spread, 0, -0.85 },
		{ EAttributeType::InaccuracyMin, 0, -0.85 },
		{ EAttributeType::InaccuracyMax, 0, -0.85 },
		{ EAttributeType::FireRate, 0, 0.3 },
	};
}

MatWeaver3::MatWeaver3() {
	Manufacturer = EManufacturer::Weaver;
	PartNum = 3;
	PartRarity = 4;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, -1.0 },
		{ EAttributeType::InaccuracyMin, 0, -1.0 },
		{ EAttributeType::InaccuracyMax, 0, -1.0 },
		{ EAttributeType::ReloadSpeed, 0, 0.3 }
	};
}


MatSmitherson1::MatSmitherson1() {
	Manufacturer = EManufacturer::Smitherson;
	PartNum = 1;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.35 },
		{ EAttributeType::FireRate, 0, -0.5 }
	};
}

MatSmitherson2::MatSmitherson2() {
	Manufacturer = EManufacturer::Smitherson;
	PartNum = 2;
	PartRarity = 2;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.25 },
		{ EAttributeType::Spread, 0, -0.5 },
		{ EAttributeType::InaccuracyMin, 0, -0.5 },
		{ EAttributeType::InaccuracyMax, 0, -0.5 },
		{ EAttributeType::FireRate, 0, -0.5 }
	};
}

MatSmitherson3::MatSmitherson3() {
	Manufacturer = EManufacturer::Smitherson;
	PartNum = 3;
	PartRarity = 4;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.5 },
		{ EAttributeType::Spread, 0, 0.6 },
		{ EAttributeType::InaccuracyMin, 0, 0.6 },
		{ EAttributeType::InaccuracyMax, 0, 0.6 },
		{ EAttributeType::FireRate, 0, -0.5 }
	};
}


MatBjorn1::MatBjorn1() {
	Manufacturer = EManufacturer::Bjorn;
	PartNum = 1;

	Bonuses = {
		{ EAttributeType::Spread, 0, 0.32 },
		{ EAttributeType::InaccuracyMin, 0, 0.32 },
		{ EAttributeType::InaccuracyMax, 0, 0.32 },
		{ EAttributeType::FireRate, 0, 0.44 },
	};
}

MatBjorn2::MatBjorn2() {
	Manufacturer = EManufacturer::Bjorn;
	PartNum = 2;
	PartRarity = 2;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.05 },
		{ EAttributeType::Spread, 0, 0.32 },
		{ EAttributeType::InaccuracyMin, 0, 0.32 },
		{ EAttributeType::InaccuracyMax, 0, 0.32 },
		{ EAttributeType::FireRate, 0, 0.5 },
	};
}

MatBjorn3::MatBjorn3() {
	Manufacturer = EManufacturer::Bjorn;
	PartNum = 3;
	PartRarity = 4;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, 0.32 },
		{ EAttributeType::InaccuracyMin, 0, 0.32 },
		{ EAttributeType::InaccuracyMax, 0, 0.32 },
		{ EAttributeType::FireRate, 0, 0.56 },
	};
}


MatBozboz1::MatBozboz1() {
	Manufacturer = EManufacturer::Bozboz;
	PartNum = 1;

	Bonuses = {
		{ EAttributeType::MagSize, 0, 0.4 },
		{ EAttributeType::ReloadSpeed, 0, -0.19 }
	};
}

MatBozboz2::MatBozboz2() {
	Manufacturer = EManufacturer::Bozboz;
	PartNum = 2;
	PartRarity = 2;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.05 },
		{ EAttributeType::MagSize, 0, 0.42 },
		{ EAttributeType::ReloadSpeed, 0, -0.19 }
	};
}

MatBozboz3::MatBozboz3() {
	Manufacturer = EManufacturer::Bozboz;
	PartNum = 3;
	PartRarity = 4;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::MagSize, 0, 0.5 },
	};
}


MatViolet1::MatViolet1() {
	Manufacturer = EManufacturer::Violet;
	PartNum = 1;

	Bonuses = {

	};
}

MatViolet2::MatViolet2() {
	Manufacturer = EManufacturer::Violet;
	PartNum = 2;
	PartRarity = 2;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.05 },
		{ EAttributeType::Spread, 0, -0.11 },
		{ EAttributeType::InaccuracyMin, 0, -0.11 },
		{ EAttributeType::InaccuracyMax, 0, -0.11 },
		{ EAttributeType::ReloadSpeed, 0, 0.11 },
	};
}

MatViolet3::MatViolet3() {
	Manufacturer = EManufacturer::Violet;
	PartNum = 3;
	PartRarity = 4;

	Bonuses = {
		{ EAttributeType::Damage, 0, 0.1 },
		{ EAttributeType::Spread, 0, -0.25 },
		{ EAttributeType::InaccuracyMin, 0, -0.25 },
		{ EAttributeType::InaccuracyMax, 0, -0.25 },
		{ EAttributeType::ReloadSpeed, 0, 0.25 }
	};
}
