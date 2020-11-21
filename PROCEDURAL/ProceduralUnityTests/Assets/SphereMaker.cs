﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SphereMaker : MonoBehaviour
{
    public static void makeSphere(Vector3 coords, float size) {
        GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        sphere.transform.position = coords;
        sphere.transform.localScale = new Vector3(size, size, size);
    }
}
