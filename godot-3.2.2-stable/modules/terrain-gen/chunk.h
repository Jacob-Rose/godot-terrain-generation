/* chunk.h */

#ifndef CHUNK_H
#define CHUNK_H

#include <core/reference.h>
#include <core/image.h>
#include <core/engine.h>
#include <scene/3d/mesh_instance.h>


class Chunk : public MeshInstance {
	GDCLASS(Chunk, MeshInstance);

	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);
	public:
		Chunk();

		void _process(float delta);

		void _draw();

};


#endif // CHUNK_H
