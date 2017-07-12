using UnityEngine;
using System.Collections;

public class Reflect : MonoBehaviour {
	
	public RaycastHit rh;
	public bool hitWithLaser;
	LineRenderer Line_Renderer;
	Vector3 newVector, lineRendererEndingPosition;
	public Vector3 inVector, inPosition;
	RaycastHit rh2;
	public Reflect script;
	bool isTrigger, doOnce;
	Laser_Trigger_Tile_Control triggerScript;
	public bool laserEnterAndExit;

	
	
	// Use this for initialization
	void Start () {
		Line_Renderer = gameObject.GetComponent<LineRenderer>();
		doOnce = true;
		isTrigger = false;
	}
	
	// Update is called once per frame
	void Update () {
		if (hitWithLaser){
			Line_Renderer.enabled = true;
			newVector = Vector3.Reflect(inVector, rh.normal);
			Line_Renderer.SetPosition(0, inPosition);
			Line_Renderer.SetPosition(1, 2000*newVector);
			
			if(Physics.Raycast(inPosition, newVector, out rh2, 2000))
			{
				if(rh2.collider.tag == "Mirror"){
					script = rh2.collider.GetComponent("Reflect") as Reflect;
					script.rh = rh2;
					script.hitWithLaser = true;
			    	script.inVector = newVector;
			    	script.inPosition = rh2.point;
			    	//lineRendererEndingPosition = rh2.point;
					//Line_Renderer.SetPosition(1, lineRendererEndingPosition);
				}
				else if(rh2.collider.tag == "Player")
				{
            		Respawn_Player respawnScript;
            		respawnScript = rh2.collider.GetComponent("Respawn_Player") as Respawn_Player;
            		respawnScript.Respawn();
        		}
				else if(rh2.collider.tag == "Laser Trigger")
				{
					triggerScript = rh2.collider.GetComponent("Laser_Trigger_Tile_Control") as Laser_Trigger_Tile_Control;
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
				lineRendererEndingPosition = rh2.point;
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
			hitWithLaser = false;
		}
		else
			Line_Renderer.enabled = false;
	
			
	}
		
	
}