/* register_types.cpp */

#include <core/class_db.h>

#include "register_types.h"
#include "subdivider.h"


void register_subdivision_types() {

	//Due to the amount of errors, were gonna create this in godot and its all contained in this ECS_EntityManager
	ClassDB::register_class<Subdivider>();

}

void unregister_subdivision_types() {
	// Nothing to do here in this example.
}
