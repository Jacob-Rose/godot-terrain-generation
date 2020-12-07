/* chunk.cpp */

#include "chunk.h"
#include "scene/main/viewport.h" //used to get mouse position in _process(float)


void Chunk::_bind_methods() {

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
	redraw = true;
	chunkSize = 0.0f;
	set_process(true);
}

Chunk::Chunk(float x, float z, int desiredSize) {
	set_process(true);
	xPos = x;
	zPos = z;
	redraw = true;
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

	//6 vertices for the two triangles
	vertices.push_back(Vector3(0, 100,0));
	vertices.push_back(Vector3(100, 0,0));
	vertices.push_back(Vector3(0, 0,0));
	vertices.push_back(Vector3(0, 100,0));
	vertices.push_back(Vector3(100, 100,0));
	vertices.push_back(Vector3(100, 0,0));

	colors.append(Color(1, 1, 1));
	colors.append(Color(0, 1, 0));
	colors.append(Color(0, 0, 1));
	colors.append(Color(1, 0, 0));
	colors.append(Color(0, 0, 0));
	colors.append(Color(0, 1, 0));

	//Copying the data into another set
	_vertices.push_back(Vector3(0, 100,0));
	_vertices.push_back(Vector3(100, 0,0));
	_vertices.push_back(Vector3(0, 0,0));
	_vertices.push_back(Vector3(0, 100,0));
	_vertices.push_back(Vector3(100, 100,0));
	_vertices.push_back(Vector3(100, 0,0));

	_colors.append(Color(1, 1, 1));
	_colors.append(Color(0, 1, 0));
	_colors.append(Color(0, 0, 1));
	_colors.append(Color(1, 0, 0));
	_colors.append(Color(0, 0, 0));
	_colors.append(Color(0, 1, 0));
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
