/*
	Make.c v2  version 1.2

   ANALOG INPUT TEST FOR CHANNEL 0



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
  Serial_SetChar(17);
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

	int input;

	int fourth;
	int third;
	int second;
	int first;
	
    int high = 0;

	uchar * score = "Your Score:";
	uchar * hiscore ="Hi Score:";

   Sleep(1000);

   DigitalOut_SetValue (4,1);

   Sleep(1000);

   DigitalOut_SetValue (5,1);

   Sleep(1000);

   DigitalOut_SetValue (6,1);

   Sleep(1000);

   DigitalOut_SetValue (7,1);

   while (true)
	{
		
          Serial_SetChar (17);		  

		  Serial_Write( score, strlen( (char*)score), 1000 );

          input = AnalogIn_GetValue(0); 

          fourth = input / 1000;
		  
          third = ( input - (fourth * 1000) ) / 100;

          second = ( input - (fourth * 1000) - (third * 100) ) / 10;

		  first = input % 10;

		  Serial_SetChar( fourth + 48  );
	      Serial_SetChar( third + 48 );
		  Serial_SetChar( second + 48 );
          Serial_SetChar( first + 48 );
		  Serial_SetChar(13);

		  Serial_Write( hiscore, strlen( (char*)hiscore), 1000 );

		  if (high <= input) 
		  {
             high = input;
		  }
		  fourth = high / 1000;
		  
          third = ( high - (fourth * 1000) ) / 100;

          second = ( high - (fourth * 1000) - (third * 100) ) / 10;

		  first = high % 10;

		  Serial_SetChar( fourth + 48  );
	      Serial_SetChar( third + 48 );
		  Serial_SetChar( second + 48 );
          Serial_SetChar( first + 48 );


          Sleep (100);
		  Serial_SetChar(12);
		  Sleep(10);

          if (DigitalIn_GetValue (6) == 1) System_SetSamba (1);  	

	}


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
