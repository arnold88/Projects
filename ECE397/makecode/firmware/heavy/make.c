/*
        Make.c changed with blinktask + serial task simutaneous.
*/


#include "stdlib.h"
#include "config.h"
#include "poly.h"
#include "serial.h"
#include "string.h"

#define MSG_MAX 4096
#define IP_ADDRESS( a, b, c, d ) ( ( (int)d << 24 ) + ( (int)c << 16 ) + ( (int)b << 8 ) + (int)a )
void BlinkTask( void* parameters );
void SerialTask( void* parameters );
void NetworkCheck( void );
void vBasicWEBServer( void *pvParameters );

void Make( )
{

  // Do this right quick after booting up - otherwise we won't be recognised
  Usb_SetActive( 1 );

  Debug_SetUdp(1);
  Debug_SetActive( 1 );

  // Active the Poly Function Task
   Poly_SetActive( true );

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
  //Network_SetActive( true );

  TaskCreate( BlinkTask, "Blink", 400, 0, 1 );
  Debug(0, "Starting Serial task\n");

  TaskCreate( SerialTask, "Ser", 300, 0, 1 );


}

void SerialTask( void* p )
{
  (void)p;
  char* request = "GET /auto/rss_full/RI/Kingston.xml?units=both HTTP/1.0\r\n\r\n";
  char *loading_msg = "Refreshing RSS Feed...";
  void* sock;
  char msg[MSG_MAX];
  int msg_index;

  Serial_SetActive(1);
  Serial_SetBaud(9600);
  Serial_SetHardwareHandshake(0);
  Serial_SetBits(8);
  Serial_SetStopBits(1);
  Serial_SetParity(0);
  Sleep(1000);

  while (true) {
    char s[33];
    char marker[] = {'i', 'o', 'n', '>' };
    int m = 0;
    int in_closing_tag = 0;
    int count;
    msg_index = 0;

    Serial_SetChar(254); // attn
    Serial_SetChar(1);   // cls
    Serial_Write((uchar*) loading_msg, strlen(loading_msg), 2000);

    int g = 0;

	for (g = 0; g < 4 ; g++)
	{
          AppLed_SetActive(g,1);
          AppLed_SetState (g,1);
		  Sleep(100);
	}

   
	for (g = 0; g < 4 ; g++)
	{
          
          AppLed_SetState (g,0);
		  Sleep(100);
	}

  }// end while (true)
}

void BlinkTask( void* p )
{
 (void)p;
  Led_SetState( 1 );
  Sleep( 1000 );

  while ( true )
  {
    Led_SetState( 0 );
    Sleep( 900 );
    Led_SetState( 1 );
    Sleep( 10 );
  }
}

// Make sure the network settings are OK
void NetworkCheck()
{
  Network_SetAddress( 192, 168, 254, 200 );
  Network_SetMask( 255, 255, 255, 0 );
  Network_SetGateway( 192, 168, 254, 1 );
  Network_SetValid( 1 );
}
