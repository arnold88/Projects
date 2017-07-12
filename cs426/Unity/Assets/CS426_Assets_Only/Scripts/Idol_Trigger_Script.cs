using UnityEngine;
using System.Collections;

public class Idol_Trigger_Script : MonoBehaviour {

	public Transform explosions;
	GameObject victoryMusic;
	
	
	public GameObject UFO;
	public GameObject DestroyGroup;
	
	public GameObject UFOcam_alt;
	public Camera UFOcam;
	public Camera maincam;
	
	
	// Use this for initialization
	void Start () {
		victoryMusic = GameObject.Find("Victory Music");
	}
	
	// Update is called once per frame
	void Update () {
	  
	}
	
	IEnumerator OnTriggerEnter(Collider collider){
		if(collider.tag == "Player"){
			victoryMusic.audio.Stop ();
			explosions.gameObject.SetActive(true);
			yield return new WaitForSeconds(1.1f);
			explosions.gameObject.SetActive(false);
			explosions.gameObject.SetActive(true);
			yield return new WaitForSeconds(1.1f);
			explosions.gameObject.SetActive(false);
			explosions.gameObject.SetActive(true);	
			Invoke ("CaveDisappear",1);
			Invoke ("SwitchToCam",2);
			Invoke ("DelayActivate",3);
			Invoke ("SwtichBackCam",5);
		    Invoke ("load_suprise",7);
		}
	}
	
	
    public void load_suprise()
	{
	     	AsyncOperation async = Application.LoadLevelAsync("Surprise Level");
			async.allowSceneActivation = true;	
		
	}
	
	
	public void SwitchToCam() {
		
		
		UFOcam.camera.enabled=true;
		maincam.camera.enabled=false;
		
		
	}
	public void SwitchBackCam() {
		
		maincam.camera.enabled=true;
		UFOcam.camera.enabled=false;
		UFOcam_alt.SetActive(false);
		
	}
	
	
    public void DelayActivate()
	{
	           
			 
			   
		       UFO.SetActive(true);
	}
	
		
	public void CaveDisappear()
	{
			DestroyGroup.SetActive(false);		
		
	}
}
