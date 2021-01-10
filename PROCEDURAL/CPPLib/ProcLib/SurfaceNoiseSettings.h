#pragma once

#include "Vector3.h"

class SurfaceNoiseSettings{

public:
	//BASE
	bool ACTIVE = true;
	int NUM_LAYERS = 1;
	float FLAT_THRESHOLD = 0.5;
	float STRENGTH = 0.1;
	float BASE_ROUGHNESS = 1.5;
	Vector3 CENTER = Vector3::zero;
	//PER LAYER ITERATION
	float ROUGHNESS = 2;
	float PERSISTANCE = 0.5;
};

