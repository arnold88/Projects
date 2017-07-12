using UnityEngine;
using System.Collections;

public class Laser_Wall_Movement : MonoBehaviour {

	Transform wallLocation;
	public float baseSpeed = .1f;
	public float addedSpeedCap = 20f;
	GameObject monk, priest;
	float addedSpeed, finalSpeed, temp;
	Respawn_Player priestRespawn, monkRespawn;
	
	// Use this for initialization
	void Start () {
		monk = GameObject.Find("Monk");
		priest = GameObject.Find("Priest");
		monkRespawn = monk.GetComponent("Respawn_Player") as Respawn_Player;
		priestRespawn = monk.GetComponent("Respawn_Player") as Respawn_Player;
	
	}
	
	// Update is called once per frame
	void Update () {
		temp = Mathf.Min((monk.transform.position.z - transform.position.z), (priest.transform.position.z - transform.position.z)) ;
		if (temp < 0){
			monkRespawn.respawn_location = new Vector3 (1, 1.5f, 1);
			monkRespawn.respawn_location = new Vector3 (-1, 1.5f, 1);
			gameObject.transform.position = new Vector3 (0,0, -5);
			monkRespawn.Respawn();
			priestRespawn.Respawn();
		}
			
		addedSpeed = temp/addedSpeedCap;
		finalSpeed = baseSpeed + addedSpeed;
		
		transform.position = new Vector3(transform.position.x, transform.position.y,transform.position.z + finalSpeed*Time.deltaTime);	
	}
}
	

