using UnityEngine;
using System.Collections;

public class Completion_Check : MonoBehaviour {
	
	public Transform leftComplete, rightComplete;
	GameObject startingLaser;
	Laser_Trigger_Tile_Control script;
	bool oneTime;
	Quaternion resetTransform;
	public Vector3 newMonkRespawnLocation, newPriestRespawnLocation;
	GameObject monk, priest;
	Respawn_Player monkRespawn, priestRespawn;
	
	// Use this for initialization
	void Start () {
		//leftComplete = transform.FindChild("Left Complete");
		//rightComplete = transform.FindChild("Right Complete");
		script = gameObject.GetComponent("Laser_Trigger_Tile_Control") as Laser_Trigger_Tile_Control;
		resetTransform = Quaternion.Euler(0,0,0);
		oneTime = true;
		startingLaser = GameObject.Find("Straight_Laser");
		monk = GameObject.Find("Monk");
		priest = GameObject.Find("Priest");
		monkRespawn = monk.GetComponent("Respawn_Player") as Respawn_Player;
		priestRespawn = priest.GetComponent("Respawn_Player") as Respawn_Player;
	}
	
	// Update is called once per frame
	void Update () {
		if(oneTime && leftComplete.gameObject.activeInHierarchy && rightComplete.gameObject.activeInHierarchy){
			script.DoActivateTrigger();
			startingLaser.transform.rotation = resetTransform;
			oneTime = false;
			monkRespawn.respawn_location = newMonkRespawnLocation;
			priestRespawn.respawn_location = newPriestRespawnLocation;
		}
	}
}
