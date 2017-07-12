#pragma strict

var clipUp :AnimationClip;
var clipDown : AnimationClip;
internal var isDown: boolean;
internal var isUp : boolean;
internal var isMoving : boolean;
internal var passenger : Transform;
internal var OperationDelay : float;
internal var NextOperationTime : float;
var liftPlane: GameObject;

function Start () {
OperationDelay = 2.2;
NextOperationTime = 0.0;
isDown = true;
isUp = false;
isMoving = false;

}

function Update () {

   

 
}

function OnTriggerEnter (collider : Collider)
  {//Debug.Log("OnTriggerEnter");
  // First Dynamically parent the player to the lift
  
if (Time.time < NextOperationTime) return;
 if (collider.transform.tag == "Player")
       {//Debug.Log("Parenting");
        passenger = collider.transform;
       passenger.parent = liftPlane.transform;}
  
  
    if(isDown && !isMoving)
        {//print("move up section");
        isMoving = true;
        liftPlane.animation.Play(clipUp.name);
       //yield WaitForSeconds (clipUp.length);
       isDown = false; isUp = true; isMoving = false;
        
       }
       
   else if(isUp && !isMoving)
      {//print("move down section");
       isMoving = true;
       liftPlane.animation.Play(clipDown.name);
       //yield WaitForSeconds (clipDown.length);
       isDown = true; isUp = false; isMoving = false;
  
        }     
    
   }
   
function OnTriggerExit(){
    //Debug.Log("OnTriggerExit");
    // now unparent
   passenger.parent = null;
 NextOperationTime = Time.time + OperationDelay;
 }
   