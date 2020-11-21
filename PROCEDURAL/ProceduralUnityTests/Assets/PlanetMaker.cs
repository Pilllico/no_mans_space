using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetMaker : MonoBehaviour{

    int seed;
    NoiseFilter noise;

    PlanetMaker(int solarSysSeed, int index) {
        noise = new NoiseFilter(solarSysSeed);
        //float size = noise.evaluate();
        //SphereMaker.makeSphere();
    }

}
