/*
	Make.c for ece 307 parallel
*/


/*
WIRING:

CHANNEL TO LCD

7 --> PIN 14
6 --> PIN 13
5 --> PIN 12
4 --> PIN 11
3 --> PIN 10
2 --> PIN 9
1 --> PIN 8
0 --> PIN 7

LCD PIN 4 (Ins. / data) TO SRV0
LCD PIN 5 (READ / WRITE) TO SRV1

PIN 6 (FIRE) TO SRV2


*/



#include "stdlib.h"
#include "config.h"
#include "poly.h"
#include "serial.h"

#include "string.h"

void BlinkTask( void* parameters );
void NetworkCheck( void );
void vBasicWEBServer( void *pvParameters );


void one();
void two();
void three();
void four();
void five();
void six();
void seven();
void eight();
void nine();
void zero();
void colon();
void fire();
void clear();

void cursor_home();
void entry_mode (int);
void display_on(int,int,int);
void cursor_shift(int,int);
void function_set( int , int , int );
//void set_cgram(int);
//void set_ddram(int);
//bool busyflag();



void Make( )
{
  TaskCreate( BlinkTask, "Blink", 400, 0, 1 );

  // Do this right quick after booting up - otherwise we won't be recognised
  Usb_SetActive( 1 );

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

	// Start the example webserver
  TaskCreate( vBasicWEBServer, "WebServ", 300, NULL, 4 );
}

void BlinkTask( void* p )
{
 (void)p;
  Led_SetState( 1 );
  Sleep( 1000 );

  int slot [ 8 ];

  while ( true )
  {
    Led_SetState( 0 );
    Sleep( 100 );
    Led_SetState( 1 );
    Sleep( 100 );
    

	
    AppLed_SetActive(1,1);
    AppLed_SetState (1,1);
	
	
	Sleep( 100 ); 


    int i; 
     // process input
	 // setup message queue for output
    for (i =0 ; i < 8 ; i++)
	{
		DigitalOut_SetActive (i,1);
		DigitalIn_SetActive (i,1);
		slot[i] = DigitalIn_GetValue (i);
        
    }

	for (i=0; i <4;i++)
	{
          Servo_SetActive(i,1);
	}
   
	AppLed_SetActive(0,1);
    AppLed_SetState (0,1);
    Sleep( 100 ); 

	// above line certified!

	// test output
 display_on (1,1,1);
 Sleep(100);
 cursor_home ();
 Sleep(100);
 entry_mode(2);
 Sleep(100);

    AppLed_SetActive(2,1);
    AppLed_SetState (2,1);
	Sleep( 100 ); 

   

	clear();

	Sleep (100);

	
	one();

	Sleep (100);

	
	fire();

	Sleep (100);

	
    AppLed_SetActive(3,1);
    AppLed_SetState (3,1);
	Sleep( 100 ); 

	
	cursor_shift(0,1);

	two();

	fire();
     
    AppLed_SetState (0,0);
    AppLed_SetState (1,0);
    AppLed_SetState (2,0);
    AppLed_SetState (3,0);
	Sleep( 100 ); 

     // process input
	 // setup message queue for output
   

  
 
  Serial_SetActive(1);
  Serial_SetBaud(9600);
  Serial_SetHardwareHandshake(0);
  Serial_SetBits(8);
  Serial_SetStopBits(1);
  Serial_SetParity(0);
  Sleep(1000);

    char *start_msg = "Starting.....";

    Serial_SetChar(254); // attn
    Serial_SetChar(1);   // cls
    Serial_Write((uchar*) start_msg, strlen(start_msg), 2000); // output start message





  } // end while
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


void one()
{
    Servo_SetActive(0,1);
	Servo_SetActive(1,0);


    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,0);
	DigitalOut_SetValue(0,1);


	return;
}

void two()
{
    Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,1);
	DigitalOut_SetValue(0,0);
	return;
}

void three()
{
    Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,1);
	DigitalOut_SetValue(0,1);
	return;
}

void four()
{
    Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,1);
	DigitalOut_SetValue(1,0);
	DigitalOut_SetValue(0,0);
	return;
}
void five()
{
   Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,1);
	DigitalOut_SetValue(1,0);
	DigitalOut_SetValue(0,1);
	return;
}

void six()
{
   Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,1);
	DigitalOut_SetValue(1,1);
	DigitalOut_SetValue(0,0);
	return;
}

void seven()
{


	Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,1);
	DigitalOut_SetValue(1,1);
	DigitalOut_SetValue(0,1);
	return;
}

void eight()
{
	Servo_SetActive(0,1);
	Servo_SetActive(1,0);

    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,1);
	DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,0);
	DigitalOut_SetValue(0,0);
	return;
}


void nine()
{
   Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,1);
	DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,0);
	DigitalOut_SetValue(0,1);
	return;
}

void zero()
{

	Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,0);
	DigitalOut_SetValue(0,0);
	return;
}

void colon()
{

	Servo_SetActive(0,1);
	Servo_SetActive(1,0);
    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,1);
	DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,1);
	DigitalOut_SetValue(0,0);
	return;
}

void fire()
{
	 Servo_SetActive (2,1);
     Servo_SetPosition (2,60);
	 Servo_SetSpeed (2,1023);
	 Sleep(50);
	 Servo_SetActive (2,0);
	 
	 return;
}

void clear()
{
    Servo_SetActive (0,0);
	Servo_SetActive (1,0);

    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,0);
	DigitalOut_SetValue(4,0);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,0);
	DigitalOut_SetValue(0,1);
	return;

}

//0 = nothing
//1 = display shift right
//2 = incrment cursor to right (space)
//3 = increment + shift

void entry_mode (int x) 
{
    Servo_SetActive (0,0);
	Servo_SetActive (1,0);

    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,0);
	DigitalOut_SetValue(4,0);
	DigitalOut_SetValue(3,0);
	DigitalOut_SetValue(2,1);

    switch (x)
	{
	case 0:
        DigitalOut_SetValue(1,0);
	    DigitalOut_SetValue(0,0);
		break;
	case 1:
		DigitalOut_SetValue(1,0);
	    DigitalOut_SetValue(0,1);
		break;
	case 2:
		DigitalOut_SetValue(1,1);
	    DigitalOut_SetValue(0,0);
		break;
	case 3:
		DigitalOut_SetValue(1,1);
	    DigitalOut_SetValue(0,1);
		break;
	default:
        DigitalOut_SetValue(1,0);
		DigitalOut_SetValue(0,0);
	}

	return;

}

void display_on(int x,int y, int z)
{

    Servo_SetActive (0,0);
	Servo_SetActive (1,0);

    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,0);
	DigitalOut_SetValue(4,0);
	DigitalOut_SetValue(3,1);
    DigitalOut_SetValue(2,x);
	DigitalOut_SetValue(1,y);
	DigitalOut_SetValue(0,z);

	return;

}

void cursor_shift (int x,int y)
{
    Servo_SetActive (0,0);
	Servo_SetActive (1,0);

    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,0);
	DigitalOut_SetValue(4,1);
	DigitalOut_SetValue(3,x);
    DigitalOut_SetValue(2,y);

	return;

}

void function_set (int x,int y, int z)
{
    Servo_SetActive (0,0);
	Servo_SetActive (1,0);

    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,1);
	DigitalOut_SetValue(4,x);
	DigitalOut_SetValue(3,y);
    DigitalOut_SetValue(2,z);

	return;


}

void cursor_home ()
{
    Servo_SetActive (0,0);
	Servo_SetActive (1,0);

    DigitalOut_SetValue(7,0);
	DigitalOut_SetValue(6,0);
	DigitalOut_SetValue(5,0);
	DigitalOut_SetValue(4,0);
	DigitalOut_SetValue(3,0);
    DigitalOut_SetValue(2,0);
	DigitalOut_SetValue(1,1);

	return;
 }