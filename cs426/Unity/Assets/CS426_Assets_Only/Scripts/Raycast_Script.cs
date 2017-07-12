using UnityEngine;
using System.Collections;

public class Raycast_Script : MonoBehaviour {
	
	public Reflect script;
	public LineRenderer Line_Renderer;
	Vector3 reset = new Vector3(0,0,2000);
	RaycastHit rh;
	Vector3 lineRendererEndingPosition;
	bool isTrigger;
	bool doOnce;
	Laser_Trigger_Tile_Control triggerScript;
	public  bool laserEnterAndExit;
	
	
	// Use this for initialization
	void Start () {
		Line_Renderer = gameObject.GetComponent<LineRenderer>();
		isTrigger = false;
		doOnce = true;
	
	}
	
	// Update is called once per frame
	void Update () {
		Line_Renderer.SetPosition(1,reset);
		if(Physics.Raycast(gameObject.transform.position, gameObject.transform.forward, out rh, 2000))
		{
			if(rh.collider.tag == "Mirror"){
				script = rh.collider.GetComponent("Reflect") as Reflect;
				script.rh = rh;
				script.hitWithLaser = true;
			    script.inVector = gameObject.transform.forward;
			    script.inPosition = rh.point;
			    //lineRendererEndingPosition = new Vector3(0,0, rh.distance);
				//Line_Renderer.SetPosition(1, lineRendererEndingPosition);
		    }
			else if(rh.collider.tag == "Player")
			{
            	Respawn_Player respawnScript;
            	respawnScript = rh.collider.GetComponent("Respawn_Player") as Respawn_Player;
            	respawnScript.Respawn();
        	}
			else if(rh.collider.tag == "Laser Trigger")
			{
				triggerScript = rh.collider.GetComponent("Laser_Trigger_Tile_Control") as Laser_Trigger_Tile_Control;
				if(doOnce)
				{
					triggerScript.DoActivateTrigger();
					triggerScript.triggerCount = 1;
					isTrigger = true;
					doOnce = false;
				}
			}
			else
			{
				if(laserEnterAndExit && isTrigger)
				{
					triggerScript.DoActivateTrigger();
					triggerScript.triggerCount = 1;
				}
				isTrigger = false;
				doOnce = true;
			}
			lineRendererEndingPosition = new Vector3(0,0, rh.distance);
			Line_Renderer.SetPosition(1, lineRendererEndingPosition);
		}
		else
		{
			if(laserEnterAndExit && isTrigger)
				{
					triggerScript.DoActivateTrigger();
					triggerScript.triggerCount = 1;
				}	
			isTrigger = false;
			doOnce = true;
		}
				
	}
		
}
