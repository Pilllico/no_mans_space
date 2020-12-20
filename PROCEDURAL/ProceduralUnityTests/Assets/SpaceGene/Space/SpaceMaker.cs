using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

public class SpaceMaker:MonoBehaviour {
    [Range(10, 200)]
    public float LOD = 50;
    public int seed;
    SpaceSettings spaceSettings;
    Vector3 currentCenter;
    NoiseFilter noise;
    List<Vector3> visited;

    private void Start() {
        //INIT
        spaceSettings = GetComponent<CommonSettings>().spaceSettings;
        currentCenter = worldToCell(transform.position);
        noise = new NoiseFilter(seed);
        //MAKING
        makeCell(currentCenter);
        visited = new List<Vector3>();
        visited.Add(currentCenter);
    }

    private void Update() {
        if (worldToCell(transform.position) != currentCenter) {
            //Vector3 direction = Vector3.Normalize(center - currentCenter);
            currentCenter = worldToCell(transform.position);
            if (!visited.Contains(currentCenter)) {
                makeCell(currentCenter * spaceSettings.subdivisionDimmension);
                visited.Add(currentCenter);
            }
        }
    }

    private void makeCell(Vector3 coords) {
        Bounds bounds = new Bounds(coords, Vector3.one * spaceSettings.subdivisionDimmension);
        for (float x = (int)coords.x - spaceSettings.subdivisionDimmension / 2; x < (int)coords.x + spaceSettings.subdivisionDimmension / 2; x+= 2-spaceSettings.density) {
            for (float y = (int)coords.y - spaceSettings.subdivisionDimmension / 2; y < (int)coords.y + spaceSettings.subdivisionDimmension / 2; y += 2 - spaceSettings.density) {
                for (float z = (int)coords.z - spaceSettings.subdivisionDimmension / 2; z < (int)coords.z + spaceSettings.subdivisionDimmension / 2; z += 2 - spaceSettings.density) {
                    //initial position
                    Vector3 pos = new Vector3(x, y, z);
                    //calculating jitter
                    Vector3 jitter = new Vector3(0.5f - noise.evaluate(pos + Vector3.left), 0.5f - noise.evaluate(pos + Vector3.up), 0.5f - noise.evaluate(pos + Vector3.forward));
                    //applying jitter
                    pos += jitter * spaceSettings.jitterMultiplier;
                    //calculating size from pos
                    float value = noise.evaluate(pos * spaceSettings.samplingResolution);
                    //creating solar system if valid
                    if (value <= 0.5 && bounds.Contains(pos)) {
                        SolarSystemMaker ssm = new SolarSystemMaker(pos);
                    }
                }
            }
        }
    }

    private Vector3 worldToCell(Vector3 world) {
        Vector3 recenter = Vector3.one * (spaceSettings.subdivisionDimmension / 2);
        world.x += Mathf.Sign(world.x) * recenter.x;
        world.y += Mathf.Sign(world.y) * recenter.y;
        world.z += Mathf.Sign(world.z) * recenter.z;
        return new Vector3((int)(world.x / spaceSettings.subdivisionDimmension), (int)(world.y / spaceSettings.subdivisionDimmension), (int)(world.z / spaceSettings.subdivisionDimmension));
    }
}
