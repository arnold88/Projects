/*Arnold Lee
IDS 462 HW #2
05/23/2009*/


***************Problem 9.13******;

PROC FORMAT;
   VALUE YES_NO   0 = 'No'
                  1 = 'Yes';
RUN;

**the following lines come from blackboard*****;

DATA LOGISTIC;
   INPUT ACCIDENT DRINK PREVIOUS @@;
   LABEL ACCIDENT = 'Accident in Last Year?'
      DRINK = 'Drinking Problem?'
      PREVIOUS = 'Accident in Previous Year?';
   FORMAT ACCIDENT DRINK PREVIOUS YES_NO.;
DATALINES;
1 0 1  1 1 1  1 1 1  1 0 0  1 1 1  0 0 1  0 1 0  0 1 0
0 0 1  0 0 0  0 1 0  0 0 1  0 1 0  0 0 0  0 0 0  1 1 0
1 0 1  1 1 1  1 1 1  1 0 1  1 1 1  1 1 0  1 0 1  1 1 0
1 1 1  0 1 1  0 1 1  0 0 1  0 0 1  0 1 0  0 0 0  0 0 1
0 1 0  0 0 0  0 0 0  1 1 1  1 1 0  1 1 1  1 1 0  1 1 1
1 1 1  1 1 1  
;
run;

**the following lines are ADDED******;

PROC LOGISTIC DATA=LOGISTIC DESCENDING;
   TITLE "Problem 9.13 - Predicting Accidents Using Logistic Regression";
   MODEL ACCIDENT = DRINK PREVIOUS /
      SELECTION = FORWARD
      RISKLIMITS;
RUN;
QUIT;

/* 

Technical Analysis:

  The logistic regression equation is:
    
     LOG(odds of accident) = -2.0810 + 1.9803 (DRINK)
            + 1.7678 (PREVIOUS).


  Odds of accident for person 1 (DRINK = 0, PREVIOUS = 0) = 0.124805
  Probability of accident for person 1                    = 0.110957

  Odds of accident for person 2 (DRINK = 1, PREVIOUS = 0) = 0.904204
  Probability of accident for person 1                    = 0.474846

  Ratio of odds = 0.904204 / 0.124805  =  7.24492
  
  This verifies with the PROC LOGISTICS output.


*/
