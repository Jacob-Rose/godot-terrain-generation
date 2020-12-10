/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)
#include <sstream>

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
	redraw = false;
	set_process(true);
	chunkPos = Vector3(0, 0, 0);
}

Chunk::Chunk(Vector3 position) {
	set_process(true);
	redraw = false;
	chunkPos = position;
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
//

void Chunk::generateTerrainMesh(Ref<Image> heightMap) {

	int width = heightMap->get_width();
	int height = heightMap->get_height();

	Ref<ArrayMesh> a = memnew(ArrayMesh);

	Vector<Vector3> newQuad;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			std::stringstream convert;
			convert << heightMap->get_pixel(x, y).g;
			printf(convert.str().c_str());

			if (y != 0 && x != width - 1)
			{
				newQuad.resize(0);
				
				newQuad.push_back(Vector3(x * 2, 1, -y * 2));
				newQuad.push_back(Vector3((x + 1) * 2, heightMap->get_pixel(x+1, y).r * 5, -y * 2));
				newQuad.push_back(Vector3(x * 2, heightMap->get_pixel(x, y-1).r * 5, -(y - 1) * 2));
				newQuad.push_back(Vector3((x + 1) * 2, heightMap->get_pixel(x+1, y-1).r * 5, -(y - 1) * 2));
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad));
				convert.clear();
				convert << "surface"+iD;
				a->surface_set_name(iD, convert.str().c_str());			
				iD++;
			}
		}

	//	//Draw Face here
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


	colors.push_back(Color(0.86, 0.08, 0.24, 1));
	colors.push_back(Color(0.86, 0.08, 0.24, 1));
	colors.push_back(Color(0.86, 0.08, 0.24, 1));
	colors.push_back(Color(0.86, 0.08, 0.24, 1));
	colors.push_back(Color(0.86, 0.08, 0.24, 1));
	colors.push_back(Color(0.86, 0.08, 0.24, 1));

	mesh_array.resize(ArrayMesh::ARRAY_MAX);
	
	mesh_array[ArrayMesh::ARRAY_VERTEX] = vertices;
	mesh_array[ArrayMesh::ARRAY_COLOR] = colors;

	return mesh_array;
}
