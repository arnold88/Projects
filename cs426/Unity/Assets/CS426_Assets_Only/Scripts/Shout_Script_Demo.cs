using UnityEngine;
using System.Collections;

public class Shout_Script_Demo : MonoBehaviour {
    public GameObject prefab;

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
        if(Input.GetKeyDown("r")){
        	Sweep();
        }
	
	}
    
	void Sweep(){
		GameObject clone;
		clone = (GameObject)Instantiate(prefab, transform.position + transform.forward*2, transform.rotation);
        clone.name = "Shout_Sweeper";
		clone.transform.parent = gameObject.transform;
	}
    
}
