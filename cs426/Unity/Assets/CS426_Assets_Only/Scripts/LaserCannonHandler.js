#pragma strict

var laserShot : GameObject;

var rate : float;
var delay: float;
internal var nextFire : float;

function Start () {


nextFire = delay;

}

function Update () {

 if(Time.time >  nextFire)
   { var shotClone : GameObject = Instantiate(laserShot,transform.position,transform.rotation);
     gameObject.audio.Play();
     nextFire = rate + Time.time;
     }

}