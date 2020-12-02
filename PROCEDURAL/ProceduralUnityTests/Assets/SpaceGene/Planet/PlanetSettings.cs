using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Scriptable Objects/PlanetSettings")]
public class PlanetSettings : ScriptableObject {
    public NoiseSettings baseLayer;
    public NoiseSettings[] noiseLayers;
}
