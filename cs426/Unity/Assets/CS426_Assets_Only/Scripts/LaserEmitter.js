#pragma strict

var target : Transform;
internal var lineRenderer : LineRenderer;


function Start () {


lineRenderer = GetComponent(LineRenderer);
}

function Update () {

  transform.LookAt(target);
  var hit : RaycastHit;
  if (Physics.Raycast(transform.position,transform.forward,hit))
       if (hit.transform.name.Equals(target.name)){
            lineRenderer.SetPosition(1,Vector3(0,0,hit.distance));}
       
  
       
  
}