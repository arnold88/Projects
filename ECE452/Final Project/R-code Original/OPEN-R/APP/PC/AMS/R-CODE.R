/////////////////////////////////////////////////////////////
// default RCodePlus Program
// version 2.51 "A"
//    [2.52 work in progress]
// released with YART 2.51.05

// YART compatible
    // that's what the //{ //} things are for

// "Mini-Obey Cat"
// Mini Obey Cat provide a very basic personality
//  You can customize this using any text editor
//  Please read the comments in this file to figure out what is happening

// NOTES:
// - provides simple functionality using built-in motions and sounds
// - a LAN connection is helpful for debugging
// - works on 2x0 and 31x model AIBOs

/////////////////////////////////////////////////////////////
// Startup

GO Main

/////////////////////////////////////////////////////////////

:Main
    // This is where the program starts

    GLOBAL doPrint 0

    VLOAD doPrint       // you can force on for 31x connected to a terminal
    IF AiboId != 0 THEN
        // LAN is connected, print status
        SET doPrint 1
    ENDIF


    GLOBAL debug 0
    VLOAD debug
    IF debug != 0 THEN
        PRINT "DEBUG MODE!"
        SET doPrint 1
    ENDIF

    IF doPrint != 0 THEN
        PRINT "RCode Plus Basic YART Program 2.51 [.05]"
        PRINT "Program will PRINT status information"
    ENDIF

    PRINT "-"

    // initialize the RCODE Runtime 'RCR'
    PUSH doPrint
    CALL RCR_Init:1

    GLOBAL AP_Vocab
    VLOAD AP_Vocab
    GLOBAL AP_VLang
    VLOAD AP_VLang

    IF doPrint != 0 THEN
        PRINT "  AiboType = %d" AiboType
        PRINT "  AP_Version = %d" AP_Version
        PRINT "  AP_Vocab = %d" AP_Vocab
            // program works properly only if AP_Vocab == 0 or 2
        PRINT "  AP_VLang = %d" AP_VLang
            // 3 is English, 2 is Japanese
    ENDIF

    IF AP_Version >= 252 THEN
        AP_DEVCTL 6 1 // enable HFD
        IF doPrint != 0 THEN
            PRINT "HFD module enabled - work in progress"
        ENDIF
    ENDIF

    //{ "Main/Startup(once)"
        PLAY ACTION LIE // lie down at start
        WAIT
    //}

    // clear globals and sensors

    CLR SENSORS
    LOCAL lastPink 0
    LOCAL lastFav 0
    LOCAL lastUnfav 0
    LOCAL idleCount 0

    LOCAL postureOld -1
    LOCAL postureNow -1

    IF debug != 0 THEN
        PRINT "Calling DoDebugMode"
        CALL DoDebugMode
        PRINT "done DoDebugMode"
    ENDIF

    // Main Loop
    WHILE 1 = 1

        // Voice and sound
        // do not change the code here
        //  instead edit "????_Handler"

        IF AP_Voice_Cmd > 0 THEN
            PUSH AP_Voice_Cmd
            PUSH AP_Voice_Level
            PUSH AP_Voice_Pitch
            PUSH AP_Voice_Horz
            CALL Voice_Handler:4
            SET AP_Voice_Cmd 0
            LET idleCount 0 
        ENDIF

        IF AP_Loud > 0 THEN
            PUSH AP_Loud_Level
            PUSH AP_Loud_Pitch
            PUSH AP_Loud_Horz
            CALL Loud_Handler:3
            SET AP_Loud 0
            LET idleCount 0 
        ENDIF

        IF AP_Tone > 0 THEN
            PUSH AP_Tone
            CALL AiboTone_Handler:1
            SET AP_Tone 0
            LET idleCount 0 
        ENDIF

        IF AP_AiboSound > 0 THEN
            PUSH AP_AiboSound
            CALL AiboSound_Handler:1
            SET AP_AiboSound 0
            LET idleCount 0 
        ENDIF

        IF AP_Noise > 0 THEN
            CALL Noise_Handler
            SET AP_Noise 0
            LET idleCount 0 
        ENDIF

        IF AP_Rhythm > 0 THEN
            CALL Rhythm_Handler
            SET AP_Rhythm 0
            LET idleCount 0 
        ENDIF

        IF Pink_Ball <> 0 THEN
            IF lastPink == 0 THEN
                PUSH Pink_Ball_H
                PUSH Pink_Ball_V
                PUSH Pink_Ball_D
                CALL PinkBall_Found_Handler:3
                SET lastPink 1
            ENDIF
            PUSH Pink_Ball_H
            PUSH Pink_Ball_V
            PUSH Pink_Ball_D
            CALL PinkBall_Any_Handler:3
            LET idleCount 0 
        ELSE
            IF lastPink != 0 THEN
                CALL PinkBall_Lost_Handler
                SET lastPink 0
                LET idleCount 0 
            ENDIF
        ENDIF

        // other colors
        LOCAL cdtFav // blue level
        LOCAL cdtUnfav // green/yellow
        AP_COLORLVL 4 cdtFav
        AP_COLORLVL 5 cdtUnfav

        IF cdtFav > 20 THEN
            IF lastFav == 0 THEN
                CALL Fav_Found_Handler
                SET lastFav 1
                LET idleCount 0 
            ENDIF
        ELSE
            IF lastFav != 0 THEN
                CALL Fav_Lost_Handler
                SET lastFav 0
                LET idleCount 0 
            ENDIF
        ENDIF

        IF cdtUnfav > 20 THEN
            IF lastUnfav == 0 THEN
                CALL Unfav_Found_Handler
                SET lastUnfav 1
                LET idleCount 0 
            ENDIF
        ELSE
            IF lastUnfav != 0 THEN
                CALL Unfav_Lost_Handler
                SET lastUnfav 0
                LET idleCount 0 
            ENDIF
        ENDIF

        ////////////////////////////////
        // normal sensors
        
        IF Head_Hit <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Head_Hit"
            ENDIF
            //{ "Sensor All/Head Hit"
                PLAY ACTION STAND
                WAIT
            //}
            SET Head_Hit 0
            LET idleCount 0 
        ENDIF
        
        IF Head_Pat <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Head_Pat"
            ENDIF
            //{ "Sensor All/Head Pat"
                PLAY ACTION SIT
                WAIT
            //}
            SET Head_Pat 0
            LET idleCount 0 
        ENDIF

        IF Head_LONG <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Head_LONG"
            ENDIF
            //{ "Sensor All/Head press long time"
                PLAY ACTION LIE
                WAIT
            //}
            SET Head_LONG 0
            LET idleCount 0 
        ENDIF

        IF Head_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Head_ON"
            ENDIF
            //{ "Sensor All/Head pressed"
            //}
            SET Head_ON 0
            LET idleCount 0 
        ENDIF

        IF Head_OFF <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Head_OFF = %d (ms)" Head_OFF
            ENDIF
            //{ "Sensor All/Head released"
            //}
            SET Head_OFF 0
            LET idleCount 0 
        ENDIF

        IF Back_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Back_ON"
            ENDIF
            //{ "Sensor 2x0/Back pressed"
                PLAY ACTION LIE
                WAIT
            //}
            SET Back_ON 0
            LET idleCount 0 
        ENDIF

        IF Back_LONG <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Back_LONG"
            ENDIF
            //{ "Sensor 2x0/Back pressed for a long time"
            //}
            SET Back_LONG 0
            LET idleCount 0 
        ENDIF

        IF Jaw_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Jaw_ON"
            ENDIF
            //{ "Sensor 2x0/Jaw pressed"
                PLAY ACTION TURN 180
                WAIT
            //}
            SET Jaw_ON 0
            LET idleCount 0 
        ENDIF

        IF Jaw_LONG <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Jaw_LONG"
            ENDIF
            //{ "Sensor 2x0/Jaw pressed for a long time"
            //}
            SET Jaw_LONG 0
            LET idleCount 0 
        ENDIF

        // 220 specific sensors
        IF RTail_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Right Tail"
            ENDIF
            //{ "Sensor 220/Right Tail button pressed"
                SET Spot 0
            //}
            SET RTail_ON 0
            LET idleCount 0 
        ENDIF

        IF CTail_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Center Tail"
            ENDIF
            //{ "Sensor 220/Center Tail button pressed"
                SET Spot 1
            //}
            SET CTail_ON 0
            LET idleCount 0 
        ENDIF

        IF LTail_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Left Tail"
            ENDIF
            //{ "Sensor 220/Left Tail button pressed"
                SET Spot 0
            //}
            SET LTail_ON 0
            LET idleCount 0 
        ENDIF

        // 310 specific sensors
        IF Tail_U_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail Up"
            ENDIF
            //{ "Sensor 31x/Tail pushed up"
                SET Horn_G 1
                SET Horn_O 1
                SET Horn_B 1
            //}
            SET Tail_U_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_D_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail Down"
            ENDIF
            //{ "Sensor 31x/Tail pushed down"
                SET Horn_G 0
                SET Horn_O 0
                SET Horn_B 0
            //}
            SET Tail_D_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_R_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail Right"
            ENDIF
            //{ "Sensor 31x/Tail pushed right"
            //}
            SET Tail_R_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_L_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail Left"
            ENDIF
            //{ "Sensor 31x/Tail pushed left"
            //}
            SET Tail_L_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_UR_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail UR"
            ENDIF
            //{ "Sensor 31x/Tail pushed up and right"
            //}
            SET Tail_UR_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_DR_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail DR"
            ENDIF
            //{ "Sensor 31x/Tail pushed down and right"
            //}
            SET Tail_DR_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_UL_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail UL"
            ENDIF
            //{ "Sensor 31x/Tail pushed up and left"
            //}
            SET Tail_UL_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_DL_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail DL"
            ENDIF
            //{ "Sensor 31x/Tail pushed down and left"
            //}
            SET Tail_DL_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_RollR <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail RollR"
            ENDIF
            //{ "Sensor 31x/Tail rolled right"
            //}
            SET Tail_RollR 0
            LET idleCount 0 
        ENDIF

        IF Tail_RollL <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail RollL"
            ENDIF
            //{ "Sensor 31x/Tail rolled left"
            //}
            SET Tail_RollL 0
            LET idleCount 0 
        ENDIF

        IF Tail_Roll3 <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail Roll3"
            ENDIF
            //{ "Sensor 31x/Tail rolled three times"
            //}
            SET Tail_Roll3 0
            LET idleCount 0 
        ENDIF

        LET postureOld postureNow
        LET postureNow Posture1  // posture in case it has changed

        IF postureNow == 3 THEN
            // currently in the LIE DOWN position
            // front paws can be used for input
            IF postureOld <> 3 THEN
                IF doPrint <> 0 THEN
                    PRINT "postureNew=SLEEP - will respond to front paws"
                ENDIF
                SET RFLeg_ON 0 // clear old values
                SET LFLeg_ON 0
            ENDIF

            IF RFLeg_ON <> 0 THEN
                IF doPrint <> 0 THEN
                    PRINT "Sensor: Front RFLeg_ON (LIEDOWN)"
                ENDIF
                //{ "Sensor All/RF Paw (sleep position)"
                //}
                SET RFLeg_ON 0
                LET idleCount 0 
            ENDIF

            IF LFLeg_ON <> 0 THEN
                IF doPrint <> 0 THEN
                    PRINT "Sensor: Front LFLeg_ON (LIEDOWN)"
                ENDIF
                //{ "Sensor All/LF Paw (sleep position)"
                //}
                SET LFLeg_ON 0
                LET idleCount 0 
            ENDIF
        ENDIF


        IF AP_FaceDetect > 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Saw your face lvl=%d hpos=%d" AP_FaceDetect AP_FaceDetect_Horz

            ENDIF

            // level can be 1->5, we provide two options
            IF AP_FaceDetect > 3 THEN
                //{ "Sensor All/HumanFace Seen Up-Close"
                    SET Warn 1 // warning light goes on during playing
                    PLAY ACTION REFLEX_SURPRISE16_SND
                    WAIT
                    SET Warn 0
                //}
            ELSE
                //{ "Sensor All/HumanFace Seen Far-Away"
                    PLAY ACTION REFLEX_SURPRISE16_SND
                    WAIT
                //}
            ENDIF
            SET AP_FaceDetect 0
            LET idleCount 0 
        ENDIF

        IF AP_FaceDetect < 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Lost sight of your face"
            ENDIF
            //{ "Sensor All/Lost HumanFace"
                PLAY ACTION FEELING_DISLIKE16_SND
                WAIT
            //}
            SET AP_FaceDetect 0
            LET idleCount 0 
        ENDIF

        ADD idleCount 1
        IF idleCount > 100 THEN
            // 100 ticks (approx 10 seconds) with nothing happening
            IF doPrint <> 0 THEN
                PRINT "Idle: postureNow = %d" postureNow
            ENDIF
            IF postureNow == 1 THEN // STAND
                CALL DoSomethingRandom_Stand
            ENDIF
            IF postureNow == 2 THEN // SIT
                CALL DoSomethingRandom_Sit
            ENDIF
            IF postureNow == 3 THEN // LIE / SLEEP
                CALL DoSomethingRandom_Sleep
            ENDIF
            // otherwise walking or something else
            LET idleCount 0
        ENDIF

        WAIT 100
    WEND // end of main loop

EXIT

/////////////////////////////////////////////////////////////
// Random skits after 10 seconds of idleness

:DoSomethingRandom_Stand
    LOCAL randVal
    RND randVal 1 5
    IF randVal == 1 THEN
        //{ "Idle/Stand Random#1"
            PLAY ACTION WALK 0 500
            WAIT
            PLAY ACTION ALONE_DANCE0_STD // (DANCE_STAND3) ; Play alone, Stepping {15:03:00} {AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 2 THEN
        //{ "Idle/Stand Random#2"
            PLAY ACTION ALONE_DANCE1_STD // (DANCE_STAND4) ; Play alone, Shake {15:03:01} {AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 3 THEN
        //{ "Idle/Stand Random#3"
            PLAY ACTION ALONE_GROOM2_STD // (SHUDDER) ; Play alone, Shake once standing after falling over. {15:01:02} {AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 4 THEN
        //{ "Idle/Stand Random#4"
            PLAY ACTION SIT // I'm tired of standing around
            WAIT
        //}
    ENDIF
    IF randVal == 5 THEN
        //{ "Idle/Stand Random#5"
            PLAY ACTION LIE // I'm tired of standing around
            WAIT
        //}
    ENDIF
RETURN

:DoSomethingRandom_Sit
    LOCAL randVal
    RND randVal 1 5
    IF randVal == 1 THEN
        //{ "Idle/Sit Random#1"
            PLAY ACTION ALONE_DANCE0_SIT // (DANCE_SIT2) ; Dance to Music, NoSound {15:05:00} {NO AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 2 THEN
        //{ "Idle/Sit Random#2"
            PLAY ACTION ALONE_DANCE1_SIT // (DANCE_SIT3) ; Dance to Music, NoSound {15:05:01} {NO AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 3 THEN
        //{ "Idle/Sit Random#3"
            PLAY ACTION ALONE_DANCE2_SIT // (DANCE_SIT1) ; Dance to Music, NoSound {15:05:02} {NO AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 4 THEN
        //{ "Idle/Sit Random#4"
            PLAY ACTION STAND // Let's get moving
            WAIT
        //}
    ENDIF
    IF randVal == 5 THEN
        //{ "Idle/Sit Random#5"
            PLAY ACTION LIE // I'm tired of sitting around
            WAIT
        //}
    ENDIF
RETURN

:DoSomethingRandom_Sleep // AKA "lie down"
    LOCAL randVal
    RND randVal 1 5
    IF randVal == 1 THEN
        //{ "Idle/Sleep Random#1"
            PLAY ACTION ALONE_DANCE0_SLP // (DANCE_SLEEP1) ; Play alone,SleepFlat {15:03:00} {AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 2 THEN
        //{ "Idle/Sleep Random#2"
            PLAY ACTION ALONE_DANCE1_SLP // (DANCE_SLEEP4) ; Play alone {15:03:01} {AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 3 THEN
        //{ "Idle/Sleep Random#3"
            PLAY ACTION ALONE_EXERCISE0_SLP // Play alone {15:00:00} {AUDIO}
            WAIT
        //}
    ENDIF
    IF randVal == 4 THEN
        //{ "Idle/Sleep Random#4"
            PLAY ACTION STAND // Let's get moving
            WAIT
        //}
    ENDIF
    IF randVal == 5 THEN
        //{ "Idle/Sleep Random#5"
            PLAY ACTION SIT // Get up
            WAIT
        //}
    ENDIF
RETURN


/////////////////////////////////////////////////////////////
// _Handler routines - YART compatible

:Voice_Handler
  ARG id
  ARG level
  ARG pitch
  ARG horz

  IF doPrint <> 0 THEN
    PRINT "Voice_Handler: %d, level=%d, pitch=%d, horz=%d" id level pitch horz
  ENDIF

  IF id == 1 THEN
    //{ "AIBO voice command/'AIBO' or <dog's name>"
        PLAY ACTION KICK 30 1000
        WAIT
    //}
  ENDIF
  IF id == 0x100 THEN
    //{ "AIBO voice command/<owner's name>"
        PLAY ACTION KICK -30 1000
        WAIT
    //}
  ENDIF
  IF id == 2 THEN
    //{ "AIBO voice command/'What's your name?'"
        CALL RCR_SayDogsName
    //}
  ENDIF
  IF id == 3 THEN
    //{ "AIBO voice command/'Say hello'"
    //}
  ENDIF
  IF id == 4 THEN
    //{ "AIBO voice command/'Shake paw'"
        PLAY ACTION KICK -30 1000
        WAIT
    //}
  ENDIF
  IF id == 5 THEN
    //{ "AIBO voice command/'Morning'"
    //}
  ENDIF
  IF id == 6 THEN
    //{ "AIBO voice command/'Hello'"
    //}
  ENDIF
  IF id == 7 THEN
    //{ "AIBO voice command/'Good night'"
    //}
  ENDIF
  IF id == 8 THEN
    //{ "AIBO voice command/'See you'"
    //}
  ENDIF
  IF id == 9 THEN
    //{ "AIBO voice command/'How are you?'"
    //}
  ENDIF
  IF id == 10 THEN
    //{ "AIBO voice command/'Hey AIBO'"
    //}
  ENDIF
  IF id == 11 THEN
    //{ "AIBO voice command/'Thanks'"
    //}
  ENDIF
  IF id == 12 THEN
    //{ "AIBO voice command/'Sorry'"
    //}
  ENDIF
  IF id == 13 THEN
    //{ "AIBO voice command/'Cheer up'"
    //}
  ENDIF
  IF id == 14 THEN
    //{ "AIBO voice command/'Banzai'"
    //}
  ENDIF
  IF id == 15 THEN
    //{ "AIBO voice command/'That's right'"
    //}
  ENDIF
  IF id == 16 THEN
    //{ "AIBO voice command/'That's wrong'"
    //}
  ENDIF
  IF id == 17 THEN
    //{ "AIBO voice command/'Good AIBO'"
    //}
  ENDIF
  IF id == 18 THEN
    //{ "AIBO voice command/'Don't do that'"
    //}
  ENDIF
  IF id == 19 THEN
    //{ "AIBO voice command/'Let's play!'"
    //}
  ENDIF
  IF id == 20 THEN
    //{ "AIBO voice command/'Sing a song'"
    //}
  ENDIF
  IF id == 21 THEN
    //{ "AIBO voice command/'Dance'"
    //}
  ENDIF
  IF id == 22 THEN
    //{ "AIBO voice command/'Show time'"
    //}
  ENDIF
  IF id == 23 THEN
    //{ "AIBO voice command/'Pose for me'"
    //}
  ENDIF
  IF id == 24 THEN
    //{ "AIBO voice command/'Clown around'"
    //}
  ENDIF
  IF id == 25 THEN
    //{ "AIBO voice command/'Show off'"
    //}
  ENDIF
  IF id == 26 THEN
    //{ "AIBO voice command/'Say message'"
    //}
  ENDIF
  IF id == 27 THEN
    //{ "AIBO voice command/'Let's be secret'"
    //}
  ENDIF
  IF id == 28 THEN
    //{ "AIBO voice command/'Open sesame'"
    //}
  ENDIF
  IF id == 29 THEN
    //{ "AIBO voice command/'Happy day'"
    //}
  ENDIF
  IF id == 30 THEN
    //{ "AIBO voice command/'Stand up'"
        PLAY ACTION STAND
        WAIT
    //}
  ENDIF
  IF id == 31 THEN
    //{ "AIBO voice command/'Lie down'"
        PLAY ACTION LIE
        WAIT
    //}
  ENDIF
  IF id == 32 THEN
    //{ "AIBO voice command/'Sit down'"
        PLAY ACTION SIT
        WAIT
    //}
  ENDIF
  IF id == 33 THEN
    //{ "AIBO voice command/'Turn right'"
        PLAY ACTION TURN -90
        WAIT
    //}
  ENDIF
  IF id == 34 THEN
    //{ "AIBO voice command/'Turn left'"
        PLAY ACTION TURN 90
        WAIT
    //}
  ENDIF
  IF id == 35 THEN
    //{ "AIBO voice command/'Go forward'"
        PLAY ACTION WALK 0 500
        WAIT
    //}
  ENDIF
  IF id == 36 THEN
    //{ "AIBO voice command/'Go backward'"
        PLAY ACTION TURN 180
        WAIT
    //}
  ENDIF
  IF id == 37 THEN
    //{ "AIBO voice command/'Go ahead'"
        PLAY ACTION WALK 0 100
        WAIT
    //}
  ENDIF
  IF id == 38 THEN
    //{ "AIBO voice command/'Stop'"
    //}
  ENDIF
  IF id == 39 THEN
    //{ "AIBO voice command/'Faster'"
    //}
  ENDIF
  IF id == 40 THEN
    //{ "AIBO voice command/'Slow down'"
    //}
  ENDIF
  IF id == 41 THEN
    //{ "AIBO voice command/'Pink ball'"
    //}
  ENDIF
  IF id == 42 THEN
    //{ "AIBO voice command/'Right leg kick'"
        PLAY ACTION KICK -30 1000
        WAIT
    //}
  ENDIF
  IF id == 43 THEN
    //{ "AIBO voice command/'Right leg touch'"
    //}
  ENDIF
  IF id == 44 THEN
    //{ "AIBO voice command/'Left leg kick'"
        PLAY ACTION KICK 30 1000
        WAIT
    //}
  ENDIF
  IF id == 45 THEN
    //{ "AIBO voice command/'Left leg touch'"
    //}
  ENDIF
  IF id == 46 THEN
    //{ "AIBO voice command/'Ready set go'"
    //}
  ENDIF
  IF id == 47 THEN
    //{ "AIBO voice command/'You won'"
    //}
  ENDIF
  IF id == 48 THEN
    //{ "AIBO voice command/'You lost'"
    //}
  ENDIF
  IF id == 49 THEN
    //{ "AIBO voice command/'Action one'"
    //}
  ENDIF
  IF id == 50 THEN
    //{ "AIBO voice command/'Action two'"
    //}
  ENDIF
  IF id == 51 THEN
    //{ "AIBO voice command/'Action three'"
    //}
  ENDIF
  IF id == 52 THEN
    //{ "AIBO voice command/'Action four'"
    //}
  ENDIF
  IF id == 53 THEN
    //{ "AIBO voice command/'Action five'"
    //}
  ENDIF
  IF id == 54 THEN
    //{ "AIBO voice command/'I'm here'"
    //}
  ENDIF
  IF id == 55 THEN
    //{ "AIBO voice command/'Take a picture'"
        CALL RCR_TakeAPicture
    //}
  ENDIF
  IF id == 56 THEN
    //{ "AIBO voice command/'Karate chop'"
    //}
  ENDIF
  IF id == 57 THEN
    //{ "AIBO voice command/'Walk around'"
    //}
  ENDIF
  IF id == 58 THEN
    //{ "AIBO voice command/'Are you tired?'"
    //}
  ENDIF
  IF id == 59 THEN
    //{ "AIBO voice command/'Are you hungry?'"
    //}
  ENDIF
  IF id == 60 THEN
    //{ "AIBO voice command/'Name registration'"
        CALL RCR_RecordDogsName
    //}
  ENDIF
  IF id == 61 THEN
    //{ "AIBO voice command/'Good boy'"
    //}
  ENDIF
  IF id == 62 THEN
    //{ "AIBO voice command/'Good girl'"
    //}
  ENDIF
  IF id == 63 THEN
    //{ "AIBO voice command/'Bad boy'"
    //}
  ENDIF
  IF id == 64 THEN
    //{ "AIBO voice command/'Bad girl'"
    //}
  ENDIF
  IF id == 65 THEN
    //{ "AIBO voice command/'Let's talk'"
    //}
  ENDIF
  IF id == 66 THEN
    //{ "AIBO voice command/'Be quiet'"
    //}
  ENDIF
  IF id == 67 THEN
    //{ "AIBO voice command/'What's you owner's name'"
        CALL RCR_SayOwnersName
    //}
  ENDIF
  IF id == 68 THEN
    //{ "AIBO voice command/'Owner registration'"
        CALL RCR_RecordOwnersName
    //}
  ENDIF
  IF id == 69 THEN
    //{ "AIBO voice command/'Function check'"
    //}
  ENDIF

RETURN

///////////////////////

:Loud_Handler
  ARG level
  ARG pitch
  ARG horz

  IF doPrint <> 0 THEN
    PRINT "Loud_Handler: level=%d, pitch=%d, horz=%d" level pitch horz
  ENDIF

  //{ "AIBO hears/loud sound"
  //}
RETURN

///////////////////////

:AiboTone_Handler
  ARG id

  IF doPrint <> 0 THEN
    PRINT "AiboTone_Handler: %d" id
  ENDIF

RETURN

///////////////////////

:AiboSound_Handler
  ARG id

  IF doPrint <> 0 THEN
    PRINT "AiboSound_Handler: %d" id
  ENDIF

  //{ "AIBO hears/another AIBO"
  //}
RETURN

///////////////////////

:Noise_Handler

  IF doPrint <> 0 THEN
    PRINT "Noise_Handler"
  ENDIF

  //{ "AIBO hears/noise"
  //}

RETURN

///////////////////////

:Rhythm_Handler
  IF doPrint <> 0 THEN
    PRINT "Rhythm_Handler"
  ENDIF

  //{ "AIBO hears/music with rhythm"
  //}
RETURN

///////////////////////
// Pink Ball

:PinkBall_Found_Handler
  ARG hangle
  ARG vangle
  ARG dist

  IF doPrint <> 0 THEN
    PRINT "PinkBall_Found_Handler (%d %d) %d" hangle vangle dist
  ENDIF

  //{ "AIBO sees/Pink Ball (seen)"
      PLAY ACTION STAND
      WAIT
      PLAY ACTION WALK 0 100
      WAIT
  //}
RETURN

:PinkBall_Lost_Handler
  IF doPrint <> 0 THEN
    PRINT "PinkBall_Lost_Handler (%d %d) %d" hangle vangle dist
  ENDIF
  //{ "AIBO sees/Pink Ball (lost)"
      PLAY ACTION SIT
      WAIT
  //}

RETURN

:PinkBall_Any_Handler // called quite often when tracking
  ARG hangle
  ARG vangle
  ARG dist

  //{ "AIBO sees/Pink Ball (tracking)"
  //}

RETURN

///////////////////////

:Fav_Found_Handler
  IF doPrint <> 0 THEN
    PRINT "Fav_Found_Handler"
  ENDIF

  //{ "AIBO sees/Fav Color (seen)"
  //}

RETURN

:Fav_Lost_Handler
  IF doPrint <> 0 THEN
    PRINT "Fav_Lost_Handler"
  ENDIF

  //{ "AIBO sees/Fav Color (lost)"
  //}

RETURN

///////////////////////

:Unfav_Found_Handler
  IF doPrint <> 0 THEN
    PRINT "Unfav_Found_Handler"
  ENDIF

  //{ "AIBO sees/Unfav Color (seen)"
  //}

RETURN

:Unfav_Lost_Handler
  IF doPrint <> 0 THEN
    PRINT "Unfav_Lost_Handler"
  ENDIF

  //{ "AIBO sees/Unfav Color (lost)"
  //}

RETURN


/////////////////////////////////////////////////////////////
:DoDebugMode
    PRINT "DBL testing"

    LOCAL fpu_array 25 // last available array
    LOCAL a
    LOCAL b

    AP_DIM fpu_array 80 // 80*2=160 bytes - enough room for 20 doubles
    SET AP_fpu fpu_array // now in use (all DBL_ opcodes will use it)

    DBL_SET 1 1 0 // fpu[1] = 1
    DBL_SET 2 2 0 // fpu[2] = 2
    DBL_ADD 3 1 2 // fpu[3] = fpu[1] + fpu[2]
    DBL_GET 3 a b
    IF a <> 3 THEN
       PRINT "DBL_ERROR add1"
    ENDIF
    IF b <> 0 THEN
       PRINT "DBL_ERROR add2"
    ENDIF
    DBL_SET 2 2 5000 // fpu[2] = 2.5

    DBL_ADD 9 3 2 // 3 + 2 = 5.5
    DBL_ADD 9 9 1 4000 // immediate form +1.4 (=6.9)
    DBL_ADD 9 9 -4 1000 // -4.1 (=2.8)
    DBL_SUB 9 9 0 1000 // -.1 (=2.7)
    DBL_GET 9 a b
    IF a <> 2 THEN
       PRINT "DBL_ERROR add3"
    ENDIF
    IF b <> 7000 THEN
       PRINT "DBL_ERROR add4"
    ENDIF
    
    DBL_MUL 9 9 10 0
    DBL_DIV 9 9 7 0
    DBL_ADD 9 9 90 3333
    DBL_GET 9 a b // 2.7 * 10 / 7 + 90.3333 = 94.1904
    IF a <> 94 THEN
       PRINT "DBL_ERROR mul1"
    ENDIF
    IF b <> 1904 THEN
       PRINT "DBL_ERROR mul2"
    ENDIF

    // some trig (angles in radians)
    // fpu[1] = 1.0
    DBL_SIN 4 1
    DBL_TAN 5 1
    DBL_ADD 9 5 4 // sin(1.0) + tan(1.0) = .8414 + 1.5574 = 2.3988

    DBL_ATAN2 6 1 0 // atan(1/0) = 1.5707 (pi/2)
    DBL_ADD 9 9 6
    DBL_ATAN2 7 1 1 // atan(1/1) = .7953 
    DBL_ADD 9 9 7

    // fpu[9] = sum of different trig calculations
        // 4.7548 fixed point with rounding error
        // 4.755073(etc) floating point
    DBL_GET 9 a b // 
    IF a <> 4 THEN
       PRINT "DBL_ERROR trig1"
    ENDIF
    IF b <> 7550 THEN
       PRINT "DBL_ERROR trig2"
    ENDIF

    // misc functions
    DBL_SQRT 10 2 0 // sqrt 2.0
    DBL_SQRT 11 2 // sqrt fpu[2] = 2.5
    DBL_ADD 9 10 11

    // calculate 10^4
    DBL_LOG 14 10 0 // fpu[14] = ln(10.0)
    DBL_MUL 15 14 4 0 // fpu[15] = 4.0*ln(10.0)
    DBL_EXP 16 15   // fpu[16] = exp(4.0*ln(10.0)) = 10 ^ 4
    DBL_ADD 9 9 16

    DBL_GET 9 a b
    IF a <> 10002 THEN
       PRINT "DBL_ERROR misc1"
    ENDIF
    IF b <> 9953 THEN
       PRINT "DBL_ERROR misc2"
    ENDIF

    PRINT "DBL testing complete"

 IF 1 == 1 THEN
    PRINT "DBL fpu register dump (non-zero)"
    FOR i 0 19
        DBL_GET i a b
        IF a <> 0 THEN
            PRINT "  fpu[%d] = %d.%04d" i a b
        ELSE
            IF b > 0 THEN
                PRINT "  fpu[%d] = 0.%04d" i b
            ENDIF
            IF b < 0 THEN
                LOCAL negb 0
                SUB negb b
                PRINT "  fpu[%d] = -0.%04d" i bneg
            ENDIF
            // no report if 0.0
        ENDIF
    NEXT
 ENDIF

RETURN

/////////////////////////////////////////////////////////////
// Include 'RCR' RCode Runtime

#AP_INCLUDE /MS/OPEN-R/APP/PC/AMS/rcrlib.r

/////////////////////////////////////////////////////////////
