#pragma strict

var timeToDestruct : float = 150.0;
var monk : GameObject;
var ting : AudioSource;
var mainAudio : AudioSource;
var victoryClip : AudioClip;
internal var isDestructing : boolean;

internal var distance : float;
internal var xdiff : float;
internal var zdiff : float;

internal var maxPitch : float = 3.0;
internal var MV : float = 1.0;

function Start () {
isDestructing = false;
monk = GameObject.Find("Monk");

Destroy(gameObject,timeToDestruct);

yield WaitForSeconds(timeToDestruct-.5);
PriestCreateSoundBeeper.alreadyBeeper = false;
}


function Update () {
 
distance = Vector3.Distance(monk.transform.position,transform.position);


if (distance <= audio.maxDistance && !isDestructing) {

if (distance <= 1) {
   mainAudio.Stop();
   ting.Stop();
   audio.PlayOneShot(victoryClip);
   PriestCreateSoundBeeper.alreadyBeeper = false;
   SelfDestruct();
   isDestructing = true;
  }
else {
if (transform.position.x > monk.transform.position.x) 
   xdiff = transform.position.x - monk.transform.position.x;
else 
  xdiff = monk.transform.position.x - transform.position.x;

if (transform.position.z > monk.transform.position.z) 
   zdiff = transform.position.z - monk.transform.position.z;
else 
  zdiff = monk.transform.position.z - transform.position.z;

mainAudio.pitch = maxPitch -(distance/mainAudio.maxDistance);

if (xdiff < zdiff) {
  mainAudio.volume = MV - (xdiff/mainAudio.maxDistance);
  if (xdiff < .5)
   {if (!ting.isPlaying)
      ting.Play();}
  else
  ting.Stop();
  }  
else 
  {mainAudio.volume = MV - (zdiff/mainAudio.maxDistance);  
  
  if (zdiff < .5)
   {if (!ting.isPlaying)
      ting.Play();}
  else
  ting.Stop();
  }
  

   
Debug.Log("X "+xdiff+" z "+zdiff);

//Debug.Log("volume"+ audio.volume);
}
}   
}

function SelfDestruct()
{
yield WaitForSeconds(victoryClip.length);

Destroy(gameObject);
}
