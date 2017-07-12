/*Arnold Lee
IDS 462 HW #3
05/27/2009*/

******Problem 17.2*********;

*** These are from the book***;
DATA FUNCTIONS;
   INPUT @1  SUBJECT        $3.
         @4  DOB      MMDDYY10.
         @14 VISIT    MMDDYY10.
         @23 (SCORE1-SCORE6)(2.);
   FORMAT DOB VISIT MMDDYY10.;
DATALINES;
00110/21/195011/11/2004908070757688
00205/05/200312/20/200499  98  9790
00307/15/194107/06/2004        9896
00406/24/193709/25/2004777879808182
;

**These lines are added**;

proc format;
   value days 1='M' 2='T' 3='W' 4='R' 5='F' 6='Sa' 7='Su';
run;

data QUES2;
   set functions;
   AGE_AT_VISIT = round(yrdif(DOB,VISIT,'ACTUAL'),.1);
   AGE_JAN = yrdif(DOB,'01JAN2004'D,'ACTUAL');
   if n(of SCORE1-SCORE6) >= 4 then SCORE = mean(of SCORE1-SCORE6);
   MIN_SCORE = min(of SCORE1-SCORE6);
   MAX_SCORE = max(of SCORE1-SCORE6);
   DAY = weekday(VISIT);
   format DAY days.;
run;

proc print data=QUES2 noobs;
   title "Problem 17.2";
run;

************Problem 17.4*************;
**********From the book**************;
DATA BIG;
   DO SUBJ = 1 TO 100;
      X = INT(RANUNI(123)*100 + 1);
      OUTPUT;
   END;
RUN;

*****added*****;

data TEN_PERCENT;
   set BIG;
   if ranuni(0) <= .1;
run;

proc print data=TEN_PERCENT noobs;
   title "Problem 17.4 - 10% random sample";
run;

**********Problem 17.6***********;

data TEMP;
   set BIG;
   CTRL = ranuni(0);
run;

proc sort data=TEMP;
   by CTRL;
run; 

data EXACT;
   set TEMP(OBS=20 DROP=CTRL);
run;

proc print data=EXACT noobs;
   title "Problem 17.6 - 20 obeservation from BIG";
run;

********Problem 17.8**********;

data ASSIGN;
   do SUBJ = 1 to 100;
      if ranuni(0) <= .5 then GROUP = 'A' ;
      else GROUP = 'B';
      output;
   end;
run;

proc freq data=ASSIGN;
   title "Problem 17.8";
   tables GROUP;
run;
