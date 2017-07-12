using UnityEngine;
using System.Collections;

public class Execute_Sweep : MonoBehaviour {
    public Vector3 point;
    public Vector3 axis;
    public int sweep_speed;
    public float angle = 0;

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
        transform.RotateAround(transform.parent.position, transform.parent.up, sweep_speed*Time.deltaTime);
        angle += sweep_speed * Time.deltaTime;
        if (angle >= 360)
            Destroy(gameObject);
	}
}
