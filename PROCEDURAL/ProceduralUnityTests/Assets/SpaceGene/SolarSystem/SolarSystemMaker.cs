using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SolarSystemMaker{

    SolarSystemSettings solarSystemSettings;

    Vector3 centerCoords;
    int seed;
    NoiseFilter noise;
    float sunRadius;

    public SolarSystemMaker(Vector3 coords) {
        solarSystemSettings = GameObject.Find("SpaceMaker").GetComponent<CommonSettings>().solarSystemSettings;
        centerCoords = coords;
        seed = ((int)coords.x) | (((int)coords.y) << 8) | (((int)coords.z) << 16);
        noise = new NoiseFilter(seed);

        makeSun();
        makePlanets();
    }

    private void makeSun() {
        sunRadius = noise.evaluate(centerCoords) / 2;
        SunMaker.makeSphere(centerCoords, sunRadius);
    }

    private void makePlanets() {
        float planetAmount = solarSystemSettings.minPlanets + (int)((solarSystemSettings.maxPlanets - solarSystemSettings.minPlanets) * noise.evaluate(centerCoords * 2));
        for (int i = 0; i < planetAmount; i++) {
            PlanetMaker pm = new PlanetMaker(centerCoords, i, sunRadius);
        }
    }

}
