using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NoiseFilter{

    public NoiseFilter(int seed) {
        this.seed = seed;
        noise = new Noise(seed);
    }

    int seed;
    Noise noise;

    public float evaluate(Vector3 point) {
        return (noise.Evaluate(point) + 1) * 0.5f;
    }
}
