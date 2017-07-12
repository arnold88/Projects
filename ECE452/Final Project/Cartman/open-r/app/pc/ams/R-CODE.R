/////////////////////////////////////////////////////////////
// default RCodePlus Program - Cartman version
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
        PLAY ACTION SIT
        WAIT
        PLAY ACTION+ OTHER_HOWDY // OTHER_HOWDY.WAV + motion + leds
        WAIT
    //}

    // clear globals and sensors

    CLR SENSORS
    LOCAL lastPink 0
    LOCAL lastFav 0
    LOCAL lastUnfav 0
    LOCAL lastHead 0
    LOCAL idleCount 0

    LOCAL postureOld -1
    LOCAL postureNow -1

    IF debug != 0 THEN
        PRINT "Calling DoDebugMode"
        CALL DoDebugMode
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
                PLAY ACTION+ FINGWEAK // "Man, this is f***'ing weak"
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
                PLAY ACTION+ SWEET // SWEET.WAV
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
                PLAY ACTION+ BEEFCAKE // BEEFCAKE.WAV + motion + leds
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
                // leave empty and use Hit/Pat instead
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
                PLAY ACTION STAND
                WAIT
                PLAY ACTION+ SWEET // SWEET.WAV
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
                PLAY ACTION+ LOVE_YOU_GUYS
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
                PLAY ACTION+ DONT_CALL_ME_ASSHOLE // DONT_CALL_ME_ASSHOLE.WAV + motion + leds
                WAIT
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
                PLAY ACTION+ MINGLI1 // MINGLI1.WAV + motion + leds
                WAIT
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
                PLAY ACTION+ BEEFCAKE // BEEFCAKE.WAV + motion + leds
                WAIT
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
                PLAY ACTION+ MINGLI2 // MINGLI2.WAV + motion + leds
                WAIT
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
                PLAY ACTION+ OTHER_BEATING_OFF_THE_DOG // OTHER_BEATING_OFF_THE_DOG.WAV + motion + leds
                WAIT
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
                PLAY ACTION+ NOT_FOLLOWING // NOT_FOLLOWING.WAV + motion + leds
                WAIT
            //}
            SET Tail_D_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_R_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail Right"
            ENDIF
            //{ "Sensor 31x/Tail pushed right"
                PLAY ACTION+ OTHER_KICK_THE_BABY // OTHER_KICK_THE_BABY.WAV + motion + leds
                WAIT
            //}
            SET Tail_R_ON 0
            LET idleCount 0 
        ENDIF

        IF Tail_L_ON <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail Left"
            ENDIF
            //{ "Sensor 31x/Tail pushed left"
                PLAY ACTION+ POUNDSTONE // POUNDSTONE.WAV + motion + leds
                WAIT
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
                PLAY ACTION+ OTHER_BEATING_OFF_THE_DOG // OTHER_BEATING_OFF_THE_DOG.WAV + motion + leds
                WAIT
            //}
            SET Tail_RollR 0
            LET idleCount 0 
        ENDIF

        IF Tail_RollL <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail RollL"
            ENDIF
            //{ "Sensor 31x/Tail rolled left"
                PLAY ACTION+ OTHER_BEATING_OFF_THE_DOG // OTHER_BEATING_OFF_THE_DOG.WAV + motion + leds
                WAIT
            //}
            SET Tail_RollL 0
            LET idleCount 0 
        ENDIF

        IF Tail_Roll3 <> 0 THEN
            IF doPrint <> 0 THEN
                PRINT "Sensor: Tail Roll3"
            ENDIF
            //{ "Sensor 31x/Tail rolled three times"
                PLAY ACTION+ OTHER_BEATING_OFF_THE_DOG // OTHER_BEATING_OFF_THE_DOG.WAV + motion + leds
                WAIT
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
                    PLAY ACTION+ BEEFCAKE // BEEFCAKE.WAV + motion + leds
                    WAIT
                //}
                SET RFLeg_ON 0
                LET idleCount 0 
            ENDIF

            IF LFLeg_ON <> 0 THEN
                IF doPrint <> 0 THEN
                    PRINT "Sensor: Front LFLeg_ON (LIEDOWN)"
                ENDIF
                //{ "Sensor All/LF Paw (sleep position)"
                    PLAY ACTION+ FLIPMEOFF // FLIPMEOFF.WAV + motion + leds
                    WAIT
                //}
                SET LFLeg_ON 0
                LET idleCount 0 
            ENDIF
        ENDIF


        IF AP_FaceDetect <> 0 THEN
            // REVIEW: make YART-able later (including Lost)
            PRINT "FACE %d %d" AP_FaceDetect AP_FaceDetect_Horz
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
            PLAY ACTION+ SPEED1 // SPEED1.WAV + motion + leds
            WAIT
        //}
    ENDIF
    IF randVal == 2 THEN
        //{ "Idle/Stand Random#2"
            PLAY ACTION+ MOM_CARPET
            WAIT
            PLAY ACTION ALONE_DANCE1_STD
            WAIT
        //}
    ENDIF
    IF randVal == 3 THEN
        //{ "Idle/Stand Random#3"
            PLAY ACTION ALONE_GROOM2_STD
            WAIT
            PLAY ACTION+ WALK2 // WALK2.WAV + motion + leds
            WAIT
            PLAY ACTION WALK 0 500
            WAIT
        //}
    ENDIF
    IF randVal == 4 THEN
        //{ "Idle/Stand Random#4"
            PLAY ACTION+ SMELLS_LIKE_ASS // SMELLS_LIKE_ASS.WAV + motion + leds
            WAIT
            PLAY ACTION SIT // I'm tired of standing around
            WAIT
        //}
    ENDIF
    IF randVal == 5 THEN
        //{ "Idle/Stand Random#5"
            PLAY ACTION+ NOT_FOLLOWING // NOT_FOLLOWING.WAV + motion + leds
            WAIT
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
            PLAY ACTION+ KITTY_SKIT // KITTY_SKIT.WAV + motion + leds
            WAIT
        //}
    ENDIF
    IF randVal == 2 THEN
        //{ "Idle/Sit Random#2"
            PLAY ACTION+ MAKE_BABIES // MAKE_BABIES.WAV + motion + leds
            WAIT
        //}
    ENDIF
    IF randVal == 3 THEN
        //{ "Idle/Sit Random#3"
            PLAY ACTION ALONE_DANCE2_SIT
            PLAY ACTION+ WE_NEED_CHICKS // WE_NEED_CHICKS.WAV + motion + leds
            WAIT
        //}
    ENDIF
    IF randVal == 4 THEN
        //{ "Idle/Sit Random#4"
            PLAY ACTION+ SCREWUGUYS_GOINGHOME // SCREWUGUYS_GOINGHOME.WAV + motion + leds
            WAIT
            PLAY ACTION STAND // Let's get moving
            WAIT
        //}
    ENDIF
    IF randVal == 5 THEN
        //{ "Idle/Sit Random#5"
            PLAY ACTION LIE // I'm tired of sitting around
            WAIT
            PLAY ACTION+ STORY_NANCY_DREW // STORY_NANCY_DREW.WAV + motion + leds
            WAIT
        //}
    ENDIF
RETURN

:DoSomethingRandom_Sleep // AKA "lie down"
    LOCAL randVal
    RND randVal 1 5
    IF randVal == 1 THEN
        //{ "Idle/Sleep Random#1"
            PLAY ACTION+ STEVIE_WONDER // STEVIE_WONDER.WAV + motion + leds
            WAIT
        //}
    ENDIF
    IF randVal == 2 THEN
        //{ "Idle/Sleep Random#2"
            PLAY ACTION ALONE_DANCE1_SLP
            WAIT
            PLAY ACTION+ OVERCROWDED // OVERCROWDED.WAV + motion + leds
            WAIT
        //}
    ENDIF
    IF randVal == 3 THEN
        //{ "Idle/Sleep Random#3"
            PLAY ACTION OFF_ESCAPE0_SLP // Offensive (attack dog) {33:04:00}
            PLAY ACTION+ OTHER_KICK_THE_BABY // OTHER_KICK_THE_BABY.WAV + motion + leds
            WAIT
            WAIT 2000 // Wait 2 seconds
            PLAY ACTION+ OTHER_KILLED_KENNY // OTHER_KILLED_KENNY.WAV + motion + leds
            WAIT
        //}
    ENDIF
    IF randVal == 4 THEN
        //{ "Idle/Sleep Random#4"
            PLAY ACTION STAND // Let's get moving
            WAIT
            PLAY ACTION+ ROSHAM // ROSHAM.WAV + motion + leds
            WAIT
        //}
    ENDIF
    IF randVal == 5 THEN
        //{ "Idle/Sleep Random#5"
            PLAY ACTION SIT // I'm tired of sitting around
            WAIT
            PLAY ACTION+ THERE_YOU_ARE // THERE_YOU_ARE.WAV + motion + leds
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
        PLAY ACTION+ WHAT_THE_HELL
        WAIT
    //}
  ENDIF
  IF id == 0x100 THEN
    //{ "AIBO voice command/<owner's name>"
        PLAY ACTION+ WHEN_SAY_SHIT // WHEN_SAY_SHIT.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 2 THEN
    //{ "AIBO voice command/'What's your name?'"
        PLAY ACTION+ OTHER_CARTMAN
        WAIT
    //}
  ENDIF
  IF id == 3 THEN
    //{ "AIBO voice command/'Say hello'"
        PLAY ACTION SIT
        WAIT
        PLAY ACTION+ OTHER_HOWDY // Mr Hanky
        WAIT
    //}
  ENDIF
  IF id == 4 THEN
    //{ "AIBO voice command/'Shake paw'"
        PLAY ACTION+ BLACKASS // BLACKASS.WAV
        WAIT
    //}
  ENDIF
  IF id == 5 THEN
    //{ "AIBO voice command/'Morning'"
        PLAY ACTION SIT
        WAIT
        PLAY ACTION+ OTHER_HOWDY
        WAIT
    //}
  ENDIF
  IF id == 6 THEN
    //{ "AIBO voice command/'Hello'"
        PLAY ACTION+ STORY_SWEATER
        WAIT
    //}
  ENDIF
  IF id == 7 THEN
    //{ "AIBO voice command/'Good night'"
        PLAY ACTION+ SCREWUGUYS_GOINGHOME // SCREWUGUYS_GOINGHOME.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 8 THEN
    //{ "AIBO voice command/'See you'"
        PLAY ACTION+ SCREWUGUYS_GOINGHOME // SCREWUGUYS_GOINGHOME.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 9 THEN
    //{ "AIBO voice command/'How are you?'"
        PLAY ACTION SIT
        WAIT
        PLAY ACTION EMOTION_SAD1_SLP2 // {20:01:01}
        WAIT
        PLAY ACTION+ STORY_GRANDMA
        WAIT
    //}
  ENDIF
  IF id == 10 THEN
    //{ "AIBO voice command/'Hey AIBO'"
        PLAY ACTION STAND
        WAIT
        PLAY ACTION KICK 30 1000 // Kick Left (nowait)
        PLAY ACTION+ NUTS // NUTS.WAV
        WAIT
    //}
  ENDIF
  IF id == 11 THEN
    //{ "AIBO voice command/'Thanks'"
        PLAY ACTION+ LAUNDRY // LAUNDRY.WAV
        WAIT
    //}
  ENDIF
  IF id == 12 THEN
    //{ "AIBO voice command/'Sorry'"
        PLAY ACTION STAND
        WAIT
        PLAY ACTION KICK -30 1000 // Kick Right (nowait)
        PLAY ACTION+ NUTS3 // NUTS3.WAV
        WAIT
    //}
  ENDIF
  IF id == 13 THEN
    //{ "AIBO voice command/'Cheer up'"
        PLAY ACTION STAND
        WAIT
        PLAY ACTION+ PROSTITUTES // PROSTITUTES.WAV + motion + leds
        WAIT
        WAIT 1000 // Wait 1 second
        PLAY ACTION+ COOL // COOL.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 14 THEN
    //{ "AIBO voice command/'Banzai'"
        PLAY ACTION+ CRIPPLEFIGHT // CRIPPLEFIGHT.WAV + motion + leds
        WAIT
        PLAY ACTION STAND
        WAIT
        PLAY ACTION+ GUN_NAM // GUN_NAM.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 15 THEN
    //{ "AIBO voice command/'That's right'"
        PLAY ACTION SIT
        WAIT
        PLAY ACTION EMOTION_JOY2_SIT // (BORED_SIT1) ;SitWide {20:00:02}
        WAIT
        PLAY ACTION+ COOL // COOL.WAV
        WAIT
    //}
  ENDIF
  IF id == 16 THEN
    //{ "AIBO voice command/'That's wrong'"
        PLAY ACTION+ SUCKED_ASS
        WAIT
        PLAY ACTION PHYSIO_EXCRETE0_STD // {1a:00:00}
        WAIT
        PLAY ACTION+ BLACKASS // BLACKASS.WAV
        WAIT
    //}
  ENDIF
  IF id == 17 THEN
    //{ "AIBO voice command/'Good AIBO'"
        PLAY ACTION+ SWEET // SWEET.WAV
        WAIT
    //}
  ENDIF
  IF id == 18 THEN
    //{ "AIBO voice command/'Don't do that'"
        PLAY ACTION OFF_ESCAPE0_SLP // Offensive (attack dog) {33:04:00}
        PLAY ACTION+ BUTMOM1
        WAIT
    //}
  ENDIF
  IF id == 19 THEN
    //{ "AIBO voice command/'Let's play!'"
        PLAY ACTION+ STARING_FROG
        WAIT
        WAIT 1000
        PLAY ACTION+ CHEESYPOOFS // CHEESYPOOFS.WAV
        WAIT
        WAIT 1000
        PLAY ACTION+ SANDY_VAGINA
        WAIT
    //}
  ENDIF
  IF id == 20 THEN
    //{ "AIBO voice command/'Sing a song'"
        PLAY ACTION SIT
        WAIT
        PLAY ACTION+ SONG_KYLESMOM // long song
        WAIT
    //}
  ENDIF
  IF id == 21 THEN
    //{ "AIBO voice command/'Dance'"
        PLAY ACTION+ STORY_SMOKECRACK
        WAIT
    //}
  ENDIF
  IF id == 22 THEN
    //{ "AIBO voice command/'Show time'"
        PLAY ACTION SIT
        WAIT
        PLAY ACTION+ MOM_GLADIATORS // MOM_GLADIATORS.WAV + motion + leds
        WAIT
        WAIT 1000 // Wait 1 second
        PLAY ACTION+ SHOWTIME // SHOWTIME.WAV
        WAIT
        PLAY ACTION ALONE_DANCE0_SIT // Dance to Music, NoSound {15:05:00}
        WAIT
        PLAY ACTION+ FREAKIN_COOL // FREAKIN_COOL.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 23 THEN
    //{ "AIBO voice command/'Pose for me'"
        PLAY ACTION+ KISSINGASS
        WAIT
        PLAY ACTION HUMAN_CHARM2_SIT // (KISS1) ; Play with human {11:05:02} {AUDIO}
        WAIT
        PLAY ACTION+ TAKE_PICTURE1
        WAIT
    //}
  ENDIF
  IF id == 24 THEN
    //{ "AIBO voice command/'Clown around'"
        PLAY ACTION EMOTION_DISGUST1_SIT // {20:04:01}
        WAIT
        PLAY ACTION+ KITTY_SKIT
        WAIT
    //}
  ENDIF
  IF id == 25 THEN
    //{ "AIBO voice command/'Show off'"
        PLAY ACTION+ SONG_BESTFRIENDS
        WAIT
    //}
  ENDIF
  IF id == 26 THEN
    //{ "AIBO voice command/'Say message'"
        PLAY ACTION+ CHICKEN_SHIT
        WAIT
        PLAY ACTION FEELING_CHEER1_SIT // Cheerful {21:00:01}
        WAIT
    //}
  ENDIF
  IF id == 27 THEN
    //{ "AIBO voice command/'Let's be secret'"
        PLAY ACTION+ MEEKROB
        WAIT
        WAIT 2000
        PLAY ACTION+ BUCKET_OF_SHIT
        WAIT
    //}
  ENDIF
  IF id == 28 THEN
    //{ "AIBO voice command/'Open sesame'"
        PLAY ACTION+ MOM_KITTY_DILDO
        WAIT
        WAIT 2000
        PLAY ACTION+ STORY_MAKEMEPIE
        WAIT
    //}
  ENDIF
  IF id == 29 THEN
    //{ "AIBO voice command/'Happy day'"
        PLAY ACTION+ LOVE_YOU_GUYS
        WAIT
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
        PLAY ACTION+ WALK2 // WALK2.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 38 THEN
    //{ "AIBO voice command/'Stop'"
        PLAY ACTION+ WALK5 // WALK5.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 39 THEN
    //{ "AIBO voice command/'Faster'"
        PLAY ACTION+ SPEED1
        WAIT
    //}
  ENDIF
  IF id == 40 THEN
    //{ "AIBO voice command/'Slow down'"
        PLAY ACTION+ RAINING_FROGS // RAINING_FROGS.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 41 THEN
    //{ "AIBO voice command/'Pink ball'"
        PLAY ACTION+ HELPME_SOB
        WAIT
        PLAY ACTION SEARCH_HEAD0_ANY // {09:00:00}
    //}
  ENDIF
  IF id == 42 THEN
    //{ "AIBO voice command/'Right leg kick'"
        PLAY ACTION+ SWEET // SWEET.WAV
        WAIT
        PLAY ACTION KICK -30 1000
        WAIT
    //}
  ENDIF
  IF id == 43 THEN
    //{ "AIBO voice command/'Right leg touch'"
        PLAY ACTION+ EXCUSE_ME // EXCUSE_ME.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 44 THEN
    //{ "AIBO voice command/'Left leg kick'"
        PLAY ACTION+ COOL // COOL.WAV
        WAIT
        PLAY ACTION KICK 30 1000
        WAIT
    //}
  ENDIF
  IF id == 45 THEN
    //{ "AIBO voice command/'Left leg touch'"
        PLAY ACTION+ EXCUSE_ME // EXCUSE_ME.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 46 THEN
    //{ "AIBO voice command/'Ready set go'"
        PLAY ACTION+ FLIPMEOFF // FLIPMEOFF.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 47 THEN
    //{ "AIBO voice command/'You won'"
        PLAY ACTION+ COP_AUTHORITAY
        WAIT
    //}
  ENDIF
  IF id == 48 THEN
    //{ "AIBO voice command/'You lost'"
        PLAY ACTION+ DONT_CALL_ME_PIGGY
        WAIT
        WAIT 2000
        PLAY ACTION+ OTHER_BEATING_OFF_THE_DOG // OTHER_BEATING_OFF_THE_DOG.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 49 THEN
    //{ "AIBO voice command/'Action one'"
        PLAY ACTION+ OTHER_KILLED_KENNY // OTHER_KILLED_KENNY.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 50 THEN
    //{ "AIBO voice command/'Action two'"
        PLAY ACTION+ OTHER_KILLED2 // OTHER_KILLED2.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 51 THEN
    //{ "AIBO voice command/'Action three'"
        PLAY ACTION+ OTHER_KICK_THE_BABY // OTHER_KICK_THE_BABY.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 52 THEN
    //{ "AIBO voice command/'Action four'"
        PLAY ACTION+ OTHER_FAT_BITCH // OTHER_FAT_BITCH.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 53 THEN
    //{ "AIBO voice command/'Action five'"
        PLAY ACTION+ OTHER_EMAIL_INTRO // OTHER_EMAIL_INTRO.WAV + motion + leds
        WAIT
    //}
  ENDIF
  IF id == 54 THEN
    //{ "AIBO voice command/'I'm here'"
        PLAY ACTION+ COURTNEY_LOVE
        WAIT
    //}
  ENDIF
  IF id == 55 THEN
    //{ "AIBO voice command/'Take a picture'"
        PLAY ACTION+ TAKE_PICTURE1 // MODE_PICTURE1.WAV
        WAIT
        CALL RCR_TakeAPicture
        PLAY ACTION+ TAKE_PICTURE2 // MODE_PICTURE2.WAV
        WAIT
    //}
  ENDIF
  IF id == 56 THEN
    //{ "AIBO voice command/'Karate chop'"
        PLAY ACTION+ SUCK_DONKEY_BALLS
        WAIT
        PLAY ACTION GUARD_ATTACK0_SIT2 // Guard Pal, Arms to Side {30:02:00}
        WAIT
        PLAY ACTION+ FREAKIN_COOL
        WAIT
    //}
  ENDIF
  IF id == 57 THEN
    //{ "AIBO voice command/'Walk around'"
        PLAY ACTION STAND
        WAIT
        PLAY ACTION WALK 0 300
        WAIT
        PLAY ACTION+ FUNKYWALK // FUNKYWALK.WAV
        WAIT
        PLAY ACTION WALK 0 600
        WAIT
        PLAY ACTION SIT
        WAIT
    //}
  ENDIF
  IF id == 58 THEN
    //{ "AIBO voice command/'Are you tired?'"
        PLAY ACTION+ GONNA_DIE
        WAIT
    //}
  ENDIF
  IF id == 59 THEN
    //{ "AIBO voice command/'Are you hungry?'"
        PLAY ACTION PHYSIO_HUNGRY0_SIT // (HUNGRY_LOT) ; {1a:05:00}
        WAIT
        PLAY ACTION+ NEEDFOOD
        WAIT
    //}
  ENDIF
  IF id == 60 THEN
    //{ "AIBO voice command/'Name registration'"
        PLAY ACTION+ DOESNTLISTEN
        WAIT
    //}
  ENDIF
  IF id == 61 THEN
    //{ "AIBO voice command/'Good boy'"
        PLAY ACTION+ FREAKIN_COOL
        WAIT
    //}
  ENDIF
  IF id == 62 THEN
    //{ "AIBO voice command/'Good girl'"
        PLAY ACTION+ STORY_SMOKECRACK
        WAIT
    //}
  ENDIF
  IF id == 63 THEN
    //{ "AIBO voice command/'Bad boy'"
        PLAY ACTION+ SCREWU2
        WAIT
    //}
  ENDIF
  IF id == 64 THEN
    //{ "AIBO voice command/'Bad girl'"
        PLAY ACTION+ CHICKEN_SHIT
        WAIT
    //}
  ENDIF
  IF id == 65 THEN
    //{ "AIBO voice command/'Let's talk'"
        PLAY ACTION+ MOM_ETHIOPIAN
        WAIT
        PLAY ACTION FEELING_CHEER0_SIT // Cheerful {21:00:00}
        WAIT
        PLAY ACTION+ SWEET // SWEET.WAV
        WAIT
    //}
  ENDIF
  IF id == 66 THEN
    //{ "AIBO voice command/'Be quiet'"
        PLAY ACTION+ MAKE_BABIES
        WAIT
    //}
  ENDIF
  IF id == 67 THEN
    //{ "AIBO voice command/'What's you owner's name'"
        PLAY ACTION+ MERV_GRIFFIN
        WAIT
    //}
  ENDIF
  IF id == 68 THEN
    //{ "AIBO voice command/'Owner registration'"
        PLAY ACTION+ KISSINGASS
        WAIT
    //}
  ENDIF
  IF id == 69 THEN
    //{ "AIBO voice command/'Function check'"
        PLAY ACTION+ NOT_FAT
        WAIT
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
      // don't do anything on random sound
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
      PLAY ACTION+ GAYDOG
      WAIT
  //}
RETURN

///////////////////////

:Noise_Handler

  IF doPrint <> 0 THEN
    PRINT "Noise_Handler"
  ENDIF

  //{ "AIBO hears/noise"
      PLAY ACTION+ OVERCROWDED // OVERCROWDED.WAV + motion + leds
      WAIT
  //}

RETURN

///////////////////////

:Rhythm_Handler
  IF doPrint <> 0 THEN
    PRINT "Rhythm_Handler"
  ENDIF

  //{ "AIBO hears/music with rhythm"
      PLAY ACTION+ RHYTHM1 // RHYTHM1.WAV + motion + leds
      WAIT
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
      PLAY ACTION+ SWEET // SWEET.WAV
      WAIT
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
      PLAY ACTION+ SCARED_CRAP
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
      PLAY ACTION+ SPEED2 // SPEED2.WAV + motion + leds
      WAIT
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
      PLAY ACTION+ STUPID // STUPID.WAV
      WAIT
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

    WHILE 1 = 1
        IF AP_FaceDetect > 0 THEN
            PRINT "FACE lvl=%d H=%d V=%d D=%d" AP_FaceDetect AP_FaceDetect_Horz AP_FaceDetect_Vert AP_FaceDetect_Dist
            SET AP_FaceDetect 0
        ENDIF
        IF AP_FaceDetect < 0 THEN
            PRINT "FACE LOST"
            // -level, last H, last V, dist=0
            SET AP_FaceDetect 0
        ENDIF

        WAIT 100

    WEND // end of main loop
RETURN

/////////////////////////////////////////////////////////////
// Include 'RCR' RCode Runtime

#AP_INCLUDE /MS/OPEN-R/APP/PC/AMS/rcrlib.r

/////////////////////////////////////////////////////////////
