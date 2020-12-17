/* chunk_manager.cpp */

#include "chunk_manager.h"
#include "core/io/resource_loader.h"
#include <thread>

void ChunkManager::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("check_for_chunk_update", "player_2d_position"), &ChunkManager::checkIfChunksNeedToBeReloaded);
	ClassDB::bind_method(D_METHOD("change_settings", "Noise Octaves", "Noise Persistance", "Noise Lacunarity"), &ChunkManager::changeSettings);
}

void ChunkManager::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_PROCESS: {

			_update();
		} break;

		case NOTIFICATION_READY: {
			_ready();
		} break;
	}
}

ChunkManager::ChunkManager() {
	//newSource = ResourceLoader::load("res://Floor.tcsn");
	locationOfCentralChunk = Vector2(0, 0);
	set_process(true);

	colorGradient.add_point(0.0f, Color(0, 0, 0));
	colorGradient.add_point(1.0f, Color(1.0f, 1.0f, 1.0f));
}
ChunkManager::~ChunkManager() {
}
//Pretty sure dont need this since we have our own custom _update function now
/*void ChunkManager::_process(float delta)
{
	//what, _process can run in editor too, we need to specify not to run in editor here
	if(!Engine::get_singleton()->is_editor_hint()) {
		
	}
}*/

void ChunkManager::_update() {
}

void ChunkManager::_ready()
{
	makeNewWaveOfChunks(Vector2(0, 0));
}

void ChunkManager::createChunk(Vector3 playerPos, Vector3 chunkOffset) {

	Chunk *chunk = memnew(Chunk, playerPos); //TODO memory leak?

	NoiseGenerator *noiseGen = new NoiseGenerator();
	Ref<Image> heightmap = noiseGen->getHeightmap(noiseImageSize, Vector2(chunkOffset.x * noiseImageScale, chunkOffset.y * noiseImageScale), noiseImageScale, noiseImageOctaves, noiseImagePersistance, noiseImageLacunarity);

	Ref<Image> colorMap = noiseGen->getColorFromHeightmap(heightmap, noiseImageSize, colorGradient);

	chunk->generateTerrainMesh(heightmap, noiseImageSize, playerPos, lengthOfSquare);
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
		locationOfCentralChunk.x -= lengthOfSquare * 2.0f;
		needsReloading = true;
	}

	if (directionalVector.x >= lengthOfSquare) {
		locationOfCentralChunk.x += lengthOfSquare * 2.0f;
		needsReloading = true;
	}

	if (directionalVector.y <= -lengthOfSquare) {
		locationOfCentralChunk.y -= lengthOfSquare * 2.0f;
		needsReloading = true;
	}

	if (directionalVector.y >= lengthOfSquare) {
		locationOfCentralChunk.y += lengthOfSquare * 2.0f;
		needsReloading = true;
	}

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
	clearOutChunks();

	float multiplierX = (newCentralChunkPos.x / (lengthOfSquare * 2));
	float multiplierY = (newCentralChunkPos.y / (lengthOfSquare * 2));

	float offsetMultiplier = (noiseImageSize/ 1000.0f);

	Vector3 playerLocation = Vector3(((lengthOfSquare * 2) - 2) * multiplierX, 0, ((lengthOfSquare * 2) - 2) * multiplierY);
	Vector3 newLocation = Vector3(offsetMultiplier * multiplierX, offsetMultiplier * -(multiplierY), 0);

	createChunk(playerLocation, newLocation);

	newLocation = Vector3(offsetMultiplier * (multiplierX + 1.0f), offsetMultiplier * -(multiplierY), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - 2) * (multiplierX + 1), 0, ((lengthOfSquare * 2) - 2) * multiplierY);

	createChunk(playerLocation, newLocation);

	newLocation = Vector3(offsetMultiplier * (multiplierX - 1.0f), offsetMultiplier * -(multiplierY), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - 2) * (multiplierX - 1), 0, ((lengthOfSquare * 2) - 2) * multiplierY);

	createChunk(playerLocation, newLocation);

	newLocation = Vector3(offsetMultiplier * multiplierX, offsetMultiplier * -(multiplierY + 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - 2) * multiplierX, 0, ((lengthOfSquare * 2) - 2) * (multiplierY + 1));

	createChunk(playerLocation, newLocation);

	newLocation = Vector3(offsetMultiplier * multiplierX, offsetMultiplier * -(multiplierY - 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - 2) * multiplierX, 0, ((lengthOfSquare * 2) - 2) * (multiplierY - 1));

	createChunk(playerLocation, newLocation);

	newLocation = Vector3(offsetMultiplier * (multiplierX + 1.0f), offsetMultiplier * -(multiplierY + 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - 2) * (multiplierX + 1), 0, ((lengthOfSquare * 2) - 2) * (multiplierY + 1));

	createChunk(playerLocation, newLocation);

	newLocation = Vector3(offsetMultiplier * (multiplierX - 1.0f), offsetMultiplier * -(multiplierY - 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - 2) * (multiplierX - 1), 0, ((lengthOfSquare * 2) - 2) * (multiplierY - 1));

	createChunk(playerLocation, newLocation);

	newLocation = Vector3(offsetMultiplier * (multiplierX + 1.0f), offsetMultiplier * -(multiplierY - 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - 2) * (multiplierX + 1), 0, ((lengthOfSquare * 2) - 2) * (multiplierY - 1));

	createChunk(playerLocation, newLocation);

	newLocation = Vector3(offsetMultiplier * (multiplierX - 1.0f), offsetMultiplier * -(multiplierY + 1.0f), 0);
	playerLocation = Vector3(((lengthOfSquare * 2) - 2) * (multiplierX - 1), 0, ((lengthOfSquare * 2) - 2) * (multiplierY + 1));

	createChunk(playerLocation, newLocation);

}


// This function finds and destroys all currently spawned chunks
void ChunkManager::clearOutChunks()
{
	Node *currentChild;

	for (int i = 0; i < get_child_count(); i++)
	{
		if (get_child(i)->get_class() == "Chunk") {
			currentChild = get_child(i);
			remove_child(currentChild);
		}
	}
}


// This function changes all of the chunk noise settings
void ChunkManager::changeSettings(int imageOctaves, float imagePersistance, float imageLacunarity)
{
	noiseImageOctaves = imageOctaves;
	noiseImagePersistance = imagePersistance;
	noiseImageLacunarity = imageLacunarity;
}
