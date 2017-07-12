using UnityEngine;
using System.Collections;

public class Player_Rotate_Laser_fixed : MonoBehaviour {

    bool inputSelected, whichPlayer;
    public bool canRotate, colliding, turnRight, turnLeft;
    FPSInputController script;
    float turnAmount, boundry;
	public float rotateSpeed;
	public float rightBoundry, leftBoundry;
	public bool turnOnce;

	// Use this for initialization
	void Start () {
        canRotate = false;
        inputSelected = false;
		turnLeft = turnRight = false;
		turnOnce = true;
	}
	
	// Update is called once per frame
	void Update () 
	{
        if(colliding == true)
		{
            if(Input.GetButtonDown("Interact")){
				whichPlayer = true; //The Monk is interacting
                inputSelected = true;
			}
			if(Input.GetButtonDown("Interact 2")){
				whichPlayer = false; //The Priest is interacting
                inputSelected = true;
			}
		}
		if (turnOnce && turnRight){
			transform.Rotate(0, rotateSpeed * Time.deltaTime, 0);
			turnOnce = false;
		}
		
		if (turnRight && (transform.eulerAngles.y <= rightBoundry || transform.eulerAngles.y >= leftBoundry)){
			transform.Rotate(0, rotateSpeed * Time.deltaTime, 0);
		}
		else{
			turnRight = false;
		}
		
		if (turnOnce && turnLeft){
			transform.Rotate(0, -rotateSpeed * Time.deltaTime, 0);
			turnOnce = false;
		}
		
		if (turnLeft && (transform.eulerAngles.y >= leftBoundry || transform.eulerAngles.y <= rightBoundry)){
			transform.Rotate(0, -rotateSpeed * Time.deltaTime, 0);
		}
		else{
			turnLeft = false;
		}
		if(transform.eulerAngles.y >= rightBoundry && transform.eulerAngles.y <= leftBoundry){
				turnOnce = true;
		}
			
			
		
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
				collision.collider.audio.volume = 0;
            }

            if (inputSelected && canRotate == true)
            {
                script = collision.collider.GetComponent("FPSInputController") as FPSInputController;
                script.enabled = true;
                canRotate = false;
                inputSelected = false;
				collision.collider.audio.volume = 1;
            }

            if (canRotate == true)
			{
				if(whichPlayer)
				{
                	turnAmount = Input.GetAxis("Horizontal");
					if (turnAmount > 0 && (transform.eulerAngles.y <= rightBoundry || transform.eulerAngles.y >= rightBoundry + 5) && turnLeft == false)
					{
						turnRight = true;						
					}
					if (turnAmount < 0 && (transform.eulerAngles.y >= leftBoundry || transform.eulerAngles.y <= leftBoundry - 5|| transform.eulerAngles.y == 0) && turnRight == false)
					{
						turnLeft = true;
					}
				}
			
				else
				{
					turnAmount = Input.GetAxis("Horizontal 2");
                	if (turnAmount > 0 && (transform.eulerAngles.y <= rightBoundry || transform.eulerAngles.y >= rightBoundry + 5) && turnLeft == false)
					{
						turnRight = true;						
					}
					if (turnAmount < 0 && (transform.eulerAngles.y >= leftBoundry || transform.eulerAngles.y <= leftBoundry - 5|| transform.eulerAngles.y == 0) && turnRight == false)
					{
						turnLeft = true;
					}
				}
			}
			
		 }
     }

    void OnTriggerExit()
    {
        colliding = false;
    }
	
}
