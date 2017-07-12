using UnityEngine;
using System.Collections;

public class Change_Tile : MonoBehaviour {

    bool doOnce;

	// Use this for initialization
	void Start () {
        doOnce = true;
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    void OnTriggerEnter(Collider collider)
    {
        if (doOnce && collider.tag == "Player")
        {
            gameObject.audio.Play();
            doOnce = false;
        }
        else
            doOnce = true;
    }
}
