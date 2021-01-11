#pragma once

#include <algorithm>
#include "Vector3.h"
#include "PlanetSettings.h"
#include "NoiseFilter.h"
#include "SurfaceNoiseSettings.h"

class ShapeGenerator{

protected:
	int seed;
	NoiseFilter noise;

    float getAltitudeFromNoiseLayer(SurfaceNoiseSettings layer, Vector3 pointOnUnitSphere) {
        float altitude = 0;
        float frequency = layer.BASE_ROUGHNESS;
        float amplitude = 1;
        for (int i = 0; i < layer.NUM_LAYERS; i++) {
            float v = noise.evaluate(pointOnUnitSphere * frequency + layer.CENTER);
            altitude += v * amplitude;
            frequency *= layer.ROUGHNESS;
            amplitude *= layer.PERSISTANCE;
        }
        altitude = std::max((float)0.0, altitude - layer.FLAT_THRESHOLD);
        altitude *= layer.STRENGTH;
        return altitude;
    }

public:

    ShapeGenerator(int seed = 0) {
        this->seed = seed;
    }

	Vector3 calculatePointOnPlanet(Vector3 pointOnUnitSphere) {
        this->noise = NoiseFilter(seed);
        float altitude = 0;
        //BASE LAYER
        if (PlanetSettings::BASE_LAYER.ACTIVE) altitude = getAltitudeFromNoiseLayer(PlanetSettings::BASE_LAYER, pointOnUnitSphere);
        //DETAIL LAYERS
        if (!PlanetSettings::ADDITIONAL_LAYERS.empty()) {
            for (int i = 0; i <= PlanetSettings::ADDITIONAL_LAYERS.size(); i++) {
                SurfaceNoiseSettings layer = PlanetSettings::ADDITIONAL_LAYERS[i];
                if (altitude > 0 && layer.ACTIVE) altitude += getAltitudeFromNoiseLayer(layer, pointOnUnitSphere);
            }
        }
        Vector3 pointOnPlanet = pointOnUnitSphere * (1 + altitude);
        return pointOnPlanet;// * radius;
    }
};

