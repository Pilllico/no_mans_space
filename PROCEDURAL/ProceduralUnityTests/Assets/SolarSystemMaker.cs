using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SolarSystemMaker{

    public static int maxPlanets = 10;
    public static int minPlanets = 0;
    public static float planetToSunRatio = 0.1f;
    public static float spaceScale = 1;
  

    Vector3 centerCoords;
    int seed;
    NoiseFilter noise;
    float sunRadius;

    public SolarSystemMaker(Vector3 coords) {
        centerCoords = coords;
        seed = ((int)coords.x) | (((int)coords.y) << 8) | (((int)coords.z) << 16);
        noise = new NoiseFilter(seed);

        makeSun();
        makePlanets();
    }

    private void makeSun() {
        float sunSize = noise.evaluate(centerCoords);
        sunRadius = sunSize / 2;
        SphereMaker.makeSphere(centerCoords, sunSize);
    }

    private void makePlanets() {
        int planetAmount = (int) (noise.evaluate(centerCoords*2) * 10.0f);
        for (int i = 0; i < planetAmount; i++) {
            PlanetMaker pm = new PlanetMaker(centerCoords, i, sunRadius);
        }
    }

}
