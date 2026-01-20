#ifndef MESH_H
#define HESH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "DataStructures.h"

using std::string;
using std::ifstream;
using std::stringstream;

class Mesh {
public:
	vector<Vertex> verts;
	vector<Edge> edges;
	vector<Triangle> tris;
	vector<size_t> minHeap;

	Mesh() {
		minHeap.push_back(0);
	};
	Mesh(const char* filename);
	~Mesh() {
		verts.clear();
		edges.clear();
		tris.clear();
		minHeap.clear();
	};

	inline Vertex& getVertex(size_t v) {
		if (v < verts.size()) {
			return verts[v];
		}
		else {
			return verts[0];
		}
	}

	inline Edge& getEdge(size_t e) {
		if (e < edges.size()) {
			return edges[e];
		}
		else {
			return edges[0];
		}
	}

	Edge& getEdge(size_t v1, size_t v2);

	inline Triangle& getTriangle(size_t t) {
		if (t < tris.size()) {
			return tris[t];
		}
		else {
			return tris[0];
		}
	}

	void printVertex(size_t v);
	void printTriangle(size_t t);

	bool isVertsNeighbour(size_t v1, size_t v2);
	size_t getDegree(size_t v);
	int getJumpCount(size_t v1, size_t v2);
	double getGeodesicDistance(size_t v1, size_t v2);
	void updateVertex(size_t v, double x, double y, double z);
	Edge& getKthShortestEdge(size_t k);

private:	
	size_t addVertex(double x, double y, double z);
	size_t addTriangle(size_t v1, size_t v2, size_t v3);
	void buildHeap();

	void bubbleDown(size_t hole) {
		size_t child; 
		size_t temp = minHeap[hole]; 

		size_t theSize = minHeap.size() - 1; 
		for(; hole * 2 <=theSize; hole = child) {
			child = hole * 2; 

			if(child != theSize && (edges[minHeap[child+1]].length < edges[minHeap[child]].length)) {
				child++; 
			}
			if(edges[minHeap[child]].length < edges[temp].length) {
				minHeap[hole] = minHeap[child]; 
			}
			else {
				break; 
			}
		}
		minHeap[hole] = temp; 
	}
	void bubbleUp(size_t hole) {
		size_t temp = minHeap[hole]; 

		size_t theSize = minHeap.size() - 1; 
		for(; hole > 1 && edges[temp].length < edges[minHeap[hole/2]].length; hole /= 2) {
			minHeap[hole] = minHeap[hole/2]; 
		}
		minHeap[hole] = temp; 
	}

	void handleEdge(size_t a, size_t b) {
		for(size_t i = 0; i<verts[a].edgeList.size(); i++) {
			size_t edgeIndex = verts[a].edgeList[i]; 

			Edge &edge = edges[edgeIndex]; 
			if((edge.v1i == a && edge.v2i == b) || (edge.v1i == b && edge.v2i == a)) {
				return; 
			}
		}
		Edge edg; 
		edg.idx = edges.size(); 

		edg.v1i = a; 
		edg.v2i = b; 
		edg.length = dist(verts[a].coords, verts[b].coords); 

		edges.push_back(edg); 
		verts[a].edgeList.push_back(edg.idx); 
		verts[b].edgeList.push_back(edg.idx); 

	}
	// Declare your helper functions here.
};

#endif // !MESH_H

