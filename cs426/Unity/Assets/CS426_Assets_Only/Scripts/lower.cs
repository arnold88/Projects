using UnityEngine;
using System.Collections;

public class lower : MonoBehaviour {
	
	
	private double y;
	private float temp;
	public double speed;
	
	
	// Use this for initialization
	void Start () {
	
		
	 	y = 5.0;
		temp = (float)y;
		transform.position = new Vector3 (0,temp,0);
		
	}
	
	// Update is called once per frame
	void Update () {
	
		if (y > 0.0)
		{
			  if (speed > 5.0) speed = 5.0;
		      y = y - speed;
			  temp = (float)y;
			  transform.position = new Vector3 (0,temp,0);
			
		}
		else
			audio.Stop();
		
		
	}
}
