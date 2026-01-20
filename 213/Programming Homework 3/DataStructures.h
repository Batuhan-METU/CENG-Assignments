#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <vector>
#include "Arithmetic.h"
using std::vector;

const size_t NONE = size_t(-1);

struct Vertex
{
	double coords[3] = { 0.0, 0.0, 0.0 };

	size_t idx;

	vector< size_t > vertList;
	vector< size_t > triList;
	vector< size_t > edgeList;


	Vertex(size_t i, double x, double y, double z) : idx(i) { assign(coords, x, y, z); };
	Vertex() : idx(NONE) { assign(coords); };
	Vertex(Vertex* vert) : idx(vert->idx), vertList(vert->vertList), edgeList(vert->edgeList), triList(vert->triList) { assign(coords, vert->coords); };
	~Vertex() { vertList.clear(); triList.clear(); edgeList.clear(); };

	//Declare your helper functions here
};

struct Edge
{
	size_t idx;
	size_t v1i, v2i; 
	double length = 0.0;

	Edge(size_t id, size_t v1, size_t v2) : idx(id), v1i(v1), v2i(v2) { };
	Edge(Edge* edge) : idx(edge->idx), v1i(edge->v1i), v2i(edge->v2i), length(edge->length) { };
	Edge() : idx(NONE), v1i(NONE), v2i(NONE) { };
	~Edge() { };

	size_t findEdge(size_t a, size_t b, vector<size_t> verts) {
		for(size_t i = 0; i<verts[a].)
	}
	//Declare your helper functions here
};

struct Triangle
{
	size_t idx; 
	size_t v1i, v2i, v3i;

	Triangle(size_t id, size_t v1, size_t v2, size_t v3) : idx(id), v1i(v1), v2i(v2), v3i(v3) { };
	Triangle(Triangle* tris) : idx(tris->idx), v1i(tris->v1i), v2i(tris->v2i), v3i(tris->v3i) { };
	Triangle() : idx(NONE), v1i(NONE), v2i(NONE), v3i(NONE) { };
	~Triangle() { };

	//Declare your helper functions here
};

#endif // !DATA_STRUCTURES_H

