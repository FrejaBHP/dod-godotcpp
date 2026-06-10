#pragma once

// Taget fra tidligere kort projekt - skal nok laves lidt om i senere
enum class EAttributeType {
	Damage,
	ProjectileCount,
	ShotCost,
	ProjectileSpeed,

	Accuracy,
	Stability,

	FireRate,
	MagSize,
	ReloadTime,

	BurstCount,
	StatusChance,
	StatusDamage,
	StatusDuration
};

enum class EElement {
	None,
	Fire,
	Shock,
	Corrosive,
	Cryo
};

enum class EManufacturer {
	Placeholder,
	Mars,			// Dahl - high stability
	Prism,			// Torgue but with lasers - high damage at the cost of firerate or accuracy
	Bozboz,			// S&S/Bandit/Scav - high capacity
	Weaver,			// Hyperion - high accuracy
	Smitherson,		// Jakobs - high damage and accuracy, not elemental, lower firerate
	Violet,			// Maliwan - always elemental, elemental bonuses
	Prometheus,		// Atlas - good damage and accuracy
	Bjorn,			// Vladof - high firerate
	COUNT
};

enum class EGunType {
	None,

	// Pistols
	PistolRepeater,
	PistolMachine,
	PistolRevolver,

	SMG,

	// Rifles
	RifleAssault,
	RifleMG,

	// Shotguns
	ShotgunCombat,
	ShotgunAssault,
	ShotgunDouble,

	// Snipers
	SniperSemiAuto,
	SniperBoltAction,

	Launcher
};

enum class EGunRarity {
	Inferior,
	Common,
	Uncommon,
	Rare,
	Epic,
	SemiLegendary,
	Legendary
};
