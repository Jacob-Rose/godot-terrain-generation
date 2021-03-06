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

		// Floats
		float levelOneMax;
		float levelTwoMax;
		float levelThreeMax;

		// Colors
		Color levelOneColor;
		Color levelTwoColor;
		Color levelThreeColor;
		Color levelFourColor;

		// Integers
		int iD;
		int faceSize;
		int noiseMult;

		// Vector3's
		Vector3 chunkPos;

		// Images
		Ref<Image> colorMap;
		Ref<Image> heightMap;

		// Mutators
		Color determineColor(float heightVal);
		Array DrawFace(Vector<Vector3> verteces, Vector<Color> newColors, int i);

		void MakeSurface(Ref<ArrayMesh> a, int x, int y, Vector3 offset, int lengthOfSquare, Vector<float> heightVals);

		// Generators
		void generateTerrainMesh(Ref<Image> _heightMap, Ref<Image> _colorMap, Vector3 generatedPosition, int lengthOfSquare);

	public:
		// Constructors
		Chunk();
		void _ready();

		// Generators
		void initializeTerrainMesh(Ref<Image> heightMap, int heightMapSize, Vector3 generatedPosition, int lengthOfSquare);

		// Settings Functions
		void addLevelSettings(float _levelOneMax, float _levelTwoMax, float _levelThreeMax, Color _levelOneColor, Color _levelTwoColor, Color _levelThreeColor, Color _levelFourColor);
		void addChunkSizeSettings(int horizontalSize, int _noiseMultiplier);
};


#endif // CHUNK_H
