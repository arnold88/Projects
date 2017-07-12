Readme for RCodePlus (version 2.52)

Supports 3 models (210, 31x, 220)

See documentation on: http://aibohack.com and http://aibohack.com/rcode

Default voice command vocabulary is "RCODE" + best of Life

==================================================
Credits:

The Base AiboWare code (RCODE 1.2) is copyrighted by Sony.
Read the LICENSE.TXT file for software licensing and distribution rules.

Extensions are my own creations.

JPEG compression code thanks to "the Independent JPEG Group"
    http://www.ijg.org  (from IJG release 6b)

JOINT.CFG extensions, thanks to Mr. Rcode

ACTION.EXT "O2_" DogsLife action names, thanks to John of DogsBody

==================================================
Change history:

Version 2.52:
    * new double floating point library
        (DBL_SET, DBL_ADD, DBL_MUL, DBL_ATAN2 etc)
    * incorporating old version HumanFaceDetector and minimal YART support
        -- experimental feature, supercore recommended
    * AP_TRACE -- experimental feature for AibNet/DogLife debugging

    BUG FIXES:
    * misc LAN telemetry bugs
    * include official LICENSE.TXT file again
    * adjust default volumes
    * removed large grow*.wav from 210 SYSAUDIO.ODA (waste of space)
    * other minor things

    Related: share 2.52 telemetry code with 'Life Plus' family of sticks
    Related: updated C++/VC++ sample files to be more consistent.

------------------------------

Version 2.51 "A" (YART release)
    * includes latest YART
    * includes new universal ACTION.EXT

Version 2.51 (final):
    * Final VLang2 (English and optional Japanese)
    * More YART features

Telemetry:
	* YUV10 video codec supported for video capture (less CPU overhead)
    * Audio capture now returns multiple audio buffers, but never just one
	    [also side steps the RCODE 1.2 IPSTACK.BIN problem]
    * Array Telemetry GETRAW and GETVARS supported
        (transfer data quickly from AIBO or RCODE program to a PC)
    * Array numbers 21->25 available for telemetry
    * AP_SETVARADDR for fast get of many variables (including system ones)

New Features:
	* Color Detection primitives: AP_COLORLVL,
	     AP_GETCOLORARRAY, AP_COLORFND, AP_COLORGRID features
	* AP_VOICEREC and AP_VoiceRec_Result
    * AP_GETSYNVOICE and AP_SynByte_Mode - for "what's your name"
    * Optional disable of "MTN_MSG_??" strings, AP_Replay_Result_Mode
            and AP_Replay_Result

Bug fixes:
	* AP_Rhythm fixed (strange ISID.CFG incompat)

Voice Commands/Language:
	* VLang2 (RCODE 1.2 + Extensions) is now the default
	    PREVIEW: VLang2 is not final (and only in English)
	* VLang3 optional so you can record your own vocabularies (ie. Yacky AIBO)

* Arrays:
    * new AP_NEWARRAY, AP_FREEARRAY for temporary array use
    * Up to 25 arrays (first 20 usable, last 5 reserved for telemetry)
    * Arrays must now be >= 1
    * Fix for AP_SETDBL.
    * Added AP_SETB, AP_GETB for byte access (up to 4 values at a time)
    * Added AP_SETW, AP_GETW for word access (up to 4 values at a time)
	* Change to AP_PEEK/AP_POKE syntax
    * Extra option for AP_LOADARRAY to get exact size
    * AP_SETARRAYASRAM and AP_Use_Ram for loading playback data from an array

On-the-fly motions:
	* AP_MOVEJOINTS for very basic motion control
	* AP_GETJOINTS to get current servo values

RCode Runtime Library:
    * #AP_INCLUDE for including other RCODE files (only nests one level)
    * See 'rcrlib.r' for library primitives

YART:
    * Sample is YART compatible
    * Preliminary YART tool included

Configuration:
	* no longer special VERSION tag (which confuses Master Studio)
	* RCODE 1.2 IPSTACK.BIN is now the default

------------------------------

Version 2.50
* updated based on released RCODE 1.2 (from AMS1.1)
* video and audio using proper connections (into AiboPetApp)
* by default:
        using LIFE voice command dictionaries (not the same as RCODE 1.2)
        RCODE voice command dictionary optional
* all @AP_ features obsolete, use new telemetry socket instead
* Only Pink_Ball supported (other two colors are not working yet)

------------------------------

Version 1.92 - not released
* all HIRAM based
* AP_SETGAIN removed (obsolete), use AP_SETGAIN2 instead
* AP_GETACCEL
* telemetry socket started

Version 1.91
* @AP_GETJ for LAN get JPG
* AP_SAVEIMAGE now saves snapshot file in .JPG format (faster and smaller)
* using C++ for AiboPet.bin
* new array features (auto save/load)
* TRIMELF used to reduce size of .BINs
* support for 220
* experimental AP_DEVCTL for camera white balance, shutter speed, mic etc

Version 1.90
* Official "Legit-i-Mutt" release of 1.6"B"
* supports 210 and 31x

Version 1.6 "B" - recovered, reimplemented
* re-implemented features in 1.6 "A" after hard drive crash
* Cleaned up for official release

Version 1.6 "A" - LOST
* merged with AiboLifePlus common code
* Increased audio buffers to 15 (around 1/2 second)
* AP_DIM, AP_SET, AP_GET
* Pink_Ball_Horz, Pink_Ball_Vert, Pink_Ball_Dist
* Fav_Color_Horz, Fav_Color_Vert, Fav_Color_Dist
* Unfav_Color_Horz, Unfav_Color_Vert, Unfav_Color_Dist

Version 1.5:
* AP_GETA, AP_RESETA added
* AP_SETGAIN

Version 1.4
* AP_SAVEIMAGE:### works (saves .BMP) - takes about 6->8 seconds to save
* AP_NoFallDown
* AP_UpSkirt

Version 1.3.05
* First release (tracks AiboLife Plus 1.3 protocol)
* voice recognition, sound recognition
* Volume control (use \CUSTOM\RPLUSCON.EXE to change settings)
* @AP_, AP_XXXXX and AP_Xxxxx additions
* slightly different boot sound

Version 1.01
* Internal build

==================================================
