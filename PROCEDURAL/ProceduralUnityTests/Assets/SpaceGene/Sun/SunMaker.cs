using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SunMaker{
    SunSettings sunSettings;
    int seed;
    NoiseFilter noise;
    Vector3 center;
    float radius;

    public SunMaker(Vector3 center) {
        //INIT
        sunSettings = GameObject.Find("SpaceMaker").GetComponent<CommonSettings>().sunSettings;
        seed = ((int)center.x) | (((int)center.y) << 8) | (((int)center.z) << 16);
        noise = new NoiseFilter(seed);
        this.center = center;
        this.radius = sunSettings.minRadius + noise.newValueFromCoords(this.center) * sunSettings.radiusMultiplier;
        //MAKING
        makeSphere(this.center, radius);
    }

    public void makeSphere(Vector3 coords, float radius) {
        GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        sphere.name = "Sun";
        sphere.transform.position = coords;
        sphere.transform.localScale = Vector3.one * radius;
        Light light = sphere.AddComponent<Light>();
        light.range = 1.15f;
    }
}
