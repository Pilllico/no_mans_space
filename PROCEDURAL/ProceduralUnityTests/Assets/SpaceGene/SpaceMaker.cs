using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

//[ExecuteInEditMode]
public class SpaceMaker:MonoBehaviour {
    public float samplingResolution = 0.5f;
    public float density = 0.1f;
    public float jitterMultiplier = 10;
    public int spaceCellDimmension = 20;
    Vector3 currentCenter;
    NoiseFilter noise;
    List<Vector3> visited;

    private void Start() {
        currentCenter = transform.position;
        noise = new NoiseFilter(125321);
        makeCell(currentCenter);
        visited = new List<Vector3>();
        visited.Add(currentCenter);
    }

    private void Update() {
        if (worldToCell(transform.position) != currentCenter) {
            //Vector3 direction = Vector3.Normalize(center - currentCenter);
            currentCenter = worldToCell(transform.position);
            if (!visited.Contains(currentCenter)) {
                makeCell(currentCenter * spaceCellDimmension);
                visited.Add(currentCenter);
            }
        }
    }

    private void makeCell(Vector3 coords) {
        Bounds bounds = new Bounds(coords, Vector3.one * spaceCellDimmension);
        for (int x = (int)coords.x - spaceCellDimmension / 2; x < (int)coords.x + spaceCellDimmension / 2; x++) {
            for (int y = (int)coords.y - spaceCellDimmension / 2; y < (int)coords.y + spaceCellDimmension / 2; y++) {
                for (int z = (int)coords.z - spaceCellDimmension / 2; z < (int)coords.z + spaceCellDimmension / 2; z++) {
                    //initial position
                    Vector3 pos = new Vector3(x, y, z);
                    //calculating jitter
                    Vector3 jitter = new Vector3(0.5f - noise.evaluate(pos + Vector3.left), 0.5f - noise.evaluate(pos + Vector3.up), 0.5f - noise.evaluate(pos + Vector3.forward));
                    //applying jitter
                    pos += jitter * jitterMultiplier;
                    //calculating size from pos
                    float value = noise.evaluate(pos * samplingResolution);
                    //creating solar system if valid
                    if (value <= density && bounds.Contains(pos)) {
                        SolarSystemMaker ssm = new SolarSystemMaker(pos);
                    }
                }
            }
        }
    }

    private Vector3 worldToCell(Vector3 world) {
        Vector3 recenter = Vector3.one * (spaceCellDimmension / 2);
        world.x += Mathf.Sign(world.x) * recenter.x;
        world.y += Mathf.Sign(world.y) * recenter.y;
        world.z += Mathf.Sign(world.z) * recenter.z;
        return new Vector3((int)(world.x / spaceCellDimmension), (int)(world.y / spaceCellDimmension), (int)(world.z / spaceCellDimmension));
    }
}
