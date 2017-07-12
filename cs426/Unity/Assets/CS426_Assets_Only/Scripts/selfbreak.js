#pragma strict
var tile:GameObject;


function Start () {

}

function Update () {

}

function OnTriggerStay( collision : Collider )
{
	
    if(collision.gameObject.tag == "Player")
    {
      Destroy(tile);
              }
} 