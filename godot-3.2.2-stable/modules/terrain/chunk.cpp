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
}

void Chunk::generateTerrainMesh(Ref<Image> heightMap) {

	int width = heightMap->get_width();
	int height = heightMap->get_height();

	Ref<ArrayMesh> a = memnew(ArrayMesh);

	Vector<Vector3> newQuad;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y != 0 && x != width - 1)
			{
				newQuad.resize(0);
				newQuad.push_back(Vector3(x * 2, y * 2, heightMap->get_pixel(x, y).r) * 10);
				newQuad.push_back(Vector3((x + 1) * 2, y * 2, heightMap->get_pixel((x + 1), y).r) * 10);
				newQuad.push_back(Vector3(x * 2, (y - 1) * 2, heightMap->get_pixel(x, y - 1).r) * 10);
				newQuad.push_back(Vector3((x + 1) * 2, (y - 1) * 2, heightMap->get_pixel(x + 1, y - 1).r) * 10);
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad));
			}
		}

		//Draw Face here
	}

	if (this != NULL)
		this->set_mesh(a);
}

Array Chunk::DrawFace(Vector<Vector3> verteces)
{
	Array mesh_array;

	vertices.resize(0);
	colors.resize(0);

	vertices.push_back(verteces[0]);
	vertices.push_back(verteces[3]);
	vertices.push_back(verteces[2]);
	vertices.push_back(verteces[0]);
	vertices.push_back(verteces[1]);
	vertices.push_back(verteces[3]);


	colors.push_back(Color(1, 1, 1));
	colors.push_back(Color(1, 1, 1));
	colors.push_back(Color(1, 1, 1));
	colors.push_back(Color(1, 1, 1));
	colors.push_back(Color(1, 1, 1));
	colors.push_back(Color(1, 1, 1));

	mesh_array.resize(ArrayMesh::ARRAY_MAX);
	mesh_array[ArrayMesh::ARRAY_VERTEX] = vertices;
	mesh_array[ArrayMesh::ARRAY_COLOR] = colors;

	return mesh_array;
}
