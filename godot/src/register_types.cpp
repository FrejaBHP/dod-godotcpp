#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "world.h"
#include "character.h"
#include "player/playerChar.h"
#include "player/playerController.h"
#include "enemies/enemyGun.h"
#include "enemies/enemyController.h"
#include "projectiles/projectile.h"
#include "gun/gun.h"
#include "gun/gunDropped.h"
#include "ui/hud.h"
#include "ui/itemCard.h"

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_RUNTIME_CLASS(World);

	GDREGISTER_RUNTIME_CLASS(Character);

	GDREGISTER_RUNTIME_CLASS(Player);
	GDREGISTER_RUNTIME_CLASS(PlayerController);

	GDREGISTER_RUNTIME_CLASS(EnemyGun);
	GDREGISTER_RUNTIME_CLASS(EnemyController);

	GDREGISTER_RUNTIME_CLASS(HUD);
	GDREGISTER_RUNTIME_CLASS(ItemCard);

	GDREGISTER_RUNTIME_CLASS(Projectile);

	GDREGISTER_RUNTIME_CLASS(Gun);
	GDREGISTER_RUNTIME_CLASS(GunDropped);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
	// Initialization
GDExtensionBool GDE_EXPORT Entry(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
