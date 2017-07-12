using UnityEngine;
using System.Collections;

public class Self_Delete : MonoBehaviour {
	
	public float pitchChange, successDistance;
	public float timeToDestroy =  5.0f;
	GameObject monk;
	public AudioSource pointerSound, endingSound;
	bool endFlag;
	
	// Use this for initialization
	void Start () {
		StartCoroutine(MyCoroutine());
		monk = GameObject.Find("Monk");
		endFlag = false;
	}
	
	// Update is called once per frame
	void Update () {
		float distance = Vector3.Distance(monk.transform.position,transform.position);
		if (distance <= audio.maxDistance)
			pointerSound.pitch = (1.0f+pitchChange) - ((distance/audio.maxDistance)*pitchChange);
		if(distance <= successDistance && !endFlag){
			SuccessCoroutine();
		}
		if(endFlag && !endingSound.isPlaying)
			Destroy(gameObject);
			
	}
	
	IEnumerator MyCoroutine(){
		yield return new WaitForSeconds(timeToDestroy);
		Destroy(gameObject);
	}
	
	void SuccessCoroutine(){
		pointerSound.Stop();
		endingSound.Play();
		endFlag = true;
	}
}
