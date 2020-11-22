using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetBehavior : MonoBehaviour{

    public Vector3 center = Vector3.zero;
    public float radius = 0;
    public float speed = 0;


    // Update is called once per frame
    void Update(){
        if(speed != 0) transform.RotateAround(center, Vector3.up, speed);
    }
}
