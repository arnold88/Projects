using UnityEngine;
using System.Collections;

public class water_heal : MonoBehaviour {
	
	
	public bool heal = false;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		
	}
	
	
	void OnTriggerEnter(Collider collider)
    {
        if (collider.tag == "Player")
        {
		    heal = true;	
            health script;
            script = collider.GetComponent("health") as health;
            script.water();
			audio.Play();
        }
    }
	
	
}
