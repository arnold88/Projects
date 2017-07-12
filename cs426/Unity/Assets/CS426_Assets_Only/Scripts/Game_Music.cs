using UnityEngine;
using System.Collections;

public class Game_Music : MonoBehaviour {
	
	AudioSource theme01, theme02;
	bool whichTheme, doOnce;
	
	// Use this for initialization
	void Start () {
		theme01 = transform.FindChild("Theme 01").gameObject.audio;
		theme02 = transform.FindChild("Theme 02").gameObject.audio;
		whichTheme = true;	
		doOnce = true;
	}
	
	// Update is called once per frame
	void Update () {
		if(!whichTheme){
			if(!theme02.isPlaying && doOnce){
				theme02.Play();
				doOnce = false;
			}
			if(!theme02.isPlaying && !doOnce){
				whichTheme = false;
				doOnce = true;
			}
		}
		if(whichTheme){
			if(!theme01.isPlaying && doOnce){
				theme01.Play();
				doOnce = false;
			}
			if(!theme01.isPlaying && !doOnce){
				whichTheme = false;
				doOnce = true;
			}
			
		}
			
	
	}
}
