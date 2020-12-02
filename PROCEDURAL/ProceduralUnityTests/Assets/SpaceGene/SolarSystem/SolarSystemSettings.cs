using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Scriptable Objects/SolarSystemSettings")]
public class SolarSystemSettings : ScriptableObject{
    [Range(0,20)]
    public int maxPlanets = 10;
    [Range(0,10)]
    public int minPlanets = 0;
    [Range(0,1)]//unused
    public float planetToSunRatio = 0.1f;
    [Range(0,10)]//unused
    public float spaceScale = 1;
}
