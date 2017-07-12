using UnityEngine;
using System.Collections;

public class Respawn_Player : MonoBehaviour {
    public Vector3 respawn_location = new Vector3(1,-4,1); 
	ParticleSystem deathParticles;
	CharacterMotor motor;
	AudioSource respawnSound;
	
	// Use this for initialization
	void Start () {
		deathParticles = transform.FindChild("Particle System").particleSystem;
		motor = gameObject.GetComponent("CharacterMotor") as CharacterMotor;
		respawnSound = transform.FindChild("Respawn Sound").audio;

	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void Respawn()
    {
		StartCoroutine(DelayedRespawn());
		// added by arnold

    }
	
	IEnumerator DelayedRespawn(){
		deathParticles.Play ();
		motor.SetControllable(false);
		respawnSound.Play();
		
		yield return new WaitForSeconds(5);
		
		respawnSound.Stop ();
		deathParticles.Stop ();
		motor.SetControllable(true);
		transform.position = respawn_location;
		transform.eulerAngles = new Vector3(0,0,0);
		health script;
		script = this.GetComponent("health") as health;
		script.other_respawn();
		//FPSInputController ctrl;
		//ctrl = this.GetComponent("FPSInputController") as FPSInputController;
		//ctrl.enabled = true;
		
	}

}
