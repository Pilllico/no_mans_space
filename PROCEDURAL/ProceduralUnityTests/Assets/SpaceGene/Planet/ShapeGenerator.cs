using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeGenerator {
    int seed;
    PlanetSettings settings;
    NoiseFilter noise;

    public ShapeGenerator(int seed, PlanetSettings settings) {
        this.seed = seed;
        this.settings = settings;
    }

    public Vector3 calculatePointOnPlanet(Vector3 pointOnUnitSphere) {
        this.noise = new NoiseFilter(seed);
        float altitude = 0;
        //BASE LAYER
        if(settings.baseLayer.active) altitude = getAltitudeFromNoiseLayer(settings.baseLayer, pointOnUnitSphere);
        //DETAIL LAYERS
        foreach (NoiseSettings layer in settings.noiseLayers) {
            if(altitude > 0 && layer.active) altitude += getAltitudeFromNoiseLayer(layer, pointOnUnitSphere);
        }

        Vector3 pointOnPlanet = pointOnUnitSphere * (1 + altitude);
        return pointOnPlanet;// * radius;
    }

    float getAltitudeFromNoiseLayer(NoiseSettings layer, Vector3 pointOnUnitSphere) {
        float altitude = 0;
        float frequency = layer.baseRoughness;
        float amplitude = 1;
        for (int i = 0; i < layer.numLayers; i++) {
            float v = noise.evaluate(pointOnUnitSphere * frequency + layer.center);
            altitude += v * amplitude;
            frequency *= layer.roughness;
            amplitude *= layer.persistance;
        }
        altitude = Mathf.Max(0, altitude - layer.flatThreshold);
        altitude *= layer.strength;
        return altitude;
    }
}