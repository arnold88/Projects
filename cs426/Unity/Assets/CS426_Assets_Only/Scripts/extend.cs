using UnityEngine;
using System.Collections;

public class extend : MonoBehaviour {
	
	
	private double y;

	private bool flag;
	
	
	// Use this for initialization
	void Start () {
	
		flag = false;

	}
	
	// Update is called once per frame
	void Update () {
	
		if ( flag && (transform.position.z > 78.0f) )
		{
		
			  transform.position -= Vector3.forward * 0.1f;
			
		}
		else
		{
			audio.Stop();
			flag = false;
		}
	}
	
	
	
	public void activate()
	{
		
	   flag = true;	
	}
}
