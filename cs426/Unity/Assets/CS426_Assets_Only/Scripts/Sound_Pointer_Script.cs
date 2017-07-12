using UnityEngine;
using System.Collections;

public class Sound_Pointer_Script : MonoBehaviour {
	
	RaycastHit rh;
	Ray ray;
	public Transform gotoPing, avoidPing;
	Transform newSoundPointer, oldSoundPointer;

	
	// Use this for initialization
	void Start () {	

		oldSoundPointer = null;
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown("delete")){
        	EmitSoundSweeper();
		}
		
		if(Input.GetKeyDown("end")){
			EmitWarningPing();
		}
    }
	
	public void EmitSoundSweeper(){
		ray = camera.ViewportPointToRay(new Vector3(0.5F, 0.5F, 0));
        if (Physics.Raycast(ray, out rh))
		{
			oldSoundPointer = newSoundPointer;
            newSoundPointer = Instantiate(gotoPing, rh.point, Quaternion.identity) as Transform;
			if(oldSoundPointer)
				Destroy(oldSoundPointer.gameObject);
		}
        else
            print("I'm looking at nothing!");	
	}
	
	public void EmitWarningPing(){
		ray = camera.ViewportPointToRay(new Vector3(0.5F, 0.5F, 0));
        if (Physics.Raycast(ray, out rh))
		{
			if(rh.collider.tag == "Laser Tile"){
				Transform temp;
				if (rh.transform.parent.name == "Lazer_Tile"){
					if(rh.transform.FindChild("Avoid Ping") == null){
						temp = (Transform)Instantiate(avoidPing, rh.transform.parent.transform.position, Quaternion.identity);
						temp.parent = rh.collider.transform.parent.transform;
						temp.gameObject.name = "Avoid Ping";
					}
				}
				else{
					if(rh.transform.FindChild("Avoid Ping") == null){
						temp = (Transform)Instantiate(avoidPing, rh.transform.position, Quaternion.identity);
						temp.parent = rh.collider.transform;
						temp.gameObject.name = "Avoid Ping";
					}
				}
			}
				
			
		}
	}
}
