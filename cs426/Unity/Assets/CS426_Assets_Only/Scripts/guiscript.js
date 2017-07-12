/*function OnGUI () {
	// Make a background box
	GUI.Box (Rect (10,10,100,90), "Loader Menu");

	// Make the first button. If it is pressed, Application.Loadlevel (1) will be executed
	if (GUI.Button (Rect (20,40,80,20), "Level 1")) {
		Application.LoadLevel (1);
	}

	// Make the second button.
	if (GUI.Button (Rect (20,70,80,20), "Quit")) {
		Application.Quit();
	}
}

*/

  var showMenu:boolean=false;



function Update () {

if(Input.GetKeyDown("g"))
	{
		print("Escape displayed");
		Screen.showCursor=true;
		showMenu=true;
	}
	
else { showMenu=false; Screen.showCursor=false;}

}

function onGUI()
{

	if(showMenu==true)
	{
		print("GUI DISPLAYED");
		GUI.BeginGroup(Rect(Screen.width/2-50,Screen.height/2-45,100,90));
		GUI.Box(Rect(0,0,100,90), "Menu");

		if(GUI.Button(Rect(10,30,80,20), "Quit")){}

		if(GUI.Button(Rect(10,60,80,20), "Resume")){}
		
		hover = GUI.tooltip;

   

  
      


		GUI.EndGroup();
	}
}

