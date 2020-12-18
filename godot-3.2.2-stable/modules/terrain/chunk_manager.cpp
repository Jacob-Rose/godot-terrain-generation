/* chunk_manager.cpp */

#include "chunk_manager.h"

// This function adds any needed functions or parameters to the editor
void ChunkManager::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("check_for_chunk_update", "player_2d_position"), &ChunkManager::checkIfChunksNeedToBeReloaded);
	ClassDB::bind_method(D_METHOD("change_settings", "Noise Octaves", "Noise Persistance", "Noise Lacunarity"), &ChunkManager::changeSettings);
	ClassDB::bind_method(D_METHOD("change_level_settings", "Level One Max", "Level Two Max", "Level Three Max", "Level One Color", "Level Two Color", "Level Three Color", "Level Four Color"), &ChunkManager::changeLevelSettings);
}


// This function gets any event calls from the engine
void ChunkManager::_notification(int p_what) {
	switch (p_what)
	{
		case NOTIFICATION_READY: {
			_ready();
		} break;
	}
}


// This function is the default constructor for the class
ChunkManager::ChunkManager()
{
	locationOfCentralChunk = Vector2(0, 0);
	set_process(true);

	colorGradient.add_point(0.0f, Color(0, 0, 0));
	colorGradient.add_point(1.0f, Color(1.0f, 1.0f, 1.0f));
}


// This function is the default destructor for the class
ChunkManager::~ChunkManager() {}


// This function gets called whenever the node gets spawned
void ChunkManager::_ready()
{
	makeNewWaveOfChunks(Vector2(0, 0));
}


// This function creates a chunk from a given player position and noise offset
void ChunkManager::createChunk(Vector3 playerPos, Vector3 chunkOffset) {

	// Create chunk and noise generator
	Chunk *chunk = memnew(Chunk);
	NoiseGenerator *noiseGen = new NoiseGenerator();

	// Make height and color maps
	Ref<Image> heightmap = noiseGen->getHeightmap(noiseImageSize, Vector2(chunkOffset.x * noiseImageScale, chunkOffset.y * noiseImageScale), noiseImageScale, noiseImageOctaves, noiseImagePersistance, noiseImageLacunarity);
	Ref<Image> colorMap = noiseGen->getColorFromHeightmap(heightmap, noiseImageSize, colorGradient);

	// Add level color settings
	chunk->addLevelSettings(levelOneMax, levelTwoMax, levelThreeMax, levelOneColor, levelTwoColor, levelThreeColor, levelFourColor);

	// Create terrain mesh and spawn into level
	chunk->initializeTerrainMesh(heightmap, noiseImageSize, playerPos, lengthOfSquare);
	add_child(chunk);

	delete noiseGen;
}


// This function checks if any new chunks need to be loaded by checking if the player has stepped outside of the central chunk
void ChunkManager::checkIfChunksNeedToBeReloaded(Vector2 playerPos) {
	bool needsReloading = false;

	// Create directional vector and the distance between the current chunk and player
	Vector2 directionalVector = playerPos - locationOfCentralChunk;
	float distance = sqrtf(powf(directionalVector.x, 2.0f) + powf(directionalVector.y, 2.0f));

	// Check if player is outside of central chunk square and adjust central chunk if needed
	if (directionalVector.x <= -lengthOfSquare) {
		locationOfCentralChunk.x -= lengthOfSquare * SIZE_OF_FACE_HORIZONTAL;
		needsReloading = true;
	}

	if (directionalVector.x >= lengthOfSquare) {
		locationOfCentralChunk.x += lengthOfSquare * SIZE_OF_FACE_HORIZONTAL;
		needsReloading = true;
	}

	if (directionalVector.y <= -lengthOfSquare) {
		locationOfCentralChunk.y -= lengthOfSquare * SIZE_OF_FACE_HORIZONTAL;
		needsReloading = true;
	}

	if (directionalVector.y >= lengthOfSquare) {
		locationOfCentralChunk.y += lengthOfSquare * SIZE_OF_FACE_HORIZONTAL;
		needsReloading = true;
	}

	// If the player is outside of the central chunk, then make new chunks
	if (needsReloading)
	{
		makeNewWaveOfChunks(getCentralChunkLocation());
	}
}


// This function gets the central chunk location
Vector2 ChunkManager::getCentralChunkLocation() {
	return locationOfCentralChunk;
}


// This function spawns a wave of 9 chunks for rendering purposes
void ChunkManager::makeNewWaveOfChunks(Vector2 newCentralChunkPos)
{
	// Destroy previous chunks
	clearOutChunks();

	// Create chunk offset
	float multiplierX = (newCentralChunkPos.x / (lengthOfSquare * 2));
	float multiplierY = (newCentralChunkPos.y / (lengthOfSquare * 2));

	// Create noise offset
	float offsetMultiplier = (noiseImageSize/ OFFSET_COEFFICIENT);

	// Center chunk
	Vector3 playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * multiplierX, 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * multiplierY);
	Vector3 newLocation = Vector3(offsetMultiplier * multiplierX, offsetMultiplier * -(multiplierY), 0);
	createChunk(playerLocation, newLocation);

	// Right Chunk
	newLocation = Vector3(offsetMultiplier * (multiplierX + 1.0f), offsetMultiplier * -(multiplierY), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierX + 1), 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * multiplierY);
	createChunk(playerLocation, newLocation);

	// Left Chunk
	newLocation = Vector3(offsetMultiplier * (multiplierX - 1.0f), offsetMultiplier * -(multiplierY), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierX - 1), 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * multiplierY);
	createChunk(playerLocation, newLocation);

	// Upper Chunk
	newLocation = Vector3(offsetMultiplier * multiplierX, offsetMultiplier * -(multiplierY + 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * multiplierX, 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierY + 1));
	createChunk(playerLocation, newLocation);

	// Lower Chunk
	newLocation = Vector3(offsetMultiplier * multiplierX, offsetMultiplier * -(multiplierY - 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * multiplierX, 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierY - 1));
	createChunk(playerLocation, newLocation);

	// Top Right Chunk
	newLocation = Vector3(offsetMultiplier * (multiplierX + 1.0f), offsetMultiplier * -(multiplierY + 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierX + 1), 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierY + 1));
	createChunk(playerLocation, newLocation);

	// Bottom Left Chunk
	newLocation = Vector3(offsetMultiplier * (multiplierX - 1.0f), offsetMultiplier * -(multiplierY - 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierX - 1), 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierY - 1));
	createChunk(playerLocation, newLocation);

	// Bottom Right Chunk
	newLocation = Vector3(offsetMultiplier * (multiplierX + 1.0f), offsetMultiplier * -(multiplierY - 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierX + 1), 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierY - 1));
	createChunk(playerLocation, newLocation);

	// Top Left Chunk
	newLocation = Vector3(offsetMultiplier * (multiplierX - 1.0f), offsetMultiplier * -(multiplierY + 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierX - 1), 0, ((lengthOfSquare * 2) - CHUNK_POSITION_OFFSET) * (multiplierY + 1));
	createChunk(playerLocation, newLocation);

}


// This function finds and destroys all currently spawned chunks
void ChunkManager::clearOutChunks()
{
	int childCount = get_child_count();

	int i = 0;

	while (i < childCount && i != childCount)
	{
		if (get_child(i)->get_class() == "Chunk")
		{
			SceneTree::get_singleton()->queue_delete(get_child(i));
		}
		i++;
	}
}


// This function changes all of the chunk noise settings
void ChunkManager::changeSettings(int imageOctaves, float imagePersistance, float imageLacunarity)
{
	noiseImageOctaves = imageOctaves;
	noiseImagePersistance = imagePersistance;
	noiseImageLacunarity = imageLacunarity;
}


// This function changes all of the level color settings
void ChunkManager::changeLevelSettings(float _levelOneMax, float _levelTwoMax, float _levelThreeMax, Color _levelOneColor, Color _levelTwoColor, Color _levelThreeColor, Color _levelFourColor)
{
	levelOneMax = _levelOneMax;
	levelTwoMax = _levelTwoMax;
	levelThreeMax = _levelThreeMax;
	levelOneColor = _levelOneColor;
	levelTwoColor = _levelTwoColor;
	levelThreeColor = _levelThreeColor;
	levelFourColor = _levelFourColor;
}
