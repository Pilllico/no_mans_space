using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SolarSystemMaker{

    SolarSystemSettings solarSystemSettings;

    Vector3 center;
    int seed;
    NoiseFilter noise;

    public SolarSystemMaker(Vector3 coords) {
        //INIT
        solarSystemSettings = GameObject.Find("SpaceMaker").GetComponent<CommonSettings>().solarSystemSettings;
        center = coords;
        seed = ((int)coords.x) | (((int)coords.y) << 8) | (((int)coords.z) << 16);
        noise = new NoiseFilter(seed);
        //MAKING
        makeSun();
        makePlanets();
    }

    private void makeSun() {
        SunMaker sm = new SunMaker(center);
    }

    private void makePlanets() {
        float planetAmount = solarSystemSettings.minPlanets + (int)((solarSystemSettings.maxPlanets - solarSystemSettings.minPlanets) * noise.newValueFromCoords(center));
        float orbit = solarSystemSettings.sunMargin;
        for (int i = 0; i < planetAmount; i++) {
            orbit = solarSystemSettings.minSpacing + noise.newValueFromCoords(center);
            PlanetMaker pm = new PlanetMaker(center, orbit);
        }
    }

}
