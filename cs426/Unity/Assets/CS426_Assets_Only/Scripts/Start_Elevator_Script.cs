using UnityEngine;
using System.Collections;

public class Start_Elevator_Script : MonoBehaviour {
	
	int numOn;
	bool justStarted;
	
	// Use this for initialization
	void Start () {
		justStarted = true;
	
	}
	
	// Update is called once per frame
	void Update () {
	}
	
	void OnTriggerEnter(){
		if(!justStarted)
			animation.Play ("Start Elevator Up");
		numOn++;
	}
	
	void OnTriggerExit(){
		if(justStarted)
			justStarted = false;
		
		numOn--;
		if(numOn == 0)
			animation.Play ("Start Elevator Down");	
	}
}
