using UnityEngine;
using System.Collections;

public class Rotate_Trigger : MonoBehaviour {
	
	GameObject platform;
	public bool leftOrRight;
	bool canEnter;
	Quaternion oldRotation, newRotation;
	
	// Use this for initialization
	void Start () {
		platform = GameObject.Find("Rotating Tiles");
	}
	
	// Update is called once per frame
	void Update () {
		//transform.rotation = Quaternion.Slerp(oldRotation, newRotation, Time.deltaTime * 5); 
	}
	
	void OnTriggerEnter(Collider collider){
		if(canEnter){
			if(leftOrRight)
				RotateLeft();
			else
				RotateRight();
			canEnter = false;
		}
		else
			canEnter = true;
	}
	
	void RotateLeft(){
		if (platform.transform.eulerAngles.y < 5 || platform.transform.eulerAngles.y > 355)
		{
			platform.animation.Play("Rotate Left 1-2");
		}
		else if (platform.transform.eulerAngles.y < 275 && platform.transform.eulerAngles.y > 265)
		{
			platform.animation.Play ("Rotate Left 2-3");
		}
		else if (platform.transform.eulerAngles.y < 185 && platform.transform.eulerAngles.y > 175)
		{
			platform.animation.Play ("Rotate Left 3-4");
		}
		else if (platform.transform.eulerAngles.y < 95 && platform.transform.eulerAngles.y > 85)
		{
			platform.animation.Play ("Rotate Left 4-1");
		}
	}
	
	void RotateRight(){
		if (platform.transform.eulerAngles.y < 5 || platform.transform.eulerAngles.y > 355)
		{
			platform.animation.Play("Rotate Right 1-4");
		}
		else if (platform.transform.eulerAngles.y < 275 && platform.transform.eulerAngles.y > 265)
		{
			platform.animation.Play ("Rotate Right 2-1");
		}
		else if (platform.transform.eulerAngles.y < 185 && platform.transform.eulerAngles.y > 175)
		{
			platform.animation.Play ("Rotate Right 3-2");
		}
		else if (platform.transform.eulerAngles.y < 95 && platform.transform.eulerAngles.y > 85)
		{
			platform.animation.Play ("Rotate Right 4-3");
		}
	}
		
	
}
