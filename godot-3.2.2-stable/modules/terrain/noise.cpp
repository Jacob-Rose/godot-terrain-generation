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
}

void NoiseGenerator::_process(float delta)
{

}

void NoiseGenerator::_draw() {

}
