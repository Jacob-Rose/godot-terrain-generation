/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "chunk.h"
#include "chunk_manager.h"

void register_mouse_image_types() {
	ClassDB::register_class<Chunk>();
	ClassDB::register_class<ChunkManager>();
}

void unregister_mouse_image_types() {
	// Nothing to do here in this example.
}
