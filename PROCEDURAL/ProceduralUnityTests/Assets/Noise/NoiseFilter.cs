using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NoiseFilter{

    public float offsetForNewValue = 1;

    public NoiseFilter(int seed) {
        this.seed = seed;
        noise = new Noise(seed);
    }

    int seed;
    Noise noise;

    public float evaluate(Vector3 point) {
        return (noise.Evaluate(point) + 1.0f) * 0.5f;
    }

    public float newValueFromCoords(Vector3 point) {
        point += Vector3.one * offsetForNewValue;
        offsetForNewValue++;
        return evaluate(point * CommonSettings.smallNoiseScale);
    }
}
