using UnityEngine;
using System.Collections;

public class Cheating_Script : MonoBehaviour {
	
	GameObject monk, priest;
	public GameObject puzzle2Enable, puzzle3Enable;
	Respawn_Player monkScript, priestScript;
	FPSInputController priestcontrol;
	Platform_Input_Controller_Custom monkcontrol;
	
	// Use this for initialization
	void Start () {
		monk = GameObject.Find("Monk");
		priest = GameObject.Find ("Priest");
		monkScript = monk.GetComponent("Respawn_Player") as Respawn_Player;
		priestScript = priest.GetComponent("Respawn_Player") as Respawn_Player;
		//puzzle2Enable = GameObject.Find ("Created on Completion(Puzzle 1)");
		//puzzle3Enable = GameObject.Find ("Created on Completion(UIC Puzzle)");
		monkcontrol = monk.GetComponent("Platform_Input_Controller_Custom") as Platform_Input_Controller_Custom;
		priestcontrol = priest.GetComponent("FPSInputController") as FPSInputController;
		
	}
	
	// Update is called once per frame
	void Update () {
	
		
		
		if(Input.GetKeyDown("7"))
		{
			monkScript.respawn_location = new Vector3(0, 1.3f, -44);
			priestScript.respawn_location = new Vector3(1, 1.3f, -44);
			monkScript.Respawn();
			priestScript.Respawn();
			puzzle2Enable.SetActive(false);
			puzzle3Enable.SetActive(false);	
			
			monkcontrol.enabled = true;
			priestcontrol.enabled = true;
			
			
			
			
		}
		
		
		if(Input.GetKeyDown("8"))
		{
			monkScript.respawn_location = new Vector3(1, 1.3f, 3);
			priestScript.respawn_location = new Vector3(-1, 1.3f, 3);
			monkScript.Respawn();
			priestScript.Respawn();
			puzzle2Enable.SetActive(true);
			puzzle3Enable.SetActive(false);	
			
				monkcontrol.enabled = true;
			priestcontrol.enabled = true;
			
			
		}
		
		if(Input.GetKeyDown("9"))
		{
			monkScript.respawn_location = new Vector3(1, 4.3f, 35);
			priestScript.respawn_location = new Vector3(-1, 4.3f, 35);
			monkScript.Respawn();
			priestScript.Respawn();
			puzzle2Enable.SetActive(true);
			puzzle3Enable.SetActive(true);	
			
			monkcontrol.enabled = true;
			priestcontrol.enabled = true;
			
		}	
		
		if(Input.GetKeyDown("0"))
		{
			monkScript.respawn_location = new Vector3(1, 4.3f, 84);
			priestScript.respawn_location = new Vector3(-1, 4.3f, 84);
			monkScript.Respawn();
			priestScript.Respawn();
			monkcontrol.enabled = true;
			priestcontrol.enabled = true;
	}
}
	
}