using UnityEngine;
using System.Collections;

public class health : MonoBehaviour {
	
	
	public int hp; // health points
	public int full =1000; // full health
	private bool onFire = false; 
	public double timer = 0 ; // Count Timer , leave it at zero
	public int wait = 1; // wait time in seconds, before consecutive damage are dealt (only if standing in fire continously)
	public int damage; // damage points
	public int respawncount;
	
	public GameObject flame;
	
	// Use this for initialization
	void Start () {
		
		full = 1000;
		hp = full;
		onFire = false;
		respawncount=0;
		
	}
	
	// Update is called once per frame
	 void Update () {
		
		  if (hp <= 0)
			{
			respawncount = respawncount + 1;
			Respawn_Player script;
            script = this.GetComponent("Respawn_Player") as Respawn_Player;
            script.Respawn();
			hp = full;
			onFire = false;
			}
		
		if (onFire)
		{      
           hp = hp - damage;
		   
		   
	    }
	}
	
	
	public void firedamage (int x)
	{
		onFire = true;
	    damage = x;
		flame.SetActive(true);
	}
	
	public void water ()
	{
	     onFire = false;	
		 flame.SetActive(false);
	}
	
	public void otherdamage (int x)
	{
	     hp=hp-x;	
	}
	
	
	// for use on other respawn events (hammer, laser, fall below etc.)
	public void other_respawn ()
	{
	    onFire = false;	
		hp = full;
		flame.SetActive(false);
		respawncount=respawncount + 1;
	}
	
	
	
}
