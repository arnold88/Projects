#pragma strict
var start:Vector3;
var end:Vector3;
var open:int=0;
var opening:int=1;
var closing:int =2;
var closed:int=3;
var currentState;
currentState=open;
public var pos:float;

function Start () {
start=transform.position;
end.x=-0.21;
end.y=start.y;
end.z=start.z;
}

function Update () {

switch(currentState)
{
                                                                                	
case closing:print("closing left="); pos += Time.deltaTime; transform.position = Vector3.Lerp(start, end, pos); if( pos > 1.0 ) currentState=closed; break;
case closed: print("closed left=");currentState=opening;break;
case opening: print("opening left="); pos -= Time.deltaTime; transform.position = Vector3.Lerp(start, end, pos); if( pos < 0 ) currentState=open;break;
case open: print("open left=");currentState=closing;		break;
	

}


  
 
 }
 