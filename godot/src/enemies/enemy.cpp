#include "enemies/enemy.h"
#include "enemies/enemyController.h"
#include "enemies/ai/basicRangedAIComponent.h"
#include "combat/healthComponent.h"
#include "gun/gun.h"
#include "gameInstance.h"
#include "runManager.h"

using namespace godot;

void Enemy::_bind_methods() {
	//VARIANT_ENUM_CAST(Enemy::FAllowedWeaponTypes);

	ClassDB::bind_method(D_METHOD("SetEXPBounty", "p_Bounty"), &Enemy::SetEXPBounty);
	ClassDB::bind_method(D_METHOD("GetEXPBounty"), &Enemy::GetEXPBounty);

	ClassDB::bind_method(D_METHOD("SetWeaponTypes", "p_WTypes"), &Enemy::SetAllowedWeaponTypes);
	ClassDB::bind_method(D_METHOD("GetWeaponTypes"), &Enemy::GetAllowedWeaponTypes);

	ClassDB::bind_method(D_METHOD("SetCanUseShield", "p_bShield"), &Enemy::SetCanUseShield);
	ClassDB::bind_method(D_METHOD("GetCanUseShield"), &Enemy::GetCanUseShield);

	/*
	ClassDB::bind_method(D_METHOD("SetHealthDict", "pDict"), &Enemy::SetHealthDict);
	ClassDB::bind_method(D_METHOD("GetHealthDict"), &Enemy::GetHealthDict);

	ADD_PROPERTY(PropertyInfo(
		Variant::DICTIONARY,
		"healthBars",
		PROPERTY_HINT_TYPE_STRING,
		String::num_int64(Variant::INT) + "/" + String::num_int64(PROPERTY_HINT_ENUM) + ":Neutral,Flesh,Shield,Armour,Energy" + ";" + "float"
	),
	"SetHealthDict", "GetHealthDict");
	*/

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "movement_speed", PROPERTY_HINT_NONE), "CharSetMaxSpeed", "CharGetMaxSpeed");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "base_exp_bounty", PROPERTY_HINT_NONE), "SetEXPBounty", "GetEXPBounty");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "can_spawn_with_shield", PROPERTY_HINT_NONE), "SetCanUseShield", "GetCanUseShield");
	ADD_PROPERTY(PropertyInfo(
		Variant::INT,
		"allowed_gun_types",
		PROPERTY_HINT_FLAGS,
		"Pistol,Revolver,SMG,Rifle,Shotgun,Sniper,Launcher"
	), "SetWeaponTypes", "GetWeaponTypes");

	ADD_SIGNAL(MethodInfo("enemy_died", PropertyInfo(Variant::OBJECT, "enemy")));
}

void Enemy::_ready() {
	Alignment = EAlignment::Enemies;
	add_to_group("Character");
	add_to_group("EnemyGun");

	Level = GameInstance::GetInstance().GetRunManager()->CurrentAreaLevel;

	FireRateMod = 0.70;

	PistolAmmo = -1;
	SMGAmmo = -1;
	ARAmmo = -1;
	RevolverAmmo = -1;
	ShotgunAmmo = -1;
	SniperAmmo = -1;
	LauncherAmmo = -1;

	Controller = get_node<EnemyController>("EnemyController");
	Controller->SetCharacter(this);

	HealthComponent* hc = (HealthComponent*)Controller->get_node_or_null("HealthComponent");
	if (hc) {
		Controller->SetHealthComponent(hc);
		hc->InitHealthBars();

		if (CanUseShield) {
			print_line(vformat("Level: %d, Max Health: %2.f", Level, hc->HealthBars.get(0)->GetMaxHealth()));
		}
	}

	EnemyAIComponent* aic = (EnemyAIComponent*)Controller->get_node_or_null("EnemyAIComponent");
	if (aic) {
		Controller->SetAIComponent(aic);
		aic->SetController(Controller);
	}

	//print_line(vformat("%d", WeaponSpawnTypes));
	
	PlayerCast = get_node<RayCast2D>("PlayerCast");

	if (AllowedGunTypes != 0) {
		InitGunUse();
	}
}

void Enemy::_physics_process(double delta) {

}

void Enemy::SetEXPBounty(const double bounty) {
	EXPBounty = bounty;
}

double Enemy::GetEXPBounty() const {
	return EXPBounty;
}

void Enemy::SetAllowedWeaponTypes(const unsigned int bitfield) {
	AllowedGunTypes = (FAllowedGunTypes)bitfield;
}

unsigned int Enemy::GetAllowedWeaponTypes() const {
	return AllowedGunTypes;
}

void Enemy::SetCanUseShield(const bool bShield) {
	CanUseShield = bShield;
}

bool Enemy::GetCanUseShield() const {
	return CanUseShield;
}

/*
void Enemy::SetHealthDict(const Dictionary& dict) {
	HealthDictionary = dict;
}

Dictionary Enemy::GetHealthDict() const {
	return HealthDictionary;
}
*/

void Enemy::Die() {
	Character::Die();
}

void Enemy::OnDeath() {
	emit_signal("enemy_died", this);

	if (CurrentGun) {
		CurrentGun->MagAmmo = CurrentGun->GunDef->MagSize;
		GameInstance::GetInstance().CopyEquippedGunToDrop(CurrentGun, get_global_position());
		CurrentGun->FreeGun();
	}

	GameInstance::GetInstance().EnemyDeath(this);

	queue_free();
}

void Enemy::InitGunUse() {
	Vector<EAmmoType> allowedTypes;

	if (AllowedGunTypes & FAllowedGunTypes::Pistol) {
		allowedTypes.append(EAmmoType::Pistol);
	}
	if (AllowedGunTypes & FAllowedGunTypes::Revolver) {
		allowedTypes.append(EAmmoType::Revolver);
	}
	if (AllowedGunTypes & FAllowedGunTypes::SMG) {
		allowedTypes.append(EAmmoType::SMG);
	}
	if (AllowedGunTypes & FAllowedGunTypes::Rifle) {
		allowedTypes.append(EAmmoType::Rifle);
	}
	if (AllowedGunTypes & FAllowedGunTypes::Shotgun) {
		allowedTypes.append(EAmmoType::Shotgun);
	}
	if (AllowedGunTypes & FAllowedGunTypes::Sniper) {
		allowedTypes.append(EAmmoType::Sniper);
	}
	if (AllowedGunTypes & FAllowedGunTypes::Launcher) {
		allowedTypes.append(EAmmoType::Launcher);
	}

	int chosenType = (int)allowedTypes.get(GetRandomInt(0, allowedTypes.size() - 1));

	Gun* newGun = GameInstance::GetInstance().GenerateNakedGun(chosenType, Level);

	if (newGun) {
		add_child(newGun);
		newGun->OwningCharacter = this;
		CurrentGun = newGun;
		Controller->ApplyCurrentGun();

		//print_line(vformat("Given gun %s", CurrentGun->GunDef->GunName.c_str()));
	}
}
