using UnityEngine;
using System.Collections;

public class Demo_Priest_Behavior : MonoBehaviour {
	Transform newSoundPointer;
	public Transform pointer;
	public GameObject shockwave1, shockwave2, shockwave3;
	
	// Use this for initialization
	IEnumerator Start () {
		GameObject temp;
		temp = GameObject.Find("Main Camera");
		Sound_Pointer_Script script = temp.GetComponent<Sound_Pointer_Script>();

		yield return new WaitForSeconds(1);
		newSoundPointer = Instantiate(pointer, new Vector3(0,0.2f,4), Quaternion.identity) as Transform;
		shockwave1.SetActive(true);
		yield return new WaitForSeconds(6);
		newSoundPointer = Instantiate(pointer, new Vector3(2,0.2f,8), Quaternion.identity) as Transform;
		shockwave2.SetActive(true);
		yield return new WaitForSeconds(7.5f);
		newSoundPointer = Instantiate(pointer, new Vector3(4,0.2f,12), Quaternion.identity) as Transform;
		shockwave3.SetActive(true);
	    Invoke ("exitdemo",6);
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	
	void exitdemo()
	{
		Application.LoadLevel(0);
	}
}
