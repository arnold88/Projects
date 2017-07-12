/*
	Make.c v2  version 1.2

    CURRENT LAYOUT:

	DIGITAL OUT:

	CHANNEL 7 --> ON/OFF
	        6 --> RECORDING
			5 --> USB CONNECT ACTIVE
			4 --> RESET (HOOK UP WITH RESET BUTTON W/ RESET PIN

	DIGITAL IN:
	4 --> DEFAULT MODE (FOR EMERGENCY ONLY)
    5 --> RECORDING BUTTON
	
	RESET GOES TO RESET PIN.

	ON/OFF GOES TO POWER IN!?



*/

#include "stdlib.h"
#include "config.h"
#include "poly.h"
#include "serial.h"

#include "string.h"

void BlinkTask( void* parameters );
void NetworkCheck( void );
void vBasicWEBServer( void *pvParameters );


const int ON_CHANNEL_LED = 7;  //LED FOR ON/OFF
const int RECORDING_LED = 6; // LED FOR RECORDING
const int PC_LED = 5; // LED FOR PC CONNECTED
const int OTHER_FUNC_LED = 4; // WHAT IS THIS?

void Make( )
{
  TaskCreate( BlinkTask, "Blink", 400, 0, 1 );

  // Do this right quick after booting up - otherwise we won't be recognised
  Usb_SetActive( 1 );

  // Active the Poly Function Task
  // Poly_SetActive( true );

  // Fire up the OSC system
  Osc_SetActive( true );
  // Add all the subsystems (make sure OSC_SUBSYSTEM_COUNT is large enough to accomodate them all)
  Osc_RegisterSubsystem( 0, AppLedOsc_GetName(), AppLedOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 1, DipSwitchOsc_GetName(), DipSwitchOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 2, ServoOsc_GetName(), ServoOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 3, AnalogInOsc_GetName(), AnalogInOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 4, DigitalOutOsc_GetName(), DigitalOutOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 5, DigitalInOsc_GetName(), DigitalInOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 6, MotorOsc_GetName(), MotorOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 7, PwmOutOsc_GetName(), PwmOutOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 8, LedOsc_GetName(), LedOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 9, DebugOsc_GetName(), DebugOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 10, SystemOsc_GetName(), SystemOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 11, NetworkOsc_GetName(), NetworkOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 12, SerialOsc_GetName(), SerialOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 13, IoOsc_GetName(), IoOsc_ReceiveMessage, NULL );
  Osc_RegisterSubsystem( 14, StepperOsc_GetName(), StepperOsc_ReceiveMessage, NULL );

  // Permit DIP switches to change the base IP settings
  NetworkCheck();

  // Starts the network up.  Will not return until a network is found...
  Network_SetActive( true );

	// Start the example webserver
  TaskCreate( vBasicWEBServer, "WebServ", 300, NULL, 4 );
}

void BlinkTask( void* p )
{
 (void)p;
  Led_SetState( 1 );
  Sleep( 100 );
  AppLed_SetActive (0,1);
  AppLed_SetActive (1,1);
  AppLed_SetActive (2,1);
  AppLed_SetActive (3,1);

  

  Serial_SetActive(1);
  Serial_SetBaud(9600);
  Serial_SetHardwareHandshake(0);
  Serial_SetBits(8);
  Serial_SetStopBits(1);
  Serial_SetParity(0);

 //data for default mode

    int RateMin [] = {74, 75, 76, 77, 78, 79, 80, 81};
	int Period [] = {0,1,1,1,1,2,2,2};
	int Length [] = {0,3,2,1,1,2,2,2};

   //store last 100 entries

   int rate_store [100];
   int period_store[100];
   int length_store[100];

   int i;

	uchar * first_msg = "Patient #:";
	uchar * second_msg  = "Heart Rate:";
	uchar * third_msg = "Period:";
	uchar * fourth_msg = "Length:";
	uchar * no_murmur = "No Murmur";
	uchar * systolic = "Systolic";
	uchar * diastolic = "Diastolic";
	uchar * early = "Early";
	uchar * late = "Late";
	uchar * phucker = "Nothing";
    
	uchar * boot = "WELCOME TO";
	uchar * boot1= "HEART MURMUR";
	uchar * boot2= "DETECTOR";
	uchar * boot3= "VERSION 1.0 !";

	uchar * wait = "Please press the";
	uchar * wait1= "RECORD button to";
	uchar * wait2= "start recording.";

	//TITLE SCREEN

	Sleep(2000);

	Serial_Write( boot, strlen( (char*)boot ), 1000 );
	Serial_SetChar(13);
	Serial_Write( boot1, strlen( (char*)boot1 ), 1000 );
	Serial_SetChar(13);
	Serial_Write( boot2, strlen( (char*)boot2 ), 1000 );
	Serial_SetChar(13);
	Serial_Write( boot3, strlen( (char*)boot3 ), 1000 );
	Serial_SetChar(13);


  int x = 0;
  for (x=0;x<8;x++)
  {
      DigitalOut_SetActive(x,1);
  }
    Sleep( 1000 );
	 
	// as buttons (channel (4-7)
	DigitalIn_SetActive (4,1);
	DigitalIn_SetActive (5,1);
	DigitalIn_SetActive (6,1);
    DigitalIn_SetActive (7,1);
	// as analog inputs (channel 0-3)
    AnalogIn_SetActive( 0 , 1); 	
    AnalogIn_SetActive( 1 , 1); 	
    AnalogIn_SetActive( 2 , 1); 	
    AnalogIn_SetActive( 3 , 1); 	
  
  // need to turn on LED on digital out.

//  DigitalOut_SetActive(ON_CHANNEL_LED,1);

   /* while (true)
	{
          Serial_SetChar(17);
		  Serial_SetChar( (AnalogIn_GetValue(0) / 102) + 48  );
          Sleep (50);
		  Serial_SetChar(12);
	}*/

  Serial_SetChar(12); // clear screen

  while ( true ) // program starts!
  {
 
     for (i=0;i<8;i++)
	 {
           Serial_SetChar(17); // turn on backlight

	    Led_SetState( 0 );
	    Serial_Write( first_msg, strlen( (char*)first_msg ), 1000 );

	
        Sleep(75);

        Serial_SetChar (i+49);
  
		Serial_SetChar(13);


        Serial_Write( second_msg, strlen( (char*)second_msg ), 1000 );

		Serial_SetChar ( ((RateMin[i]) / 10) + 48 );
		Serial_SetChar ( RateMin[i] - ((RateMin[i] / 10) *10)  + 48  );
		
        Serial_SetChar (13);


		Serial_Write( third_msg, strlen( (char*)third_msg ), 1000 );

		if (Period[i]==0)
	    {
		Serial_Write( no_murmur, strlen( (char*)no_murmur), 1000 );

	    }
	    else if (Period[i]==1)
	    {
		Serial_Write( systolic, strlen( (char*)systolic ), 1000 );

	    }
	    else
	    {
		Serial_Write( diastolic, strlen( (char*)diastolic), 1000 );

	    }
     
		Serial_SetChar (13);

        Serial_Write( fourth_msg, strlen( (char*)fourth_msg ), 1000 );

       if (Length[i]==0)
	   {
	   Serial_Write( no_murmur, strlen( (char*)no_murmur), 1000 );
       }
	   else if (Length[i]==1)
	   {
		Serial_Write( early, strlen( (char*)early) , 1000 );
	   }
	   else if (Length[i]==2)
	   {
		Serial_Write( late, strlen( (char*)late), 1000 );
	   }
	   else
	   {
         Serial_Write( phucker, strlen( (char*)phucker), 1000 );
	   }


	Sleep(3000);
    Led_SetState(1);

	Serial_SetChar(12);
	
	Sleep (100);

	// if anytime the switch is on, quit default mode
	//if (DigitalIn_GetValue (4) == 1) 
		//break;

     
	/*else 
	{
	uchar * wait = "Please press the";
	uchar * wait1= "RECORD button to";
	uchar * wait2= "start recording.";

	}*/

	 AppLed_SetState (1,1);
	 AppLed_SetState (0,0);
	 Sleep(1000);



   } // end else if


  }// end while (which never ends)

}// end make controller main 


// Make sure the network settings are OK
void NetworkCheck()
{
  // Check to see if there's an override from the dip switch
  // The DIP switch would need to be 
  //   1 2 3 4 5 6 7 8
  //   x X y Y 1 1 1 0
  // Where Xx & Yy are added to the base address
  //   192.168.0+Yy.200+Xx
  int sw = DipSwitch_GetValue();
  int dipload = ( sw & 0xF0 ) == 0x70;

  // if either the network settings were invalid or the dipswitch is set to load
  if ( !Network_GetValid( ) || dipload )
  {
    // we're shooting for 192.168.0.200
    int a3 = 0;
    int a4 = 200;

    // the dip switch can offset the loaded addresses a little bit
    if ( dipload )
    {
      // 0000Yy00 
      a3 += ( sw & 0x0C ) >> 2;
      // 000000Xx 
      a4 += ( sw & 0x03 );
    }

    Network_SetAddress( 192, 168, a3, a4 );
    Network_SetMask( 255, 255, 255, 0 );
    Network_SetGateway( 192, 168, a3, 1 );
    Network_SetValid( 1 );
  }
}
