using UnityEngine;
using System.Collections;

public class HammerCollide : MonoBehaviour {
	
	public int damage = 100;
	
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
            /*Respawn_Player script;
            script = collider.GetComponent("Respawn_Player") as Respawn_Player;
            script.Respawn();*/
			
			health script;
            script = collider.GetComponent("health") as health;
            script.otherdamage(damage);
			
        }
    }
}
