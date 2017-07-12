// RCR : RCode Runtime Library

// Version 2.51 .02 [for ObeyCat]

// interface rules:
//   all public entries start with "RCR_"
//   all private entries start with "_RCR_"
//   all public global variables start with "rcr_"
//   all private global variables start with "_rcr_"
//   use local variables (and dynamic arrays) where possible

// NOTE: the RCODE calling convention is a little strange
//   PUSH arg1
//   PUSH arg2
//   CALL RCR_routine 2

// make sure you pass the right number of arguments

////////////////////////////////////////////////////////////////////a/

PRINT "FATAL: bad #AP_INCLUDE - trying to run from start of RCRLIB.R"
HALT

////////////////////////////////////////////////////////////////////a/

:RCR_Init
  ARG _doPrint
    SET rcr_doPrint _doPrint
            // set initial flag (trace output or not)
    IF rcr_doPrint != 0 THEN
        PRINT "Inside RCR_Init"
    ENDIF
RETURN

////////////////////////////////////////////////////////////////////a/

:RCR_MoveHeadFast
  ARG pan
  ARG tilt

    LOCAL joints
    AP_NEWARRAY joints 2
    AP_SETW joints 0 tilt pan // roll not changed
    DO
	    AP_MOVEJOINTS joints 0 0xC02 4 // move head X,Y - very fast
    LOOP WHILE AP_Move_Result == -1

    AP_FREEARRAY joints
RETURN

////////////////////////////////////////////////////////////////////a/
// TODO:
// record voice proper feedback
// cool LED combinations

////////////////////////////////////////////////////////////////////a/

:RCR_PlaySynVoice
    // return TRUE if played
  ARG vcmd_id
    LOCAL syn_array
    AP_NEWARRAY syn_array 1000    // much larger than needed

    LOCAL syn_size
    AP_GETSYNVOICE syn_array syn_size vcmd_id
    IF syn_size <= 0 THEN
        RET:-1
    ENDIF
    LOCAL bite_me 0
    IF AiboType == 210 THEN
        SET bite_me 1
    ENDIF

    IF rcr_doPrint != 0 THEN
        PRINT "Calling RCR_PlaySynVoiceFromArray %d %d %d" syn_array syn_size bite_me
    ENDIF
    PUSH syn_array
    PUSH syn_size
    PUSH bite_me
    CALL RCR_PlaySynVoiceFromArray:3
    AP_FREEARRAY syn_array
RET:1

:RCR_PlaySynVoiceFromArray
  ARG syn_array
  ARG syn_array_size // actual size in bytes
  ARG bite_me   // 0 for sound only, 1 for sound + bite

	SET AP_Replay_Result_Mode 0  // disable hook

    IF Wait > 0 THEN
        PRINT "Forcing Wait from %d to 0" Wait
        SET Wait 0
    ENDIF

    INIT MTN
    WAIT

    IF bite_me != 0 THEN
	    SET AP_SynBite_Mode 3 // sound and mouth
    ELSE
	    SET AP_SynBite_Mode 1 // sound only
    ENDIF
    AP_SETARRAYASRAM syn_array 0 syn_array_size

    LOAD SND ram
    WAIT

    PLAY MTN
    WAIT

    SET AP_Use_Ram 0 // no longer used
    SET AP_SynBite_Mode 0 // back to normal
RETURN

////////////////////////////////////////////////////////////////////a/

:RCR_RecordVcmd // with feedback
  ARG vcmd_id

    IF rcr_doPrint != 0 THEN
        PRINT "Recording voice command %d" vcmd_id
    ENDIF

    LOCAL tries
    FOR tries 1 5

        SET Warn 1 // REVIEW: better feedback

	    AP_VOICEREC vcmd_id 
	    WHILE AP_VoiceRec_Result == -1
	        WAIT 10
	    WEND
	
        SET Warn 0 // REVIEW: better feedback
	
	    IF AP_VoiceRec_Result == 1 THEN
		    IF rcr_doPrint != 0 THEN
		        PRINT "RECORDED!"
            ENDIF
            RET:1
	    ELSE
	        PRINT "ERROR: NOT RECORDED"
	
	        IF AP_VoiceRec_Result == 100 THEN
			    IF rcr_doPrint != 0 THEN
		            PRINT "WHOOPS: voice recording is not responding !"
                ENDIF
                RET:-1
	        ENDIF
            // otherwise keep trying
	    ENDIF
    NEXT

	PRINT "ERROR: NOT RECORDED (timeout)"
    IF rcr_doPrint != 0 THEN
        PRINT "Recording failed after 5 tries"
    ENDIF
RET:-1

////////////////////////////////////////////////////////////////////a/

:RCR_TakeAPicture // with minimal feedback
	AP_SNAPSHOT
	PLAY ACTION PHOTOSNAP // camera shutter sound
    WAIT
	DO
		WAIT 50
	LOOP WHILE AP_Snap_Ready == 0

	SET Warn 1 // REVIEW: better feedback
    LOCAL picnum
	VLOAD picnum
	AP_SAVEIMAGE picnum
	ADD picnum 1
	VSAVE picnum
	SET Warn 0 // REVIEW: better feedback
RETURN

////////////////////////////////////////////////////////////////////a/
// simple routines for YART (no args)

:RCR_SayDogsName
    PUSH 1
    CALL RCR_PlaySynVoice:1
RETURN

////////

:RCR_RecordDogsName
    // immediate record - no sitting and back pressing
    SET Context -55 // DEBUGONLY

    PUSH 1
    CALL RCR_RecordVcmd:1

    IF rcr_doPrint != 0 THEN // DEBUGONLY
        PRINT "Return from RCR_RecordVcmd %d" Context
    ENDIF

    IF Context == 1 THEN
        CALL RCR_SayDogsName
    ELSE
        PLAY ACTION WAVE_ERROR_SIT
        WAIT
    ENDIF
RETURN

////////

:RCR_SayOwnersName
    PUSH 0x100      // 256 is owners name
    CALL RCR_PlaySynVoice:1
RETURN

////////

:RCR_RecordOwnersName
    // immediate record - no sitting and back pressing
    SET Context -55 // DEBUGONLY

    PUSH 0x100      // 256 is owners name
    CALL RCR_RecordVcmd:1
    IF rcr_doPrint != 0 THEN // DEBUGONLY
        PRINT "Return from RCR_RecordVcmd %d" Context
    ENDIF

    IF Context == 1 THEN
        CALL RCR_SayOwnersName
    ELSE
        PLAY ACTION WAVE_ERROR_SIT
        WAIT
    ENDIF
RETURN

////////////////////////////////////////////////////////////////////a/
// Experimental

:RCR_CheesyMimicMode
    LOCAL vcmd_id 0x101 // non-standard ID
    LOCAL mimic_count

    // mimic 10 words then stop
    FOR mimic_count 1 10

        // quick
        SET Warn 1
        WAIT 250
        SET Warn 0

	    AP_VOICEREC vcmd_id 
	    WHILE AP_VoiceRec_Result == -1
	        WAIT 10
	    WEND
	
	    IF AP_VoiceRec_Result == 1 THEN
            // RECORDED
		    PUSH vcmd_id
		    CALL RCR_PlaySynVoice:1
	    ENDIF
    NEXT
RETURN

////////////////////////////////////////////////////////////////////a/

