using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetMaker {
    public int resolution = 50;
    ShapeGenerator shapeGenerator;
    MeshFilter[] meshFilters;
    PlanetFace[] planetFaces;
    int seed;
    NoiseFilter noise;
    Vector3 solarSysCenter;
    PlanetSettings settings;
    float radius;
    float orbitRadius;
    float speed;

    public PlanetMaker(Vector3 solarSysCenter, int index, float sunRadius) {

        this.settings = GameObject.Find("SpaceMaker").GetComponent<CommonSettings>().planetSettings;
        this.solarSysCenter = solarSysCenter;
        Vector3 seedPosition = solarSysCenter * ((float)index * 10.0f);
        seed = ((int)(seedPosition.x)) | (((int)(seedPosition.y)) << 8) | (((int)(seedPosition.z)) << 16);
        Debug.Log(seed);
        noise = new NoiseFilter(seed);
        radius = noise.evaluate(solarSysCenter* 165.0f * (float)index) / 20.0f;
        orbitRadius = (noise.evaluate(solarSysCenter * 17.0f * (float)index) + index) / 10.0f + sunRadius * 2.0f;
        speed = noise.evaluate(solarSysCenter * (float)(index)) / 5.0f;

        GameObject planet = new GameObject("Planet");
        
        initialize(planet);
        generateMesh();

        planet.transform.position = solarSysCenter + Vector3.left * orbitRadius;
        planet.transform.localScale = Vector3.one * radius;

        planet.AddComponent(typeof(PlanetBehavior));
        planet.GetComponent<PlanetBehavior>().center = solarSysCenter;
        planet.GetComponent<PlanetBehavior>().radius = orbitRadius;
        planet.GetComponent<PlanetBehavior>().speed = speed;
    }

    void initialize(GameObject planet) {
        shapeGenerator = new ShapeGenerator(seed, settings);

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
