/* chunk_manager.h */

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <core/main/node.h>
#include <core/image.h>
#include <core\engine.h>


class ChunkManager : public Node {
	GDCLASS(ChunkManager, Node);

	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);
	public:
		ChunkManager();

		void _process(float delta);

		void _draw();
};


#endif // CHUNKMANAGER_H
