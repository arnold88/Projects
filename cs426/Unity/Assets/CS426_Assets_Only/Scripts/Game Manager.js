#pragma strict
  var showMenu:boolean=false;




function Update () {

if(Input.GetKeyDown("g"))
	{
	
		print("Escape displayed");
		showMenu=!showMenu;
			Screen.showCursor=!Screen.showCursor;

	}
	

}

function OnGUI()
{

	if(showMenu==true)
	{
		//print("GUI DISPLAYED");
		Screen.showCursor=true;
		GUI.BeginGroup(Rect(Screen.width/2-50,Screen.height/2-45,130,150));
		GUI.Box(Rect(0,0,100,120), "Menu");

		if(GUI.Button(Rect(10,30,80,20), "Start")){Application.LoadLevel (1);}

	    if(GUI.Button(Rect(10,60,80,20), "Demo")){Application.LoadLevel (2);}

		if(GUI.Button(Rect(10,90,80,20), "Quit")){Application.Quit();}


		GUI.EndGroup();
	}
}

