using UnityEngine;
using System.Collections;

public class Beep_Demo : MonoBehaviour {
    public float lowPitch = 0.9f;
	Transform tileRendering, changeTile;
	public Color changeColor;
	
	// Use this for initialization
	void Start () {
		tileRendering = transform.parent.transform.FindChild("Tile_Cube");
		changeTile = transform.parent.transform.FindChild("Change Trigger");
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    void OnTriggerExit(Collider collider){
        if (collider.tag == "Shout_Sweeper")
        {
			tileRendering.renderer.material.color = changeColor;
            Execute_Sweep script;
            script = collider.GetComponent("Execute_Sweep") as Execute_Sweep;
            BeepDammit(script.angle);	
        }
    }

    void OnTriggerEnter(Collider collider)
    {
        if (collider.tag == "Player")
        {
        	//Respawn_Player script;
            //script = collider.GetComponent("Respawn_Player") as Respawn_Player;
            //script.Respawn();
			tileRendering.gameObject.SetActive(false);
			changeTile.gameObject.SetActive(false);	
        }
    }
    
        
    public void BeepDammit(float angle)
    {
        if (angle <= 90 || angle >= 270)
            audio.pitch = 1;
        else
            audio.pitch = lowPitch;
        audio.Play();
    } 
}
