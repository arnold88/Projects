// Disco AIBO 4 for the 210, 220, 31x
// Requires RCodePlus 2.5x for AP_AiboSound and special TDASDATA.BIN

 // startup

 GLOBAL part 0  // 0=general/backup part, 1=lead, 2=2nd lead
 GLOBAL calibrated 0
 GLOBAL play_intro 1


 // Require version 250 or better
 IF AP_Version < 250 THEN
    HALT
 ENDIF

 GLOBAL doPrint 0
 // SET doPrint 1

 IF doPrint != 0 THEN
    PRINT "Disco AIBO 4.5 (%d)" AiboType
 ENDIF


 SET NoFallDown 1 // don't reset if it falls down

:Main
  IF calibrated == 0 THEN
    IF doPrint != 0 THEN
	    PRINT "Calibrating"
	ENDIF
    PLAY ACTION SIT
    WAIT
	SET Warn 0
    LET calibrated 1
    SET AP_AiboSound 0 // purge pending
    SET Head_ON 0
    SET Back_ON 0
    SET Tail_U_ON 0
  ENDIF

  IF play_intro != 0 THEN
    PLAY ACTION+ INTRO // intro song (after calibrated)
    WAIT
    SET play_intro 0
  ENDIF

  IF Batt_Rest < 20 THEN
    HALT
  ENDIF

  IF AP_AiboSound > 0 THEN
    IF doPrint != 0 THEN
        PRINT "AP_AiboSound = %d" AP_AiboSound
	ENDIF

    PUSH AP_AiboSound
    CALL DanceToTune 1
    WAIT 1000 // wait a second
    PLAY ACTION LIE // safer
    WAIT
	// force recalibration after dance (will clear any pending inputs)
    LET calibrated 0
    GO Main
  ENDIF

  LOCAL bump 0
  // for ERS-2x0
  IF Back_ON > 0 THEN
    LET bump 1
	SET Back_ON 0
  ENDIF

  // for ERS-31x
  IF Tail_U_ON != 0 THEN
    LET bump 1
    SET Tail_U_ON 0
  ENDIF

  IF bump != 0 THEN
    ADD part 1
    IF part > 2 THEN
       LET part 0
    ENDIF
    LET show_eye 1 // show eyes for which part
  ENDIF

  IF Head_ON > 0 THEN
    LET show_eye 1
    SET Head_ON 0
  ENDIF

  IF show_eye > 0 THEN
    IF part == 0 THEN
        IF AiboType == 310 THEN
            PLAY ACTION+ EYE_BACKUP_31x
        ELSE
            PLAY ACTION+ EYE_BACKUP
	    ENDIF
    ENDIF
    IF part == 1 THEN
        IF AiboType == 310 THEN
            PLAY ACTION+ EYE_LEAD1_31x
        ELSE
            PLAY ACTION+ EYE_LEAD1
	    ENDIF
    ENDIF
    IF part == 2 THEN
        IF AiboType == 310 THEN
			PLAY ACTION+ EYE_LEAD2_31x
        ELSE
			PLAY ACTION+ EYE_LEAD2
	    ENDIF
    ENDIF
    WAIT // wait for LED to finish
    LET show_eye 0
  ENDIF
 WAIT 2 // not too long
 GO Main

EXIT

///////////////////////////////////////////////

:DanceToTune
  ARG:tune

  IF tune == 2 THEN
    PLAY ACTION+ DANCE02
    CALL DanceDogDance
  ENDIF

  IF tune == 3 THEN
    PLAY ACTION+ DANCE03
    CALL DanceDogDance
  ENDIF

  IF tune == 4 THEN
    PLAY ACTION+ DANCE04
    CALL DanceDogDance
  ENDIF

  IF tune == 5 THEN
    PLAY ACTION+ DANCE05
    CALL DanceDogDance
  ENDIF

  IF tune == 6 THEN
    PLAY ACTION+ DANCE06
    CALL DanceDogDance
  ENDIF

  IF tune == 7 THEN
    PLAY ACTION+ DANCE07
    CALL DanceDogDance
  ENDIF

  // multi-part
  IF tune == 8 THEN
    IF part == 0 THEN
      PLAY ACTION+ DANCE08A
      CALL DanceDogDance
    ELSE
      PLAY ACTION+ DANCE08B
      CALL DanceDogDance
    ENDIF
  ENDIF

  IF tune == 9 THEN
    IF part == 0 THEN
      PLAY ACTION+ DANCE09A
      CALL DanceDogDance
    ENDIF
    IF part == 1 THEN
      PLAY ACTION+ DANCE09B
      CALL DanceDogDance
    ENDIF
    IF part == 2 THEN
      PLAY ACTION+ DANCE09C
      CALL DanceDogDance
    ENDIF
  ENDIF

  IF tune == 10 THEN
    IF part == 0 THEN
      PLAY ACTION+ DANCE10A
      CALL DanceDogDance
    ENDIF
    IF part == 1 THEN
      PLAY ACTION+ DANCE10B
      CALL DanceDogDance
    ENDIF
    IF part == 2 THEN
      PLAY ACTION+ DANCE10C
      CALL DanceDogDance
    ENDIF
  ENDIF

  IF tune == 11 THEN
    PLAY ACTION+ DANCE11
    CALL DanceDogDance
  ENDIF

  IF tune == 12 THEN
    PLAY ACTION+ DANCE12
    CALL DanceDogDance
  ENDIF

  IF tune == 13 THEN
    IF part == 0 THEN
      PLAY ACTION+ DANCE13A
      CALL DanceDogDance
    ELSE
      PLAY ACTION+ DANCE13B
      CALL DanceDogDance
    ENDIF
  ENDIF

  IF tune == 14 THEN
    PLAY ACTION+ DANCE14
    CALL DanceDogDance
  ENDIF

  IF tune == 15 THEN
    IF part == 0 THEN
      PLAY ACTION+ DANCE15A
      CALL DanceDogDance
    ELSE
      PLAY ACTION+ DANCE15B
      CALL DanceDogDance
    ENDIF
  ENDIF

  IF tune == 16 THEN
    PLAY ACTION+ DANCE16
    CALL DanceDogDance
  ENDIF


  // Disco 4.5 additions:
  IF tune == 17 THEN
    IF part == 0 THEN
      PLAY ACTION+ DANCE17A
      CALL DanceDogDance
    ELSE
      PLAY ACTION+ DANCE17B
      CALL DanceDogDance
    ENDIF
  ENDIF


  IF tune == 18 THEN
    PLAY ACTION+ DANCE18
    CALL DanceDogDance
  ENDIF

  IF tune == 19 THEN
    PLAY ACTION+ DANCE19
    CALL DanceDogDance
  ENDIF

  IF tune == 20 THEN
    PLAY ACTION+ DANCE20
    CALL DanceDogDance
  ENDIF

  IF tune == 21 THEN
    PLAY ACTION+ DANCE21
    CALL DanceDogDance
  ENDIF

  IF tune == 22 THEN
    PLAY ACTION+ DANCE22
    CALL DanceDogDance
  ENDIF

  IF tune == 23 THEN
    PLAY ACTION+ DANCE23
    CALL DanceDogDance
  ENDIF


RETURN

///////////////////////////////////////////////

:DanceDogDance

  SET Back_LONG 0
  SET Tail_U_LONG 0
  WHILE Wait > 0
    IF Tail_U_LONG > 0 THEN
        SET Back_LONG 1
    ENDIF
    IF Back_LONG > 0 THEN
	    IF doPrint != 0 THEN
	        PRINT "ABORT"
		ENDIF
        QUIT // emergency stop
        SET Wait 0
        SET calibrated 0
		SET play_intro 1 // riff after abort
        SET Warn 1
        RETURN
    ENDIF
    WAIT 20
  WEND

RETURN

///////////////////////////////////////////////

