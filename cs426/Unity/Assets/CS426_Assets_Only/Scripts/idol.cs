using UnityEngine;
using System.Collections;

public class idol : MonoBehaviour {
	
    public bool monk_entered;
	public bool priest_entered;
	public GameObject door;
	
	public GameObject destroygroup;
	
	public GameObject UFO;
	
	public GameObject Explosion;
	public GameObject UFOcam_alt;
	public Camera UFOcam;
	public Camera maincam;
	
	
	
	// Use this for initialization
	void Start () {
	
		monk_entered = false;
		priest_entered = false;	
	}
	
	// Update is called once per frame
	void Update () {
		
		if ( monk_entered && priest_entered )
		{
			door.SetActive(true);
			Invoke ("DelayActivate",2);
			Invoke ("DelayUFO",5);
            			
			
			
		}
		
	}
	
	
	void OnTriggerEnter (Collider collider)
	{
	    if (collider.name == "Monk")
		{
			monk_entered = true;
		}
		
		
	      if (collider.name == "Priest")
		{
			priest_entered = true;
		}
	}
	
	
	public void SwitchToCam() {
		
		
		//UFOcam.camera.enabled=true;
		//maincam.camera.enabled=false;
		
		
	}
	public void SwitchBackCam() {
		
		maincam.camera.enabled=true;
		//UFOcam.camera.enabled=false;
		UFOcam_alt.SetActive(false);
		
	}
	
	
    public void DelayActivate()
	{
	           
			   Explosion.SetActive(true);
			   destroygroup.SetActive(false);	
		       
	}
	
	public void DelayUFO()
	{
	       UFO.SetActive(true);	
	}
	
}
