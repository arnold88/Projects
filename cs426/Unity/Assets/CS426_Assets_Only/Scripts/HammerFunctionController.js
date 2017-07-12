#pragma strict

var hammerTrig : GameObject;
var hammerParent: GameObject;

function start()
{
//hammerTrig = transform.FindChild("HammerTrigger");
}

function HammerHit()
{
hammerParent.SendMessage("hitSound",SendMessageOptions.DontRequireReceiver);
}

function SetDamageTrue()
{
hammerTrig.SendMessage("DamageTrue",SendMessageOptions.DontRequireReceiver);
}

function SetDamageFalse()
{
hammerTrig.SendMessage("DamageFalse",SendMessageOptions.DontRequireReceiver);
}