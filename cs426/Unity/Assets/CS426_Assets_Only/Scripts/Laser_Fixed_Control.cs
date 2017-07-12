using UnityEngine;
using System.Collections;

public class Laser_Fixed_Control : MonoBehaviour {
	
	bool colliding, canRotate, whichPlayer, monkInputSelected, priestInputSelected, firstTime, rightOrLeft;
	FPSInputController script;
	float turnAmount;
	public string M2R, R2M, M2L, L2M;
	Platform_Input_Controller_Custom inputScript;

	
	// Use this for initialization
	void Start () {
		monkInputSelected = priestInputSelected = false;
		canRotate = false;
		firstTime = true;
	}
	
	// Update is called once per frame
	void Update () {
		if(colliding == true)
		{
            if(Input.GetButtonDown("Interact")){
				//whichPlayer = true; //The Monk is interacting
                monkInputSelected = true;
			}
			if(Input.GetButtonDown("Interact 2")){
				//whichPlayer = false; //The Priest is interacting
                priestInputSelected = true;
			}
		}
	
	}
	
	void OnTriggerStay(Collider collision)
	{
		colliding = true;
		if(monkInputSelected && collision.collider.name == "Monk")
		{	
			whichPlayer = true;
	    	if (canRotate == false)
	       	{
	        	inputScript = collision.collider.GetComponent("Platform_Input_Controller_Custom") as Platform_Input_Controller_Custom;
	            inputScript.enabled = false;
	            canRotate = true;
				collision.collider.audio.volume = 0;
	        }

           	else
            {
	        	inputScript = collision.collider.GetComponent("Platform_Input_Controller_Custom") as Platform_Input_Controller_Custom;
	            inputScript.enabled = true;
	            canRotate = false;
				collision.collider.audio.volume = 1;
            }
			monkInputSelected = false;
		}
			
		if(priestInputSelected && collision.collider.name == "Priest")
		{
			whichPlayer = false;
	    	if (canRotate == false)
	        {
	        	script = collision.collider.GetComponent("FPSInputController") as FPSInputController;
	            script.enabled = false;
	            canRotate = true;
				collision.collider.audio.volume = 0;
	        }

            else
            {
	            script = collision.collider.GetComponent("FPSInputController") as FPSInputController;
	        	script.enabled = true;
	            canRotate = false;
				collision.collider.audio.volume = 1;
            }
			priestInputSelected = false;
		}
		
		if(canRotate == true)
		{
			if(whichPlayer)
			{
        		turnAmount = Input.GetAxis("Horizontal");
				if (turnAmount > 0f)
				{
					if(firstTime)
					{
						animation.Play (M2R);
						firstTime = false;
						rightOrLeft = true;
					}
					else if(!rightOrLeft && !animation.isPlaying){
						animation.Play (L2M);
						animation.PlayQueued(M2R);
						rightOrLeft = true;
					}
				}
				if (turnAmount < 0f)
				{
					if(firstTime)
					{
						animation.Play (M2L);
						firstTime = false;
						rightOrLeft = false;
					}
					else if(rightOrLeft && !animation.isPlaying){
						animation.Play (R2M);
						animation.PlayQueued(M2L);
						rightOrLeft = false;
					}
				}
			}
			else{
				turnAmount = Input.GetAxis("Horizontal 2");
				if (turnAmount > 0f)
				{
					if(firstTime)
					{
						animation.Play (M2R);
						firstTime = false;
						rightOrLeft = true;
					}
					else if(!rightOrLeft && !animation.isPlaying){
						animation.Play (L2M);
						animation.PlayQueued(M2R);
						rightOrLeft = true;
					}
				}
				if (turnAmount < 0f)
				{
					if(firstTime)
					{
						animation.Play (M2L);
						firstTime = false;
						rightOrLeft = false;
					}
					else if(rightOrLeft && !animation.isPlaying){
						animation.Play (R2M);
						animation.PlayQueued(M2L);
						rightOrLeft = false;
					}
				}
			}
		}
	}
	
	void OnTriggerExit(){
		colliding = false;
	}
}
