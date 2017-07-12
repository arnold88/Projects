/*Arnold Lee
IDS 462 HW #1
05/20/2009*/


***************Problem 9.3****;

DATA LIBRARY;
   INPUT BOOKS ENROLL DEGREE AREA;
DATALINES;
 4   5  3   20
 5   8  3   40
10  40  3  100
 1   4  2   50
 5   2  1  300
 2   8  1  400
 7  30  3   40
 4  20  2  200
 1  10  2    5
 1  12  1  100
;

PROC REG DATA=LIBRARY;
   title "Problem 9.3 output";
   MODEL BOOKS = ENROLL DEGREE AREA / SELECTION=FORWARD;
RUN;

/* 
Technical Analysis:

Based on the output,  the following is the factor that influence the dependent variable,
sorted by order of importanace:

1. DEGREE 
2. ENROLL
3. AREA

DEGREE has a higher degree of influence because the F-stat is signigicate at P = 0.051.
The parameter estimate of DEGREE is 2.51, indicates that higher number of graduate students
(MA and PhD) may result in a higher estimate of number of books in the library.

ENROLL has a slighty higher p-value (P = 0.0761) so it has less influence in the dependent
varaiable than DEGREE.

AREA has the least signficance as the regression coefficient (0.01208) has not statistically different from 
zero.



*/
