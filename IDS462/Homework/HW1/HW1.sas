
/*Arnold Lee
IDS 462 HW #1
05/20/2009*/


***************Problem 1.2 part (a);

data diet;

input SUBJ    $ 1-3
      HEIGHT    4-5
      WT_INIT   6-8
      WT_FINAL  9-11;
   
	  *conversion;
   WT_INIT = WT_INIT/2.2;
   WT_FINAL = WT_FINAL/2.2;
   HEIGHT = HEIGHT*.0254;

      *calculation;
   BMI_INIT = WT_INIT/(HEIGHT**2);
   BMI_FINAL = WT_FINAL/(HEIGHT**2);
   BMI_DIFF = BMI_FINAL-BMI_INIT;

datalines;
00768155150
00272250240
00563240200
00170345298
;
run;

*****************Problem 1.2 part (b);

proc sort data=diet;
   by SUBJ;
run;

proc print data=diet;
   title "Problem 1.2 part (b)";
   id SUBJ;
   var HEIGHT BMI_INIT BMI_FINAL BMI_DIFF;
run;

*****************Problem 1.4 part (a);
 
  *the following five lines are given;
data IQ_AND_TEST_SCORES;
   input ID      1-3
         IQ      4-6
         MATH    7-9
         SCIENCE 10-12;

  *The following four lines are added;
OVERALL = (IQ + MATH + SCIENCE)*(1/3)*(1/500);
if IQ GE 0 and IQ LE 100 then GROUP = 1;
else if IQ GE 101 and IQ LE 140 then GROUP = 2;
else if IQ GT 140 then GROUP = 3;

datalines;
001128550590
002102490501
003140670690
004115510510
;

*******************Problem 1.4 part (b);

proc sort data = IQ_AND_TEST_SCORES;
 by IQ;
run;

proc print data = IQ_AND_TEST_SCORES;
 title " Problem 1.4 part (b) ";
 id ID;
run;

******************Problem 1.4 part (c);

proc freq data = IQ_AND_TEST_SCORES;
    title " Problem 1.4 part (c) ";
   	tables GROUP;
run;

******************Problem 1.10;

data rain;
   input CITY $ 
         RAIN_JUNE 
         RAIN_JULY 
         RAIN_AUGUST;

   AVERAGE        = (RAIN_JUNE + RAIN_JULY + RAIN_AUGUST)/3;
   PERCENT_JUNE   = (RAIN_JUNE/AVERAGE)*100;
   PERCENT_JULY   = (RAIN_JULY/AVERAGE)*100;
   PERCENT_AUGUST = (RAIN_AUGUST/AVERAGE)*100;

datalines;
Trenton  23 25 30
Newark   18 27 22
Albany   22 21 27
;

proc sort data=rain;
   by CITY;
run;

proc print data=rain;
   title "Problem 1.10 - Rain data set";
   id CITY;
run;

proc means data=rain mean STD CLM MAXDEC=2;
    title "Problem 1.10 - Rainfall average and SD";
	var RAIN_JUNE RAIN_JULY RAIN_AUGUST;
run;
