using UnityEngine;

using System.Collections;

 

public class FPScount : MonoBehaviour

{

 

    public float updateInterval = 1.0f;

    private float accum = 0.0f; // FPS accumulated over the interval

    private int frames = 0; // Frames drawn over the interval

    private float timeleft; // Left time for current interval

    private float fps = 15.0f; // Current FPS

    private float lastSample;

    private int gotIntervals = 0;

 

    void Start()

    {

        timeleft = updateInterval;

        lastSample = Time.realtimeSinceStartup;

    }

 

    float GetFPS() { return fps; }

    bool HasFPS() { return gotIntervals > 2; }

 

    void Update()

    {

        ++frames;

        float newSample = Time.realtimeSinceStartup;

        float deltaTime = newSample - lastSample;

        lastSample = newSample;

 

        timeleft -= deltaTime;

        accum += 1.0f / deltaTime;

 

        // Interval ended - update GUI text and start new interval

        if (timeleft <= 0.0f)

        {

            // display two fractional digits (f2 format)

            fps = accum / frames;

            

            timeleft = updateInterval;

            accum = 0.0f;

            frames = 0;

            ++gotIntervals;

        }

    }
	
	void OnGUI()
	{
	  
		GUI.Label (new Rect (450,35,250,250), (" Frames Per Second: " + fps.ToString("f2") ) );
		
	}

}