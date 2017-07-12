/* Arnold Lee
   IDS 462 HW #7 - Chapter 7 problems
   06/04/2009
*/


******Problem 7.2************;
DATA CHOL;
   LENGTH TREAT $ 7;
   DO TREAT = 'A','B','PLACEBO';
      DO I = 1 TO 10;
         INPUT CHOLESTEROL @;
         OUTPUT;
      END;
   END;
   DROP I;
DATALINES;
220  190  180  185  210  170  178  200  177  189
160  168  178  200  172  155  159  167  185  199
240  220  246  244  198  238  277  255  190  188
;

proc anova DATA=CHOL;
   title "Comparison of Cholesterol Treatments";
   class treat ;
   model cholesterol = treat;
   means treat / snk;
run;
quit;