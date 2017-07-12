/* Arnold Lee
   UIN: 665453451
   IDS 462 HW #6 - Chapter 4 problems
   06/01/2009
*/




***Problem 4-2;
**Be sure to replace seeds for random number generators with called for
  digits from your UIN.  Be sure to remove quotes.;


DATA ABC_CORP;
   DO SUBJ = 1 TO 10;
      DOB = INT(RANUNI(66)*15000);
      VISIT_DATE = INT(RANUNI(54)*1000) + '01JAN2000'D;
      OUTPUT;
   END;
   FORMAT DOB VISIT_DATE DATE9.;
RUN;

**added code***;

data AGES;
   set ABC_CORP;
   AGE_ACTUAL = yrdif(DOB,'15JAN2005'D,'ACTUAL');
   AGE_TODAY  = round(YRDIF(DOB,TODAY(),'ACTUAL'),0.1);
   AGE        = int(yrdif(DOB,VISIT_DATE,'ACTUAL'));
run;

proc print data=AGES;
   title "Problem 4.2 --- Listing of AGES dataset";
run;


***Problem 4-4;

DATA CLINICAL;
   *Use LENGTH statement to control the order of
    variables in the data set;
   LENGTH PATIENT VISIT DATE_VISIT 8;
   RETAIN DATE_VISIT WEIGHT;
   DO PATIENT = 1 TO 25;
      IF RANUNI(53) LT .5 THEN GENDER = 'Female';
      ELSE GENDER = 'Male';
      X = RANUNI(53);
      IF X LT .33 THEN GROUP = 'A';
      ELSE IF X LT .66 THEN GROUP = 'B';
      ELSE GROUP = 'C';
      DO VISIT = 1 TO INT(RANUNI(53)*5);
         IF VISIT = 1 THEN DO;
             DATE_VISIT = INT(RANUNI(53)*100) + 15800;
             WEIGHT = INT(RANNOR(53)*10 + 150);
         END;
         ELSE DO;
            DATE_VISIT = DATE_VISIT + VISIT*(10 + INT(RANUNI(53)*50));
            WEIGHT = WEIGHT + INT(RANNOR(53)*10);
         END;
         OUTPUT;
         IF RANUNI(53) LT .2 THEN LEAVE;
      END;
   END;
   DROP X;
   FORMAT DATE_VISIT DATE9.;
RUN;

***added code***;

data DIFF;
   set CLINICAL;
   by PATIENT;
   DIFF = dif(WEIGHT);
   if not FIRST.PATIENT then output;
RUN;

proc print data=DIFF noobs;
   title "Problem 4.4 -- Weight Difference";
run;


****Problem 4.6*******;

data CHANGE;
   set CLINICAL;
   by PATIENT;
   if FIRST.PATIENT and LAST.PATIENT then delete;
   retain ORIGINAL_WEIGHT FIRST_VISIT;

   if FIRST.PATIENT then do;
      ORIGINAL_WEIGHT = WEIGHT;
      FIRST_VISIT = DATE_VISIT;
   end;

   if LAST.PATIENT then do;
      DIFF = WEIGHT - ORIGINAL_WEIGHT;
      DAYS_ELAPSED = DATE_VISIT - FIRST_VISIT;
      output;
   end;

   keep PATIENT WEIGHT DIFF DAYS_ELAPSED;

run;

proc print data=CHANGE noobs;
   title "Problem 4.6 -- Cumulative weight difference between 1st and last visit";
run;

******Problem 4.8*****;

proc means data=CLINICAL noprint nway;

   class PATIENT;
   var WEIGHT;
   output out= DETAIL(drop=_TYPE_ rename=(_FREQ_ = NUM_OF_VISITS))
          mean=
          median=
          min=
          max= / autoname;

run;

proc print data=DETAIL noobs;
   title "Problem 4.8 - Patient Details";
run;

*********Problem 4.10*******;

proc means data=CLINICAL chartype;

   class GENDER GROUP;
   var WEIGHT;
   output out=SUMMARY
          mean=
          median=
          stddev= / autoname;

run;

proc print data=SUMMARY noobs;
   title "Problem 4.10 - Patient Summary";
run;
