using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetMaker : MonoBehaviour{

    int seed;
    NoiseFilter noise;
    Vector3 solarSysCenter;
    float size;
    float orbitRadius;
    float speed;

    public PlanetMaker(Vector3 solarSysCenter, int index, float sunRadius) {
        this.solarSysCenter = solarSysCenter;
        seed = ((int)(solarSysCenter.x * index)) | (((int)(solarSysCenter.y * index)) << 8) | (((int)(solarSysCenter.z * index)) << 16);
        noise = new NoiseFilter(seed);
        size = noise.evaluate(solarSysCenter)/20.0f;
        orbitRadius = (noise.evaluate(solarSysCenter*2) + index) / 10.0f + sunRadius * 2;
        speed = noise.evaluate(solarSysCenter * 3) /5.0f;
        GameObject sphere = SphereMaker.makeSphere(solarSysCenter + Vector3.left*orbitRadius, size);
        sphere.AddComponent(typeof(PlanetBehavior));
        sphere.GetComponent<PlanetBehavior>().center = solarSysCenter;
        sphere.GetComponent<PlanetBehavior>().radius = orbitRadius;
        sphere.GetComponent<PlanetBehavior>().speed = speed;
    }

}
