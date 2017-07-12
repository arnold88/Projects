using UnityEngine;
using System.Collections;

public class CameraInit : MonoBehaviour {
	
	public GameObject maincam;
	public GameObject trapcam1;
	public GameObject trapcam2;
	public GameObject trapcam3;
	
	public Camera maincam_alt;
	public Camera trapcam1_alt;
	public Camera trapcam2_alt;
	public Camera trapcam3_alt;
	
	
	// Use this for initialization
	void Start () {
	
		maincam.SetActive(true);
		trapcam1.SetActive(true);
		trapcam2.SetActive(true);
		trapcam3.SetActive(true);
		
		maincam_alt.camera.enabled = true;
		trapcam1_alt.camera.enabled = false;
		trapcam2_alt.camera.enabled = false;
		trapcam3_alt.camera.enabled = false;
		
	}
	
	// Update is called once per frame
	void Update () {
	
		
		
	}
}
