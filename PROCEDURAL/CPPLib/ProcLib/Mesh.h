#pragma once

#include <vector>
#include "Vector3.h"

using namespace std;

class Mesh{

public:
	vector<Vector3> vertices;
	vector<int> triangles;
	vector<Vector3> normals;

	Mesh() {
		vertices = vector<Vector3>();
		triangles = vector<int>();
	}

	void recalculateNormals() { // https://mrl.cs.nyu.edu/~perlin/courses/fall2002/meshnormals.html
		normals = vector<Vector3>(vertices.size(), Vector3::zero);
		
		for (int i = 0; i < triangles.size(); i += 3) {
			Vector3 a = vertices[triangles[i]];
			Vector3 b = vertices[triangles[i+1]];
			Vector3 c = vertices[triangles[i+2]];
			Vector3 sum = Vector3::zero;
			sum = sum + Vector3::Cross((b - a), (c - b));
			sum = sum + Vector3::Cross((c - b), (a - c));
			sum = sum + Vector3::Cross((c - a), (b - a));
			normals[i] = normals[i] + sum;
			normals[i+1] = normals[i+1] + sum;
			normals[i+2] = normals[i+2] + sum;
		}

		for (int i = 0; i < normals.size(); i++) normals[i] = normals[i].normalized();
	}

};

