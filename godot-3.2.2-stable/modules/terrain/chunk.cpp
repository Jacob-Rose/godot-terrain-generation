/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)


void Chunk::_bind_methods() {

}

void Chunk::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_PROCESS: {

			_update();
		} break;

		case NOTIFICATION_READY: {
			_ready();
		} break;
	}
}

Chunk::Chunk() {
	set_process(true);
}

Chunk::Chunk(float x, float z, int desiredSize) {
	set_process(true);
	xPos = x;
	zPos = z;
	chunkSize = desiredSize;
}

void Chunk::_update() {
}

void Chunk::_ready() {
	
}

//void Chunk::_process(float delta)
//{
//	//_process can run in editor too, we need to specify not to run in editor here
//	if(!Engine::get_singleton()->is_editor_hint()) {
//
//
//	}
//}
