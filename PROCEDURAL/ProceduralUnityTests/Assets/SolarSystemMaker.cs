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

    public SolarSystemMaker(Vector3 coords) {
        centerCoords = coords;
        seed = ((int)coords.x) | (((int)coords.y) << 8) | (((int)coords.z) << 16);
        noise = new NoiseFilter(seed);

        makeSun();
    }

    private void makeSun() {
        float sunSize = noise.evaluate(new Vector3(13214,132132,76683));
        SphereMaker.makeSphere(centerCoords, sunSize);
    }

}
