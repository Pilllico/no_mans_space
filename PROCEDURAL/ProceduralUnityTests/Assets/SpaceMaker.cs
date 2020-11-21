using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpaceMaker:MonoBehaviour {
    public static float jitterMultiplier = 10;
    public static int spaceCellDimmension = 20;
    public Vector3 center = Vector3.zero;

    private void Start() {
        Bounds bounds = new Bounds(center, Vector3.one * spaceCellDimmension);
        NoiseFilter noise = new NoiseFilter(125321);
        for (int x = (int)center.x - spaceCellDimmension/2; x < (int)center.x + spaceCellDimmension / 2; x++) {
            for (int y = (int)center.y - spaceCellDimmension / 2; y < (int)center.y + spaceCellDimmension / 2; y++) {
                for (int z = (int)center.z - spaceCellDimmension / 2; z < (int)center.z + spaceCellDimmension / 2; z++) {
                    //initial position
                    Vector3 pos = new Vector3(x, y, z);
                    //calculating jitter
                    Vector3 jitter = new Vector3(0.5f - noise.evaluate(pos + Vector3.left), 0.5f - noise.evaluate(pos + Vector3.up), 0.5f - noise.evaluate(pos + Vector3.forward));
                    //applying jitter
                    pos += jitter * jitterMultiplier;
                    //calculating size from pos
                    float size = noise.evaluate(pos);
                    //creating solar system if valid
                    if (size > 0.933 && bounds.Contains(pos)) {
                        SolarSystemMaker ssm = new SolarSystemMaker(pos );
                    }

                }
            }
        }
    }
}
