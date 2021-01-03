/* chunk_manager.h */

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <array>
#include "string"
#include "scene/main/node.h"
#include "core/image.h"
#include "core/engine.h"
#include "chunk.h"
#include "noise.h"
#include "core/resource.h"
#include <scene/resources/gradient.h>

// Constant ints
const int DEFAULT_NOISE_IMAGE_SIZE = 2;
const int DEFAULT_NOISE_IMAGE_OCTAVES = 3;
const int CHUNK_POSITION_OFFSET = 2;
const int DEFAULT_NOISE_MULTIPLIER = 5;

// Constant floats
const float DEFAULT_NOISE_IMAGE_SCALE = 30.0f;
const float DEFAULT_NOISE_IMAGE_PERSISTENCE = 2.5f;
const float DEFAULT_NOISE_IMAGE_LACUNARITY = 2.0f;
const float DEFAULT_LEVEL_ONE_MAX = 0.1f;
const float DEFAULT_LEVEL_TWO_MAX = 0.75f;
const float DEFAULT_LEVEL_THREE_MAX = 0.9f;
const float OFFSET_COEFFICIENT = 0.00111f;

// Constant colors
const Color DEFAULT_LEVEL_ONE_COLOR = Color(0, 0, 1, 1);
const Color DEFAULT_LEVEL_TWO_COLOR = Color(0, 1, 0, 1);
const Color DEFAULT_LEVEL_THREE_COLOR = Color(0.5f, 0.5f, 0.5f, 1);
const Color DEFAULT_LEVEL_FOUR_COLOR = Color(1, 1, 1, 1);

class ChunkManager : public Node {
	GDCLASS(ChunkManager, Node);

	protected:

		// Chunk Locations
		Vector2 locationOfCentralChunk;

		// Gradients
		Gradient colorGradient;

		// Level heights
		float levelOneMax = DEFAULT_LEVEL_ONE_MAX;
		float levelTwoMax = DEFAULT_LEVEL_TWO_MAX;
		float levelThreeMax = DEFAULT_LEVEL_THREE_MAX;

		// Level colors
		Color levelOneColor = DEFAULT_LEVEL_ONE_COLOR;
		Color levelTwoColor = DEFAULT_LEVEL_TWO_COLOR;
		Color levelThreeColor = DEFAULT_LEVEL_THREE_COLOR;
		Color levelFourColor = DEFAULT_LEVEL_FOUR_COLOR;

		// Noise-based variables
		int lengthOfSquare = DEFAULT_NOISE_IMAGE_SIZE;
		int noiseImageSize = DEFAULT_NOISE_IMAGE_SIZE;
		float noiseImageScale = DEFAULT_NOISE_IMAGE_SCALE;
		int noiseImageOctaves = DEFAULT_NOISE_IMAGE_OCTAVES;
		float noiseImagePersistance = DEFAULT_NOISE_IMAGE_PERSISTENCE;
		float noiseImageLacunarity = DEFAULT_NOISE_IMAGE_LACUNARITY;
		float noiseImageOffset = OFFSET_COEFFICIENT * (DEFAULT_NOISE_IMAGE_SIZE - 1);
		int chunkPositionOffset = CHUNK_POSITION_OFFSET;
		int noiseMultiplier = DEFAULT_NOISE_MULTIPLIER; 


		// Default Engine functions
		static void _bind_methods();
		void _notification(int p_what);

		// Acessors
		Vector2 getCentralChunkLocation();

		// Mutators
		void createChunk(Vector3 playerPos, Vector3 chunkOffset);
		void makeNewWaveOfChunks(Vector2 newCentralChunkPos);
		void clearOutChunks();

	public:
		// Constructors / Destructors
		ChunkManager();
		~ChunkManager();
		void _ready();

		// Update functions
		void checkIfChunksNeedToBeReloaded(Vector2 playerPos);

		// Mutators
		void changeSettings(int imageOctaves, float imagePersistance, float imageLacunarity, float imageSize, int horizontalSize, int heightMultiplier);
		void changeLevelSettings(float _levelOneMax, float _levelTwoMax, float _levelThreeMax, Color _levelOneColor, Color _levelTwoColor, Color _levelThreeColor, Color _levelFourColor);
};


#endif // CHUNKMANAGER_H
