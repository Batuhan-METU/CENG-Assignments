#include "Mesh.h"

Mesh::Mesh(const char* filename)
{
	int nVerts, nTris, n, k = 0;
	double x, y, z;
	minHeap.push_back(0);

	ifstream file(filename);

	string line;
	getline(file, line);
	getline(file, line);
	stringstream str(line);
	str >> nVerts >> nTris >> n;

	while (k++ < nVerts)
	{
		getline(file, line);
		stringstream str2(line);

		str2 >> x >> y >> z;
		addVertex(x, y, z); // Not Implemented.
	}
	k = 0;
	while (k++ < nTris)
	{
		getline(file, line);
		stringstream str2(line);

		str2 >> n >> x >> y >> z;
		addTriangle((size_t)x, (size_t)y, (size_t)z); // Not Implemented.
	}

	file.close();

	buildHeap(); // Not Implemented.
}


size_t Mesh::addVertex(double x, double y, double z) {
	Vertex v; 	  
	v.coords[0] = x; 
	v.coords[1] = y; 
	v.coords[2] = z;
	v.idx = verts.size(); 

	verts.push_back(v);

	return v.idx; 
}
size_t Mesh::addTriangle(size_t v1, size_t v2, size_t v3) {
	Triangle tri;
	tri.v1i = v1; 
	tri.v2i = v2; 
	tri.v3i = v3;

	tri.idx = tris.size(); 
	tris.push_back(tri); 
	
	verts[v1].triList.push_back(tri.idx);
	verts[v2].triList.push_back(tri.idx);  
	verts[v3].triList.push_back(tri.idx);  

	// handle edge, vertexler arasında o edge zaten varsa eklemeyecek, o edge yoksa ekleyecek.
	handleEdge(v1,v2);   
	handleEdge(v1,v3);
	handleEdge(v2,v3);
}

void Mesh::buildHeap() {
	minHeap.push_back(0); // dummy
	for(size_t i = 0; i<edges.size(); i++) {
		minHeap.push_back(i); 
	}

	size_t theSize = minHeap.size() - 1; 

	for(int i = theSize / 2; i >= 1; i--) {
		bubbleDown(i); 
	}
}

Edge& Mesh::getEdge(size_t v1, size_t v2) {
	if(v1 >= verts.size() || v2 >= verts.size() || v1 < 0 || v2 < 0) return edges[0]; 

	for(size_t i = 0; i<verts[v1].edgeList.size(); i++) {
		size_t edgeIndex = verts[v1].edgeList[i]; 

		Edge &edge = edges[edgeIndex]; 

		if((v1 == edge.v1i && v2 == edge.v2i) || (v1 == edge.v2i && v2 == edge.v1i)) {
			return edge; 
		}
	}
	return edges[0]; 
}

void Mesh::printVertex(size_t v) {
	if(0<=v && v<verts.size()) {
		std::cout << verts[v].coords[0] << " " << verts[v].coords[1] << " " << verts[v].coords[2]; 
	}
}

void Mesh::printTriangle(size_t t) {
	if(0<=t && t<tris.size()) {
		std::cout << tris[t].idx << " " << tris[t].v1i << " " << tris[t].v2i << " " << tris[t].v3i;
	}
}

bool Mesh::isVertsNeighbour(size_t v1, size_t v2) {
	for(size_t i = 0; i<verts[v1].vertList.size(); i++) {
		size_t vInd = verts[v1].vertList[i]; 
		if(vInd == v2) return true; 
	}
	return false; 
}

size_t Mesh::getDegree(size_t v) {
	if(0<=v && v<verts.size()) return 0; 

	return verts[v].edgeList.size(); 
}

int Mesh::getJumpCount(size_t v1, size_t v2)
{
	if(v1 == v2) return 0; 

	if(v1 < 0 || v2 < 0 || v1 >= verts.size() || v2 >= verts.size()) return -1; 

	int jumpCount = 0;
	std::queue<int> q; 
	std::vector<bool> visited(verts.size(), false); 

	q.push(v1);
	visited[v1] = true; 
	jumpCount++;  

	while(!q.empty()) {
		int levelSize = q.size();  
		for(int j = 0; j < levelSize;j++) {
			int current = q.front(); 
			q.pop(); 

			if(current == v2) return jumpCount; 

			for(int i = 0; i < verts[current].vertList.size(); i++) {
				int neighbourIndex = verts[current].vertList[i]; 

				if(!visited[neighbourIndex]) {
					q.push(neighbourIndex); 
					visited[neighbourIndex] = true;
				}
			}
		} 
		jumpCount++; 
	}
	return -1; 
}

double Mesh::getGeodesicDistance(size_t v1, size_t v2) {
	if(v1 == v2) return 0; 
	if(v1 < 0 || v2 < 0 || v1 >= verts.size() || v2 >= verts.size()) return -1; 

	vector<double> distance(verts.size(), INT_MAX); 
	vector<bool> visited(verts.size(), false);

	distance[v1] = 0; 
	visited[v1] = true; 

	while(true) {
		int u = -1; 
		int minDist = INT_MAX;
		
		for(int i = 0; i < verts.size(); i++) {
			if(!visited[i] && distance[i] < minDist) {
				minDist = distance[i]; 
				u = i; 
			}
		}

		if(u == -1) break; 
		if(u == v2) return distance[u]; 

		visited[u] = true; 

		for(int i = 0; i < verts[u].vertList.size(); i++) {
			int neighbour = verts[u].vertList[i]; 
			if(visited[neighbour]) continue;

			double edgeLength = dist(verts[u].coords, verts[neighbour].coords); 

			if(distance[u] + edgeLength < distance[neighbour]) {
				distance[neighbour] = distance[u] + edgeLength; 
			}
		}
	}
	return -1; 
}

void Mesh::updateVertex(size_t v, double x, double y, double z) {
	if(v >= verts.size() || v < 0) return; 

	verts[v].coords[0] = x; 
	verts[v].coords[1] = y; 
	verts[v].coords[2] = z;

	for(int i = 0; i<verts[v].edgeList.size(); i++) {
		int edgeIndex = verts[v].edgeList[i]; 
		Edge &e = edges[edgeIndex]; 

		size_t v1 = e.v1i;  
		size_t v2 = e.v2i;

		double newLength = dist(verts[v1].coords, verts[v2].coords); 
		e.length = newLength; 
	}
	buildHeap(); 
}

Edge& Mesh::getKthShortestEdge(size_t k) {
	return edges[0];
}

// Implement your helper functions here.