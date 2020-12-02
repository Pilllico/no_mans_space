using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetTestTool : MonoBehaviour {
    public PlanetSettings settings;
    public int seed = 1;
    public float radius = 1;

    [HideInInspector]
    public bool settingsFoldout;

    ShapeGenerator shapeGenerator;

    [Range(2,256)]
    public int resolution = 10;

    [SerializeField, HideInInspector]
    MeshFilter[] meshFilters;
    PlanetFace[] planetFaces;

    public void generatePlanet() {
        initialize();
        generateMesh();
    }

    void initialize() {
        shapeGenerator = new ShapeGenerator(seed, settings, radius);

        if(meshFilters == null || meshFilters.Length == 0) meshFilters = new MeshFilter[6];
        planetFaces = new PlanetFace[6];

        Vector3[] directions = { Vector3.up, Vector3.down, Vector3.right, Vector3.left, Vector3.forward, Vector3.back };
        for (int i = 0; i < 6; i++) {
            if (meshFilters[i] == null) {
                GameObject meshObj = new GameObject("mesh");
                meshObj.transform.parent = transform;

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
