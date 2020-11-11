#include "objparse.h"

#include <cstdio>
#include <iterator>
#include <vector>
#include <iostream>
#include <map>
#include<string>
#include<sstream>
using namespace std;
#pragma GCC visibility push(hidden)

namespace meshparse {


using std::back_inserter;
using std::cout;
using std::endl;
using std::istream;
using std::istream_iterator;
using std::istringstream;
using std::string;
using std::vector;

struct objface {
    unsigned int id;
    vector<unsigned int> vids;
    vector<unsigned int> nids;
};

vector<struct objface> objfaces;

int obj_parse_vertex_spec(const string vspec) {
    unsigned int vid;
    sscanf(vspec.c_str(), "%d", &vid);
    return vid;
}

void obj_parse_line(mesh &objm, string line) {
    // TODO: support vn directives
    if (line[0] == 'v' && line[1] == ' ') {
        vertex *v = new vertex();

        float x, y, z;
        sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
        v->loc = Vector3(x, y, z);
        v->id = objm.verteces.size() + 1;

        objm.verteces.push_back(v);
    } else if (line[0] == 'f' && line[1] == ' ') {
        istringstream tokenizer(line);
        vector<string> tokens;
        copy(istream_iterator<string>(tokenizer),
                istream_iterator<string>(),
                back_inserter<vector<string> >(tokens));

        struct objface f;
        f.id = objfaces.size() + 1;
        for (unsigned int i=1; i<tokens.size(); i++) {
            string token = tokens[i];
            f.vids.push_back(obj_parse_vertex_spec(token));
        }

        objfaces.push_back(f);
    }
}

void obj_add_triangle(mesh &objm, vector<unsigned int> vids) {
    face *f = new face();
    f->id = objm.faces.size() + 1;

    edge *last_edge;
    for (unsigned int i = 0; i < vids.size(); i++) {
        edge *e = new edge();
        e->vert = objm.verteces[vids[i] - 1];
        objm.verteces[vids[i] - 1]->e = e;
        e->f = f;
        e->id = objm.edges.size() + 1;
        e->pair = NULL;
        if (i != 0) {
            last_edge->next = e;
        } else {
            f->e = e;
        }

        last_edge = e;
        objm.edges.push_back(e);
    }
    last_edge->next = f->e;
    f->calculate_normal();
    objm.faces.push_back(f);
}

bool load_obj(istream& file, mesh &mesh) {
    if (!file.good()) {
        cout << "Could not read file." << endl;
        return false;
    }

    string line;
    while (file.good()) {
        getline(file, line);
        obj_parse_line(mesh, line);
    }

    for (auto objf = objfaces.begin(); objf != objfaces.end(); objf++) {
        obj_add_triangle(mesh, objf->vids);
    }
    merge_half_edges(mesh);

    cout << "Loaded mesh: " << endl
        << "  " << mesh.verteces.size() << " verteces." << endl
        << "  " << mesh.edges.size() << " edges." << endl
        << "  " << objfaces.size() << " faces in OBJ file." << endl;
    return true;
}

void merge_half_edges(mesh& mesh) {
    map<pair<unsigned int, unsigned int>, edge*> halfedges;
    for (vector<edge*>::const_iterator edge_iter = mesh.edges.begin();
        edge_iter != mesh.edges.end(); edge_iter++) {
        edge* e = *edge_iter;

        int vid1 = e->vert->id;
        edge* previous = e;
        while (previous->next != e) previous = previous->next;
        int vid2 = previous->vert->id;

        pair<unsigned int, unsigned int> vids =
            pair<unsigned int, unsigned int>(
                vid1 < vid2 ? vid1 : vid2, vid1 < vid2 ? vid2 : vid1);

        map<pair<unsigned int, unsigned int>, edge*>::iterator
            mapval = halfedges.find(vids);

        if (mapval == halfedges.end()) {
            halfedges.insert(
                pair<pair<unsigned int, unsigned int>, edge*>(vids, e));
        }
        else {
            edge* opposite = mapval->second;
            e->pair = opposite;
            opposite->pair = e;
        }
    }
}

} // namespace meshparse

#pragma GCC visibility pop
