/* chunk_manager.cpp */

#include "chunk_manager.h"


void ChunkManager::_bind_methods() {
}

void ChunkManager::_notification(int p_what)
{
	//switch (p_what) {
	//	case NOTIFICATION_PROCESS:
	//		_process(get_process_delta_time()); //this is called each frame like Update() in Unity
	//		update();
	//		break;
	//	case NOTIFICATION_DRAW:
	//		_draw();
	//}
}

ChunkManager::ChunkManager() {
	set_process(true);
}

void ChunkManager::_process(float delta)
{
	//what, _process can run in editor too, we need to specify not to run in editor here
	if(!Engine::get_singleton()->is_editor_hint()) {
		
	}
}

void ChunkManager::_draw() {

}
