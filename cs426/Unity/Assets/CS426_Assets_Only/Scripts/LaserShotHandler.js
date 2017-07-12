#pragma strict

var velocity :float;

function Start () {

Destroy(gameObject,3);
}

function Update () {

transform.Translate(0,0,velocity*Time.deltaTime);


}


function OnCollisionEnter(other: Collision)
{
  if (other.transform.tag == 'Player')
      other.transform.SendMessage('Respawn',SendMessageOptions.DontRequireReceiver);
      
  Destroy(gameObject);
  }