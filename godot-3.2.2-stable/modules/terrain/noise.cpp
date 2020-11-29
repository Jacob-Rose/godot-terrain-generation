/* noise.cpp */

#include "noise.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)


void NoiseGenerator::_bind_methods() {

}

void NoiseGenerator::_notification(int p_what) {
	//switch (p_what) {
	//	case NOTIFICATION_PROCESS:
	//		_process(get_process_delta_time()); //this is called each frame like Update() in Unity
	//	case NOTIFICATION_DRAW:
	//		_draw();
	//}
}

NoiseGenerator::NoiseGenerator() {
	set_process(true);
}

void NoiseGenerator::_process(float delta)
{
	//_process can run in editor too, we need to specify not to run in editor here
	if(!Engine::get_singleton()->is_editor_hint()) {


	}
}

void NoiseGenerator::_draw() {

}
