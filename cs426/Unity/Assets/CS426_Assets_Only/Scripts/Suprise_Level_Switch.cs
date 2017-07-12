using UnityEngine;
using System.Collections;

public class Suprise_Level_Switch : MonoBehaviour {

	public GameObject hLasers, vLasers;
	bool colliding, canRotate, whichPlayer, monkInputSelected, priestInputSelected;
	FPSInputController script;
	float turnAmount;
	Platform_Input_Controller_Custom inputScript;
	
	// Use this for initialization
	void Start () {
		//hLasers = GameObject.Find("Horizontal Lasers");
		monkInputSelected = priestInputSelected = false;
		canRotate = false;
	}
	
	// Update is called once per frame
	void Update () {
		if(colliding == true)
		{
            if(Input.GetButtonDown("Interact")){
                monkInputSelected = true;
			}
			if(Input.GetButtonDown("Interact 2")){
                priestInputSelected = true;
			}
		}
	
	}
	
void OnTriggerStay(Collider collision)
	{

		colliding = true;
		if (collision.collider.tag == "Player")
        {
			if(monkInputSelected && collision.collider.name == "Monk")
			{
				whichPlayer = true; //The Monk is interacting
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
				whichPlayer = false; //The Priest is interacting
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
		}
		
		if(canRotate == true)
		{
			if(whichPlayer)
			{
        		turnAmount = Input.GetAxis("Horizontal");
				if (turnAmount > 0f)
				{
					hLasers.SetActive(true);
					vLasers.SetActive(false);
					animation.Play ("Switch Middle to Right");
					animation.PlayQueued("Switch Right to Middle");
				}
				if (turnAmount < 0f)
				{
					hLasers.SetActive(false);
					vLasers.SetActive(true);
					animation.Play ("Switch Middle to Left");
					animation.PlayQueued("Switch Left to Middle");
				}
			}
			else
			{
				turnAmount = Input.GetAxis("Horizontal 2");	
				if (turnAmount > 0f)
				{
					hLasers.SetActive(true);
					vLasers.SetActive(false);
					animation.Play ("Switch Middle to Right");
					animation.PlayQueued("Switch Right to Middle");
				}
				if (turnAmount < 0f)
				{
					hLasers.SetActive(false);
					vLasers.SetActive(true);
					animation.Play ("Switch Middle to Left");
					animation.PlayQueued("Switch Left to Middle");
				}
			}
		}
		
	}
	
	void OnTriggerExit()
	{
		colliding = false;	
	}
	
	
	
}
