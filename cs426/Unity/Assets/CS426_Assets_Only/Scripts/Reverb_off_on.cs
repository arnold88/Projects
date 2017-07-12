using UnityEngine;
using System.Collections;

public class Reverb_off_on : MonoBehaviour {
	bool doOnce;
	Transform reverb;
	
	// Use this for initialization
	void Start () {
		doOnce = true;
		reverb = transform.FindChild("Reverb Zone");
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown("l") && reverb.gameObject.activeInHierarchy && doOnce){
			reverb.gameObject.SetActive(false);
			doOnce = false;
		}

		
		if(Input.GetKeyDown("l") && !reverb.gameObject.activeInHierarchy && doOnce){
			reverb.gameObject.SetActive(true);
			doOnce = false;
		}
		
		if(Input.GetKeyUp("l") && !doOnce)
			doOnce = true;
	}
}
