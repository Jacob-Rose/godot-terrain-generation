#ifndef __OBJPARSE_H__
#define __OBJPARSE_H__

#include <istream>
using namespace std;
#include "he_mesh.h"

namespace meshparse {
    bool load_obj(std::istream& input, mesh& mesh);
    void merge_half_edges(mesh& mesh);
}

#endif
