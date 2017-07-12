using UnityEngine;
using System.Collections;

public class Execute_Trigger : MonoBehaviour {
	
	public string objectToFind;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	void OnTriggerStay(Collider collider)
    {
        if (collider.tag == "Player")
        {
			GameObject targetObject;
            targetObject = GameObject.Find(objectToFind);
			if(targetObject != null)
            	targetObject.renderer.enabled = true;
        }
    }
	void OnTriggerExit(Collider collider){
		if (collider.tag == "Player")
        {
			GameObject targetObject;
            targetObject = GameObject.Find(objectToFind);
			if(targetObject != null)
            	targetObject.renderer.enabled = false;
        }
	}
}
