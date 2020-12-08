/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)


void Chunk::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("generate_Terrain_Mesh", "heightMap"), &Chunk::generateTerrainMesh);
}

void Chunk::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_PROCESS: {

			_update();
		} break;

		case NOTIFICATION_READY: {
			_ready();
		} break;

	}
}

Chunk::Chunk()
{
	xPos = 0.0f;
	zPos = 0.0f;
	redraw = false;
	chunkSize = 0.0f;
	set_process(true);
}

Chunk::Chunk(float x, float z, int desiredSize) {
	set_process(true);
	xPos = x;
	zPos = z;
	redraw = false;
	chunkSize = desiredSize;
}

void Chunk::_update()
{
	if (redraw) {
		Ref<ArrayMesh> a = memnew(ArrayMesh);
		Array arrays;
		arrays.resize(ArrayMesh::ARRAY_MAX);
		arrays[ArrayMesh::ARRAY_VERTEX] = _vertices; // required
		arrays[ArrayMesh::ARRAY_COLOR] = _colors;

		//optionally u can add texture coordinates and attach a texture from the editor to this arraymesh in the scene

		a->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

		if (this != NULL)
			this->set_mesh(a);
		redraw = false;
	}
}

void Chunk::_ready()
{
	set_process(true);
	set_process_input(true);
}

void Chunk::_draw()
{
	if (redraw)
	{
		Ref<ArrayMesh> a = memnew(ArrayMesh);
		Array arrays;
		arrays.resize(ArrayMesh::ARRAY_MAX);
		arrays[ArrayMesh::ARRAY_VERTEX] = _vertices; // required
		arrays[ArrayMesh::ARRAY_COLOR] = _colors;

		//optionally u can add texture coordinates and attach a texture from the editor to this arraymesh in the scene

		a->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

		if (this != NULL)
			this->set_mesh(a);
		redraw = false;
	}
}

//void Chunk::_process(float delta)
//{
//	//_process can run in editor too, we need to specify not to run in editor here
//	if(!Engine::get_singleton()->is_editor_hint()) {
//
//
//	}
//}
void Chunk::MeshData::addTriangle(int a, int b, int c) {
	triangles[triangleiD].append(a);
	triangles[triangleiD + 1].append(b);
	triangles[triangleiD + 2].append(c);
	triangleiD += 3;
}


void Chunk::MeshData::createMesh() {
	mesh_array.resize(ArrayMesh::ARRAY_MAX);
	mesh_array[ArrayMesh::ARRAY_VERTEX] = vertices;
	mesh_array[ArrayMesh::PRIMITIVE_TRIANGLES] = triangles;
	mesh_array[ArrayMesh::ARRAY_TEX_UV] = uvs;
	mesh_array[ArrayMesh::ARRAY_COLOR] = Color(1, 1, 1);
	rArrayMesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, mesh_array);
}

void Chunk::generateTerrainMesh(Ref<Image> heightMap) {

	int width = heightMap->get_width();
	int height = heightMap->get_height();

	float topLeftX = (width - 1) / -2.0f;
	float topLeftY = (height - 1) / 2.0f;
	int vertiD = 0;

	MeshData *meshData = new MeshData(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			meshData->vertices[vertiD].append(Vector3(topLeftX + x, heightMap->get_pixel(x, y).r, topLeftY - y));
			meshData->uvs[vertiD].append(Vector2(x / static_cast<float>(width), y / static_cast<float>(height)));

			if (x < width - 1 && y < height - 1) {
				meshData->addTriangle(vertiD, vertiD + width + 1, vertiD + width);
				meshData->addTriangle(vertiD + width + 1, vertiD, vertiD + 1);
			}
			vertiD++;
		}
	}
	Ref<ArrayMesh> a = memnew(ArrayMesh);

	meshData->createMesh();
	a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, meshData->mesh_array);

	if (this != NULL)
		this->set_mesh(a);
}
