using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SphereMaker : MonoBehaviour
{
    public static GameObject makeSphere(Vector3 coords, float size) {
        GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        sphere.transform.position = coords;
        sphere.transform.localScale = Vector3.one * size;
        return sphere;
    }
}
