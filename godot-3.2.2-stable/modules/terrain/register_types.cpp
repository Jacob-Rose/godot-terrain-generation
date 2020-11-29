/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "chunk.h"
#include "noise.h"
#include "chunk_manager.h"

void register_terrain_types() {
	ClassDB::register_class<Chunk>();
	ClassDB::register_class<ChunkManager>();
	ClassDB::register_class<NoiseGenerator>();
}

void unregister_terrain_types() {
	// Nothing to do here in this example.
}
