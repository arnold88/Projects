#pragma strict

var soundBeeperPrefab : GameObject;
var avoidSoundBeeper : GameObject;
internal var hit : RaycastHit;
static var alreadyBeeper : boolean;
internal var clone : GameObject;
internal var aclone : GameObject;


function Start () {
alreadyBeeper = false;

}

function Update () {
   
   if (Input.GetMouseButtonDown(0)){
        if (Physics.Raycast(transform.position,transform.forward,hit,200) && !alreadyBeeper){
         alreadyBeeper = true;
         clone = Instantiate(soundBeeperPrefab,hit.point,Quaternion(0,0,0,1));
        
         }
        }
    else if (Input.GetMouseButton(1))
     {
      if (Physics.Raycast(transform.position,transform.forward,hit,200)){
         if (hit.transform.tag == "Lazer Tile") {
         aclone = Instantiate(avoidSoundBeeper,hit.point,Quaternion(0,0,0,1));}
             
     }
     
     }
   }   