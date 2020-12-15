/* chunk_manager.cpp */

#include "chunk_manager.h"
#include "core/io/resource_loader.h"

void ChunkManager::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_central_chunk_location"), &ChunkManager::getCentralChunkLocation);
	ClassDB::bind_method(D_METHOD("check_for_chunk_update", "player_2d_position"), &ChunkManager::checkIfChunksNeedToBeReloaded);
	//ClassDB::bind_method(D_METHOD("create_chunk", "player_2d_position","size_chunk"), &ChunkManager::checkIfChunksNeedToBeReloaded);
	ClassDB::bind_method(D_METHOD("create_chunk", "Playerpos", "aqui"), &ChunkManager::createChunk);
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

ChunkManager::ChunkManager()
{
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

void ChunkManager::_ready() {
	
}

void ChunkManager::createChunk(Vector3 playerPos,Vector3 chunkOffset) {


		Chunk* chunk = memnew(Chunk, playerPos); //TODO memory leak?

		NoiseGenerator* noiseGen = new NoiseGenerator();
		PoolRealArray heightmap = noiseGen->getHeightmap(noiseImageSize, Vector2(chunkOffset.x * noiseImageScale, chunkOffset.y * noiseImageScale), noiseImageScale, noiseImageOctaves, noiseImagePersistance, noiseImageLacunarity);

		Ref<Image> colorMap = noiseGen->getColorFromHeightmap(heightmap, noiseImageSize, colorGradient);

		chunk->generateTerrainMesh(heightmap, noiseImageSize, playerPos);
		add_child(chunk);

		printf("Chunk spawned");
		delete noiseGen;
}


// This function checks if any new chunks need to be loaded by checking if the player has stepped outside of the central chunk
bool ChunkManager::checkIfChunksNeedToBeReloaded(Vector2 playerPos) {
	bool needsReloading = false;

	// Create directional vector and the distance between the current chunk and player
	Vector2 directionalVector = playerPos - locationOfCentralChunk;
	float distance = sqrtf(powf(directionalVector.x, 2.0f) + powf(directionalVector.y, 2.0f));

	// Check if player is outside of central chunk square and adjust central chunk if needed
	if (directionalVector.x <= -LENGTH_OF_SQUARE)
	{
		locationOfCentralChunk.x -= LENGTH_OF_SQUARE * 2.0f;
		needsReloading = true;
	}

	if (directionalVector.x >= LENGTH_OF_SQUARE)
	{
		locationOfCentralChunk.x += LENGTH_OF_SQUARE * 2.0f;
		needsReloading = true;
	}

	if (directionalVector.y <= -LENGTH_OF_SQUARE)
	{
		locationOfCentralChunk.y -= LENGTH_OF_SQUARE * 2.0f;
		needsReloading = true;
	}

	if (directionalVector.y >= LENGTH_OF_SQUARE)
	{
		locationOfCentralChunk.y += LENGTH_OF_SQUARE * 2.0f;
		needsReloading = true;
	}

	return needsReloading;
}

// This function gets the central chunk location
Vector2 ChunkManager::getCentralChunkLocation()
{
	return locationOfCentralChunk;
}
