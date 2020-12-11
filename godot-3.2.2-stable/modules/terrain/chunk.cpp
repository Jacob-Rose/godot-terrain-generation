/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)
#include <sstream>
#include "noise.h"

void Chunk::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("generateTerrainMesh", "heightMap"), &Chunk::generateTerrainMesh);
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
	/*
	std::stringstream convert;
	convert << heightMap[(y*heightMapSize)+x];
	
	printf(convert.str().c_str());
	*/
}

void Chunk::_ready()
{
	set_process(true);
	set_process_input(true);
}

void Chunk::_draw()
{

}

void Chunk::generateTerrainMesh(PoolRealArray heightMap, int heightMapSize) {
	Ref<Image> img = memnew(Image);
	img->create(heightMapSize, heightMapSize, false, Image::Format::FORMAT_RGB8);
	generateTerrainMesh(heightMap, img);
}

void Chunk::generateTerrainMesh(PoolRealArray heightMap, Ref<Image> colorMap) {
	Ref<ArrayMesh> a = memnew(ArrayMesh);
	Vector<Vector3> newQuad;
	mColorMap = colorMap;
	mColorMap->lock();
	for (int y = 0; y < colorMap->get_height(); y++) {
		for (int x = 0; x < colorMap->get_width(); x++) {
			if (y != 0 && x != colorMap->get_width() - 1) {
				newQuad.resize(0);
				float heightVal = heightMap[(x) + (y * colorMap->get_height())];
				newQuad.push_back(Vector3(x * 2, heightVal * 5, y * 2));
				newQuad.push_back(Vector3((x + 1) * 2, heightVal * 5, y * 2));
				newQuad.push_back(Vector3(x * 2, heightVal * 5, (y + 1) * 2));
				newQuad.push_back(Vector3((x + 1) * 2, heightVal * 5, (y + 1) * 2));
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad, 0));
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad, 1));
				a->surface_set_name(iD, String(std::to_string(iD).c_str()) + "Tri1");
				iD++;
				a->surface_set_name(iD, String(std::to_string(iD).c_str()) + "Tri2");
				iD++;
			}
		}
	}
	mColorMap->unlock();
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
			colors.push_back(mColorMap->get_pixel(verteces[0].x, verteces[0].y));
			vertices.push_back(verteces[3]);
			colors.push_back(mColorMap->get_pixel(verteces[3].x, verteces[3].y));
			vertices.push_back(verteces[2]);
			colors.push_back(mColorMap->get_pixel(verteces[2].x, verteces[2].y));

			uvs.push_back(Vector2(verteces[0].x / 3.0, verteces[0].z / 3.0));
			uvs.push_back(Vector2(verteces[3].x / 3.0, verteces[3].z / 3.0));
			uvs.push_back(Vector2(verteces[2].x / 3.0, verteces[2].z / 3.0));

			normals.push_back(verteces[1]);
			normals.push_back(verteces[2]);
			normals.push_back(verteces[3]);
			break;

		case 1:
			vertices.push_back(verteces[0]);
			colors.push_back(mColorMap->get_pixel(verteces[0].x, verteces[0].y));
			vertices.push_back(verteces[1]);
			colors.push_back(mColorMap->get_pixel(verteces[1].x, verteces[1].y));
			vertices.push_back(verteces[3]);
			colors.push_back(mColorMap->get_pixel(verteces[3].x, verteces[3].y));

			uvs.push_back(Vector2(verteces[0].x / 3.0, verteces[0].z / 3.0));
			uvs.push_back(Vector2(verteces[1].x / 3.0, verteces[1].z / 3.0));
			uvs.push_back(Vector2(verteces[3].x / 3.0, verteces[3].z / 3.0));

			normals.push_back(verteces[1]);
			normals.push_back(verteces[0]);
			normals.push_back(verteces[2]);
			break;

	}
	

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
