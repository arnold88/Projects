using UnityEngine;
using System.Collections;

public class SavePoint : MonoBehaviour {
	
	public Vector3 respawnPlace;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void OnTriggerEnter(Collider collider){
		if(collider.tag == "Player"){
			Respawn_Player script = collider.GetComponent("Respawn_Player") as Respawn_Player;
			if(script.respawn_location != respawnPlace)
				script.respawn_location = respawnPlace;				
		}
	}
}
