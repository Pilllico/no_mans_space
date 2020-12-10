using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Scriptable Objects/PlanetSettings")]
public class PlanetSettings : ScriptableObject {

    [Range(0.0f, 10.0f)]
    public float minRadius = 0.1f;
    [Range(0.0f, 1.0f)]
    public float radiusMultiplier = 0.2f;
    [Range(0.0f, 2.0f)]
    public float speedMultiplier = 1.0f;

    public NoiseSettings baseLayer;
    public NoiseSettings[] noiseLayers;
}
