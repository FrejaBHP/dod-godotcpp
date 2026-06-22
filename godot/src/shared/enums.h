#pragma once


enum class EAlignment {
	Neutral,
	Player,
	Enemies
};


enum class EAttributeType {
	Damage,
	ProjectileCount,
	ShotCost,
	ProjectileSpeed,

	Recoil,
	Spread,
	InaccuracyMin,
	InaccuracyMax,
	InaccuracyRegen,

	FireRate,
	MagSize,
	ReloadSpeed,

	BurstCount,
	StatusChance,
	StatusDamage,
	StatusDuration
};

enum class EFireMode {
	Automatic,
	Semi,
	Burst
};

enum class EElement {
	None,
	Fire,
	Shock,
	Corrosive,
	Cryo
};

enum class EManufacturer {
	Mars,			// Dahl - high stability
	Prism,			// Torgue but with lasers - high damage at the cost of firerate or accuracy
	Bozboz,			// S&S/Bandit/Scav - high capacity
	Weaver,			// Hyperion - high accuracy
	Smitherson,		// Jakobs - high damage and accuracy, not elemental, lower firerate
	Violet,			// Maliwan - always elemental, elemental bonuses
	Prometheus,		// Atlas - good damage and accuracy
	Bjorn,			// Vladof - high firerate
	COUNT,
	Placeholder
};

enum class EGunType {
	None,
	Pistol,
	Revolver,
	SMG,
	Rifle,
	Shotgun,
	Sniper,
	Launcher
};

enum class EGunSubType {
	None,

	// Pistols
	Repeater,
	MachinePistol,

	// Rifles
	CombatRifle,
	MachineGun,

	// Shotguns
	CombatShotgun,
	AssaultShotgun,
	DoubleBarrel,

	// Snipers
	SniperSemiAuto,
	SniperBoltAction,
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
