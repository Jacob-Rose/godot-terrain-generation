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
		PoolVector3Array vertices = PoolVector3Array();
		PoolVector3Array normals = PoolVector3Array();
		PoolIntArray indices = PoolIntArray();

	public:
		ChunkManager();

	//	void _process(float delta);
		void _update();
		void _ready();
		void createChunk(int desiredChunks);
		bool checkIfChunksNeedToBeReloaded(Vector2 playerPos);
		Vector2 getCentralChunkLocation();
		void createCube(MeshInstance* meshInstance,int x, int y, int z);
		void makeFace(Vector3 a, Vector3 b, Vector3 c, Vector3 d);
		
		int numberOfChunks = 1;
};


#endif // CHUNKMANAGER_H
