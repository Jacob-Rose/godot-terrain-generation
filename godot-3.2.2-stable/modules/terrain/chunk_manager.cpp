/* chunk_manager.cpp */

#include "chunk_manager.h"
#include "core/io/resource_loader.h"

void ChunkManager::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_central_chunk_location"), &ChunkManager::getCentralChunkLocation);
	ClassDB::bind_method(D_METHOD("check_for_chunk_update", "player_2d_position"), &ChunkManager::checkIfChunksNeedToBeReloaded);
	ClassDB::bind_method(D_METHOD("creaet_chunk", "player_2d_position","size_chunk"), &ChunkManager::checkIfChunksNeedToBeReloaded);
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
	newSource = ResourceLoader::load("res://Floor.tcsn");
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
	
}

void ChunkManager::createChunk(Vector3 playerPos,int desiredChunks) {

	for (int i = 0; i < desiredChunks; i++) {
		Chunk *chunk = new Chunk(0, 1, 0);
		NoiseGenerator *noiseMap = new NoiseGenerator();
		//chunk->set_mesh(mySimpleMesh);
		for (int j = 0; j < 1; j++) {
			//createCube(chunk, 0, 1, 0);
			chunk->generateTerrainMesh(noiseMap->getImage(10, Vector2(0, 0), 1));
			add_child(chunk);
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

Ref<ArrayMesh> ChunkManager::generateTerrainMesh(Image heightMap) {

	int width = heightMap.get_width();
	int height = heightMap.get_height();

	float topLeftX = (width - 1) / -2.0f;
	float topLeftY = (height - 1) / 2.0f;
	int vertiD = 0;

	MeshData *meshData = new MeshData(width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			meshData->vertices[vertiD].append(Vector3(topLeftX+x, heightMap.get_pixel(x,y).r,topLeftY-y));
			meshData->uvs[vertiD].append(Vector2(x / (float)width, y / (float)height));
			if (x < width -1 && y < height -1) {
				meshData->addTriangle(vertiD, vertiD + width + 1, vertiD + width);
				meshData->addTriangle(vertiD+width+1, vertiD, vertiD + 1);
			}
			vertiD++;
		}
	}
	Ref<ArrayMesh> a = memnew(ArrayMesh);
	a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES,meshData->mesh_array);
	return a;
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

void ChunkManager::MeshData::addTriangle(int a, int b, int c) {
	triangles[triangleiD].append(a);
	triangles[triangleiD+1].append(b);
	triangles[triangleiD+2].append(c);
	triangleiD += 3;
}


Ref<ArrayMesh> ChunkManager::MeshData::createMesh() {

	Ref<ArrayMesh> a = memnew(ArrayMesh);

	mesh_array[ArrayMesh::ARRAY_VERTEX] = vertices;
	mesh_array[ArrayMesh::PRIMITIVE_TRIANGLES] = triangles;
	mesh_array[ArrayMesh::ARRAY_TEX_UV] = uvs;
	mesh_array[ArrayMesh::ARRAY_COLOR] = Color(1, 1, 1);
	a->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, mesh_array);

	return a;
}
