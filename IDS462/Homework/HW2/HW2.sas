
/*Arnold Lee
IDS 462 HW #2
05/23/2009*/


***************Problem 2.2******;

data CLINIC;
   input ID     $   1-3
         GENDER $   4
         RACE   $   5
         HR         6-8
         SBP        9-11
         DBP        12-14
         N_PROC     15-16;
 
       *calculate average bloop pressure;
        AVE_BP = DBP + (SBP - DBP)/3;

datalines;
001MW08013008010
002FW08811007205
003MB05018810002
004FB   10806801
005MW06812208204
006FB101   07404
007FW07810406603
008MW04811207006
009FB07719011009
010FB06616410610
;

proc means data = CLINIC n mean std clm median;
   title "Problem 2.2 - Clinic Data";
   var SBP DBP AVE_BP;
run;

*****************Problem 2.4*********;

*Frequency generation;
proc freq data = CLINIC;
   title "Problem 2.4 - Frequency table";
   table GENDER / nocum nopercent;
run;

*Bar graphic chart generation;
proc gchart data = CLINIC; 
   title "Problem 2.4 - Bar Chart";
   vbar GENDER;
run;

****************Problem 2.6**********;

proc univariate data = CLINIC plot;
   title "Problem 2.6 - stem-n-leaf plot";
   var SBP DBP;
run;

***************Problem 2.8***********;

proc chart data = CLINIC;
   title "Problem 2.8 Charts";
   vbar GENDER / group = RACE;
   vbar HR / group = GENDER midpoints = 50 to 100 by 10;
run;

***************Problem 2.10 part (a)********;

*define plot symbols;
symbol v = PLUS color = BLACK;
symbol2 v = CIRCLE color = BLACK;


* graphic plot;
proc gplot data = CLINIC;
   title "Problem 2.10(a) - Plot of SBP vs. HR";
   plot SBP * HR;
run;

***************Problem 2.10 part (b)*******;

proc gplot data = CLINIC;
   title "Problem 2.10(b) - Plot of SBP vs. DBP";
   plot SBP * DBP ;
run;


***************Problem 2.10 part (c)*******;

proc sort data = CLINIC;
   by RACE;
run;

proc gplot data = CLINIC;
   title "Problem 2.10(c) - Graph for each race";
   by RACE;
   plot SBP * HR;
   plot SBP * HR = GENDER;
run;






