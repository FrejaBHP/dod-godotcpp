#pragma once


enum class EAlignment {
	Neutral,
	Player,
	Enemies
};

enum class EHealthType {
	Neutral,
	Flesh,
	Shield,
	Armour,
	Energy
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

	TechLevel,
	StatusChance,
	StatusDamage,
	StatusDuration,

	SellValue
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
	Cryo,
	Explosive,
	COUNT
};

enum class EElementCompType {
	None,
	Cryo,
	ExplosiveNormal,
	ExplosiveBlast,
	IncendiaryDoT,
	IncendiaryBlast,
	ShockDoT,
	ShockBlast,
	CorrosiveDoT,
	CorrosiveBlast,
	COUNT
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
	Revolver,

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

	// For parity and ease of use
	SMG,
	Launcher,
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

enum class EAmmoType {
	Pistol,
	Revolver,
	SMG,
	Rifle,
	Shotgun,
	Sniper,
	Launcher,
	NONE
};


enum class EAIState {
	NONE, // Do nothing
	Idle, // Do not a lot
	Search, // Don't know where the player is - search for them
	Chase, // Know where the player is - find them and attack them
	Hold, // Attack from position, unmoving
	Flee, // Unwilling to fight
	Hide, // Vulnerable, like reloading. Will attack if able if exposed
	Panic, // Special state. Low on health or other factor. Should make them run away or do something crazy

	// Enemy goals. Probably not states, but a secret third thing
	Strafe,
	SeekCover,
	Reload,
};
