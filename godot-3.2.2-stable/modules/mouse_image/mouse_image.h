/* mouse_image.h */

#ifndef MOUSEIMAGE_H
#define MOUSEIMAGE_H

#include <core/reference.h>
#include <core/image.h>
#include <core\engine.h>
#include <tuple>
#include <scene/2d/node_2d.h>


class MouseImage : public Node2D {
	GDCLASS(MouseImage, Node2D);

		Ref<Texture> texture;

	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);
	public:
		MouseImage();

		void _process(float delta);

		void _draw();

		void set_texture(const Ref<Texture> &p_texture);
		Ref<Texture> get_texture() const;

		void setPositionToMouse();

};


#endif // MOUSEIMAGE_H
