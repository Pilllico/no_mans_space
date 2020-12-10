using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Scriptable Objects/SunSettings")]
public class SunSettings : ScriptableObject{
    [Range(0.1f, 1.0f)]
    public float minRadius = 0.5f;
    [Range(0.0f, 2.0f)]
    public float radiusMultiplier = 1.0f;
}
