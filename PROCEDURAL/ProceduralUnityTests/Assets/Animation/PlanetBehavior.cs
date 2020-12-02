using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetBehavior : MonoBehaviour{

    public Vector3 center = Vector3.zero;
    public float radius = 0;
    public float speed = 0;

    private void Start() {
        //Orbit planet relative to game time
        if (speed != 0) transform.RotateAround(center, Vector3.up, speed * (Time.frameCount + 10000)); //Added 10000 to simulate time already passing when game is launched.
    }

    void Update(){
        if(speed != 0) transform.RotateAround(center, Vector3.up, speed);
    }
}
