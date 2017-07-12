*--------------------------------------------------------------------------*
| Programs and Data from Applied Statistics and the SAS Programming        |
| Language, 5th edition                                                    |
|                                                                          |
| The following file are available for downloading:                        |
|                                                                          |
| PROGRAMS.SAS - This file contains the programs used in this book         |
|                                                                          |
| HOMEWORK.DAT - Homework data and program files                           |
|                                                                          |
| HW_SOLUTIONS_ODD.SAS - Solutions to the odd-numbered homework problems   |                                                    |
|                                                                          |
| HW_SOLUTIONS_EVEN.SAS - Solutions to the even-numbered homework          |
|                         problems (available only to faculty)             |
*--------------------------------------------------------------------------*;
 
***Applied Statistics and the SAS Programming Language, 5th edition
   Solutions to the odd-numbered problems;

***CHAPTER 1;

***Problem 1-1;
***a;
DATA COLLEGE;
   INPUT ID AGE GENDER $ GPA CSCORE;
DATALINES;
1 18 M 3.7 650
2 18 F 2.0 490
3 19 F 3.3 580
4 23 M 2.8 530
5 21 M 3.5 640
;

***b;
PROC MEANS DATA=COLLEGE;
   VAR GPA CSCORE;
RUN;

***c;
/*******************************************************
Between the INPUT and DATALINES lines insert:
   INDEX = GPA + 3*CSCORE/500;
********************************************************/

***Add to the end of the program:;

PROC SORT DATA=COLLEGE;
   BY INDEX;
RUN;

PROC PRINT DATA=COLLEGE;
   TITLE "Students in Index Order"; /* optional */
   ID ID;
   VAR GPA CSCORE INDEX;
RUN;

***Problem 1-3;
**a;
DATA TAXPROB;
   INPUT SS SALARY AGE RACE $;
   FORMAT SS SSN11.; /* See Chapter 3 about FORMATS */
DATALINES;
123874414 28000 35 W
646239182 29500 37 B
012437652 35100 40 W
018451357 26500 31 W
;
PROC MEANS DATA=TAXPROB N MEAN MAXDEC=0;
   TITLE "Descriptive Statistics for Salary and Age";
   VAR SALARY AGE;
RUN;

***b;
/*
Add a line after the INPUT statement:
TAX = .30 * SALARY;
*/

***Add to the end of the program:;
PROC SORT DATA=TAXPROB;
   BY SS;
RUN;
PROC PRINT DATA=TAXPROB;
   TITLE "Listing of Salary and Taxes";
   ID SS;
   VAR SALARY TAX;
RUN;


***Problem 1-5;
1   DATA MISTAKE;
2   INPUT ID 1-3 TOWN 4-6 REGION 7-9 YEAR 11-12 BUDGET 13-14
3   VOTER-TURNOUT 16-20
4   DATALINES;
    00104050422 12345
   (more data lines)
5   ;
6   PROC MEANS DATA=MISTAKE;
7   VAR ID REGION VOTER-TURNOUT;
8   N,STD,MEAN;
9   RUN;


/*
Line 2: Not a mistake, but you might want ID to be a character variable.
Line 3: Variable name cannot contain a dash. Semicolon missing at the end of the line.
Line 7: We probably don't want the mean ID. Also, would be more meaningful to use PROC FREQ for a categorical variable such as REGION.
Line 8: Options for PROC MEANS go on the PROC line between the word MEANS and the semicolon. The options must have a space between them, not a comma.

Corrected Program:
*/

DATA MISTAKE;
   INPUT ID $ 1-3 TOWN 4-6 REGION 7-9 YEAR 11-12 BUDGET 13-14
         VOTER_TURNOUT 16-20;
DATALINES;
00104005  0422 12345
(more data lines)
;
PROC MEANS DATA=MISTAKE N MEAN STD;
   VAR BUDGET VOTER_TURNOUT;
RUN;


***Problem 1-7;
/*
We have a SAS data set with the variables AGE, GENDER, RACE, INCOME, MARITAL, and 
HOME (homeowner versus renter).

Code Book		
Variable Name	Col(s)	Description and Formats
		AGE	1	Age group of subject
		1 = 10 to 19    2 = 20-29    3 = 30-39
			4 = 40-49	5 = 50-59	6 = 60+
		GENDER	2	Gender,  1 = male  2 = female
		RACE	3	Race,  1 = white  2 = African Am.  3 = hispanic
					4 = other
		INCOME	4	Income group, 1 = 0 to $9,999
			2 = 10,000 to 19,999
			3 = 20,000 to 39,000
			4 = 40,000 to 59,000
			5 = 60,000 to 79,000
			6 = 80,000 and over
		MARITAL	5	Marital status, 1 = single  2 = married
			3 = separated  4 = divorced  5 = widowed
		HOME	6	Homeowner or renter,  1 = homeowner
			0 = renter

*/

DATA CEO;
      INPUT AGE      $ 1 
            GENDER   $ 2 
            RACE     $ 3 
            INCOME   $ 4 
            MARITAL  $ 5 
            HOME     $ 6;
DATALINES;
311411
122310
411221
(more data lines)
;
PROC FREQ DATA=CEO ORDER=FREQ;
   *Note, the ORDER = FREQ option will list the frequencies in
   decreasing frequency order, i.e. the most frequent first;
   TITLE 'Frequencies and Contingency Tables for CEO Report';
   TABLES AGE GENDER RACE INCOME MARITAL HOME
   AGE*GENDER*RACE INCOME*AGE*GENDER MARITAL*HOME;
   *or whatever other combinations you are interested in;
RUN;
PROC GCHART DATA=CEO;
   TITLE "Histograms";
   VBAR AGE GENDER RACE INCOME MARITAL HOME / DISCRETE;
RUN;

***Problem 1-9;
DATA PROB1_9;
   INPUT ID RACE $ SBP DBP HR;
DATALINES;
001   W   130   80   60
002   B   140   90   70
003   W   120   70   64
004   W   150   90   76
005   B   124   86   72
;
PROC SORT DATA=PROB1_9;
   BY SBP;
RUN;
PROC PRINT DATA=PROB1_9;
   TITLE "Race and Hemodynamic Variables";
   ID ID;
   VAR RACE SBP DBP;
RUN;


***CHAPTER 2;

***Problem 2-1;
PROC FREQ DATA=COLLEGE;
   TABLES GENDER;
RUN;

***Problem 2-3;
DATA TAXPROB;
   INPUT SS SALARY AGE RACE $;
   IF AGE GE 0 AND AGE LE 35 THEN AGE_GROUP = 1;
   ELSE IF AGE GT 35 THEN AGE_GROUP = 2;
   FORMAT SS SSN11.; /* See Chapter 3 about FORMATS */
DATALINES;
123874414 28000 35 W
646239182 29500 37 B
012437652 35100 40 W
018451357 26500 31 W
;
PROC FREQ DATA=TAXPROB;
   TITLE "Problem 2-3";
   TABLES RACE AGE_GROUP / NOCUM;
RUN;

***Problem 2-5;
DATA PROB2_5;
   LENGTH GROUP $ 1;
   INPUT X Y Z GROUP $;
DATALINES;
2   4   6   A
3   3   3   B
1   3   7   A
7   5   3   B
1   1   5   B
2   2   4   A
5   5   6   A
;
***a;
PROC GCHART DATA=PROB2_5;
   VBAR GROUP;
RUN;
***b;
PROC GPLOT DATA=PROB2_5;
   PLOT Y*X;
RUN;
***c;
PROC SORT DATA=PROB2_5;
   BY GROUP;
RUN;
PROC GPLOT DATA=PROB2_5;
   BY GROUP;
   PLOT Y*X;
RUN;

/*
Don't forget that you must have your data set sorted by the BY variables before you 
can use a BY statement in a PROC. 
*/

***Problem 2-7;
DATA LIVER;
   INPUT SUBJ DOSE REACT LIVER_WT SPLEEN;
DATALINES;
1   1  5.4  10.2  8.9
2   1  5.9   9.8  7.3
3   1  4.8  12.2  9.1
4   1  6.9  11.8  8.8
5   1 15.8  10.9  9.0
6   2  4.9  13.8  6.6
7   2  5.0  12.0  7.9
8   2  6.7  10.5  8.0
9   2 18.2  11.9  6.9
10  2  5.5   9.9  9.1
;
PROC SORT DATA=LIVER;
   BY DOSE;   *Note, optional since already in dose order;
RUN;
PROC UNIVARIATE DATA=LIVER NORMAL PLOT;
   TITLE "Distributions for Liver Data";
   VAR REACT -- SPLEEN;
   *** The notation first -- last is a short
       way of referring to all the variables from
       first to last IN THE ORDER THEY ARE in the
       SAS data set;
RUN;
PROC UNIVARIATE DATA=LIVER NORMAL PLOT;
   BY DOSE;
   TITLE "Distributions for Liver Data by Dose";
   VAR REACT -- SPLEEN;
RUN;

***Problem 2-9;

   1   DATA 123;
   2      INPUT AGE STATUS PROGNOSIS DOCTOR GENDER STATUS2
   3            STATUS3;
   4   (data lines)
         ;
   5   PROC CHART DATA=123 BY GENDER;
   6      VBAR STATUS
   7      VBAR PROGNOSIS;
   8   RUN;
   9   PROC PLOT DATA=123;
   10      DOCTOR BY PROGNOSIS;
   11   RUN;

/*
Line 1: Invalid data set name, cannot start with a number.
Line 2: Not really an error, but it would be better to list GENDER with the 
other demographic variables.
Line 2: Again, not an error, but an ID variable is desirable.
Lines 2 and 3: Boy, we're picky. If you have STATUS2 and STATUS3, STATUS should be STATUS1.
DATALINES; or CARDS; statement missing between lines 3 and 4.
Line 5: Two things wrong here: One, If you use a BY variable, the data set must 
be sorted in order of the BY variable; two, a semicolon is missing between PROC CHART 
and BY GENDER.
Line 6: Missing a semicolon at the end of the line.
Line 7: In case you thought this was an error, it isn't. You can have two (or more) 
VBAR statements with one PROC CHART.
Line 8: Missing the keyword PLOT before the plot request. Also, the plot request 
is of the form Y*X not Y BY X.
*/

***Problem 2-11;
***a;
DATA SALES;
   INPUT PERSON $ TARGET $ VISITS CALLS UNITS;
DATALINES;
Brown      American   3   12   28000
Johnson   VRW      6   14   33000
Rivera   Texam      2   6   8000
Brown      Standard   0   22   0
Brown      Knowles   2   19   12000
Rivera   Metro      4   8   13000
Rivera   Uniman   8   7   27000
Johnson   Oldham   3   16   8000
Johnson   Rondo      2   14   2000
;
PROC MEANS DATA=SALES N SUM MEAN STD MAXDEC=0;
   CLASS PERSON;
   TITLE "Sales Figures for Each Salesperson";
   VAR VISITS CALLS UNITS;
RUN;
***b;   
PROC GPLOT DATA=SALES;
   TITLE "Sales Plots";
   PLOT VISITS*CALLS = PERSON;
RUN;

***c;
PROC CHART DATA=SALES;
   TITLE "Distribution of Units Sold by Salesperson";
   VBAR PERSON / SUMVAR=UNITS TYPE=SUM;
RUN;
      *or;
PROC CHART DATA=SALES;
   TITLE "Distribution of Units Sold by Salesperson";
   VBAR UNITS / GROUP=PERSON;
RUN;

/*
The first PROC CHART in part (c) above will produce a single bar for each salesperson, 
the height representing the total (sum) of the units sold. The alternate statements 
will produce an actual frequency distribution of the number of units sold, for each 
salesperson, in a side-by-side fashion.
*/

***Problem 2-13;
DATA PROB2_13;
   INPUT ID TYPE $ SCORE;
DATALINES;
1   A   44
1   B   9
1   C   203
2   A   50
2   B   7
2   C   188
3   A   39
3   B   9
3   C   234
;
PROC MEANS DATA=PROB2_13;
   CLASS TYPE;
   VAR SCORE;
RUN;

/*
If you use a BY statement instead of a CLASS statement, remember to sort your data set first.
*/

***CHAPTER 3;

***Problem 3-1;
PROC FORMAT;
   VALUE FGROUP 1 = 'CONTROL' 
                2 = 'DRUG A'
                3 = 'DRUG B';
RUN;

***Problem 3-3;
PROC FORMAT;
   VALUE $GENDER 'M' = 'Male'
                 'F' = 'Female';
   VALUE $PARTY '1' = 'Republican'
                '2' = 'Democrat'
                '3' = 'Not Registered';
   VALUE YESNO 0 = 'No' 1 = 'Yes';
RUN;
DATA SURVEY;
   INPUT ID     1-3 
         GENDER $ 4 
         PARTY  $ 5
         VOTE     6 
         FOREIGN  7 
         SPEND    8;
   LABEL PARTY   =  'Political Party'
         VOTE    =  'Vote in Last Election?'
         FOREIGN = 'Agree with Government Policy?'
         SPEND   = 'Should we Increase Domestic Spending?';
   FORMAT GENDER $GENDER. 
          PARTY $PARTY. 
          VOTE FOREIGN SPEND YESNO.;
DATALINES;
007M1110
013F2101
137F1001
117 1111
428M3110
017F3101
037M2101
;
PROC FREQ DATA=SURVEY;
   TITLE "Political Survey Results";
   TABLES GENDER PARTY VOTE FOREIGN SPEND;
   TABLES VOTE*(SPEND FOREIGN) / CHISQ;
RUN;

***Problem 3-5;
***Method 1 ***;
DATA DEMOG;
   INPUT WEIGHT HEIGHT GENDER $;
   *Create weight groups;
   IF 0 LE WEIGHT LT 101 THEN WTGRP = 1;
   ELSE IF 101 LE WEIGHT LT 151 THEN WTGRP = 2;
   ELSE IF 151 LE WEIGHT LE 200 THEN WTGRP = 3;
   ELSE IF WEIGHT GT 200 THEN WTGRP = 4;
   *Create height groups;
   IF 0 LE HEIGHT LE 70 THEN HTGRP = 1;
   ELSE IF HEIGHT GT 70 THEN HTGRP = 2;
DATALINES;
155 68 M
98 60 F
202 72 M
280 75 M
130 63 F
.   57 F
166  . M
;
PROC FREQ DATA=DEMOG;
   TABLES WTGRP*HTGRP;
RUN;

/*
(NOTE: You may use < =  instead of LE,<instead of LT, and>instead of GT.)
*/

***Method 2 ***;

PROC FORMAT;
   VALUE WTFMT 0-100    = '1' 
               101-150  = '2' 
               151-200  = '3' 
               201-HIGH = '4';
   VALUE HTFMT 0-70    = '1' 
               71-HIGH = '2';
RUN;
DATA DEMOG;
   INPUT WEIGHT HEIGHT GENDER $;
DATALINES;
155 68 M
98 60 F
202 72 M
280 75 M
130 63 F
.   57 F
166  . M
;
PROC FREQ DATA=DEMOG;
   TITLE "Problem 3-5";
   TABLES WEIGHT*HEIGHT;
   FORMAT WEIGHT WTFMT. HEIGHT HTFMT.;
RUN;

***Problem 3-7;
DATA ASTHMA;
   INPUT ASTHMA $ SES $ COUNT;
DATALINES;
YES LOW 40
NO LOW 100
YES HIGH 30
NO HIGH 130
;
PROC FREQ DATA=ASTHMA;
   TITLE "Relationship between Asthma and SES";
   TABLES SES*ASTHMA / CHISQ;
   WEIGHT COUNT;
RUN;

/*
Chi-square = 4.026, p = .045.
*/

***Problem 3-9;
DATA VITAMIN;
   INPUT V_CASE $ V_CONT $ COUNT;
   LABEL V_CASE = 'Case Use Vitamins'
         V_CONT = 'Control Use Vitamins';
   ***Note: Values of V_CASE and V_CONT chosen so that 1-YES will 
            come before 2-NO in the table;
DATALINES;
1-YES  1-YES  100
1-YES  2-NO    50
2-NO   1-YES   90
2-NO   2-NO   200
;
PROC FREQ DATA=VITAMIN;
   TITLE "Matched Case-control Study";
   TABLES V_CASE * V_CONT / AGREE;
   WEIGHT COUNT;
RUN;

/*
Chi-square (McNemar) = 11.429, p = .001 More likely to develop disease X if you do 
not use vitamins. (Remember, it is only the discordant pairs (yes/no or no/yes) that 
contribute to the McNemar Chi-square.)
*/

***Problem 3-11;
DATA VDT_USE;
   INPUT GROUP $ VDT $ COUNT;
DATALINES;
CASE 1-YES 30
CASE 2-NO 50
CONTROL 1-YES 90
CONTROL 2-NO 200
;
PROC FREQ DATA=VDT_USE;
   TITLE "Case-control study of VDT Use";
   TABLES VDT * GROUP / CHISQ CMH;
   WEIGHT COUNT;
RUN;

/*
Chi-square = 1.1961, p = .2741  OR = 1.333, 95% CI (.7956, 2.2349).
*/

***Problem 3-13;
DATA CLASS;
   INPUT TYPE : $10. PROBLEM $ COUNT;
DATALINES;
1-STANDARD 1-YES 30
1-STANDARD 2-NO 220
2-PROOFED  1-YES 20
2-PROOFED 2-NO 280
;
PROC FREQ DATA=CLASS;
   TITLE "Sound Proofing Study";
   TABLES TYPE * PROBLEM / CHISQ CMH;
   WEIGHT COUNT;
RUN;

/*
RR = 1.800 (room noise increases the incidence of problems), 95% CI (1.057, 3.065).
*/

PROC FORMAT;
   VALUE SIZE 1 = 'Small' 
              2 = 'Medium' 
              3 = 'Large' 
              4 = 'Gigantic';
RUN;
DATA CLASS;
   INPUT SIZE PROBLEM $ COUNT @@;
   FORMAT SIZE SIZE.;
DATALINES;
11-YES 31 2-NO 122 1-YES 62 2-NO 22
31-YES 173 2-NO 384 1-YES 804 2-NO 120
;
PROC FREQ DATA=CLASS;
   TITLE "Relationship Between Class Size and Behavior";
   TABLES PROBLEM * SIZE / CHISQ;
   WEIGHT COUNT;
RUN;

/*
Chi-square test for trend = 6.038, p = .014.
	NOTE: The chi-square for the 2 by 4 table is 6.264, with p = .094.
*/

***Problem 3-17;
DATA TEMP;
   INPUT T_CONTRL $ GROUP : $10. COLD $ COUNT;
DATALINES;
1-POOR SMOKERS 1-YES 30
1-POOR SMOKERS 2-NO 50
1-POOR NONSMOKERS 1-YES 40
1-POOR NONSMOKERS 2-NO 100
2-GOOD SMOKERS 1-YES 20
2-GOOD SMOKERS 2-NO 55
2-GOOD NONSMOKERS 1-YES 35
2-GOOD NONSMOKERS 2-NO 150
;
PROC FREQ DATA=TEMP;
   TITLE "Relationship Between Temperature Control and Colds";
   TABLES GROUP * T_CONTRL * COLD / ALL;
   WEIGHT COUNT;
RUN;

/*
The overall RR for the combined tables = 1.468.
	The 95% CI is (1.086, 1.985).
	The p-value is .013.
*/

***Problem 3-19;
PROC FORMAT;
   VALUE PROB 1 = 'Cold' 
              2 = 'Flu' 
              3 = 'Trouble Sleep'
              4 = 'Chest Pain'  
              5 = 'Muscle Pain' 
              6 = 'Headache'
              7 = 'Overweight'  
              8 = 'High BP' 
              9 = 'Hearing Loss';
RUN;
DATA PATIENT;
   INPUT SUBJ   1-2 
         PROB1    3 
         PROB2    4 
         PROB3    5 
         HR     6-8 
         SBP   9-11  
         DBP  12-14;
DATALINES;
1112778130 80
178782180110
03162120 78
426168130 80
8958120 76
994882178100
;
PROC MEANS DATA=PATIENT N MEAN STD MAXDEC=1;
   TITLE "Statistics from Patient Data Base";
   VAR HR SBP DBP;
RUN;

/*
For part (b) add:
*/

***Solution without arrays;
DATA PROBLEM;         
   SET PATIENT;         
   PROB = PROB1;         
   IF PROB NE . THEN OUTPUT;   
   PROB = PROB2;         
   IF PROB NE . THEN OUTPUT;   
   PROB = PROB3;         
   IF PROB NE . THEN OUTPUT;   
   FORMAT PROB PROB.;      
   KEEP PROB;         
RUN;

*Solution with arrays;
DATA PROBLEM;
   SET PATIENT;
   ARRAY XPROB[3] PROB1-PROB3;
   DO I = 1 TO 3;
      PROB = XPROB[I];
      IF PROB NE . THEN OUTPUT;
   END;
   FORMAT PROB PROB.;
   KEEP PROB;
RUN;

PROC FREQ DATA=PROBLEM;
   TABLES PROB;
RUN;

***Problem 3-21;

/*
Line 3: The formats cannot be assigned to variables before they have been defined. 
Therefore, move lines 5 through 8 to the beginning of the program (before line 1).
Line 11: PROC FREQ uses the keyword TABLES, not VAR, to specify a list of variables.
Line 11: You cannot use the CHISQ option unless a two-way table (or higher order) 
is specified. That is, we could have written:
*/

PROC FREQ DATA=IGOOFED;
   TABLES GENDER*RACE / CHISQ;
RUN;

/*
Line 14: You cannot use a BY statement unless the data set has been sorted first by the 
same variable.
*/

***CHAPTER 4;

***Problem 4-1;
DATA PROB4_1;
   INPUT @1 ID 3.
         @5 (DOB ST_DATE END_DATE)(MMDDYY8.)
         /**************************************************
            Note: The line above is using a variable list
            and an informat list.  An alternative is to
            list each variable with a column pointer and
            an informat 
         ***************************************************/
         @29 SALES 4.;
   AGE = YRDIF(DOB,ST_DATE,'ACTUAL');
   *For section E, substitute the line below for AGE;
   AGE = INT(YRDIF(DOB,ST_DATE,'ACTUAL'));
   LENGTH = YRDIF(ST_DATE,END_DATE,'ACTUAL') + 1;
   SALES_YR = SALES / LENGTH;
   *For section, E substitute the line below for SALES_YR;
   SALES_YR = ROUND ((SALES/LENGTH),10);
   FORMAT DOB ST_DATE END_DATE MMDDYY10. 
          SALES_YR DOLLAR8.;
DATALINES;
001 1021194611121980122819887343
002 0913195502021980020419880123
005 0606194003121981031220040000
003 0705194411151980111320009544
;
PROC PRINT DATA=PROB4_1;
   TITLE "Report for Homework Problem 4-1";
   ID ID;
   VAR DOB AGE LENGTH SALES_YR;
RUN;

***Problem 4-3;
DATA RATS;
   INPUT @1 RAT_NO 1.
         @3 DOB DATE9.
         @13 DISEASE DATE9.
         @23 DEATH DATE9.
         @33 GROUP $1.;
    BIR_TO_D = DISEASE - DOB;
    DIS_TO_D = DEATH - DISEASE;
    AGE = DEATH - DOB;
    FORMAT DOB DISEASE DEATH MMDDYY10.;
DATALINES;
1 23MAY1990 23JUN1990 28JUN1990 A
2 21MAY1990 27JUN1990 05JUL1990 A
3 23MAY1990 25JUN1990 01JUL1990 A
4 27MAY1990 07JUL1990 15JUL1990 A
5 22MAY1990 29JUN1990 22JUL1990 B
6 26MAY1990 03JUL1990 03AUG1990 B
7 24MAY1990 01JUL1990 29JUL1990 B
8 29MAY1990 15JUL1990 18AUG1990 B
;
PROC MEANS DATA=RATS MAXDEC=1 N MEAN STD STDERR;
   CLASS GROUP;
   VAR BIR_TO_D--AGE;
RUN;

***Problem 4-5;
DATA PATIENTS;
   INPUT  @1  ID         3.
          @4  DATE MMDDYY6.
          @10 HR         3.
          @13 SBP        3.
          @16 DBP        3.
          @19 DX         3.
          @22 DOCFEE     4.
          @26 LABFEE     4.;
   FORMAT DATE MMDDYY8.;
DATALINES;
00710218307012008001400400150
00712018307213009002000500200
00909038306611007013700300000
00507058307414008201300900000
00501158208018009601402001500
00506188207017008401400800400
00507038306414008401400800200
;
PROC SORT DATA=PATIENTS;
   BY ID DATE;
RUN;
DATA PROB4_5;
   SET PATIENTS;
   BY ID;
  *Omit the first VISIT for each patient;
  IF NOT FIRST.ID;
RUN;
PROC MEANS DATA=PROB4_5 MEAN MAXDEC=2;
   CLASS ID;
   VAR HR SBP DBP;
RUN;

***Problem 4-7;
PROC SORT DATA=PATIENTS; ***From problem 4-5;
   BY ID;
RUN;
DATA PROB4_7;
   SET PATIENTS;
   BY ID;
   *Omit patients with only one visit;
IF FIRST.ID AND LAST.ID THEN DELETE;
RUN;
PROC MEANS DATA=PROB4_7 NOPRINT NWAY;
   CLASS ID;
   VAR HR SBP DBP;
   OUTPUT OUT = PAT_MEAN MEAN= / AUTONAME;
RUN;

***Problem 4-9;
***Program to create data set BLOOD;
DATA BLOOD;
   LENGTH GROUP $ 1;
   INPUT ID GROUP $ TIME WBC RBC @@;
DATALINES;
1 A 1 8000 4.5   1 A 2 8200 4.8   1 A 3 8400 5.2
1 A 4 8300 5.3   1 A 5 8400 5.5
2 A 1 7800 4.9   2 A 2 7900 5.0
3 B 1 8200 5.4   3 B 2 8300 5.4   3 B 3 8300 5.2
3 B 4 8200 4.9   3 B 5 8300 5.0
4 B 1 8600 5.5
5 A 1 7900 5.2   5 A 2 8000 5.2   5 A 3 8200 5.4
5 A 4 8400 5.5
;
PROC MEANS DATA=BLOOD NWAY NOPRINT;
   CLASS ID;
   ID GROUP;
   VAR WBC RBC;
   OUTPUT OUT=TEMP(WHERE=(_FREQ_ GT 2) 
                   DROP=_TYPE_) 
                   MEAN = M_WBC M_RBC;
RUN;
PROC PRINT DATA=TEMP NOOBS;
   TITLE "Listing of data set TEMP";
RUN;

***Problem 4-11;
/*
Replace the OUTPUT statement of PROC MEANS with:

OUTPUT OUT=TEMP(WHERE=(_FREQ_ GT 2) 
                DROP=_TYPE_)
                MEAN=  
                STD= /AUTONAME;
RUN;
*/

***CHAPTER 5;

***Problem 5-1;
***a;
DATA PROB5_1;
   INPUT X Y Z;
DATALINES;
1 3 15
7 13 7
8 12 5
3 4 14
4 7 10
;
PROC CORR DATA=PROB5_1;   /* x vs. y r =  .965 p = .0078 */
   VAR X;                   /* x vs. z r = -.975 p = .0047 */
   WITH Y Z;
RUN;
***b;
PROC CORR DATA=PROB5_1;   /* y vs. z r = -.963 p = .0084 */
   VAR X Y Z;
RUN;

***Problem 5-3;
DATA PRESSURE;
   INPUT AGE SBP;
DATALINES;
15 116
20 120
25 130
30 132
40 150
50 148
;
PROC CORR DATA=PRESSURE;
   VAR AGE SBP;
RUN;

***Problem 5-5;
***a;
PROC REG DATA=PROB5_1;
   MODEL Y = X;
RUN;

/**************************************
 Intercept = .781, prob>|t| = .5753
 Slope = 1.524, prob>|t| = .0078
***************************************/

***Problem 5-7;
DATA PROB5_7;
   INPUT X Y Z;
   LX = LOG(X);
   LY = LOG(Y);
   LZ = LOG(Z);
DATALINES;
1 3 15
7 13 7
8 12 5
3 4 14
4 7 10
;
PROC CORR DATA=PROB5_7;
   VAR LX LY LZ;
RUN;

***Problem 5-9;
***a;
PROC PLOT DATA=PROB5_1;
   PLOT Y*X;
RUN;
***b;
SYMBOL1 VALUE=DOT COLOR=BLACK;
PROC REG DATA=PROB5_1;
   MODEL Y = X;
   PLOT Y*X;
RUN;
***Alternative using PROC GPLOT;
SYMBOL VALUE=DOT COLOR=BLACK I=RL;
PROC GPLOT DATA=PROB5_1;
   TITLE "Plot of Problem 5-1 Data and Regression Line";
   PLOT Y*X;
RUN;

***Problem 5-11;
***a - c;
DATA PROB5_11;
   INPUT COUNTY POP HOSPITAL FIRE_CO RURAL $;
DATALINES;
1   35   1   2   YES
2   88   5   8   NO
3    5   0   1   YES
4   55   3   3   YES
5   75   4   5   NO
6  125   5   8   NO
7  225   7   9   YES
8  500  10  11   NO
;
PROC UNIVARIATE DATA=PROB5_11 NORMAL PLOT;
   TITLE "Checking the Distributions";
   VAR POP HOSPITAL FIRE_CO;
RUN;
PROC CORR DATA=PROB5_11 NOSIMPLE PEARSON SPEARMAN;
   TITLE "Correlation Matrix";
   VAR POP HOSPITAL FIRE_CO;
RUN;

/*
Because of the outliers in the population variable, we prefer the Spearman correlation for 
this problem.
(d) We can use the output from MEANS or UNIVARIATE to find the medians and do the recoding. 
In Chapter 6 we will see that PROC RANK can be used to produce a median cut automatically by 
using the GROUPS=2 option. For now, we will recode the variables using formats. You can also 
create new variables in the data step with IF statements.
*/

PROC FORMAT;
   VALUE POP LOW-81  = 'Below median' 
             82-HIGH = 'Above Median';
   VALUE HOSPITAL LOW-4  = 'Below Median' 
                  5-HIGH = 'Above Median';
   VALUE FIRE_CO LOW-6  = 'Below Median' 
                 7-HIGH = 'Above Median';
RUN;
PROC FREQ DATA=PROB5_11; ***Data set from above;
   TITLE "Cross Tabulations";
   FORMAT POP POP. HOSPITAL HOSPITAL. FIRE_CO FIRE_CO.;
   TABLES RURAL*(POP HOSPITAL FIRE_CO) / CHISQ;
RUN;

***Problem 5-13;
/**********************************************************************
Line 1: Incorrect data set name, cannot contain a dash.
Lines 3-5: These lines will recode missing values to 1, which we probably do not want to do. the correct form of these statements is:
  IF X LE 0 AND X NE . THEN X = 1;

Line 10: The options PEARSON and SPEARMAN do not follow a slash. The line should read:
   PROC CORR DATA=MANY_ERR PEARSON SPEARMAN;

Line 11: The correct form for a list of variables where the "root" is not the same is:
   VAR X -- LOGZ;

   Remember, the single dash is used for a list of variables such as ABC1 - ABC25.
***********************************************************************/

***CHAPTER 6;

***Problem 6-1;
DATA HEADACHE;
   INPUT TREAT $ TIME @@;
DATALINES;
A 40 A 42 A 48 A 35 A 62 A 35
T 35 T 37 T 42 T 22 T 38 T 29
;
PROC TTEST DATA=HEADACHE;
   TITLE "Headache Study";
   CLASS TREAT;
   VAR TIME;
RUN;

/*
Not significant at the .05 level (t = 1.93, p = .083).
*/

***Problem 6-3;
PROC NPAR1WAY DATA=HEADACHE WILCOXON;
   TITLE "Nonparametric Comparison";
   CLASS TREAT;
   VAR TIME;
   EXACT WILCOXON;
RUN;

/*
Sum of ranks for A = 48.5; for B, 29.5.
Exact two-sided p = .1385
Approximation using a normal approximation with a continuity correction z = 1.45, p = .146.
*/

***Problem 6-5;
***Use a paired t-test;
   DATA PAIR;
      INPUT SUBJ A_TIME B_TIME;
   DATALINES;
   1 20 18
   2 40 36
   3 30 30
   4 45 46
   5 19 15
   6 27 22
   7 32 29
   8 26 25
   ;
   PROC TTEST DATA=PAIR;
      TITLE "Paired T-Test";
      PAIRED A_TIME * B_TIME;
   RUN;

/*
   t = 3.00, p = .0199; drug B works faster.
*/

***Problem 6-7;
PROC FORMAT;
   VALUE GROUP 0 = 'A' 1 = 'B' 2 = 'C';
RUN;
DATA RANDOM;
   INPUT SUBJ @@;
   GROUP = RANUNI(0); *NOTE: CAN ALSO USE UNIFORM FUNCTION;
DATALINES;
001 137 454 343 257 876 233 165 002
;
PROC RANK DATA=RANDOM OUT = RANKED GROUP = 3;
   VAR GROUP;
RUN;
PROC SORT DATA=RANKED;
   BY SUBJ;
RUN;
PROC PRINT DATA=RANKED;
   TITLE "Listing of Subject Numbers and Group Assignments";
   FORMAT GROUP GROUP.;
   ID SUBJ;
   VAR GROUP;
RUN;

***Problem 6-9;
/*
Line 2: Variable name HEARTRATE too long.
Line 11: Correct procedure name is TTEST.
*/

***CHAPTER 7;

***Problem 7-1;
DATA BRANDTST;
   DO BRAND = 'A','N','T';
      DO SUBJ = 1 TO 8;
         INPUT TIME @;
         OUTPUT;
      END;
   END;
DATALINES;
8 10 9 11 10 10 8 12
4 7 5 5 6 7 6 4
12 8 10 10 11 9 9 12
;
PROC ANOVA DATA=BRANDTST;
   TITLE "Brand of Tennis Shoe Comparison";
   CLASS BRAND;
   MODEL TIME = BRAND;
   MEANS BRAND / SNK;
RUN;

/*********************************************************************
F = 28.89, p = .0001; N is significantly lower than either T or A 
(p < .05). T and A are not significantly different (p > .05).
**********************************************************************/

***Problem 7-3;
DATA BOUNCE;
   DO AGE = 'NEW', 'OLD';
      DO BRAND = 'W','P';
         DO I = 1 TO 5;
            INPUT BOUNCES @;
            OUTPUT;
         END;
      END;
   END;
   DROP I;
DATALINES;
67 72 74 82 81 75 76 80 72 73
46 44 45 51 43 63 62 66 62 60
;
PROC ANOVA DATA=BOUNCE;
   TITLE "Two-way ANOVA (AGE by BRAND) for Tennis Balls";
   CLASS AGE BRAND;
   MODEL BOUNCES = AGE | BRAND;
   MEANS AGE | BRAND;
RUN;

/*********************************************************************
NOTE: A simpler INPUT statement could have been used:

   INPUT BRAND $ AGE $ BOUNCES;

With the data listed one number per line such as:
W NEW 67
P NEW 75
   etc.

Both main effects (AGE and BRAND) are significant (p = .0001 and .0002, respectively). The interaction is also significant, p = .0002.
*********************************************************************/

***Problem 7-5;
***a;
DATA SODA;
   INPUT BRAND $ AGEGRP RATING @@;
DATALINES;
C 1 7  C 1 6  C 1 6  C 1 5  C 1 6  P 1 9  P 1 8
P 1 9  P 1 9  P 1 9  P 1 8  C 2 9  C 2 8  C 2 8
C 2 9  C 2 7  C 2 8  C 2 8  P 2 6  P 2 7  P 2 6
P 2 6  P 2 5
;
PROC GLM DATA=SODA;
   TITLE "Two-way Unbalanced ANOVA";
   CLASS BRAND AGEGRP;
   MODEL RATING = BRAND | AGEGRP;
   MEANS BRAND | AGEGRP;
RUN;
***b;
PROC MEANS DATA=SODA NWAY NOPRINT;
   CLASS BRAND AGEGRP;
   VAR RATING;
   OUTPUT OUT = MEANS MEAN = ;
RUN;
SYMBOL1 VALUE=CIRCLE I=JOIN COLOR=BLACK;
SYMBOL2 VALUE=SQUARE I=JOIN COLOR=BLACK;
PROC GPLOT DATA=MEANS;
     PLOT RATING*AGEGRP = BRAND;
RUN;
***c;
PROC SORT DATA=SODA;
   BY AGEGRP;
RUN;
PROC TTEST DATA=SODA;
   BY AGEGRP;
   CLASS BRAND;
   VAR RATING;
RUN;

***Problem 7-7;
PROC TTEST DATA=BRANDTST;
   WHERE BRAND = 'A' OR BRAND = 'T';
   /* Alternative: WHERE BRAND IN ('A','T'); */
   /* WHERE BRAND NE 'N'; is not as desirable, since
   in a more general data set, there may be missing
   or miscoded values */
   CLASS BRAND;
   VAR TIME;
RUN;

*Problem 7-9;
/*
Line 4: Since this is a two-way unbalanced design, PROC GLM should be used instead of PROC ANOVA.
*/

***Problem 7-11;
***a;
DATA PROB7_6;
   DO GROUP = 'A','B','C';
      INPUT M_SCORE AGE @;
      OUTPUT;
   END;
DATALINES;
90 16 92 18 97 18
88 15 88 13 92 17
72 12 76 12 88 16
82 14 78 14 92 17
65 12 90 17 99 17
74 13 68 12 82 14
;
PROC ANOVA DATA=PROB7_6;
   CLASS GROUP;
   MODEL M_SCORE AGE = GROUP;
   MEANS GROUP / SNK;
RUN;
***b;
PROC GLM DATA=PROB7_6;
   TITLE "Testing Assumption of Homogeneity of Slope";
   CLASS GROUP;
   MODEL M_SCORE = AGE GROUP AGE*GROUP;
RUN;

/* Interaction term not significant. OK to do analysis of covariance */

***c;
PROC GLM DATA=PROB7_6;
   TITLE "Analysis of Covariance";
   CLASS GROUP;
   MODEL M_SCORE = AGE GROUP;
   LSMEANS GROUP / PDIFF;
RUN;

/**********************************************************************
   In the unadjusted analysis, the groups are significantly different 
(p = .0479) and the ages are nearly significant (p = .0559). The null hypothesis that the slopes are equal among the three groups is not rejected (AGE*GROUP interaction p = .1790). Adjusting for age, the group differences on math scores disappears completely (p = .7606).
***********************************************************************/

***CHAPTER 8;

***Problem 8-1;
DATA SHIRT;
   INPUT (JUDGE BRAND COLOR WORK OVERALL)(1.);
   INDEX = (3*OVERALL+2*WORK+COLOR) / 6.0;
DATALINES;
11836
21747
31767
41846
12635
22534
32546
42436
13988
23877
33978
43887
;
PROC ANOVA DATA=SHIRT;
   TITLE "Problem 8-1";
   CLASS JUDGE BRAND;
   MODEL COLOR WORK OVERALL INDEX = JUDGE BRAND;
   MEANS BRAND / SNK;
RUN;

***Problem 8-3;
DATA WATER;
   INPUT ID 1-3 CITY $ 4 RATING 5;
DATALINES;
00118
00126
00138
00145
00215
00226
00235
00244
00317
00324
00336
00344
00417
00425
00437
00443
;
PROC ANOVA DATA=WATER;
   TITLE "Problem 8-3";
   CLASS ID CITY;
   MODEL RATING = ID CITY;
   MEANS CITY / SNK;
RUN;

***Problem 8-5;
PROC FORMAT;
   VALUE CITY 1 = 'New York' 
              2 = 'New Orleans'
              3 = 'Chicago' 
              4 = 'Denver';
RUN;
DATA PROB8_5;
   INPUT JUDGE 1-3 @;
   DO CITY = 1 TO 4;
      INPUT TASTE 1. @;
      OUTPUT;
   END;
   FORMAT CITY CITY.;
DATALINES;
0018685
0025654
0037464
0047573
;
***Same PROC ANOVA statements as problem 8-3 except for the
Data Set Name;
***Solution using the REPEATED statement of PROC ANOVA;
DATA REPEAT;
   INPUT ID 1-3 @4 (RATING1-RATING4)(1.);
DATALINES;
0018685
0025654
0037464
0047573
;
PROC ANOVA DATA=REPEAT;
      MODEL RATING1-RATING4 = /NOUNI;
      REPEATED CITY;
   RUN;

/*********************************************************************************
   The unadjusted comparison shows that the cities are not all equal (p =  .0067). 
   Using the Greenhouse-Geisser correction, the p-value is .0375 and, using the 
   Huynh-Feldt correction, the p-value is .0108. Therefore, you should feel 
   comfortable in rejecting the null hypothesis at the .05 level, regardless of 
   which correction (if any) you use.
**********************************************************************************/

***Problem 8-7;
DATA RATS;
   INPUT GROUP $ RATNO DISTAL PROXIMAL;
DATALINES;
N 1 34 38
N 2 28 38
N 3 38 48
N 4 32 38
D 5 44 42
D 6 52 48
D 7 46 46
D 8 54 50
;
PROC ANOVA DATA=RATS;
   CLASS GROUP;
   MODEL DISTAL PROXIMAL = GROUP / NOUNI;
   REPEATED LOCATION 2;
RUN;

/***********************************************************************
   Although the main effects are significant (GROUP p = .01, LOCATION 
p = .0308) the interaction term is highly significant (GROUP*LOCATION 
interaction F = 31.58, p = .0014). We should look carefully at the 
interaction graph to see exactly what is going on.
***********************************************************************/

***Problem 8-9;
/*
The DO loops are in the wrong order, and the OUTPUT statement is missing. 
Lines 2 through 8 should read:

DO SUBJ = 1 TO 3;
   DO GROUP = 'CONTROL','DRUG';
      DO TIME = 'BEFORE','AFTER';
         INPUT SCORE @;
         OUTPUT;
      END;
   END;
END;

   There are no other errors.
*/

***CHAPTER 9;

***Problem 9-1;
DATA TOMATO;
   DO LIGHT = 5,10,15;
      DO WATER = 1,2;
         DO I = 1 TO 3;
            INPUT YIELD @;
            OUTPUT;
         END;
      END;
   END;
   DROP I;
DATALINES;
12 9 8 13 15 14 16 14 12 20 16 16 18 25 20 25 27 29
;
PROC REG DATA=TOMATO;
   TITLE "Question 9-1";
   MODEL YIELD = LIGHT WATER;
RUN;

***Problem 9-3;
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
   MODEL BOOKS = ENROLL DEGREE AREA / SELECTION=FORWARD;
RUN;

***Problem 9-5;
DATA PROB9_3;
   INPUT GPA HS_GPA BOARD IQ;
DATALINES;
3.9   3.8   680   130
3.9   3.9   720   110
3.8   3.8   650   120
3.1   3.5   620   125
2.9   2.7   480   110
2.7   2.5   440   100
2.2   2.5   500   115
2.1   1.9   380   105
1.9   2.2   380   110
1.4   2.4   400   110
;
PROC REG DATA=PROB9_3;
   MODEL GPA = HS_GPA BOARD IQ / SELECTION = MAXR;
RUN;

***Problem 9-7;
DATA PEOPLE;
   INPUT HEIGHT WAIST LEG ARM WEIGHT;
DATALINES;
(data lines)
;
PROC CORR DATA=PEOPLE NOSIMPLE;
   VAR HEIGHT--WEIGHT;
RUN;
PROC REG DATA=PEOPLE;
   MODEL WEIGHT = HEIGHT WAIST LEG ARM /
   SELECTION = STEPWISE;
RUN;

***You may also use FORWARD, BACKWARD, or MAXR instead of STEPWISE;

***Problem 9-9;
/*
Ha! No errors here. As a matter of fact, you can use this program for problem 9-7.
*/

***Problem 9-11;
PROC LOGISTIC DATA=SMOKING ORDER=FORMATTED;
   TITLE "SMOKING, ASBESTOS, AND SES IN THE MODEL";
   CLASS SES (PARAM=REF REF='2-Medium');
   MODEL OUTCOME = SMOKING ASBESTOS SES / CTABLE PPROB=0 TO 1 BY .1
                                          OUTROC=ROCDATA;
RUN;
SYMBOL1 V=DOT I=SM60 COLOR=BLACK WIDTH=2;
PROC GPLOT DATA=ROCDATA;
   TITLE "ROC Curve";
   PLOT _SENSIT_ * _1MSPEC_ ;
   LABEL _SENSIT_ = 'Sensitivity'
         _1MSPEC_ = '1 - Specificity';
RUN;

***Problem 9-13;
*Program Name: PROB9_13.SAS in C:\APPLIED
Purpose: Solution to homework problem 9-13
Date: April, 2004;
PROC FORMAT;
   VALUE YES_NO   0 = 'No'
                  1 = 'Yes';
RUN;
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
PROC LOGISTIC DATA=LOGISTIC DESCENDING;
   TITLE "Predicting Accidents Using Logistic Regression";
   MODEL ACCIDENT = DRINK PREVIOUS /
      SELECTION = FORWARD
      RISKLIMITS;
RUN;
QUIT;

/******************************************************************
   The logistic regression equation is:
   LOG(odds of accident) = -1.9207 + 1.9559 (DRINK)
            + 1.7770 (PREVIOUS).
   The odds and probability of an accident for person 1 (no drinking history, no previous accidents) are .1465 and .1278 respectively. For person 2 (history of a drinking problem but no previous accident history), they are 1.0358 and .5088 respectively. The odds ratio is 1.0358.1465 = 7.07, which agrees with the PROC LOGISTIC output.
********************************************************************/

***CHAPTER 10;

***Problem 10-1;
DATA QUEST;
   INPUT ID 1-3 AGE 4-5 GENDER $ 6 RACE $ 7 MARITAL $ 8
      EDUC $ 9 PRES 10 ARMS 11 CITIES 12;
DATALINES;
001091113232
002452222422
003351324442
004271111121
005682132333
006651243425
;
PROC FACTOR DATA=QUEST 
            ROTATE=VARIMAX
            SCREE
            NFACTORS=2 
            OUT=FACT;
   TITLE "Example of Factor Analysis";
   VAR PRES ARMS CITIES;
   PRIORS SMC;
RUN;

***Problem 10-3;
DATA SCORE;
   ARRAY ANS[5] $ 1 ANS1-ANS5;
   ARRAY KEY[5] $ 1 KEY1-KEY5;
   ARRAY S[5] 3 S1-S5; ***Score array 1 = right,0 = wrong;
   RETAIN KEY1-KEY5;
   IF _N_ = 1 THEN INPUT (KEY1-KEY5)($1.);
   INPUT @1 ID 1-9
   @11 (ANS1-ANS5)($1.);
   DO I = 1 TO 5;
      S[I] = KEY[I] EQ ANS[I];
   END;
   DROP I;
DATALINES;
ABCDE
123456789 ABCDE
035469871 BBBBB
111222333 ABCBE
212121212 CCCDE
867564733 ABCDA
876543211 DADDE
987876765 ABEEE
;
PROC FACTOR DATA=SCORE 
            OUT=FACTDATA 
            NFACTORS=1;
   TITLE "Factor Analysis of Test Data";
   VAR S1-S5;
   PRIORS SMC;
RUN;
PROC PRINT DATA=FACTDATA;
   TITLE "Listing of Data Set FACTDATA";
RUN;

***CHAPTER 11;

***Problem 11-1;
*---------------------------------------------------------*
| Program to score a five item multiple choice exam.      |
| Data: The first line is the answer key, remaining lines |
| contain the student responses.                          |
*---------------------------------------------------------*;
DATA SCORE;
   ARRAY ANS[5] $ 1 ANS1-ANS5; ***Student answers;
   ARRAY KEY[5] $ 1 KEY1-KEY5; ***Answer key;
   ARRAY S[5] 3 S1-S5; ***Score array 1 = right,0 = wrong;
   RETAIN KEY1-KEY5;
   ***Read the answer key;
   IF _N_ = 1 THEN INPUT (KEY1-KEY5)($1.);
   ***Read student responses;
   INPUT @1 SS 1-9
   @11 (ANS1-ANS5) ($1.);
   ***Score the test;
   DO I = 1 TO 5;
   S[I] = KEY[I] EQ ANS[I];
   END;
   ***Compute Raw and Percentage scores;
   RAW = SUM (OF S1-S5);
   PERCENT = 100*RAW / 5;
   KEEP SS RAW PERCENT S1-S5; ***S1-S5 needed for 11-3;
   LABEL SS = 'Social Security Number'
      RAW = 'Raw Score'
      PERCENT = 'Percent Score';
DATALINES;
BCDAA
123456789 BCDAA
001445559 ABCDE
012121234 BCCAB
135632837 CBDAA
005009999 ECECE
789787878 BCDAA
;
PROC SORT DATA=SCORE;
   BY SS;
RUN;
PROC PRINT DATA=SCORE LABEL;
   TITLE "Listing of Student Scores in SS Order";
   ID SS;
   VAR RAW PERCENT;
   FORMAT SS SSN11.;
RUN;
PROC SORT DATA=SCORE;
   BY DESCENDING RAW;
RUN;
PROC PRINT DATA=SCORE LABEL;
   TITLE "Listing of Student Scores in Decreasing Order";
   ID SS;
   VAR RAW PERCENT;
   FORMAT SS SSN11.;
RUN;

***Problem 11-3;
PROC CORR DATA=SCORE ALPHA NOSIMPLE;
   TITLE "Computing KR-20";
   VAR S1-S5;
RUN;
PROC CORR DATA=SCORE NOSIMPLE;
   TITLE "Point-biserial Correlations";
   VAR S1-S5;
   WITH RAW; ***Same results if you use PERCENT;
RUN;

***Problem 11-5;
DATA KAPPA;
   LENGTH RATER_1 RATER_2 $ 1;
   INPUT RATER_1 RATER_2 @@;
DATALINES;
C C   X X   X X   C X   X C   X X   X X
C X   C C   X X   C C   C C   X X   C C
;
PROC FREQ DATA=KAPPA;
   TITLE "Inter-rater Reliability: Coefficient Kappa";
   TABLES RATER_1 * RATER_2 / AGREE NOCUM NOPERCENT;
RUN;

***CHAPTER 12;

***Problem 12-1;
***a;
DATA PROB12_1;
   INPUT GROUP $ SCORE;
DATALINES;
P   77
P   76
P   74
P   72
P   78
D   80
D   84
D   88
D   87
D   90
;
***b;
DATA PROB12_1;
   INPUT GROUP $ SCORE @@;
DATALINES;
P 77 P 76 P 74 P 72 P 78
D 80 D 84 D 88 D 87 D 90
;
***c;
DATA PROB12_1;
   DO GROUP = 'P','D';
      DO I = 1 TO 5;
      INPUT SCORE @@;
      OUTPUT;
   END;
END;
DROP I;
DATALINES;
77 76 74 72 78
80 84 88 87 90
;
***d;
DATA PROB12_1;
   DO GROUP = 'P','D';
      DO I = 1 TO 5;
         SUBJ+1;
         INPUT SCORE @@;
         OUTPUT;
      END;
   END;
   DROP I;
DATALINES;
77 76 74 72 78
80 84 88 87 90
;

***Problem 12-3;
DATA PROB12_3;
   INFILE DATALINES DLM = ',';
   INPUT X1-X4;
DATALINES;
1,3,5,7
2,4,6,8
9,8,7,6
;

***Problem 12-5;
DATA PROB12_5;
   INFILE DATALINES DSD MISSOVER;
   LENGTH C $ 9;
   INPUT X Y C $ Z;
DATALINES;
1,,"HELLO",7
2,4,TEXT,8
9,,,6
21,31,SHORT
100,200,"LAST LINE",999
;

***Problem 12-7;
DATA OFFICE;
   INFORMAT VISIT MMDDYY8. DX $10. COST DOLLAR8.;
   INFILE DATALINES MISSOVER;
   INPUT ID VISIT DX COST;
DATALINES;
1 10/01/1996   V075   $102.45
2   02/05/1997   X123456789 $3,123
3   07/07/1996   V4568
4   11/11/1996   A123   $777.
;

***Problem 12-9;
DATA PROB12_9;
   INPUT   SUBJECT $ 1-3
      A1   $ 5
      X   7-8
      Y   9-10
      Z   11-12;
DATALINES;
A12 X 111213
A13 W 102030
;

***Problem 12-11;
DATA PROB12_11;
   INPUT @1   SUBJECT   $3.
      @5   A1   $1.
      @7   (X Y Z)   (2.);   /* OK to specify X, Y, and Z */
DATALINES;                   /* separately                */
A12 X 111213
A13 W 102030
;

***Problem 12-13;
DATA PROB12_13;
   INPUT @1   ID   3.
      @4   GENDER   $1.
      @10   (DOB VISIT DISCHRG)   (MMDDYY6.)
      @30   (SBP1-SBP3)   (3. + 5)
      @33   (DBP1-DBP3)   (3. + 5)
      @36   (HR1-HR3)   (2. + 6);
   FORMAT DOB VISIT DISCHRG MMDDYY8.;
DATALINES;
123M   102146111196111396   130 8668134 8872136 8870
456F   010150122596020597   220110822101028424012084
;

***Problem 12-15;
DATA PROB12_15;
   INPUT #1 @1   ID  2.
            @4   X   2.
            @6   Y   2.
         #2 @3   A1 $3.
            @6   A2 $1.;
DATALINES;
01 2345
   AAAX
02 9876
   BBBY
;

***Problem 12-17;
DATA PROB12_17;
   INPUT X Y @@;
DATALINES;
1 2  3 4  5 6  7 8
11 12   13 14
21 22  23 24  25 26  27 28
;

***Problem 12-19;
DATA SURVEY;
   INPUT @12 TEST 1. @;
   IF TEST = 1 THEN
   INPUT @1  ID    $3.
         @4  HEIGHT 2.
         @6  WEIGHT 3.;
      ELSE IF TEST = 2 THEN
      INPUT @1 ID   $3.
            @4 AGE    2.
            @6 HEIGHT 2.
            @8 WEIGHT 3.;
   DROP TEST;
DATALINES;
00168155   1
00272201   1
0034570170 2
0045562 90 2
;

***CHAPTER 13;

***Problem 13-1;
LIBNAME A 'A:\';
DATA A.BILBO;
   INFILE 'A:FRODO' PAD; *(Don't forget the PAD);
   INPUT ID 1-3 AGE 5-6 HR 8-10 SBP 12-14 DBP 16-18;
   AVEBP = 2*DBP/3 + SBP/3;
RUN;
DATA A.HIBP;
   SET A.BILBO;
   WHERE AVEBP GE 100;
RUN;

/*************************************************************
Alternative solutions using a WHERE data set option:
**************************************************************/
DATA A.HIBP;
   SET A.BILBO(WHERE=(AVEBP GE 100));
RUN;

***Problem 13-3;
LIBNAME INDATA 'C:\SASDATA';
OPTIONS FMTSEARCH = (INDATA);
***Alternative is to use the default library name LIBRARY;
PROC FREQ DATA=INDATA.SURVEY ORDER=FREQ;
   TITLE "Frequencies for ICD_9 codes from the 1990 Survey";
   TABLES ICD_9;
RUN;
PROC MEANS DATA=INDATA.SURVEY N MEAN
      STD STDERR MIN MAX MAXDEC=2;
   TITLE "Descriptive Statistics for the Survey";
   VAR AGE;
RUN;

***Problem 13-5;
LIBNAME C 'C:\MYDATA';
DATA C.DEM_9697;
   IF END96 NE 1 THEN INFILE 'A:DEM_1996' END=END96;
   ELSE INFILE 'A:DEM_1997';
   INPUT @1   ID       $3.
         @4   AGE       2.
         @6   JOB_CODE $1.
         @7   SALARY    6.;
RUN;

***Problem 13-7;
DATA PROB13_4;
   INFILE 'B:SAMPLE.DTA' LRECL=320 MISSOVER;
   INPUT X1-X100;
RUN;

***Problem 13-9;
***DATA step to create MILTON;
DATA MILTON;
   INPUT X Y A B C Z;
DATALINES;
1 2 3 4 5 6
11 22 33 44 55 66
;
DATA _NULL_; ***No need to create a SAS data set;
   SET MILTON;
   FILE 'C:\MYDATA\OUTDATA';
   PUT @1 (A B C) (3.);
RUN;

***CHAPTER 14;

***Problem 14-1;
***a;
DATA GYM;
   LENGTH GENDER $ 1;
   INPUT ID GENDER AGE VAULT FLOOR P_BAR;
   ***GENDER is already declared a character variable by the LENGTH  
      statement so a $ is not needed in the INPUT statement;
DATALINES;
3   M    8   7.5   7.2   6.5
5   F   14   7.9   8.2   6.8
2   F   10   5.6   5.7   5.8
7   M    9   5.4   5.9   6.1
6   F   15   8.2   8.2   7.9
;
***b;
DATA MALE_GYM;
      SET GYM;
      WHERE GENDER = 'M';
   RUN;

*or;

DATA MALE_GYM;
   SET GYM(WHERE = (GENDER = 'M'));
RUN;

***c;
DATA OLDER_F;
   SET GYM;
   WHERE GENDER = 'F' AND AGE GE 10; ***IF statement OK;
RUN;

*or;

DATA OLDER_F;
   SET GYM(WHERE=(GENDER = 'F' AND AGE GE 10));
RUN;

***Problem 14-3;
DATA YEAR1996;
   INPUT ID HEIGHT WEIGHT;
DATALINES;
2 68 155
1 63 102
4 61 111
;
DATA YEAR1997;
   INPUT ID HEIGHT WEIGHT;
DATALINES;
7 72 202
5 78 220
3 66 105
;
DATA BOTH;
   SET YEAR1996 YEAR1997;
RUN;

***Problem 14-5;
DATA MONEY;
   INPUT ID INCOME : $1. L_NAME : $10.;
DATALINES;
3 A Klein
7 B Cesar
8 A Solanchick
1 B Warlock
5 A Cassidy
2 B Volick
;
PROC SORT DATA=GYM;
   BY ID;
RUN;
PROC SORT DATA=MONEY;
   BY ID;
RUN;
DATA GYMMONEY;
   MERGE GYM(IN=IN_GYM) MONEY;
   BY ID;
   IF IN_GYM;
RUN;
PROC PRINT DATA=GYMMONEY;
   ***Note: GYMMONEY already in ID order;
   TITLE "Listing of Gym and Financial Data";
   ID ID;
   VAR L_NAME GENDER AGE;
RUN;

***Problem 14-7;
PROC SORT DATA=BOTH;
   BY ID;
RUN;
DATA FREDDY;
   MERGE GYMMONEY(IN=ONE)
         BOTH(IN=TWO);
   BY ID;
   IF ONE AND TWO;
RUN;
PROC PRINT DATA=FREDDY NOOBS;
   TITLE "Listing of Data Set FREDDY";
RUN;

***Problem 14-9;
DATA FINANCE;
   LENGTH INCOME GENDER PLAN $ 1;
   INPUT INCOME GENDER PLAN @@;
DATALINES;
A M W A F X B M Y B F Z
;
PROC SORT DATA=FINANCE;
   BY GENDER INCOME;
RUN;
PROC SORT DATA=GYMMONEY;
   BY GENDER INCOME;
RUN;
DATA FINAL;
   MERGE FINANCE GYMMONEY;
   BY GENDER INCOME;
RUN;
PROC PRINT DATA=FINAL NOOBS;
   TITLE "Listing of Data Set FINAL";
RUN;

***Problem 14-11;
DATA NEW;
   INFILE DATALINES MISSOVER;
   ***MISSOVER needed because of short lines;
   INPUT ID GENDER : $1. AGE VAULT P_BAR;
DATALINES;
3 . . .  6.7
5 . 15 8.1 7.2
7 F
;
PROC SORT DATA=NEW;
   BY ID;
RUN;
PROC SORT DATA=GYM;
   BY ID;
RUN;
DATA GYM_2;
   UPDATE GYM NEW;
   BY ID;
RUN;
PROC PRINT DATA=GYM_2 NOOBS;
   TITLE "Listing of Data Set GYM_2";
RUN;

*An alternative way to create the update (NEW) data set is;

DATA NEW;
   LENGTH GENDER $ 1;
   INPUT ID = GENDER = $ AGE = VAULT = P_BAR = ;
DATALINES;
ID = 3 P_BAR = 6.7
ID = 5 AGE = 15 VAULT = 8.1 P_BAR = 7.2
ID = 7 GENDER = F
;

*   This is called NAMED input.  You can learn more from the
OnLine Doc™ or other SAS manuals;

***CHAPTER 15;

***Problem 15-1;
DATA PROB15_1;
   INPUT (HT1-HT5)(2.) (WT1-WT5)(3.);
   ARRAY HT[*] HT1-HT5;
   ARRAY WT[*] WT1-WT5;
   ARRAY DENS[*] DENS1-DENS5;
   DO I = 1 TO 5;
      DENS[I] = WT[I] / HT[I]**2;
   END;
   DROP I;
DATALINES;
6862727074150090208230240
64  68  70140   150   170
;

***Problem 15-3;
DATA OLDMISS;
   INPUT A B C X1-X3 Y1-Y3;
   ARRAY NINE[*] A B C X1-X3;
   ARRAY SEVEN[*] Y1-Y3;
   DO I = 1 TO 6;
      IF NINE[I] = 999 THEN NINE[I] = .;
   END;
   DO I = 1 TO 3;
      IF SEVEN[I] = 777 THEN SEVEN[I] = .;
   END;
   DROP I;
DATALINES;
1 2 3 4 5 6 7 8 9
999 4 999 999 5 999 777 7 7
;

*alternative;

DATA OLDMISS;
INPUT A B C X1-X3 Y1-Y3;
ARRAY NINE[*] A B C X1-X3;
   ARRAY SEVEN[*] Y1-Y3;
   DO I = 1 TO 6;
      IF NINE[I] = 999 THEN NINE[I] = .;
      IF I LE 3 AND SEVEN[I] = 777 THEN SEVEN[I] = .;
   END;
   DROP I;
DATALINES;
1 2 3 4 5 6 7 8 9
999 4 999 999 5 999 777 7 7
;

***Problem 15-5;
DATA SPEED;
   INPUT X1-X5 Y1-Y3;
DATALINES;
1 2 3 4 5 6 7 8
11 22 33 44 55 66 77 88
;
DATA SPEED2;
   SET SPEED;
   ARRAY X[5] X1-X5;
   ARRAY Y[3] Y1-Y3;
   ARRAY LX[5] LX1-LX5;
   ARRAY SY[3] SY1-SY3;
   DO I =  1 TO 5;
      LX[I] = LOG(X[I]);
      IF I LE 3 THEN SY[I] = SQRT(Y[I]);
   END;
   DROP I;
RUN;

***Problem 15-7;
DATA PROB15_4;
   LENGTH C1-C5 $ 2;
   INPUT C1-C5 $ X1-X5 Y1-Y5;
   ARRAY C[5] $ C1-C5;
   ARRAY X[5] X1-X5;
   ARRAY Y[5] Y1-Y5;
   DO I = 1 TO 5;
      IF C[I] = 'NA' THEN C[I] = ' ';
      IF X[I] = 999 OR Y[I] = 999 THEN DO;
         X[I] = .; 
         Y[I] = .;
      END;
   END;
   DROP I;
DATALINES;
AA BB CC DD EE 1 2 3 4 5 6 7 8 9 10
NA XX NA YY NA 999 2 3 4 999 999 4 5 6 7
;

***CHAPTER 16;

***Problem 16-1;
DATA FROG;
   INPUT ID X1-X5 Y1-Y5;
DATALINES;
01   4   5   4   7   3   1   7   3   6   8
02   8   7   8   6   7   5   4   3   5   6
;
DATA TOAD;
   SET FROG;
   ARRAY XX[5] X1-X5;
   ARRAY YY[5] Y1-Y5;
   DO TIME = 1 TO 5;
      X = XX[TIME];
      Y = YY[TIME];
      OUTPUT;
   END;
   DROP X1-X5 Y1-Y5;
RUN;

***Problem 16-3;
DATA STATE;
   INFORMAT STATE1-STATE5 $2.;
   INPUT ID STATE1-STATE5;
DATALINES;
1   NY   NJ   PA   TX   GA
2   NJ   NY   CA   XX   XX
3   PA   XX   XX   XX   XX
;
DATA NEWSTATE;
   SET STATE;
   ARRAY XSTATE[*] $ STATE1-STATE5;
   DO I = 1 TO 5;
      IF XSTATE[I] = 'XX' THEN XSTATE[I] =  ' ';
      STATE = XSTATE[I];
      OUTPUT;
   END;
   DROP I;
RUN;
PROC FREQ DATA=NEWSTATE ORDER = FREQ;
   TITLE "Frequencies on States Visited";
   TABLES STATE;
RUN;

***Problem 16-5;
DATA NEW;
   SET BLAH;
   ARRAY JUNK[*] X1-X5 Y1-Y5 Z1-Z5;
   DO J = 1 TO DIM(JUNK);
      IF JUNK[J] = 999 THEN JUNK[J] = .;
   END;
   DROP J;
RUN;

***CHAPTER 17;

***Problem 17-1;
DATA HOSP;
   INFORMAT ID $3. GENDER $1. DOB DOS MMDDYY8.;
   INPUT ID GENDER DOB DOS LOS SBP DBP HP;
   FORMAT DOB DOS MMDDYY10.;
DATALINES;
1 M 10/21/46 3/17/97 3 130 90 68
2 F 11/1/55 3/1/97 5 120 70 72
3 M 6/6/90 1/1/97 100 102 64 88
4 F 12/21/20 2/12/97 10 180 110 86
;
DATA NEW_HOSP;
   SET HOSP;
   LOG_LOS = LOG10(LOS); ***Part A;
   AGE_LAST = INT(YRDIF(DOB,DOS,'ACTUAL')); ***Part B;
   ***Alternative (YRDIF is preferred)
   AGE_LAST = INT((DOS-DOB)/365.25);
   X = ROUND(SQRT(MEAN(OF SBP DBP)),.1); ***Part C;
RUN;

***Problem 17-3;
DATA MANY;
   INPUT X1-X5 Y1-Y5;
***a;
MEAN_X = MEAN(OF X1-X5);
MEAN_Y = MEAN(OF Y1-Y5);
***b;
MIN_X = MIN(OF X1-X5);
MIN_Y = MIN(OF Y1-Y5);
***c;
CRAZY = MAX(OF X1-X5) * MIN_Y * (N(OF X1-X5) + NMISS(OF Y1-Y5));
***d;
IF N(OF X1-X5) GE 3 AND N(OF Y1-Y5) GE 4 THEN
   MEAN_X_Y = MEAN(OF X1-X5 Y1-Y5);
DATALINES;
1 2 3 4 5   6 7 8 9 10
3 . 5 . 7   5 … 15
9 8 . . .   4 4 4 4 1
;

***Problem 17-5;
DATA UNI;
   DO I = 1 TO 1000;
      N = INT(RANUNI(0)*5+1);
      OUTPUT;
   END;
   DROP I;
RUN;
PROC FREQ DATA=UNI;
   TABLES N / NOCUM TESTP=(.2 .2 .2 .2 .2);
RUN;

***Problem 17-7;
PROC FORMAT;
   VALUE DAYFMT 1 = 'SUN' 2 = 'MON' 3 = 'TUE' 4 = 'WED' 5 = 'THU'
      6 = 'FRI' 7 = 'SAT';
RUN;
DATA DATES;
   SET HOSP; ***From 17-1;
   DAY = WEEKDAY(DOS);
   MONTH = MONTH(DOS);
   FORMAT DAY DAYFMT.;
RUN;
PROC CHART DATA=DATES;
***Or GCHART;
   VBAR DAY MONTH / DISCRETE;
RUN;

***Problem 17-9;
DATA MIXED;
   INPUT X Y A $ B $;
DATALINES;
1 2 3 4
5 6 7 8
;
DATA NUMS;
   SET MIXED;
   A_NUM = INPUT(A,8.);
   B_NUM = INPUT(B,8.);
   DROP A B; ***Don't forget this;
RUN;

***Problem 17-11;
PROC FORMAT;
   VALUE AGEGRP LOW- < 20   = '1'
      20-40   = '2' /*OK SINCE INTEGERS*/
      41-HIGH   = '3';
RUN;
DATA NEWER;
   SET NEW_HOSP; ***From 17-1;
   AGEGROUP = PUT(AGE_LAST,AGEGRP.);
RUN;

***CHAPTER 18;

***Problem 18-1;
   DATA CHAR1;
   INPUT @1  STRING1 $1.
         @2  STRING2 $5.
         @3  STRING3 $8.
         @11 (C1-C5)($1.);
DATALINES;
XABCDE12345678YNYNY
YBBBBB12V56876yn YY
ZCCKCC123-/. ,WYNYN
;

DATA ERROR;
   SET CHAR1;
   LENGTH DUMMY $ 5;
   DUMMY = C1 || C2 || C3 || C4 || C5;
   IF VERIFY(STRING1,'XYZ') NE 0   OR
      VERIFY(STRING2,'ABCDE') NE 0  OR
      VERIFY(UPCASE(DUMMY),'NY') NE 0 THEN OUTPUT;
   DROP DUMMY;
RUN;

***Problem 18-3;
DATA PROB18_3;
   SET CHAR1; ***From 18-1;
   NEW3 = TRANSLATE(COMPRESS(STRING3,' -/.,'),'ABCDEFGH','12345678');
   IF VERIFY(COMPRESS(NEW3,'ABCDEFGH')) NE 0 THEN NEW3 =  ' ';
RUN;

***Problem 18-5;
DATA PROB18_5;
   SET CHAR1; ***From 18-1;
   ARRAY C[5] $ 1 C1-C5; ***Create a character array;
   DO I = 1 TO 5;
      C[I] = UPCASE(C[I]);
      IF VERIFY(C[I],'NY ') NE 0 THEN C[I] = ' ';
   END;
   DROP I;
RUN;

***Problem 18-7;
DATA PHONE;
   INPUT CHAR_NUM $20.;
   NUMBER = INPUT(COMPRESS(CHAR_NUM,' ()-/'),10.);
DATALINES;
(908)235-4490
(800) 555 - 1 2 1 2
203/222-4444
;

***Problem 18-9;
DATA EXPER;
   INPUT ID   $ 1-5
      GROUP $ 7
      DOSE   $ 9-12;
   LENGTH SUB_ID $ 2 GRP_DOSE $ 6;
   SUB_ID = SUBSTR(ID,2,2);
   GRP_DOSE = GROUP || '-' || DOSE;
DATALINES;
1NY23 A HIGH
3NJ99 B HIGH
2NY89 A LOW
5NJ23 B LOW
;

***Problem 18-11;
DATA PROB18_11;
   SET EXPER; ***From problem 18-9;
   LENGTH ID2 $ 6;
   ID2 = ID;
   IF INPUT(SUBSTR(ID,4,1),1.) GE 5 THEN SUBSTR(ID2,6,1) = '*';
RUN;

***Problem 18-13;
DATA ONE;
   INPUT @1   GENDER     $1.
         @2   DOB   MMDDYY8.
         @10  NAME      $11.
         @21  STATUS     $1.;
   FORMAT DOB MMDDYY8.;
DATALINES;
M10/21/46CADY   A
F11/11/50CLINE   B
M11/11/52SMITH   A
F10/10/80OPPENHEIMERB
M04/04/60JOSE   A
;
DATA TWO;
   INPUT @1  GENDER     $1.
         @2  DOB   MMDDYY8.
         @10 NAME      $11.
         @21 WEIGHT      3.;
   FORMAT DOB MMDDYY8.;
DATALINES;
M10/21/46CODY   160
F11/11/50CLEIN   102
F11/11/52SMITH   101
F10/10/80OPPENHAIMER120
M02/07/60JOSA   220
;
DATA ONE_TMP;
   SET ONE;
   S_NAME = SOUNDEX(NAME);
RUN;
DATA TWO_TMP;
   SET TWO;
   S_NAME = SOUNDEX(NAME);
RUN;
PROC SORT DATA=ONE_TMP;
   BY GENDER DOB S_NAME;
RUN;
PROC SORT DATA=TWO_TMP;
   BY GENDER DOB S_NAME;
RUN;
DATA COMBINED;
   MERGE ONE_TMP(IN = INONE) TWO_TMP(IN = INTWO);
   BY GENDER DOB S_NAME;
   IF INONE AND INTWO;
RUN;

*   NOTE: There are no problems for chapters 19 and 20.;

