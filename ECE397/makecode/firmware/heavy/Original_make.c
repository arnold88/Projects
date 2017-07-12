/*
	Make.c FOR ECE 397
*/

#include "stdlib.h"
#include "config.h"
#include "poly.h"
#include "serial.h"
#include "string.h"


#define MSG_MAX 4096
void BlinkTask( void* parameters );
void NetworkCheck( void );
void vBasicWEBServer( void *pvParameters );
void signaltest(void* p );

void Make( )
{
  TaskCreate( BlinkTask, "Blink", 400, 0, 2 );

  // Do this right quick after booting up - otherwise we won't be recognised
  Usb_SetActive( 1 );

  Debug_SetUdp(1);
  Debug_SetActive( 1 );

  // Active the Poly Function Task
  //Poly_SetActive( true );

  // Fire up the OSC system
  Osc_SetActive( true );
  // Add all the subsystems
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

  NetworkCheck();

  // Starts the network up.  Will not return until a network is found...
  Network_SetActive( true );

	// Start the example webserver
  TaskCreate( vBasicWEBServer, "WebServ", 300, NULL, 4 );

  TaskCreate (signaltest, "input", 300, NULL, 6);


}




// testing signal input + serial output
void signaltest (void* p)
{
   

   (void)p;
   
   Led_SetState( 1 );
    AppLed_SetActive(1,1);
    AppLed_SetState (1,1);
	AppLed_SetActive(0,0);
    AppLed_SetState (0,0);
	Sleep( 500 ); 

 
	int slot [ 8 ];

	


    // output here

  char msg[MSG_MAX];
  int msg_index = 8;
  char *start_msg = "Starting.....";
  char *refresh_msg = "Refreshing.....";


  Serial_SetActive(1);
  Serial_SetBaud(9600);
  Serial_SetHardwareHandshake(0);
  Serial_SetBits(8);
  Serial_SetStopBits(1);
  Serial_SetParity(0);
  Sleep(1000);

    Serial_SetChar(254); // attn
    Serial_SetChar(1);   // cls
    Serial_Write((uchar*) start_msg, strlen(start_msg), 2000); // output start message
  
  while (true)
  {
    int i; 
     // process input
	 // setup message queue for output
    for (i =0 ; i < msg_index ; i++)
	{
		
		DigitalIn_SetActive (i,1);
		slot[i] = DigitalIn_GetValue (i);
        msg[( i*2 )] = i;
		msg[ (i * 2) + 1] = ' ';
    }    
 
	// output module
	int j;
    for (j = 0; j < 10; j++) 
	{ 
      int chars_written = 0;
      int i;
      for (i = 0; i < msg_index; i++) 
	  {
        if (msg[i] == 254) 
		{
          Sleep(2500); // pause before sending special character
		}
   
        if (msg[i] >= ' ' && msg[i] <= 127) 
		{
          chars_written++;
          Sleep(125);
		}
        
        Serial_SetChar(msg[i]);

        if (chars_written == 32) 
		{
           Sleep(750);
           Debug(0, "Clearing Screen after pause");
           Serial_SetChar(254); // attn
           Serial_SetChar(1);   // cls
           chars_written = 0;
        }
	  }// end for
	} // end 2nd for, output module 





    Sleep (2000); 
	Serial_Write((uchar*) start_msg, strlen(start_msg), 2000);
	Sleep (1000);
  } // end while

} // end signalinput task
  

void BlinkTask( void* p )
{
 (void)p;
  Led_SetState( 1 );
  Sleep( 1000 );
      int x;
  for ( x=1; x<=10;x++)
  {
    Led_SetState( 0 );
    Sleep( 50 );
    Led_SetState( 1 );
    Sleep( 10 );
    //Debug( 0, "D %d", count++ );
  }

    Led_SetState (0);
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
