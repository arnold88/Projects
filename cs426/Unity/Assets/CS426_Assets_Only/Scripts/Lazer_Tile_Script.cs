using UnityEngine;
using System.Collections;

public class Lazer_Tile_Script : MonoBehaviour {
	
	RaycastHit rh;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if(Physics.Raycast(gameObject.transform.position, gameObject.transform.up, out rh, 30))
			if(rh.collider.tag == "Player")
				{
            		Respawn_Player respawnScript;
            		respawnScript = rh.collider.GetComponent("Respawn_Player") as Respawn_Player;
            		respawnScript.Respawn();
        		}
	
	}
}
