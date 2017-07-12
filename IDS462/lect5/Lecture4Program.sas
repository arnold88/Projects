



**Use Import to Bring the Coil data in from Excel, or use the program you may have saved from last week.;

**Get the sas program Lecture 3 Programs.sas from blackboard and run the ENTIRE program;
**Why do you get nothing in the output window when you run the entire program?;



**You can adjust the program below to run all the charts you need;

data indep;                                                                   
set  coil (drop=resp seqnum);                                                 
run;                                                                          
                                                                              
%ObsAndVars(indep);                                                           
%varlist(indep);                                                              


%macro GraphLoop;                                                             
 %do i=1 %to 2;                                                               
   %let variable=%scan(&varlist,&i);                                          
%DissGraphMakerLogOdds(coil,10,&variable,resp);
 %end;                                                                        
%mend GraphLoop;                                                              
*%GraphLoop; 



**Initial program to transform Moshoo to make it more _________?;
data temp;
set  coil;
DifMoshoo=abs(Moshoo-6);
SqrMoshoo=(Moshoo-6)**2;
run;

%DissGraphMakerLogOdds(temp,10,DiffMoshoo,resp);
%DissGraphMakerLogOdds(temp,10,SqrMoshoo,resp);
**Run to here 1;



proc logistic data=temp;
model resp=DifMoshoo;
ods output GlobalTests=LRDif(where=(Test="Likelihood Ratio"));
title "Logistic Model for DifMoshoo";
run;
proc logistic data=temp;
model resp=SqrMoshoo;
ods output GlobalTests=LRSqr(where=(Test="Likelihood Ratio"));
title "Logistic Model for SqrMoshoo";
run;
title;



data compare (keep=transform chisq);
retain transform ChiSq;
set  LRDif (in=inDif)
     LRSqr (in=inSqr)
	 ;
if   inDif then Transform='Linear';
if   inSqr then Transform='Square';
run;


proc print data=compare noobs;
title "Comparison of LR Chi-Square for MoShoo";
run;
title;



data two;
input x y;
xsq=x*x;
xadj=(6-x)**2;
datalines;
2	16
3	9
4	4
5	1
6	0
7	1
8	4
9	9
10	16
;
run;

proc print data=two;
title "Printout of Data";
run;
title;

proc plot data=two;
plot y*xadj;
run;
quit;

proc reg data=two;
model y=xadj;
title "Results of Linear Model After Adjustment";
run;
title;

proc reg data=two;
model y= x xsq;
title "Results of Quadratic Model Without Adjustment";
run;
title;
quit;







data temp;
set  coil2;
moshoosq=moshoo*moshoo;
moshoocu=moshoo**3;
run;

proc logistic descending data=temp;
model resp=moshoo;
run;
proc logistic descending data=temp;
model resp=moshoo moshoosq;
run;
proc logistic descending data=temp;
model resp=moshoo moshoosq moshoocu;
run;



data coil2(keep=seqnum--MGODPR mrelge MFALLE MFWEKI MOPLHO 
mska--mzpart 
minkge--PMOTSC PAANHA
AWAPAR--AMOTSC resp respholdout)
;
set  coil ;
rand=ranuni(092765);
     if rand <=.7 then RespHoldout=.;
else if rand  >.7 then do;
   RespHoldout=Resp;
   Resp=.
   ;
end;
run;


data coil3;
set  coil2;
array orig[10](0, 1, 2,  3,  4,  5,   6,   7,    8,    9);
array new[10] (0,25,75,150,350,750,3000,7500,15000,30000);
retain orig1-orig10 new1-new10; 
do i=1 to dim(orig); 
 if pwapar=orig[i] then pwapar2=new[i];
 if PAANHA=orig[i] then PAANHA2=new[i];
 if PPERSA=orig[i] then PPERSA2=new[i];
end;
drop orig1--orig10 new1--new10 i; 
run;





