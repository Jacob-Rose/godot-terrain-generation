/* mouse_image.cpp */

#include "mouse_image.h"
#include <scene/main/viewport.h> //used to get mouse position in _process(float)


void MouseImage::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_texture", "texture"), &MouseImage::set_texture);
	ClassDB::bind_method(D_METHOD("get_texture"), &MouseImage::get_texture);
}

void MouseImage::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_PROCESS:
			_process(get_process_delta_time()); //this is called each frame like Update() in Unity
		case NOTIFICATION_DRAW:
			_draw();
	}
}

MouseImage::MouseImage() {
	set_process(true);
}

void MouseImage::_process(float delta)
{
	//what, _process can run in editor too, we need to specify not to run in editor here
	if(!Engine::get_singleton()->is_editor_hint()) {
		setPositionToMouse();
	}
}

void MouseImage::_draw() {
	if (texture.is_null())
		return;

	RID ci = get_canvas_item();
	bool filter_clip = false;
	int size = 32;


	texture->draw_rect(ci, Rect2(-size/2, -size/2, size, size), false, Color(1, 1, 1), filter_clip);
}

void MouseImage::set_texture(const Ref<Texture> &p_texture) {
	texture = p_texture;
}

Ref<Texture> MouseImage::get_texture() const {
	return Ref<Texture>();
}

void MouseImage::setPositionToMouse() {
	set_global_position(get_viewport()->get_mouse_position());
}
