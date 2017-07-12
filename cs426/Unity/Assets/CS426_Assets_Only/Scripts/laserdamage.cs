using UnityEngine;
using System.Collections;

public class laserdamage : MonoBehaviour {
	
	public int damage = 250;
	
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
		  if (damage <= 0)
			{
		       
				
			   Respawn_Player script1;
               script1 = collider.GetComponent("Respawn_Player") as Respawn_Player;
               script1.Respawn();
            
			}
		  else
			{
				
			health script;
            script = collider.GetComponent("health") as health;
            script.otherdamage(damage);
				
			}
        }
    }
	
}
