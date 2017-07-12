#pragma strict
var startr:Vector3;
var endr:Vector3;

var startl:Vector3;
var endl:Vector3;

var startu:Vector3;
var endu:Vector3;

var startd:Vector3;
var endd:Vector3;


//var adjustment:Vector3;


public var left:GameObject;
public var right:GameObject;
public var up:GameObject;
public var down:GameObject;

var uclosing:int=0;
var uclosed:int=1;
var uopening:int=2;
var uopen:int=3;

var lclosing:int=4;
var lclosed:int=5;
var lopening:int=6;
var lopen:int=7;

var currentState:int=0;
public var pos:float;
public var pos2:float;

function Start () {

//transform.parent.position = Vector3(5,5,5);

left.transform.localPosition = Vector3(-1.5,0,0);
right.transform.localPosition = Vector3(1.5,0,0);
up.transform.localPosition = Vector3(0,1.5,0);
down.transform.localPosition = Vector3(0,-1.5,0);

startl=left.transform.localPosition;
startr=right.transform.localPosition;
startu=up.transform.localPosition;
startd=down.transform.localPosition;




endu.y=0.1;
endu.x=startu.x;
endu.z=startu.z;

endd.y=-0.1;
endd.x=startd.x;
endd.z=startd.z;


endl.x=-0.1;
endl.y=startl.y;
endl.z=startl.z;

endr.x=0.1;
endr.y=startr.y;
endr.z=startr.z;




}

function Update () {

   switch(currentState)
    {
//CODE FOR UP DOWN
case uclosing:print("AAAAAA");
	pos2=pos2+Time.deltaTime;
	up.transform.localPosition = Vector3.Lerp(startu, endu, pos2);
	down.transform.localPosition = Vector3.Lerp(startd, endd, pos2);
	if(pos2>1)currentState=uclosed;
	break;

case uclosed:print("BBBBBBBB");
	currentState=uopening;
	break;

case uopening:print("CCCCCCC");
	pos2=pos2-Time.deltaTime;
	up.transform.localPosition = Vector3.Lerp(startu, endu, pos2) ;
	down.transform.localPosition = Vector3.Lerp(startd, endd, pos2);
	if(pos2<0)currentState=uopen;
	break;

case uopen:print("DDDDDDDDDDDD");
	currentState=lclosing;
	break;





//CODE FOR LEFT RIGHT
case lclosing:print("closing left="); 
	pos += Time.deltaTime; 
	left.transform.localPosition = Vector3.Lerp(startl, endl, pos); 
	right.transform.localPosition = Vector3.Lerp(startr, endr, pos);
	if( pos > 1.0 ) currentState=lclosed; 
	break;
									
case lclosed: 
	print("closed left=");
	currentState=lopening;
	break;
case lopening: 
	print("opening left="); 
	pos -= Time.deltaTime; 
	left.transform.localPosition = Vector3.Lerp(startl, endl, pos);
	right.transform.localPosition = Vector3.Lerp(startr, endr, pos); 
	if( pos < 0 ) currentState=lopen;
	break;
case lopen: 
	print("open left=");
	currentState=uclosing;		
	break;


     }

}