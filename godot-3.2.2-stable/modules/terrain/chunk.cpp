/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)
#include <sstream>

void Chunk::_bind_methods() {
	ClassDB::bind_method(D_METHOD("generateTerrainMesh", "heightMap"), &Chunk::generateTerrainMesh);
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
	construct(Vector3(0, 0, 0));
}

Chunk::Chunk(Vector3 position) {
	construct(position);
}

void Chunk::construct(Vector3 pos) {
	set_process(true);
	chunkPos = pos;
	iD = 0; //TODO remove or set properly
}

void Chunk::_update()
{

}

void Chunk::_ready()
{
	set_process(true);
	set_process_input(true);
}

void Chunk::_draw()
{

}

void Chunk::generateTerrainMesh(Ref<Image> heightMap) {

	int width = heightMap->get_width();
	int height = heightMap->get_height();

	Ref<ArrayMesh> a = memnew(ArrayMesh);

	Vector<Vector3> newQuad;

	heightMap->lock();

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

				newQuad.push_back(Vector3(x * 2, heightMap->get_pixel(x + 1, y).r * 5, y * 2));
				newQuad.push_back(Vector3((x + 1) * 2, heightMap->get_pixel(x + 1, y).r * 5, y * 2));
				newQuad.push_back(Vector3(x * 2, heightMap->get_pixel(x + 1, y).r * 5, (y + 1) * 2));
				newQuad.push_back(Vector3((x + 1) * 2, heightMap->get_pixel(x + 1, y).r * 5, (y + 1) * 2));
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad,0));
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad, 1));	
				a->surface_set_name(iD, convert.str().c_str());			
				iD++;
			}
		}
	}
	heightMap->unlock();

	set_material_override(a->surface_get_material(0));
	a->regen_normalmaps();
	//	//Draw Face here
	if (this != NULL)
		this->set_mesh(a);
}

Array Chunk::DrawFace(Vector<Vector3> verteces, int i)
{
	Array mesh_array;

	vertices.resize(0);
	colors.resize(0);
	uvs.resize(0);
	normals.resize(0);

	switch (i) {

		case 0:
			vertices.push_back(verteces[0]);
			vertices.push_back(verteces[3]);
			vertices.push_back(verteces[2]);

			uvs.push_back(Vector2(verteces[0].x / 3.0, verteces[0].z / 3.0));
			uvs.push_back(Vector2(verteces[3].x / 3.0, verteces[3].z / 3.0));
			uvs.push_back(Vector2(verteces[2].x / 3.0, verteces[2].z / 3.0));

			normals.push_back(verteces[1]);
			normals.push_back(verteces[2]);
			normals.push_back(verteces[3]);
			break;

			case 1:
			vertices.push_back(verteces[0]);
			vertices.push_back(verteces[1]);
			vertices.push_back(verteces[3]);

			uvs.push_back(Vector2(verteces[0].x / 3.0, verteces[0].z / 3.0));
			uvs.push_back(Vector2(verteces[1].x / 3.0, verteces[1].z / 3.0));
			uvs.push_back(Vector2(verteces[3].x / 3.0, verteces[3].z / 3.0));

			normals.push_back(verteces[1]);
			normals.push_back(verteces[0]);
			normals.push_back(verteces[2]);
			break;

	}


	colors.append(Color(1, 0, 0));
	colors.append(Color(0, 1, 0));
	colors.append(Color(1, 0, 0));

	for (int i = 0; i < vertices.size();i++) {
		indeces.push_back(i);
	}


	mesh_array.resize(ArrayMesh::ARRAY_MAX);
	
	mesh_array[ArrayMesh::ARRAY_VERTEX] = vertices;
	mesh_array[ArrayMesh::ARRAY_TEX_UV] = uvs;
	mesh_array[ArrayMesh::ARRAY_NORMAL] = normals;
	mesh_array[ArrayMesh::ARRAY_COLOR] = colors;

	mesh_array[ArrayMesh::ARRAY_INDEX] = indeces;


	return mesh_array;
}
