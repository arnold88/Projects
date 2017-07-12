#pragma strict

internal var isDamage : boolean;

function Start () {
isDamage = true;
}

function Update () {

}

function DamageTrue()
{
isDamage=true;
}

function DamageFalse()
{
isDamage=false;
}

function OnTriggerEnter (other : Collider)
{
if (other.transform.tag == "Player" && isDamage)
   {other.transform.SendMessage("Respawn",SendMessageOptions.DontRequireReceiver);}
   
}

