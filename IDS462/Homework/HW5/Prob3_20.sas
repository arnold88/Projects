*Arnold Lee;
*IDS 462 HW #5;
*06/01/2009;

******Problem 3.20*********;

PROC FORMAT;
   VALUE COMPOSER 1  = 'Bach'
                  2  = 'Handel'
                  3  = 'Scarlatti'
                  4  = 'Hayden'
                  5  = 'Mozart'
                  6  = 'Beethoven'
                  7  = 'Schubert'
                  8  = 'Brahms'
                  9  = 'Schumann'
                  10 = 'Stravinsky'
                  11 = 'Shostakovich';
RUN;
DATA CLASSICAL;
   INPUT SUBJ $ GENDER : $1. CHOICE1 CHOICE2 CHOICE3;
DATALINES;
1  M  6  4  5
2  F  2  4  3
3  M  7  11 9
4  M  5  6  3
5  F  7  8  10
6  F  1  2  4
7  M  6  5  9
8  M  2  9  11
9  F  5  1  2
;

*****These lines are added***************;

data VOTE;
   set CLASSICAL;
   VOTE = CHOICE1;
   output;
   VOTE = CHOICE2;
   output;
   VOTE = CHOICE3;
   output;
   keep VOTE;
   format VOTE COMPOSER.;
run;


proc freq data=VOTE order=FREQ;
   title "Problem 3.20 - The Most Favorite Composers Poll";
   tables VOTE / nocum;
run;

data VOTEARRAY;
set CLASSICAL;
array V[3] CHOICE1--CHOICE3;

do i=1 to 3;
VOTE=V[i];
if V[i] ~= . then output;
end;

run;

ods html file='H:\IDS462\Homework\HW5\PROB3_20.xls' style=minimal;

proc freq data=VOTEARRAY;
tables VOTE*GENDER/chisq exact;
title "Chi-Square Test for Composer Preference";
format VOTE COMPOSER.;
run;

ods html close;

/* Technical Analysis:

In the excel table, each composer has 4 varibles for each gender:

Frequency: Number of people listed as choice1,choice2 or choice3

Percent: % of total people listed this composer as either choice1,choice2 or choice3

Row Pct: Distribution of votes categorized by each composer, listed as a percentage
(for example, a 66.67% in Row Pct for Hayden-Female indicates that for the people who 
vote for Hayden, 66.67% are females)

Col Pct: Distribution of votes categorized by each gender, listed as a percentage
(for example, a 16.67% in Col Pct for Hayden-Female indicates that 16.67% of all females
voted for Hayden)

*/




















*/
