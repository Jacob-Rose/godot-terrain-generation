/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)
#include <sstream>
#include <string>
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

void Chunk::generateTerrainMesh(PoolRealArray heightMap, int heightMapSize, Vector3 generatedPosition) {
	Ref<Image> img = memnew(Image);
	img->create(heightMapSize, heightMapSize, false, Image::Format::FORMAT_RGB8);
	generateTerrainMesh(heightMap, img, generatedPosition);
}

void Chunk::generateTerrainMesh(PoolRealArray heightMap, Ref<Image> colorMap, Vector3 generatedPosition) {
	Ref<ArrayMesh> a = memnew(ArrayMesh);
	Vector<Vector3> newQuad;
	Vector3 offset = Vector3(-colorMap->get_height() + generatedPosition.x, 0, -colorMap->get_height() + generatedPosition.z); 
	mColorMap = colorMap;
	mColorMap->lock();
	for (int y = 1; y < colorMap->get_height(); y++) {
		for (int x = 0; x < colorMap->get_width(); x++) {
			if (x != colorMap->get_width() - 1) {
				newQuad.clear();
				newQuad.resize(0);

				//Create the four new vertices 
				float heightVal = heightMap[(x) + ((10 - y) * colorMap->get_height())];
				newQuad.push_back(Vector3(x * 2, heightVal * 5, y * 2) + offset);
				heightVal = heightMap[(x + 1) + ((10 - y) * colorMap->get_height())];
				newQuad.push_back(Vector3((x + 1) * 2, heightVal * 5, y * 2) + offset);
				heightVal = heightMap[(x) + (((10 - y) - 1) * colorMap->get_height())];
				newQuad.push_back(Vector3(x * 2, heightVal * 5, (y + 1) * 2) + offset);
				heightVal = heightMap[(x + 1) + (((10 - y) - 1) * colorMap->get_height())];
				newQuad.push_back(Vector3((x + 1) * 2, heightVal * 5, (y + 1) * 2) + offset);

				//Create each face
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad, 0));
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad, 1));

				//set the name of the surfaces
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

	Vector2 vert0 = checkOutOfBounds(0, verteces);
	Vector2 vert1 = checkOutOfBounds(1, verteces);
	Vector2 vert2 = checkOutOfBounds(2, verteces);
	Vector2 vert3 = checkOutOfBounds(3, verteces);

	switch (i) {

		case 0:
			//Push vertices in a clockwise motion, top left, top right, bottom right
			//create essentially the first triangle
			vertices.push_back(verteces[0]);
			colors.push_back(mColorMap->get_pixel(vert0.x, vert0.y));
			vertices.push_back(verteces[1]);
			colors.push_back(mColorMap->get_pixel(vert1.x, vert1.y));
			vertices.push_back(verteces[3]);
			colors.push_back(mColorMap->get_pixel(vert3.x, vert3.y));

			//set the uvs
			uvs.push_back(Vector2(verteces[0].x / 3.0, verteces[0].z / 3.0));
			uvs.push_back(Vector2(verteces[1].x / 3.0, verteces[1].z / 3.0));
			uvs.push_back(Vector2(verteces[3].x / 3.0, verteces[3].z / 3.0));

			//normals
			normals.push_back(verteces[1]);
			normals.push_back(verteces[0]);
			normals.push_back(verteces[2]);
			break;

		case 1:
			//Push vertices in a clockwise motion, bottom right, bottom left, top left
			//create essentially the second triangle
			vertices.push_back(verteces[3]);
			colors.push_back(mColorMap->get_pixel(vert3.x, vert3.y));
			vertices.push_back(verteces[2]);
			colors.push_back(mColorMap->get_pixel(vert2.x, vert2.y));
			vertices.push_back(verteces[0]);
			colors.push_back(mColorMap->get_pixel(vert0.x, vert0.y));

			uvs.push_back(Vector2(verteces[3].x / 3.0, verteces[3].z / 3.0));
			uvs.push_back(Vector2(verteces[2].x / 3.0, verteces[2].z / 3.0));
			uvs.push_back(Vector2(verteces[0].x / 3.0, verteces[0].z / 3.0));

			normals.push_back(verteces[2]);
			normals.push_back(verteces[3]);
			normals.push_back(verteces[1]);
			break;

	}
	
	//set the indeces of the mesharray
	for (int i = 0; i < vertices.size();i++) {
		indeces.push_back(i);
	}

	//resize then set the mesh array with each appropriate data into the array.
	mesh_array.resize(ArrayMesh::ARRAY_MAX);

	mesh_array[ArrayMesh::ARRAY_VERTEX] = vertices;
	mesh_array[ArrayMesh::ARRAY_TEX_UV] = uvs;
	mesh_array[ArrayMesh::ARRAY_NORMAL] = normals;
	mesh_array[ArrayMesh::ARRAY_COLOR] = colors;

	mesh_array[ArrayMesh::ARRAY_INDEX] = indeces;


	return mesh_array;
}

Vector2 Chunk::checkOutOfBounds(int i, Vector<Vector3> verteces) {
	Vector2 vector;
	vector.x = Math::abs(verteces[i].x);
	vector.y = Math::abs(verteces[i].y);

	//These should help with making sure the values wont be out of bounds when we sample
	if (vector.x >= mColorMap->get_size().x) {
		vector.x -= 1;
	} else if (vector.x <= 0) {
		vector.x += 1;
	}
	if (vector.y >= mColorMap->get_size().y) {
		vector.y -= 1;
	} else if (vector.y <= 0) {
		vector.y += 1;
	}
	
	return vector;
}
