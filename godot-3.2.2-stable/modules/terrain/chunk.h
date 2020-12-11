/* chunk.h */

#ifndef CHUNK_H
#define CHUNK_H

#include "core/math/triangle_mesh.h"
#include "scene/main/node.h"
#include "core/reference.h"
#include "core/image.h"
#include "scene/resources/mesh.h"
#include "core/os/input.h"
#include "core/engine.h"
#include "core/method_bind_ext.gen.inc"
#include "scene/3d/mesh_instance.h"


class Chunk : public MeshInstance {
	GDCLASS(Chunk, MeshInstance);

	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);

		//original
		PoolVector3Array vertices;
		PoolVector3Array normals;
		PoolVector2Array uvs;
		PoolColorArray colors;
		PoolIntArray indeces;

		//updated
		PoolVector3Array _vertices;
		PoolColorArray _colors;

		int iD;
		Vector3 chunkPos;

		Ref<Image> mColorMap;

		void construct(Vector3 pos);

	public:
		Chunk();
		Chunk(Vector3 position);



		//	void _process(float delta);
		void _update();
		void _ready();
		void _draw();

		Array DrawFace(Vector<Vector3> verteces,int i);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="heightMap"></param>
		/// <param name="heightMapSize">The size of one side of the 2D heightmap, e.x. 25 == 25 * 25 size array</param>
		void generateTerrainMesh(PoolRealArray heightMap, int heightMapSize);
		void generateTerrainMesh(PoolRealArray heightMap, Ref<Image> colorMap);
};


#endif // CHUNK_H
