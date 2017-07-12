using UnityEngine;
using System.Collections;

// alternate ending


public class stage_3_completion_check : MonoBehaviour {
	
	Transform pianoA, pianoB, pianoC, pianoD, victoryMusic;
	int state;
	public GameObject bridge;
	public GameObject idol;

	
	
	
	// Use this for initialization
	void Start () {
		pianoA = transform.FindChild("Piano A");
		pianoB = transform.FindChild("Piano B");
		pianoC = transform.FindChild("Piano C");
		pianoD = transform.FindChild("Piano D");
		victoryMusic = transform.FindChild("Fake Victory Sound");
		state = 0;
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
			    
			extend script;
			script = bridge.GetComponent("extend") as extend;
	        script.activate();
			victoryMusic.audio.Play ();
			idol.SetActive(true);
		}
	}
}
		
