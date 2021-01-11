#pragma once

#include "SurfaceNoiseSettings.h"
#include <vector>

class PlanetSettings{

public:
	//PLANET
	static float MIN_RADIUS;
	static float RADIUS_MULTIPLIER;
	static float SPEED_MULTIPLIER;
	//SURFACE
	static SurfaceNoiseSettings BASE_LAYER;
	static std::vector<SurfaceNoiseSettings> ADDITIONAL_LAYERS;

};

