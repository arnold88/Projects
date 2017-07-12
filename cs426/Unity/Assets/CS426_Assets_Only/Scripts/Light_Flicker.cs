using UnityEngine;
using System.Collections;

public class Light_Flicker : MonoBehaviour {
	
	public float flickerSpeed;
	
	// Use this for initialization
	void Start () {
		StartCoroutine (Flicker());
	
	}
	
	// Update is called once per frame
	IEnumerator Flicker () {
		while(true){
			light.enabled = true;
			yield return new WaitForSeconds(flickerSpeed);
			light.enabled = false;
			yield return new WaitForSeconds(flickerSpeed);
		
		}
	
	}
}
