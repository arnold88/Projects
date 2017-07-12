using UnityEngine;
using System.Collections;

public class Door_Close_Script : MonoBehaviour {
	
	Transform idolDoor, victoryMusic;
	GameObject monk, priest, gameMusic;
	bool doOnce = true;
	
	// Use this for initialization
	void Start () {
		idolDoor = transform.FindChild("Idol Room Door");
		victoryMusic = transform.FindChild("Victory Music");
		monk = GameObject.Find("Monk");
		priest = GameObject.Find ("Priest");
		gameMusic = GameObject.Find ("Music");
	}
	
	// Update is called once per frame
	void Update () {
		if(doOnce && monk.transform.position.z >= transform.position.z && priest.transform.position.z >= transform.position.z){
			idolDoor.animation.Play("Idol Door Down");
			doOnce = false;
			gameMusic.gameObject.SetActive(false);
			victoryMusic.audio.Play();
		}
	}
}
