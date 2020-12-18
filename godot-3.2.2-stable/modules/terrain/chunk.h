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

		float levelOneMax;
		float levelTwoMax;
		float levelThreeMax;

		Color levelOneColor;
		Color levelTwoColor;
		Color levelThreeColor;
		Color levelFourColor;

		int iD;
		Vector3 chunkPos;

		Ref<Image> mColorMap;
		Ref<Image> mHeightMap;

		void construct(Vector3 pos);

	public:
		Chunk();
		Chunk(Vector3 position);



		//	void _process(float delta);
		void _update();
		void _ready();
		void _draw();

		Array DrawFace(Vector<Vector3> verteces, Vector<Color> newColors, int i);

		Vector2 checkOutOfBounds(int i, Vector<Vector3> verteces);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="heightMap"></param>
		/// <param name="heightMapSize">The size of one side of the 2D heightmap, e.x. 25 == 25 * 25 size array</param>
		void generateTerrainMesh(Ref<Image> heightMap, int heightMapSize, Vector3 generatedPosition, int lengthOfSquare);
		void generateTerrainMesh(Ref<Image> heightMap, Ref<Image> colorMap, Vector3 generatedPosition, int lengthOfSquare);
		Color determineColor(float heightVal);

		void addLevelSettings(float _levelOneMax, float _levelTwoMax, float _levelThreeMax, Color _levelOneColor, Color _levelTwoColor, Color _levelThreeColor, Color _levelFourColor);
};


#endif // CHUNK_H
