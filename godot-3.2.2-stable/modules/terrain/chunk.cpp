/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)


void Chunk::_bind_methods() {

}

void Chunk::_notification(int p_what) {
	//switch (p_what) {
	//	case NOTIFICATION_PROCESS:
	//		_process(get_process_delta_time()); //this is called each frame like Update() in Unity
	//	case NOTIFICATION_DRAW:
	//		_draw();
	//}
}

Chunk::Chunk() {
	set_process(true);
}

void Chunk::_process(float delta)
{
	//_process can run in editor too, we need to specify not to run in editor here
	if(!Engine::get_singleton()->is_editor_hint()) {


	}
}

void Chunk::_draw() {

}
