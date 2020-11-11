#ifndef __HEMESH_H__
#define __HEMESH_H__

#define CMP_EPSILON 1e-5

using namespace std;
#include <vector>
#include "core/math/vector3.h"
#include<string>
namespace meshparse {

class vertex;
class edge;
class face;

enum normal_mode {
    NO_NORMALS,
    AVERAGE
};

typedef std::pair<int, int> vertpair;
vertpair make_vertpair(int v1, int v2);

typedef struct {
    float max_x;
    float max_y;
    float max_z;
    float min_x;
    float min_y;
    float min_z;
} bounds;

class vertex {
    public:
        vertex();
        vertex(const vertex &other);
        bool operator==(const vertex &other);
        bool onboundary() const;

        int id;
        Vector3 loc;
        Vector3 normal;
        // the edge that points to this vertex
        edge* e;
};

class edge {
    public:
        int id;
        // the vertex that points to this edge
        vertex* vert;
        face* f;
        edge* next;
        edge* pair;

        edge* previous() const;
        edge* rewind() const;
        Vector3 as_vector() const;
        Vector3 midpoint() const;
        float angle_between(const edge& other) const;
};

class face {
    public:
        face();
        face(const face &other);
        float area() const;
        int sides() const;
        void calculate_normal();
        Vector3 centroid() const;

        int id;
        Vector3 normal;
        // a random edge on this face.
        edge* e;
};

class mesh {
    public:
        mesh();
        mesh(const mesh &other);
        void calculate_normals(normal_mode mode);
        void scale_to_unit_cube();
        bounds get_bounds() const;

        std::vector<vertex*> verteces;
        std::vector<edge*> edges;
        std::vector<face*> faces;
};

class vector_comparitor {
    public:
        bool operator()(const Vector3 &v1, const Vector3 &v2) const;
};

// loads a mesh, guessing the appropriate loader from the file name.
bool load_mesh(const std::string &filename, std::ifstream &input, mesh &mesh);

} // namespace meshparse

#endif
