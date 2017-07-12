using UnityEngine;
using System.Collections;

public class Shout_Script : MonoBehaviour {
    public GameObject prefab;
	
	Transform newSoundPointer;
	bool pointerActive;
	GameObject clone;
	
	// Use this for initialization
	void Start () {
		pointerActive = false;
	}
	
	// Update is called once per frame
	void Update () {
        if(Input.GetKeyDown("r") && pointerActive == false){
        	Sweep();
        }
		if(!clone)
			pointerActive = false;	
	}
    
	public void Sweep(){
		clone = (GameObject)Instantiate(prefab, transform.position + transform.forward*2, transform.rotation);
        clone.name = "Shout_Sweeper";
		clone.transform.parent = gameObject.transform;
		pointerActive = true;
	}
    
}
