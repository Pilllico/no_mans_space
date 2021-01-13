#pragma once

#include "ShapeGenerator.h"
#include "PlanetFace.h"
#include "PlanetSettings.h"
#include "SpaceSettings.h"
#include "Vector3.h"
#include "Mesh.h"

class PlanetMaker {

    //MESH SETTINGS
    int resolution = 50;
    ShapeGenerator shapeGenerator;
    PlanetFace planetFaces[6];
    //PLANET
    int seed;
    NoiseFilter noise;
    Vector3 solarSysCenter;
    float radius;
    float orbit;
    float speed;

public:

    PlanetMaker(Vector3 solarSysCenter = Vector3::zero, float orbit = 0) {
        //INIT
        Vector3 seedPosition = solarSysCenter * orbit;
        seed = ((int)(seedPosition.x)) | (((int)(seedPosition.y)) << 8) | (((int)(seedPosition.z)) << 16);
        //Debug.Log(seed);
        noise = NoiseFilter(seed);
        Vector3 position = solarSysCenter + Vector3::left * orbit;
        this->radius = PlanetSettings::MIN_RADIUS + noise.newValueFromCoords(position) * PlanetSettings::RADIUS_MULTIPLIER;
        this->orbit = orbit;
        this->speed = noise.newValueFromCoords(position) * PlanetSettings::SPEED_MULTIPLIER;
        //MAKING

        initialize();
        generateMesh();
    }

    PlanetFace getPlanetFace(int i) {
        return planetFaces[i];
    }

private:

    void initialize() {
        shapeGenerator = ShapeGenerator(seed);

        Vector3 directions[] = { Vector3::up, Vector3::down, Vector3::right, Vector3::left, Vector3::forward, Vector3::back };
        for (int i = 0; i < 6; i++) {
            planetFaces[i] = PlanetFace(shapeGenerator, resolution, directions[i]);
        }
    }

    void generateMesh() {
        for (int i = 0; i < 6; i++) {
            planetFaces[i].constructMesh();
        }
    }

};