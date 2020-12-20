using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetMaker {
    //MESH SETTINGS
    public int resolution = 50;
    ShapeGenerator shapeGenerator;
    MeshFilter[] meshFilters;
    PlanetFace[] planetFaces;
    //PLANET
    PlanetSettings planetSettings;
    int seed;
    NoiseFilter noise;
    Vector3 solarSysCenter;
    float radius;
    float orbit;
    float speed;

    public PlanetMaker(Vector3 solarSysCenter, float orbit) {
        //INIT
        this.planetSettings = GameObject.Find("SpaceMaker").GetComponent<CommonSettings>().planetSettings;
        Vector3 seedPosition = solarSysCenter * orbit * CommonSettings.smallNoiseScale;
        seed = ((int)(seedPosition.x)) | (((int)(seedPosition.y)) << 8) | (((int)(seedPosition.z)) << 16);
        //Debug.Log(seed);
        noise = new NoiseFilter(seed);
        Vector3 position = solarSysCenter + Vector3.left * orbit;
        this.radius = planetSettings.minRadius + noise.newValueFromCoords(position) * planetSettings.radiusMultiplier;
        this.orbit = orbit;
        this.speed = noise.newValueFromCoords(position) * planetSettings.speedMultiplier;
        //MAKING
        GameObject planet = new GameObject("Planet");
        
        initialize(planet);
        generateMesh();

        planet.transform.position = solarSysCenter + Vector3.left * this.orbit;
        planet.transform.localScale = Vector3.one * radius;

        planet.AddComponent(typeof(PlanetBehavior));
        planet.GetComponent<PlanetBehavior>().center = solarSysCenter;
        planet.GetComponent<PlanetBehavior>().radius = this.orbit;
        planet.GetComponent<PlanetBehavior>().speed = speed;
    }

    void initialize(GameObject planet) {
        shapeGenerator = new ShapeGenerator(seed, planetSettings);

        if (meshFilters == null || meshFilters.Length == 0) meshFilters = new MeshFilter[6];
        planetFaces = new PlanetFace[6];

        Vector3[] directions = { Vector3.up, Vector3.down, Vector3.right, Vector3.left, Vector3.forward, Vector3.back };
        for (int i = 0; i < 6; i++) {
            if (meshFilters[i] == null) {
                GameObject meshObj = new GameObject("mesh");
                meshObj.transform.parent = planet.transform;
                meshObj.transform.position = planet.transform.position;

                meshObj.AddComponent<MeshRenderer>().sharedMaterial = new Material(Shader.Find("Standard"));
                meshFilters[i] = meshObj.AddComponent<MeshFilter>();
                meshFilters[i].sharedMesh = new Mesh();
            }

            planetFaces[i] = new PlanetFace(shapeGenerator, meshFilters[i].sharedMesh, resolution, directions[i]);
        }
    }

    void generateMesh() {
        foreach (PlanetFace face in planetFaces) {
            face.constructMesh();
        }
    }


}
