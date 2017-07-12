using UnityEngine;
using System.Collections;

public class Monk_Camera_Follow : MonoBehaviour {
	
	GameObject monk;
	
	// Use this for initialization
	void Start () {
		monk = GameObject.Find("Monk");

	}
	
	// Update is called once per frame
	void Update () {
		transform.position = new Vector3 (monk.transform.position.x, gameObject.transform.position.y, monk.transform.position.z);
	}
}
