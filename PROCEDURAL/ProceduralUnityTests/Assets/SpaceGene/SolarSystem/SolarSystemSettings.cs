using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Scriptable Objects/SolarSystemSettings")]
public class SolarSystemSettings : ScriptableObject{
    [Range(0,20)]
    public int maxPlanets = 10;
    [Range(0,10)]
    public int minPlanets = 0;
    [Range(0.0f, 10.0f)]
    public float minSpacing = 0.5f;
    [Range(0.1f, 1.0f)]
    public float spacingMultiplier = 1.0f;
    [Range(0.0f, 3.0f)]
    public float sunMargin = 0.5f;
}
