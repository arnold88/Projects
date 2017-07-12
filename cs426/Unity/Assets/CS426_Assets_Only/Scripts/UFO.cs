using UnityEngine;
using System.Collections;

public class UFO : MonoBehaviour {
	

	
	public GameObject monk;
	public GameObject priest;
	
	public AudioClip start;
	public AudioClip stop;
	
	//private float startTime;
   // private float ellapsedTime;
	
	
	private bool once;
	
	

	
	public void BeamUp()
	{
		audio.Play ();
	}
	
	public void Stop()
	{
	    audio.Stop();	
		audio.PlayOneShot(stop,0.7f);
	}
	
	// Use this for initialization
	void Start () {
	  
		
		
		once = true;
		audio.PlayOneShot(start,1f);
		Invoke ("BeamUp",2);
		
		
		
		
	}
	
	// Update is called once per frame
	void Update () {
	
	
		
		if  ((monk.transform.position.y < 100f) && ( priest.transform.position.y < 100f))
		{
		
		monk.transform.position += Vector3.up*1.5f;
		priest.transform.position += Vector3.up*1.5f;
		
		  	
		}
		else
		{
			if (once) 
			{
			   once = false;
			   Stop ();
			}
			
			
		}
		
		
	}
}
