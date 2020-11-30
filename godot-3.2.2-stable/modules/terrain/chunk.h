/* chunk.h */

#ifndef CHUNK_H
#define CHUNK_H

#include "core/reference.h"
#include "core/image.h"
#include "scene/resources/mesh.h"
#include "core/os/input.h"
#include "core/engine.h"
#include "scene/3d/mesh_instance.h"


class Chunk : public MeshInstance {
	GDCLASS(Chunk, MeshInstance);

	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);
	public:
		Chunk();
		Chunk(float x, float z, int desiredSize);

		//	void _process(float delta);
		void _update();
		void _ready();

		float xPos, zPos;

		int chunkSize;
		
};


#endif // CHUNK_H
