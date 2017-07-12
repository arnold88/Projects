#pragma strict


var source1: Transform;


internal var lineRenderer : LineRenderer;




function Start () {

lineRenderer = GetComponent(LineRenderer);

}

function Update () {

  transform.LookAt(source1);
  var hit : RaycastHit;
  
  
  transform.position = Vector3.Reflect (transform.position, Vector3.right);
  
  Physics.Raycast(transform.position,transform.forward,hit);
       
  lineRenderer.SetPosition(1,Vector3(0,0,hit.distance));
       
 
      
}