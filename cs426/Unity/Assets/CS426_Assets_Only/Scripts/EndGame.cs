using UnityEngine;
using System.Collections;

public class EndGame : MonoBehaviour {
	
	GameObject mainMusic;
	
	// Use this for initialization
	void Start () {
		mainMusic = GameObject.Find ("Music");
	
	}
	
	// Update is called once per frame
	void OnTriggerEnter(Collider collider){
		if(collider.tag == "Player")
		 mainMusic.audio.Stop();
		 audio.Play ();
		
	}
}
