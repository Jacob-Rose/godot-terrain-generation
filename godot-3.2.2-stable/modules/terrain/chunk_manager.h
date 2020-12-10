/* chunk_manager.h */

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <array>
#include "string"
#include "scene/main/node.h"
#include "scene/resources/mesh.h"
#include "core/math/triangle_mesh.h"
#include "core/image.h"
#include "core/engine.h"
#include "chunk.h"
#include "noise.h"
#include "core/resource.h"

class ChunkManager : public Node {
	GDCLASS(ChunkManager, Node);



	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);

		//Ref<ArrayMesh> arrayMesh;
		ArrayMesh arrayMesh;
		Array mesh_array;

		Vector3 meshArray[6];
		const float LENGTH_OF_SQUARE = 10.0f;
		Vector2 locationOfCentralChunk;
		
		Ref<Resource> newSource;

		NoiseGenerator noiseGenerator;

	public:
		ChunkManager();

	//	void _process(float delta);
		void _update();
		void _ready();
		void createChunk(Vector3 playerPos,Vector3 chunkOffset);
		bool checkIfChunksNeedToBeReloaded(Vector2 playerPos);
		Vector2 getCentralChunkLocation();

		int numberOfChunks = 1;
};


#endif // CHUNKMANAGER_H
