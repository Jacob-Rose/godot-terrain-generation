/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h"
#include <string>
#include "noise.h"

// This function adds any needed functions or parameters to the editor
void Chunk::_bind_methods() { }


// This function gets any event calls from the engine
void Chunk::_notification(int p_what) {
	switch (p_what) {

		case NOTIFICATION_READY: {
			_ready();
		} break;

	}
}


// This function is the default constructor of the class
Chunk::Chunk()
{
	iD = 0;
	levelOneMax = 0;
	levelTwoMax = 0;
	levelThreeMax = 0;
}


// This function gets called when the node is spawned
void Chunk::_ready()
{

	// Override material so vertex colors display
	Ref<SpatialMaterial> newMaterial = memnew(SpatialMaterial);
	newMaterial->set_flag(SpatialMaterial::FLAG_ALBEDO_FROM_VERTEX_COLOR, true);
	set_material_override(newMaterial);


	set_process(true);
	set_process_input(true);
}


// This function creates all necessary variables to generate a terrain mesh and then generates it
void Chunk::initializeTerrainMesh(Ref<Image> heightMap, int heightMapSize, Vector3 generatedPosition, int lengthOfSquare) {

	// Make color map
	Ref<Image> img = memnew(Image);
	img->create(heightMapSize, heightMapSize, false, Image::Format::FORMAT_RGB8);

	// Generate with new color map
	generateTerrainMesh(heightMap, img, generatedPosition, lengthOfSquare);
}


// This function generates the terrain mesh with the given height and color map
void Chunk::generateTerrainMesh(Ref<Image> _heightMap, Ref<Image> _colorMap, Vector3 generatedPosition, int lengthOfSquare) {

	// Initialize vertex array, vertex colors and arraymesh
	Ref<ArrayMesh> a = memnew(ArrayMesh);
	Vector<Vector3> newQuad;
	Vector<Color> newColors;

	// Set and lock color and height map
	colorMap = _colorMap;
	heightMap = _heightMap;
	colorMap->lock();
	heightMap->lock();

	// Set offset
	Vector3 offset = Vector3(-colorMap->get_height() + generatedPosition.x, 0, -colorMap->get_height() + generatedPosition.z); 

	for (int y = 1; y < colorMap->get_height(); y++) {
		for (int x = 0; x < colorMap->get_width(); x++) {
			if (x != colorMap->get_width() - 1) {

				// clear out vertex and color vectors
				newQuad.clear();
				newQuad.resize(0);
				newColors.clear();
				newColors.resize(0);

				//Create the four new vertices 
				float heightVal = heightMap->get_pixel(x, lengthOfSquare - y).r;
				newColors.push_back(determineColor(heightVal));
				newQuad.push_back(Vector3(x * SIZE_OF_FACE_HORIZONTAL, heightVal * NOISE_MULTIPLIER, y * SIZE_OF_FACE_HORIZONTAL) + offset);

				heightVal = heightMap->get_pixel(x + 1, lengthOfSquare - y).r;
				newColors.push_back(determineColor(heightVal));
				newQuad.push_back(Vector3((x + 1) * SIZE_OF_FACE_HORIZONTAL, heightVal * NOISE_MULTIPLIER, y * SIZE_OF_FACE_HORIZONTAL) + offset);

				heightVal = heightMap->get_pixel(x, (lengthOfSquare - y) - 1).r;
				newColors.push_back(determineColor(heightVal));
				newQuad.push_back(Vector3(x * SIZE_OF_FACE_HORIZONTAL, heightVal * NOISE_MULTIPLIER, (y + 1) * SIZE_OF_FACE_HORIZONTAL) + offset);

				heightVal = heightMap->get_pixel((x + 1), (lengthOfSquare - y) - 1).r;
				newColors.push_back(determineColor(heightVal));
				newQuad.push_back(Vector3((x + 1) * SIZE_OF_FACE_HORIZONTAL, heightVal * NOISE_MULTIPLIER, (y + 1) * SIZE_OF_FACE_HORIZONTAL) + offset);

				//Create each face
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad, newColors, 0));
				a->add_surface_from_arrays(ArrayMesh::PRIMITIVE_TRIANGLES, DrawFace(newQuad, newColors, 1));

				//set the name of the surfaces
				a->surface_set_name(iD, String(std::to_string(iD).c_str()) + "Tri1");
				iD++;
				a->surface_set_name(iD, String(std::to_string(iD).c_str()) + "Tri2");
				iD++;
			}
		}
	}
	// Unlock color and height maps
	colorMap->unlock();
	heightMap->unlock();

	// Finally set mesh to array mesh
	if (this != NULL)
		this->set_mesh(a);
}


// This function draws a face with the given verteces and colors
Array Chunk::DrawFace(Vector<Vector3> verteces, Vector<Color> newColors, int i)
{
	Array mesh_array;

	//resize which should make sure its empty before pushing back
	vertices.resize(0);
	colors.resize(0);
	normals.resize(0);
	indeces.resize(0);

	switch (i) {

		case 0:
			//Push vertices in a clockwise motion, top left, top right, bottom right
			//create essentially the first triangle
			vertices.push_back(verteces[0]);
			colors.push_back(newColors[0]);
			vertices.push_back(verteces[1]);
			colors.push_back(newColors[1]);
			vertices.push_back(verteces[3]);
			colors.push_back(newColors[3]);

			//normals
			normals.push_back(verteces[1]);
			normals.push_back(verteces[0]);
			normals.push_back(verteces[2]);
			break;

		case 1:
			//Push vertices in a clockwise motion, bottom right, bottom left, top left
			//create essentially the second triangle
			vertices.push_back(verteces[3]);
			colors.push_back(newColors[3]);
			vertices.push_back(verteces[2]);
			colors.push_back(newColors[2]);
			vertices.push_back(verteces[0]);
			colors.push_back(newColors[0]);

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
	mesh_array[ArrayMesh::ARRAY_NORMAL] = normals;
	mesh_array[ArrayMesh::ARRAY_COLOR] = colors;
	mesh_array[ArrayMesh::ARRAY_INDEX] = indeces;

	return mesh_array;
}


// This function assigns color to a vertex based on a given height val
Color Chunk::determineColor(float heightVal)
{
	// Lowest level
	if (heightVal < levelOneMax)
	{
		return levelOneColor;
	}

	// Second Lowest level
	if (heightVal < levelTwoMax)
	{
		return levelTwoColor;
	}

	// Second Highest level
	if (heightVal < levelThreeMax)
	{
		return levelThreeColor;
	}

	// Highest level
	return levelFourColor;
}


// This function sets all of the given level settings based on what is passed on the settings passed into it
void Chunk::addLevelSettings(float _levelOneMax, float _levelTwoMax, float _levelThreeMax, Color _levelOneColor, Color _levelTwoColor, Color _levelThreeColor, Color _levelFourColor)
{
	levelOneMax = _levelOneMax;
	levelTwoMax = _levelTwoMax;
	levelThreeMax = _levelThreeMax;
	levelOneColor = _levelOneColor;
	levelTwoColor = _levelTwoColor;
	levelThreeColor = _levelThreeColor;
	levelFourColor = _levelFourColor;
}
