/* register_types.cpp */

#include <core/class_db.h>

#include "register_types.h"

#include "component.h"
#include "entity_manager.h"

void register_ecs_types() {

	//Due to the amount of errors, were gonna create this in godot and its all contained in this ECS_EntityManager
	ClassDB::register_class<ECS_EntityManager>();

}

void unregister_ecs_types() {
	// Nothing to do here in this example.
}
