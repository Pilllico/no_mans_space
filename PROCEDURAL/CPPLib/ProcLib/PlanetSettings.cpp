#include "PlanetSettings.h"

//PLANET
float PlanetSettings::MIN_RADIUS = 0.1;
float PlanetSettings::RADIUS_MULTIPLIER = 0.2;
float PlanetSettings::SPEED_MULTIPLIER = 1.0;
//SURFACE
SurfaceNoiseSettings PlanetSettings::BASE_LAYER = SurfaceNoiseSettings();
std::vector<SurfaceNoiseSettings> PlanetSettings::ADDITIONAL_LAYERS = std::vector<SurfaceNoiseSettings>(0);
