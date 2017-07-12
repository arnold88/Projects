#pragma strict
var splash:AudioClip;

function Start () {

}

function Update () {

}


function OnTriggerEnter(other:Collider)
{
Debug.Log("whblsj");
Debug.Log(other.gameObject.name);
audio.PlayClipAtPoint(splash,transform.position);
}