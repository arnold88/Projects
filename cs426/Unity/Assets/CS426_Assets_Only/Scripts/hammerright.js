#pragma strict
var start:Vector3;
var end:Vector3;
public var pos:float;
var open=0;
var closed=1;
var opening=2;
var closing=3;
var currentState=open;

function Start () {
start=transform.position;
end.x=0.21;
end.y=start.y;
end.z=start.z;
}
function Update () {

switch(currentState)
{


case closing:print("b pos="+pos);
pos=pos+Time.deltaTime;transform.position = Vector3.Lerp(start, end, pos);
if(pos>1)currentState=closed;break;


case closed:print("c");currentState=opening;break;

case opening:print("d");
pos=pos-Time.deltaTime;
transform.position = Vector3.Lerp(start, end, pos);if(pos<0)currentState=open;break;

case open:print("a");currentState=closing;break;

}








//transform.position = Vector3.Lerp(start, end, Time.time);
   

 //transform.Translate(0, Time.deltaTime,0);

}