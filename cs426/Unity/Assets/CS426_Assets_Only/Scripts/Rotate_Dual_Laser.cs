using UnityEngine;
using System.Collections;

public class Rotate_Dual_Laser : MonoBehaviour {
	
	public float speed = .1f ;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		transform.RotateAround(transform.position, transform.forward, speed*Time.deltaTime);
	}
}
