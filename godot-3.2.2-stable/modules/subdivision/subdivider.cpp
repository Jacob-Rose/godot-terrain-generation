#include "subdivider.h"
#include "halfedge/objparse.h"
#include "halfedge/he_mesh.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <core/os/input.h>
#include <core\engine.h>

void Subdivider::_bind_methods() {

}

void Subdivider::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_READY:
			_ready();
			break;
		case NOTIFICATION_PROCESS:
			_process();
			break;
	}
}

Subdivider::Subdivider()
{
	m_HalfEdgeMesh = new meshparse::mesh();
	set_process(true);
	set_process_input(true);
}

Subdivider::~Subdivider() {
	delete m_HalfEdgeMesh;
}

void Subdivider::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	std::ifstream infile;
	infile.open("cube.obj");

	if(meshparse::load_obj(infile, *m_HalfEdgeMesh)) {
		m_OriginalMesh = m_HalfEdgeMesh;
		m_ShouldRedraw = true;
	}

	m_oVerticies = m_Verticies;
	m_oColors = m_oColors;
}

void Subdivider::_process() {
	if (Input::get_singleton()->is_key_pressed(32)) {
		//key list https://docs.godotengine.org/en/stable/classes/class_@globalscope.html#enum-globalscope-keylist
		//i chose space
		m_TargetNumSubdivisions++;
		if (m_TargetNumSubdivisions > 3) {
			m_TargetNumSubdivisions = 0;
		}
		subdivideMesh();
		std::cout << "input detected: space key pressed";
	}


	if (m_ShouldRedraw) {
		std::cout << "starting redraw";
		Ref<ArrayMesh> a = memnew(ArrayMesh);
		Array arrays;
		for (std::vector<meshparse::face *>::iterator it = m_HalfEdgeMesh->faces.begin(); it != m_HalfEdgeMesh->faces.end(); ++it) {
			Vector3 v0, v1, v2, v3;
			v0 = (*it)->e->vert->loc;
			m_Verticies.push_back(Vector3(v0.x, v0.y, v0.z));
			v1 = (*it)->e->next->vert->loc;
			m_Verticies.push_back(Vector3(v1.x, v1.y, v1.z));
			std::cout << (*it)->e->next->next;
			v2 = (*it)->e->next->next->vert->loc;
			m_Verticies.push_back(Vector3(v2.x, v2.y, v2.z));

			m_Colors.append(Color(1, 1, 1));
			m_Colors.append(Color(0, 1, 0));
			m_Colors.append(Color(0, 0, 1));
			std::cout << "still iterating" << *it;
		}
		std::cout << "m_RedrawingMesh";
		m_ShouldRedraw = true;
		arrays.resize(ArrayMesh::ARRAY_MAX);
		arrays[ArrayMesh::ARRAY_VERTEX] = m_Verticies; // required
		arrays[ArrayMesh::ARRAY_COLOR] = m_Colors;

		//optionally u can add texture coordinates and attach a texture from the editor to this arraymesh in the scene

		a->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

		if (this != NULL) {
			this->set_mesh(a);
			std::cout << "mesh set and redrawn";
		}

		m_ShouldRedraw = false;
	}
}

void Subdivider::_draw() {
	
}

void Subdivider::_input(InputEvent *e) {
	if (InputEventKey* keyEvent = dynamic_cast<InputEventKey*>(e)) {
		//key list https://docs.godotengine.org/en/stable/classes/class_@globalscope.html#enum-globalscope-keylist
		//i chose space
		if (keyEvent->is_pressed() && keyEvent->get_scancode() == 32) {
			m_TargetNumSubdivisions++;
			if (m_TargetNumSubdivisions > 3) {
				m_TargetNumSubdivisions = 0;
			}
			std::cout << "input detected: space key pressed";
		}
	}
}

void Subdivider::setFilename(std::string filename) {
	m_Filename = filename;
}

std::string Subdivider::getFilename() {
	return m_Filename;
}

Vector3 Subdivider::calculateNewEdgeMidpoint(meshparse::edge *edge) {
	Vector3 vertexPointEdge;
	vertexPointEdge.zero();

	vertexPointEdge += edge->next->vert->loc;
	vertexPointEdge += edge->previous()->vert->loc;

	if (edge->pair != nullptr) {
		vertexPointEdge += edge->pair->f->centroid(); //add the opposite face
		vertexPointEdge += edge->f->centroid(); //add our face now too
	}
	return vertexPointEdge / 4;
}

Vector3 Subdivider::calculateNewVertPosition(meshparse::vertex *vert) {
	int pointsAddedQ = 1;
	Vector3 vertexPointQ = vert->e->f->centroid();
								   /*vert->e->previous()->pair->f->centroid() +
								   vert->e->previous()->f->centroid() +
								   vert->e->pair->f->centroid()) / 4;
								   */
	int pointsAddedR = 2;
	Vector3 vertexPointR = vert->e->midpoint() + vert->e->previous()->midpoint();


	if (vert->e->pair != nullptr) {
		vertexPointQ += vert->e->pair->f->centroid();
		++pointsAddedQ;
		vertexPointR += vert->e->pair->previous()->midpoint();
		++pointsAddedR;
	}

	if (vert->e->previous()->pair != nullptr) {
		vertexPointQ += vert->e->previous()->pair->next->midpoint();
		++pointsAddedQ;
		vertexPointR += vert->e->previous()->pair->f->centroid();
		++pointsAddedR;
		if (vert->e->previous()->pair->next != nullptr) {
			vertexPointQ += vert->e->previous()->pair->next->f->centroid();
			++pointsAddedQ;
		}
	}

	vertexPointQ /= pointsAddedQ;
	vertexPointR /= pointsAddedR;






	Vector3 vertexPointS = vert->loc;

	return (vertexPointQ / 4) + (vertexPointR / 2) + (vertexPointS / 4);
}


void Subdivider::resetMesh() {
	delete m_HalfEdgeMesh;
	m_HalfEdgeMesh = m_OriginalMesh;
	m_ShouldRedraw = true;
}
using namespace meshparse;
void Subdivider::subdivideMesh() {
	//catmell-clark section
	//http://www.rorydriscoll.com/2008/08/01/catmull-clark-subdivision-the-basics/
	//https://github.com/CMU-Graphics/Scotty3D/blob/master/src/geometry/halfedge.cpp

	meshparse::mesh *newMesh = new meshparse::mesh();

	for (std::vector<meshparse::face *>::iterator fit = m_HalfEdgeMesh->faces.begin(); fit != m_HalfEdgeMesh->faces.end(); ++fit) {

		//split edge and its twin together
		//https://stackoverflow.com/questions/8297897/finding-the-twins-when-implementing-catmull-clark-subdivision-using-half-edge-me


		//Create midpoint vertex
		meshparse::vertex *faceMidpoint = new meshparse::vertex();
		faceMidpoint->loc = (*fit)->centroid();

		//we are creating completly new parts, so no recycling in this iteration
		std::vector<meshparse::vertex *> newVertsFromFace = std::vector<meshparse::vertex*>();
		std::vector<meshparse::edge *> newEdgesFromFace = std::vector<meshparse::edge *>();
		std::vector<meshparse::face *> newFacesFromFace = std::vector<meshparse::face *>();

		newVertsFromFace.push_back(faceMidpoint);
		
		short count = 0;
		meshparse::edge *cEdge = (*fit)->e;
		meshparse::edge *startEdge = cEdge;

		while (cEdge->next != startEdge) {
			//the new vert on the midpoint || newVertsOnEdge[edge]
			meshparse::vertex *edgeMidpointVert = new meshparse::vertex();
			//edgeMidpointVert->loc = (*eit)->midpoint();
			edgeMidpointVert->loc = calculateNewEdgeMidpoint(cEdge);
			newVertsFromFace.push_back(edgeMidpointVert);

			//The original vert || newVertsOnEdge[edge+1]
			meshparse::vertex *edgeOriginalVert = new meshparse::vertex();
			//edgeOriginalVert->loc = (*eit)->vert->loc;
			edgeOriginalVert->loc = calculateNewVertPosition(cEdge->vert);
			newVertsFromFace.push_back(edgeOriginalVert);

			//The edge from the original || newEdgesOnEdge[edge * 4]
			meshparse::edge *edgeOriginal = new meshparse::edge();
			edgeOriginal->vert = edgeOriginalVert;
			newEdgesFromFace.push_back(edgeOriginal);

			//The edge from the midpoint to the next edges original || newEdgesOnEdge[(edge*4)+1]
			meshparse::edge *edgeFromMidpoint = new meshparse::edge();
			edgeFromMidpoint->vert = edgeMidpointVert;
			newEdgesFromFace.push_back(edgeFromMidpoint);

			//The edge that goes from the edge || newEdgesOnEdge[(edge *4) + 2]
			meshparse::edge *edgeToCenter = new meshparse::edge();
			edgeToCenter->vert = edgeMidpointVert;
			newEdgesFromFace.push_back(edgeToCenter);

			//The edge that goes from the center to the midpoint || newEdgesOnEdge[(edge *4) + 3]
			meshparse::edge *edgeFromCenter = new meshparse::edge();
			edgeFromCenter->vert = faceMidpoint;
			newEdgesFromFace.push_back(edgeFromCenter);

			//New Face Per Edge
			meshparse::face *newFace = new meshparse::face();
			newFace->e = edgeOriginal;
			newFacesFromFace.push_back(newFace);

			edgeToCenter->f = newFace;
			edgeOriginal->f = newFace;

			edgeToCenter->pair = edgeFromCenter;
			edgeFromCenter->pair = edgeToCenter;

			edgeOriginal->next = edgeToCenter;
			edgeFromCenter->next = edgeFromMidpoint;

			if (count > 0) {
				//link
				newEdgesFromFace[(count * 4) + 3]->next = edgeOriginal;
				edgeToCenter->next = newEdgesFromFace[(count * 4) + 2];

				newEdgesFromFace[(count * 4) + 3]->f = newFace;
				newEdgesFromFace[(count * 4) + 1]->f = newFace;
			}
			cEdge = cEdge->next;
			count++;
		}


		//link up the first loop to the now created edges
		newEdgesFromFace[15]->next = newEdgesFromFace[0];
		newEdgesFromFace[1]->next = newEdgesFromFace[14];


		newEdgesFromFace[15]->f = newFacesFromFace[0];
		newEdgesFromFace[15]->f = newFacesFromFace[0];


		//add them to the full set
		newMesh->faces.insert(newMesh->faces.begin(), newFacesFromFace.begin(), newFacesFromFace.end());
		newMesh->edges.insert(newMesh->edges.begin(), newEdgesFromFace.begin(), newEdgesFromFace.end());
		newMesh->verteces.insert(newMesh->verteces.begin(), newVertsFromFace.begin(), newVertsFromFace.end());



		
		//for each face, we will create a "floating" mesh of 2x2 quads. We will set the positions and not connect them in the current state

		//we then will connect them based on the midpoint and the new edges
		//Th

	}
	if (m_HalfEdgeMesh != m_OriginalMesh) {
		delete m_HalfEdgeMesh;
	}
	m_HalfEdgeMesh = newMesh;
	m_ShouldRedraw = true;
	std::cout << "mesh subdivided?";
}
