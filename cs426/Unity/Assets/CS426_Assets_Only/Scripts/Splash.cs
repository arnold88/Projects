using UnityEngine;
using System.Collections;

public class Splash : MonoBehaviour {
public float lowPitch = 0.9f;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    void OnTriggerExit(Collider collider){
        if (collider.tag == "Shout_Sweeper")
        {
            Execute_Sweep script;
            script = collider.GetComponent("Execute_Sweep") as Execute_Sweep;
            SplashNoise(script.angle);
        }
    }

    void OnTriggerEnter(Collider collider)
    {
        if (collider.tag == "Player")
        {
            Respawn_Player script;
            script = collider.GetComponent("Respawn_Player") as Respawn_Player;
            script.Respawn();
        }
    }
    
        
    public void SplashNoise(float angle)
    {
        if (angle <= 90 || angle >= 270)
            audio.pitch = 1;
        else
            audio.pitch = lowPitch;
        audio.Play();
    } 
}
