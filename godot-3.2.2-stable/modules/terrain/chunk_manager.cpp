/* chunk_manager.cpp */

#include "chunk_manager.h"


void ChunkManager::_bind_methods() {
}

void ChunkManager::_notification(int p_what)
{
	switch (p_what) {
		case NOTIFICATION_PROCESS: {
	
			_update();
		} break;

		case NOTIFICATION_READY: {
			_ready();
		} break;
	}
}

ChunkManager::ChunkManager() {
	set_process(true);
}
//Pretty sure dont need this since we have our own custom _update function now
/*void ChunkManager::_process(float delta)
{
	//what, _process can run in editor too, we need to specify not to run in editor here
	if(!Engine::get_singleton()->is_editor_hint()) {
		
	}
}*/

void ChunkManager::_update() {
}

void ChunkManager::_ready() {

	for (int i = 0; i < numberOfChunks; i++) {
		Chunk *chunk = new Chunk(2, 2, 1);
		//chunk->set_mesh(mySimpleMesh);
		printf("Chunkspawned");
	}
	
}
