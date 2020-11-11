/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "mouse_image.h"

void register_mouse_image_types() {
	ClassDB::register_class<MouseImage>();
}

void unregister_mouse_image_types() {
	// Nothing to do here in this example.
}
