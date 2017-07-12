using UnityEngine;
using System.Collections;

public class Player_Rotate_Object : MonoBehaviour {

    bool inputSelected;
    bool canRotate, colliding;
    FPSInputController script;
    float turnAmount;

	// Use this for initialization
	void Start () {
        canRotate = false;
        inputSelected = false;
	
	}
	
	// Update is called once per frame
	void Update () {
        if(colliding == true)
            if(Input.GetButtonDown("Interact"))
                inputSelected = true;
    }

    void OnTriggerStay(Collider collision)
    {
        colliding = true;
        if (collision.collider.tag == "Player")
        {
            if (inputSelected && canRotate == false)
            {
                script = collision.collider.GetComponent("FPSInputController") as FPSInputController;
                script.enabled = false;
                canRotate = true;
                inputSelected = false;
            }

            if (inputSelected && canRotate == true)
            {
                script = collision.collider.GetComponent("FPSInputController") as FPSInputController;
                script.enabled = true;
                canRotate = false;
                inputSelected = false;
            }

            if (canRotate == true)
            {
                turnAmount = Input.GetAxis("Horizontal");
                transform.RotateAroundLocal(collision.collider.transform.up, turnAmount * Time.deltaTime);
            }
        }
     }

    void OnTriggerExit()
    {
        colliding = false;
    }

}
