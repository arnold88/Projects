using UnityEngine;
using System.Collections;

public class Elevator : MonoBehaviour {
	public GameObject complete;
	bool state;
	public string upAnimation, downAnimation;
	
	// Use this for initialization
	void Start () {
		state = false;
		
	}
	
	// Update is called once per frame
	void Update () 
	{
		
		
	    if(complete.activeInHierarchy && state == false )
		{
			animation.Play(upAnimation);
			state = true;
			
		}
		
		if(!complete.activeInHierarchy && state == true)
		{
			animation.Play (downAnimation);
			state = false;
			
			
	    }
	}
	


}
	


