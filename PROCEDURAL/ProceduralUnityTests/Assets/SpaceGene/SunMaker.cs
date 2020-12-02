using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SunMaker : MonoBehaviour
{
    public static GameObject makeSphere(Vector3 coords, float size) {
        GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        sphere.transform.position = coords;
        sphere.transform.localScale = Vector3.one * size;
        Light light = sphere.AddComponent<Light>();
        light.range = 3;
        
        return sphere;
    }
}
