#pragma once

#include "FastNoiseLite.h"

class NoiseFilter{

public:
	float offsetForNewValue = 1;
	float frequencyMultiplierForNewValues = 100000;

	NoiseFilter() {
		this->seed = 0;
		noise = FastNoiseLite();
		noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
	}

	NoiseFilter(int seed) {
		this->seed = seed;
		noise = FastNoiseLite(seed);
		noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
	}

	float evaluate(Vector3 point) {
		return (noise.GetNoise(point.x, point.y, point.z) + 1.0) * 0.5;
	}

	float newValueFromCoords(Vector3 point) {
		point = (point + Vector3::zero * offsetForNewValue) * frequencyMultiplierForNewValues;
		offsetForNewValue++;
		return evaluate(point);
	}

protected:

	int seed;
	FastNoiseLite noise;

};

