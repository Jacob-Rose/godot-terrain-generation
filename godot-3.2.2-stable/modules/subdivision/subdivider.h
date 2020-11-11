#ifndef SUBDIVIDE_H
#define SUBDIVIDE_H

#include <scene/3d/mesh_instance.h>
#include "halfedge/he_mesh.h"

class Subdivider : public MeshInstance {
	GDCLASS(Subdivider, MeshInstance);

	protected:
		static void _bind_methods();
		//notification is the only auto-linked function in a GDCLASS
		void _notification(int p_what);

		meshparse::mesh* m_HalfEdgeMesh;
		meshparse::mesh *m_OriginalMesh;


		//Updated based on what were working on
		PoolVector3Array m_Verticies;
		PoolColorArray m_Colors;
		//original to reset back too
		PoolVector3Array m_oVerticies;
		PoolColorArray m_oColors;

		int m_TargetNumSubdivisions = 0;
		int m_CurrentNumSubdivisions = 0;
		bool m_ShouldRedraw = false;

		std::string m_Filename;
	public:
		Subdivider();
		~Subdivider();

		void _ready();
		void _process();
		void _draw();
		void _input(InputEvent *e);

		void setFilename(std::string filename);
		std::string getFilename();

		Vector3 calculateNewEdgeMidpoint(meshparse::edge* edge);
		Vector3 calculateNewVertPosition(meshparse::vertex *vert);

		void resetMesh();
		void subdivideMesh();
};
#endif
