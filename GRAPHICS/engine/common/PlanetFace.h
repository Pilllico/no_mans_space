#pragma once

#include "ShapeGenerator.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Vector2.h"

class PlanetFace{

private:
	ShapeGenerator shapeGenerator;
	Mesh mesh;
	int resolution;
	Vector3 localUp;
	Vector3 axisA;
	Vector3 axisB;

public:

	PlanetFace() {}

	PlanetFace(ShapeGenerator shapeGenerator, int resolution, Vector3 localUp) {
		this->shapeGenerator = shapeGenerator;
		this->mesh = mesh;
		this->resolution = resolution;
		this->localUp = localUp;

		axisA = Vector3(localUp.y, localUp.z, localUp.x);
		axisB = Vector3::Cross(localUp, axisA);
	}

	void constructMesh() {
		vector<Vector3> vertices = vector<Vector3>(resolution * resolution);
		vector<int> triangles = vector<int>((resolution - 1) * (resolution - 1) * 6);

		int triIndex = 0;

		for (int y = 0; y < resolution; y++) {
			for (int x = 0; x < resolution; x++) {
				int i = x + y * resolution;
				Vector2 percent = Vector2(x, y) / (resolution - 1);
				Vector3 pointOnUnitCube = localUp + axisA * (percent.x - 0.5f) * 2.0f  + axisB * (percent.y - 0.5f) * 2.0f;
				Vector3 pointOnUnitSphere = pointOnUnitCube.normalized();
				Vector3 pointOnPlanet;
				if (resolution > 30) pointOnPlanet = shapeGenerator.calculatePointOnPlanet(pointOnUnitSphere);
				else pointOnPlanet = pointOnUnitSphere;
				vertices[i] = pointOnPlanet;

				if (x != resolution - 1 && y != resolution - 1) {
					triangles[triIndex] = i;
					triangles[triIndex + 1] = i + resolution + 1;
					triangles[triIndex + 2] = i + resolution;

					triangles[triIndex + 3] = i;
					triangles[triIndex + 4] = i + 1;
					triangles[triIndex + 5] = i + resolution + 1;
					triIndex += 6;
				}
			}
		}

		mesh.vertices = vertices;
		mesh.triangles = triangles;
		mesh.recalculateNormals();
	}

	Mesh getMesh() {
		return mesh;
	}
};

