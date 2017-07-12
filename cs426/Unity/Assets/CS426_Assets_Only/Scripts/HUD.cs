using UnityEngine;
using System.Collections;
     
public class HUD: MonoBehaviour
{
	
	public GameObject monk;
	public GameObject priest;
    private int fullhealth;
	health script;
	private int mhp;
	private int php;
	public int monkrespawn;
	public int priestrespawn;
	public int buildnum;
	private float startTime;
    private float ellapsedTime;
     
    void Start()
	{
		startTime = Time.time; 
	}
     
    void Update () 
	{
		script = monk.GetComponent("health") as health;
		mhp = script.hp;
		fullhealth = script.full;
		monkrespawn = script.respawncount;
		
		script = priest.GetComponent("health") as health;
		php = script.hp;
		priestrespawn = script.respawncount;
		
		ellapsedTime = Time.time - startTime;
    
    }
     
 
    void OnGUI()
	{
		
    //GUI.Label(new Rect(50,25, 250, 20), ( "Monk HP:" + mhp.ToString() + "/" + fullhealth.ToString() ));
    GUI.Label(new Rect(50,40, 250, 20), ( "Monk Respawns:" + monkrespawn.ToString()));
		
		
	//GUI.Label (new Rect(1000,25,250,20), ( "Priest HP:"+ php.ToString() + "/" + fullhealth.ToString() )  );
    GUI.Label(new Rect(1000,40, 250, 20), ( "Priest Respawns:" + priestrespawn.ToString() ) );
		
		
	GUI.Label (new Rect (400,5,400,250), ( " Ascension - RELEASE CANDIDATE Build Version " + buildnum.ToString() ) );
	GUI.Label (new Rect (370,20,250,250), (" For Educational Use Only - Not for Resale " ) );
		
	GUI.Label (new Rect (400,50,250,250), (" Time elapsed in seconds: " + ellapsedTime.ToString() ) );
		
   
		
    }
}