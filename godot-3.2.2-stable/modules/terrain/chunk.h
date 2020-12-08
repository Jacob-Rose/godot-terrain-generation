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

	class MeshData {

	public:
		PoolVector3Array *vertices;
		PoolIntArray *triangles;
		PoolVector2Array *uvs;
		Array mesh_array;
		int triangleiD = 0;

		Ref<ArrayMesh> rArrayMesh = memnew(ArrayMesh);
		;
		MeshData(double meshX, double meshY) {
			vertices = new PoolVector3Array[meshX * meshY];
			triangles = new PoolIntArray[(meshX - 1) * (meshY - 1) * 6];
			uvs = new PoolVector2Array[meshX * meshY];
		}
		void addTriangle(int a, int b, int c);
		void createMesh();
	};

	protected:
		static void _bind_methods();

		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);

		//original
		PoolVector3Array vertices;
		PoolColorArray colors;

		//updated
		PoolVector3Array _vertices;
		PoolColorArray _colors;
		bool redraw;
	public:
		Chunk();
		Chunk(float x, float z, int desiredSize);

		//	void _process(float delta);
		void _update();
		void _ready();
		void _draw();

		float xPos, zPos;

		void generateTerrainMesh(Ref<Image> heightMap);
		int chunkSize;
		
};


#endif // CHUNK_H
