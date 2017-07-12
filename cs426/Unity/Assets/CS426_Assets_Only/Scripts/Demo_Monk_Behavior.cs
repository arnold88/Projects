using UnityEngine;
using System.Collections;

public class Demo_Monk_Behavior : MonoBehaviour {

	IEnumerator Start () {
		Shout_Script script = gameObject.GetComponent<Shout_Script>();
		
		yield return new WaitForSeconds(1.5f);
		script.Sweep();
		yield return new WaitForSeconds(6);
		script.Sweep();
		yield return new WaitForSeconds(6);
		script.Sweep();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
