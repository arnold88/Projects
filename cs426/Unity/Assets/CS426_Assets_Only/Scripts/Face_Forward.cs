using UnityEngine;
using System.Collections;

public class Face_Forward : MonoBehaviour {
	
	
	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		if( transform.eulerAngles != new Vector3(0,0,0))
			transform.eulerAngles = new Vector3(0,0,0);
	}
}
