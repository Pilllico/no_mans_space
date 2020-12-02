using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Scriptable Objects/SpaceSettings")]
public class SpaceSettings : ScriptableObject {
    [Range(0, 2)]
    public float samplingResolution = 0.5f;
    [Range(0, 0.5f)]
    public float density = 0.06f;
    [Range(0, 10)]
    public float jitterMultiplier = 5;
    [Range(1,100)]
    public int   subdivisionDimmension = 10;
}
