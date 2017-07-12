#pragma strict

var up:int=0;
var down:int=1;
var currentState=down;
var start:Vector3;
var end:Vector3;
var pos:float;



function Start () {
start=transform.position;
end.x=start.x;
end.z=start.z;
 }

function Update () {

switch(currentState)
{
case up: pos+=Time.deltaTime/1.1;
			transform.position=Vector3.Lerp(start,end,pos);
			if(pos>1.0)
			currentState=down;break;
			
case down: pos-=Time.deltaTime/1.1;
			transform.position=Vector3.Lerp(start,end,pos);
			if(pos<0.0)
			currentState=up;break;


}

}