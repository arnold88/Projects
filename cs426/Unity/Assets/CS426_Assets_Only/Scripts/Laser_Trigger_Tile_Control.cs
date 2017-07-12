using UnityEngine;
using System.Collections;

public class Laser_Trigger_Tile_Control : MonoBehaviour {
	

	public enum Mode {
		Trigger   = 0, // Just broadcast the action on to the target
		Replace   = 1, // replace target with source
		Activate  = 2, // Activate the target GameObject
		Enable    = 3, // Enable a component
		Animate   = 4, // Start animation on target
		Deactivate= 5, // Decativate target GameObject
		Audio     = 6, // Plays and audio clip
		Toggle    = 7, // Activates and deactivates target GameObject
		ToggleAndAudio = 8, //Plays audio and toggles
		ActivateAndAudio = 9 //Activate and plays audio
	}

	/// The action to accomplish
	public Mode action = Mode.Activate;

	/// The game object to affect. If none, the trigger work on this game object
	public Object target;
	public GameObject source;

	public int triggerCount = 1;///
	public bool repeatTrigger;
	public bool activated, usesCams = false;
	public bool useEnters, useExits;
	bool canEnter = true;
	bool canExit = false;
	
	
	// added by arnold , camera switching code
	public Camera trapcam; 
	public Camera maincam;
	
	public void SwitchToCam() {
		
		
		trapcam.camera.enabled=true;
		maincam.camera.enabled=false;
		
		
	}
	public void SwitchBackCam() {
		
		maincam.camera.enabled=true;
		trapcam.camera.enabled=false;
		
		
	}
	
	public void DelayActivate() {
	  
		    Object currentTarget = target != null ? target : gameObject;
		    GameObject targetGameObject = currentTarget as GameObject;
	        targetGameObject.SetActive(true);
	
	}
	
	
	// end camera switching code
	
	public void DoActivateTrigger () {
		triggerCount--;

		if (triggerCount == 0 || repeatTrigger) {
			Object currentTarget = target != null ? target : gameObject;
			Behaviour targetBehaviour = currentTarget as Behaviour;
			GameObject targetGameObject = currentTarget as GameObject;
			if (targetBehaviour != null)
				targetGameObject = targetBehaviour.gameObject;
		
			switch (action) {
				case Mode.Trigger:
					print("DoActivateTrigger");
					break;
				case Mode.Replace:
					if (source != null) {
						Object.Instantiate (source, targetGameObject.transform.position, targetGameObject.transform.rotation);
						DestroyObject (targetGameObject);
					}
					break;
				case Mode.Activate:
					
					activated = true;
		        
				//added by arnold
				if(usesCams){
					SwitchToCam ();
					Invoke("DelayActivate",2);  
					Invoke("SwitchBackCam",5); 
				}
				else
				{
					targetGameObject.SetActive(true);
				}
				
					
					break;
				case Mode.Enable:
					if (targetBehaviour != null)
						targetBehaviour.enabled = true;
					break;	
				case Mode.Animate:
					targetGameObject.animation.Play ();
					break;	
				case Mode.Deactivate:
					targetGameObject.SetActive(false);
					break;
				case Mode.Audio:
					targetGameObject.audio.Play();
					break;
				case Mode.Toggle:
					if(targetGameObject.activeInHierarchy)
						targetGameObject.SetActive(false);				
					else
						targetGameObject.SetActive(true);
					break;
				case Mode.ToggleAndAudio:
					if(targetGameObject.activeInHierarchy)
						targetGameObject.SetActive(false);				
					else
						targetGameObject.SetActive(true);
						audio.Play();
					break;
				case Mode.ActivateAndAudio:
					targetGameObject.SetActive(true);
					audio.Play ();
					break;
			}
		}
	}
	
	
	
	void OnTriggerEnter(Collider collider){
		if (useEnters && canEnter && (collider.tag != "Shout_Sweeper")) 
		{
			DoActivateTrigger();
			triggerCount = 1;
			canExit = true;
			canEnter = false;
		}
		else
			canEnter = true;
	}
	
	void OnTriggerExit(Collider collider){
		if(useExits && canExit && (collider.tag != "Shout_Sweeper"))
		{
			DoActivateTrigger();
			triggerCount = 1;
			canExit = false;
			canEnter = true;
		}
		else
			canExit = true;
	}
	
	

	
	
	
	
	
}


	
