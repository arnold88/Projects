#pragma strict

var idleAnimation : AnimationClip;
var walkAnimation : AnimationClip;
var runAnimation : AnimationClip;
var jumpPoseAnimation : AnimationClip;

internal var velocity : Vector3;
internal var grounded : boolean;

internal var jumping = false;
internal var isMoving = false;

internal var jumpingReachedApex : boolean = false;

function Start () {

	animation.Stop();

	// slow the jump animation pose so we can leave it looping
	animation[jumpPoseAnimation.name].speed = 0.01;

}


function Update () {

		// is  the character jumping?
		if(jumping) {
			
			if(!jumpingReachedApex) {
 				// go into jump
				animation.CrossFade(jumpPoseAnimation.name);
			} else {
 				// fall into walk
				animation.CrossFade(walkAnimation.name);				
			}
		}

	else 
	{
		// Are we moving the character?
		if (isMoving) {
			animation.CrossFade (runAnimation.name);
		}
		// Go back to idle when not moving
		else {
		//print ("idling");
			animation.CrossFade (idleAnimation.name, 0.5);
		}
	}
}

// Ch. Motor sends grounded info every frame
function GetGrounded (groundedX : boolean) {

	grounded = groundedX;
	
	if (grounded && velocity.z != 0.0) isMoving = true;
	else isMoving = false;
}

// Ch. Motor sends velocity info every frame
function GetVelocity (velocityX : Vector3) {

	velocity = velocityX;
	
	// he's on his way down
	if (jumping && velocity.y <= 0.0) {
		jumpingReachedApex = true;
	}
	//just started or just stopped jumping
	if (jumping && grounded) {
		jumpingReachedApex = false;
	}
}




// Ch. Motor sends notification of jump event
function OnJump () {

	jumping = true;
	//animation.CrossFade(jumpPoseAnimation.name);
}


// Ch. Motor sends notification of landing event
function OnLand () {

	jumping = false;
	jumpingReachedApex = false;

}
