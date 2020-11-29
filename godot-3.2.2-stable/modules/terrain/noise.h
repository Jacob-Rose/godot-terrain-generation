/* noise.h */

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "core/reference.h"
#include "core/image.h"
#include "core/engine.h"
#include "scene/3d/mesh_instance.h"


class NoiseGenerator : public Reference {
	GDCLASS(NoiseGenerator, Reference);

	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);
	public:
		NoiseGenerator();

		void _process(float delta);

		void _draw();

};


#endif // PERLINNOISE_H
