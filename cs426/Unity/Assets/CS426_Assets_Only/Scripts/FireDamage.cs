using UnityEngine;
using System.Collections;

public class FireDamage : MonoBehaviour {
	
	
	public int damage = 1; // deduction
	
	
	
	void Start () {
		
	}
	
	
	void Update () {
	
		
	   
	}
	
	// For dragon flame
	
	 void OnParticleCollision(GameObject collider) {
        
        if (collider.tag == "Player") 
		{
 
			health script;
			script = collider.GetComponent("health") as health;
			script.firedamage(damage);
				
        }
	}

    
}
