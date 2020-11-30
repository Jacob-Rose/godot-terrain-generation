/* chunk_manager.h */

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "scene/main/node.h"
#include "scene/resources/mesh.h"
#include "core/math/triangle_mesh.h"
#include "core/image.h"
#include "core/engine.h"
#include "chunk.h"

class ChunkManager : public Node {
	GDCLASS(ChunkManager, Node);

	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);
	public:
		ChunkManager();

	//	void _process(float delta);
		void _update();
		void _ready();

		int numberOfChunks = 1;
};


#endif // CHUNKMANAGER_H
