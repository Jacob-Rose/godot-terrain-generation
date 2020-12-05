/* chunk_manager.cpp */

#include "chunk_manager.h"

void ChunkManager::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_central_chunk_location"), &ChunkManager::getCentralChunkLocation);
	ClassDB::bind_method(D_METHOD("check_for_chunk_update", "player_2d_position"), &ChunkManager::checkIfChunksNeedToBeReloaded);
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
	locationOfCentralChunk = Vector2(0, 0);
	set_process(true);
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
	createChunk(numberOfChunks);
}

void ChunkManager::createChunk(int desiredChunks) {

	for (int i = 0; i < desiredChunks; i++) {
		Chunk *chunk = new Chunk(0, 1, 0);
		//chunk->set_mesh(mySimpleMesh);
		for (int j = 0; j < 1; j++) {
			createCube(chunk, 0, 1, 0);
			printf("Cube spawned");
		}

		printf("Chunk spawned");
	}
}

void ChunkManager::createCube(MeshInstance *meshI, int x, int y, int z) {

	//left face
	makeFace(Vector3(x, y, z), Vector3(x, y + 1, z), Vector3(x, y + 1, z + 1), Vector3(x, y, z + 1));
	//Right face
	makeFace(Vector3(x + 1, y, z + 1), Vector3(x + 1, y + 1, z + 1), Vector3(x + 1, y + 1, z), Vector3(x + 1, y, z));
	//down face
	makeFace(Vector3(x + 1, y, z), Vector3(x, y, z), Vector3(x, y, z + 1), Vector3(x + 1, y, z + 1));
	//upface
	makeFace(Vector3(x + 1, y + 1, z + 1), Vector3(x, y + 1, z + 1), Vector3(x, y + 1, z), Vector3(x + 1, y + 1, z));
	//backface
	makeFace(Vector3(x + 1, y, z), Vector3(x + 1, y + 1, z), Vector3(x, y + 1, z), Vector3(x, y, z));
	//frontface
	makeFace(Vector3(x, y, z + 1), Vector3(x, y + 1, z + 1), Vector3(x + 1, y + 1, z + 1), Vector3(x + 1, y, z + 1));

	Ref<ArrayMesh> a = memnew(ArrayMesh);

	mesh_array.resize(Mesh::ARRAY_MAX);

	mesh_array[Mesh::ARRAY_VERTEX] = vertices;
	mesh_array[Mesh::ARRAY_INDEX] = indices;
	mesh_array[Mesh::ARRAY_NORMAL] = normals;
	mesh_array[ArrayMesh::ARRAY_COLOR] = Color(1, 1, 1);

	arrayMesh.add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, mesh_array);
	a = arrayMesh.reference();

	meshI->set_mesh(a);
	call_deferred("add_child", meshI);
}

void ChunkManager::makeFace(Vector3 a, Vector3 b, Vector3 c, Vector3 d) {

	int length = vertices.size();
	//add the index's
	indices.append(length);
	indices.append(length + 1);
	indices.append(length + 2);
	indices.append(length);
	indices.append(length + 2);
	indices.append(length + 3);

	//then all the vertices of the face
	vertices.append(a);
	vertices.append(b);
	vertices.append(c);
	vertices.append(d);

	// then normals
	normals.append(a.normalized());
	normals.append(b.normalized());
	normals.append(c.normalized());
	normals.append(d.normalized());
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
