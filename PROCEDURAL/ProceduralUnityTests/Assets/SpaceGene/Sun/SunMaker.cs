using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SunMaker : MonoBehaviour
{
    public static GameObject makeSphere(Vector3 coords, float radius) {
        GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        sphere.name = "Sun";
        sphere.transform.position = coords;
        sphere.transform.localScale = Vector3.one * radius;
        Light light = sphere.AddComponent<Light>();
        light.range = 1.15f;
        
        return sphere;
    }
}
