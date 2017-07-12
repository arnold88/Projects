using UnityEngine;
using System.Collections;

public class Footsteps : MonoBehaviour {

    float hRunSpeed, vRunSpeed, ourRunSpeed;
    public string horizontalAxis, verticalAxis;

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
        hRunSpeed = Input.GetAxis(horizontalAxis);
        vRunSpeed = Input.GetAxis(verticalAxis);
        if (hRunSpeed != 0 || vRunSpeed != 0)
        {
            if (Mathf.Abs(hRunSpeed) >= Mathf.Abs(vRunSpeed))
                ourRunSpeed = Mathf.Abs(hRunSpeed);
            else
                ourRunSpeed = Mathf.Abs(vRunSpeed);
            if (!gameObject.audio.isPlaying)
            {
                gameObject.audio.Play();
            }
            gameObject.audio.pitch = 1 + ourRunSpeed*0.2f;
        }
        else
            if (gameObject.audio.isPlaying)
                gameObject.audio.Stop();
            
	}
}
