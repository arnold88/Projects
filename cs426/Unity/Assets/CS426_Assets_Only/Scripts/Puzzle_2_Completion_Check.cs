using UnityEngine;
using System.Collections;

public class Puzzle_2_Completion_Check : MonoBehaviour {
	
	Transform pianoA, pianoB, pianoC, pianoD;
	int state;
	public GameObject UFO;
	public GameObject CaveWallGroup;
	public GameObject Explosion;
	public GameObject UFOcam_alt;
	public Camera UFOcam;
	public Camera maincam;

	
	// Use this for initialization
	void Start () {
		pianoA = transform.FindChild("Piano A");
		pianoB = transform.FindChild("Piano B");
		pianoC = transform.FindChild("Piano C");
		pianoD = transform.FindChild("Piano D");
		state = 0;
	}
	
	public void SwitchToCam() {
		
		
		UFOcam.camera.enabled=true;
		maincam.camera.enabled=false;
		
		
	}
	public void SwitchBackCam() {
		
		maincam.camera.enabled=true;
		UFOcam.camera.enabled=false;
		UFOcam_alt.SetActive(false);
		
	}
	
	
    public void DelayActivate()
	{
	           
			   Explosion.SetActive(true);
			   CaveWallGroup.SetActive(false);	
		       UFO.SetActive(true);
	}
	
	// Update is called once per frame
	void Update () {
		if(state == 0)
			if(pianoA.gameObject.activeInHierarchy)
				state = 1;
			else if(pianoC.gameObject.activeInHierarchy || pianoB.gameObject.activeInHierarchy || pianoD.gameObject.activeInHierarchy)
			{
				pianoA.gameObject.SetActive(false);
				pianoB.gameObject.SetActive(false);
				pianoC.gameObject.SetActive(false);
				pianoD.gameObject.SetActive(false);
				audio.Play();
			}
			
		
		if (state == 1)
			if(pianoD.gameObject.activeInHierarchy)
				state = 2;
			else if(pianoC.gameObject.activeInHierarchy || pianoB.gameObject.activeInHierarchy || !pianoA.gameObject.activeInHierarchy)
			{
				state = 0;
				pianoA.gameObject.SetActive(false);
				pianoB.gameObject.SetActive(false);
				pianoC.gameObject.SetActive(false);
				pianoD.gameObject.SetActive(false);
				audio.Play();
			}
		
		if(state == 2)
			if(pianoB.gameObject.activeInHierarchy)
				state = 3;
			else if(pianoC.gameObject.activeInHierarchy || !pianoD.gameObject.activeInHierarchy || !pianoA.gameObject.activeInHierarchy)
			{
				state = 0;
				pianoA.gameObject.SetActive(false);
				pianoB.gameObject.SetActive(false);
				pianoC.gameObject.SetActive(false);
				pianoD.gameObject.SetActive(false);
				audio.Play();
			}
		
		if(state == 3)
			if(pianoC.gameObject.activeInHierarchy)
				state = 4;
			else if(!pianoB.gameObject.activeInHierarchy || !pianoD.gameObject.activeInHierarchy || !pianoA.gameObject.activeInHierarchy)
			{
				state = 0;
				pianoA.gameObject.SetActive(false);
				pianoB.gameObject.SetActive(false);
				pianoC.gameObject.SetActive(false);
				pianoD.gameObject.SetActive(false);
				audio.Play();
			}
		if(state == 4)
		{
                //victory code
			  
			   
			        SwitchToCam ();
					Invoke("DelayActivate",2);  
					Invoke("SwitchBackCam",7); 
			   
		
			
			
			
		}
	}	
	
	
		
}
