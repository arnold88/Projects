

#pragma strict

var up:int=0;
var down:int=2;
var currentState=up;

var start:Vector3;
var end:Vector3;
var pos:float;
var stay:Vector3;
var stayThere:int=1;
var stayThere2:int=3;


function Start () {
start=transform.eulerAngles;


end.x=start.x;
end.z=start.z;
end.y=start.y;

stay.x=end.x;
stay.y=90;
stay.z=end.z;
  
    }


function Update () {

switch(currentState)
{
case up: pos+=Time.deltaTime;
			transform.eulerAngles=Vector3.Lerp(start,stay,pos);
			if(pos>1.0) 
			currentState=stayThere;break;

case stayThere: pos-=Time.deltaTime/4;
			transform.eulerAngles=Vector3.Lerp(stay,stay,pos);
			if(pos<0.0)currentState=down;break;
						
case down: pos+=Time.deltaTime;
			transform.eulerAngles=Vector3.Lerp(stay,end,pos);
			if(pos>1.0)
			currentState=stayThere2;break;
			
case stayThere2: pos-=Time.deltaTime/4;
			transform.eulerAngles=Vector3.Lerp(end,end,pos);
			if(pos<0.0)currentState=up;break;
			



}

}