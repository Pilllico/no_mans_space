using System.Collections;
using System.Collections.Generic;
using UnityEngine;
[System.Serializable]
public class NoiseSettings{
    public bool active = true;

    [Range(1, 8)]
    public int numLayers = 1;

    [Range(0, 1)]
    public float flatThreshold = 0.5f;
    [Range(0,0.5f)]
    public float strength = 0.1f;
    [Range(0,10)]
    public float baseRoughness = 1.5f;

    public Vector3 center = Vector3.zero;

    [Header("Per layer iteration")]
    [Range(1,10)]
    public float roughness = 2;
    [Range(0,1)]
    public float persistance = 0.5f;
}
