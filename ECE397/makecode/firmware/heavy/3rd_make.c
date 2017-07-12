/*
	Make.c v2  version 1.2

    CURRENT LAYOUT:

	DIGITAL OUT FOR LED:

	CHANNEL 7 --> ON/OFF
	        6 --> RECORDING
			5 --> USB CONNECT ACTIVE
			4 --> RESET / REBOOT

	DIGITAL IN:
	4 --> DEFAULT MODE (FOR EMERGENCY ONLY)
    5 --> RECORDING BUTTON
	6 --> RESET
	
	

	ON/OFF GOES TO POWER IN!?



*/

#include "stdlib.h"
#include "config.h"
#include "poly.h"
#include "serial.h"

#include "string.h"

// system core

void BlinkTask( void* parameters );
void NetworkCheck( void );
void vBasicWEBServer( void *pvParameters );

// custom function

void title_screen();
void default_mode();


const int ON_CHANNEL_LED = 7;  //LED FOR ON/OFF
const int RECORDING_LED = 6; // LED FOR RECORDING
const int PC_LED = 5; // LED FOR PC CONNECTED
const int RESET_LED = 4; // RESET

const	uchar * first_msg = "Point #:";
const	uchar * second_msg  = "Heart Rate:";
const	uchar * third_msg = "Period:";
const	uchar * fourth_msg = "Length:";
const	uchar * no_murmur = "No Murmur";
const	uchar * systolic = "Systolic";
const	uchar * diastolic = "Diastolic";
const	uchar * early = "Early";
const	uchar * late = "Late";
const	uchar * phucker = "Nothing";

const 	uchar * wait = "Please press the";
const	uchar * wait1= "RECORD button to";
const	uchar * wait2= "start recording.";

const   uchar * boot = "WELCOME TO";
const	uchar * boot1= "HEART MURMUR";
const	uchar * boot2= "DETECTOR";
const	uchar * boot3= "VERSION 1.0 !";

// controller main for boot up
void Make( )
{
  TaskCreate( BlinkTask, "Blink", 400, 0, 1 );

  // Do this right quick after booting up - otherwise we won't be recognised
  Usb_SetActive( 1 );

  // Active the Poly Function Task
  // Poly_SetActive( true );

  System_SetActive( 1 );

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


// program starts here

void BlinkTask( void* p )
{
 (void)p;
  Led_SetState( 1 );
  
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

  Sleep( 100 );
   //store last 100 entries
   int rate_store   [100];
   int period_store [100];
   int length_store [100];

   int i;
   int patient_count = 0;

  int x = 0;
  for (x=0;x<8;x++)
  {
      DigitalOut_SetActive(x,1);
  }
  Sleep( 90 );
	 
	// as buttons (channel (4-7)
	DigitalIn_SetActive (4,1);
	DigitalIn_SetActive (5,1);
	DigitalIn_SetActive (6,1);
    DigitalIn_SetActive (7,1);
  
  // need to turn on LED on digital out.

  DigitalOut_SetValue(ON_CHANNEL_LED,1);

  Serial_SetChar(12); // clear screen
  Sleep (50);

  bool default_flag = false;

  title_screen();

  Serial_SetChar(12); // clear screen
  Sleep (50);

while ( true ) // program starts!
{
  
	   while ( DigitalIn_GetValue(5) == 0) // not on recording
	   {
	   Serial_Write( wait, strlen( (char*)wait ), 1000 );
	   Serial_SetChar(13);
	   Serial_Write( wait1, strlen( (char*)wait1 ), 1000 );
	   Serial_SetChar(13);
	   Serial_Write( wait2, strlen( (char*)wait2 ), 1000 );

	   Sleep (1000);
	   Serial_SetChar (12);
	   Sleep(50);
 
	   if ( DigitalIn_GetValue (4) == 1 )  default_mode();//default mode not-active, start if 0

	    if (DigitalIn_GetValue (6) == 1 ) // reset button launched
	    {
            DigitalOut_SetValue(RESET_LED,1);
			System_SetReset(1); // reset
        }

      }//---> end while not on recording mode

   // recording implmenetation still needs to be done	
  

	// Display the heart detail
     /*
     if (DigitalIn_GetValue (5) == 0) // not - recording , start if 1
	  {
	   Serial_SetChar(12);
	   Sleep(50);
	   uchar * wait = "Please press the";
	   uchar * wait1= "RECORD button to";
	   uchar * wait2= "start recording.";

	   Serial_Write( wait, strlen( (char*)wait ), 1000 );
	   Serial_SetChar(13);
	   Serial_Write( wait1, strlen( (char*)wait1 ), 1000 );
	   Serial_SetChar(13);
	   Serial_Write( wait2, strlen( (char*)wait2 ), 1000 );
	 } // end if 1
	 else  // start else 1
	 {
      Serial_SetChar(12);    
 
	 int in_heart_rate[3];
	 int input_raw;

	   for (i=0;i<1000;i++) 
	   {
         Serial_SetChar(17); // turn on backlight
         
		// patient #?
		 Led_SetState( 0 );
	    Serial_Write( first_msg, strlen( (char*)first_msg ), 1000 );
     
		Serial_SetChar ( patient_count + 48 );

        Sleep(25);
        
        Serial_SetChar ( 13 );

		 Serial_Write( second_msg, strlen( (char*)second_msg ), 1000 );

		 // read microphone data from channel zero
        // the divisor is the calibration factor. change when needed.
		 input_raw = (AnalogIn_GetValue(3));

		 in_heart_rate[0] = input_raw / 100;
         in_heart_rate[1] = (input_raw / 10) - (in_heart_rate[0] * 10) ;
		 in_heart_rate[2] = input_raw % 10;

         Serial_SetChar( in_heart_rate[0] + 48  );
         Serial_SetChar( in_heart_rate[1] + 48  );
		 Serial_SetChar( in_heart_rate[2] + 48  );
         Sleep (25);

         Serial_SetChar( 13  );         

         Serial_Write( fourth_msg, strlen( (char*)fourth_msg ), 1000 );
		  
		 if (input_raw < 60)
		 {
             Serial_Write( phucker, strlen( (char*)phucker ), 1000 ); 
		 }
		 else if (input_raw < 120)
		 {
            Serial_Write( late, strlen( (char*)late ), 1000 ); 
		 }
		 else
		 {
             Serial_Write( early, strlen( (char*)early ), 1000 ); 
		 }

          Serial_SetChar( 13  );         

         Serial_Write( third_msg, strlen( (char*)third_msg ), 1000 );
		  
		 if (input_raw < 60)
		 {
             Serial_Write( no_murmur, strlen( (char*)no_murmur ), 1000 ); 
		 }
		 else if (input_raw < 120)
		 {
            Serial_Write( diastolic, strlen( (char*)diastolic ), 1000 ); 
		 }
		 else
		 {
             Serial_Write( systolic, strlen( (char*)systolic ), 1000 ); 
		 }



 
		  if (DigitalIn_GetValue (4) == true)  // emegency enabled?
		  {
               default_flag == true;
			   break; // break out for loop, go stright to default mode.
		  }
		  else if (DigitalIn_GetValue (5) == 0)
		  {
                    break; // break out the loop.
		  }
		  else if (DigitalIn_GetValue (6) == 1)
		  {
                 System_SetReset(1);
		  }

       }// end for
	 } // end else 1
	 AppLed_SetState (1,1);
	 AppLed_SetState (0,0);
	 Sleep(100);
   } //end if 0*/

  }// end while (which never ends)
}// end make controller main 

//*******************************************************************************************************************************************

void title_screen()
{
    Serial_SetChar (12);
	Sleep (50);

	//TITLE SCREEN
	Serial_Write( boot, strlen( (char*)boot ), 1000 );
	Serial_SetChar(13);
	Serial_Write( boot1, strlen( (char*)boot1 ), 1000 );
	Serial_SetChar(13);
	Serial_Write( boot2, strlen( (char*)boot2 ), 1000 );
	Serial_SetChar(13);
	Serial_Write( boot3, strlen( (char*)boot3 ), 1000 );
	Serial_SetChar(33);

    Sleep (5000);

    return;
}

void default_mode()
{
     //data for default mode



    int RateMin [] = {74, 75, 76, 77, 78, 79, 80, 81};
	int Period [] = {0,1,1,1,1,2,2,2};
	int Length [] = {0,3,2,1,1,2,2,2};

    int i;

    Serial_SetChar(12); 
    Sleep (100);


   while (true)
   {
	for (i=0;i<8;i++)
	 {		 
		Serial_Write( first_msg, strlen( (char*)first_msg ), 1000 );
        Sleep(25);
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
       Serial_SetChar (147);
	   Serial_SetChar (68);   // Print 'D' in upper-right corner indicates default mode
	   Serial_SetChar (128);
	   Sleep (2000);
       Serial_SetChar(12); 
       Sleep (25);
       
       if (DigitalIn_GetValue (4) == 0 ) return; // end defualt mode while button not active
	   if (DigitalIn_GetValue (6) == 1 )
	   {
		   DigitalOut_SetValue(RESET_LED,1);
		   System_SetReset(1);
	   }
	}// end for	 
   }// end while(true)
}// end default_mode module