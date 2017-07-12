
libname desk "H:\IDS462\lect10";
libname ids "H:\IDS462\lect10";

*libname desk "C:\Documents and Settings\john\Desktop";
*Build Index, as necessary;

data desk.q091901495 (index=(permno date));
set  desk.q091901495;
run;
proc contents data=desk.q091901495;
run;


*Go to Macro Below First;

%Macro MomentumEval;
proc sort nodupkey data=Past;*Dedupe (remove duplicates) records for the same month and permno;
by permno date;
run;

proc freq noprint data=Past;*Determine number of months on record for each security;
tables permno/out=NumOfMonths;
run;

data Full6 (keep=PermNo);*retain only securities with 6 months of history;
set  NumOfMonths;
if   count=6;
run;

data  ReadyToCalc;*Get return rates for securities with 6 months of history;
merge Past Full6 (in=inFull6);
by    PermNo;
if    inFull6;
LogRet=log(1+Ret);*Get logarithm in order to sum instead of having to use product for geometric mean;
run;

proc summary data=ReadyToCalc;*Sum to create sum of log(a)+lob(b)...;
by permno;
var LogRet;
output out=LogRet6Mo sum=;
run;

data ActualRet6Mo (drop=logret);
set  LogRet6Mo (drop=_type_ _freq_);
if LogRet>.;
Ret=exp(LogRet)-1;*exp the log and subtrac 1 to get geometric average;
run;

proc rank data=ActualRet6Mo out=RankedRet6Mo groups=10;*Form deciles based on past returns;
var Ret;
ranks RetRanks;
run;

proc sort nodupkey data=Future;
by permno date;
run;

data  ReadyToCalc;
set   Future;
by    PermNo;
LogRet=log(1+Ret);*Prepare for geometric Long Return (includes dividends);
LogRetx=log(1+Retx);*Prepare for geometric Short Return (not include dividends);
run;

proc summary data=ReadyToCalc;*Calculate both types of returns for all securities in the 'Future';
by permno;
var LogRet LogRetx;
output out=LogRet6Mo sum(LogRet)=LongRet sum(LogRetx)=ShortRet;
run;

data FutureRet6Mo;
set  LogRet6Mo (drop=_type_ _freq_);
LongRet= exp(LongRet)-1;
ShortRet=exp(ShortRet)-1;*Complete calculation by taking exp;
run;


data  Eval;*Match to file containing past performance deciles;
merge RankedRet6Mo (in=inPast)
      FutureRet6Mo (in=inFuture)
	  ;
by    permno;
if    inPast;
run;

proc summary data=Eval nway;*Calculate average future returns by decile.  ASSUMES EQUAL WEIGHTED PORTFOLIO.  See slides;
class RetRanks;
var LongRet ShortRet;
output out=EvalReturn mean(LongRet)=AvgLongRet
                      mean(ShortRet)=AvgShortRet
					  ;
run;


Data EvalFinal;*Retain only averages in top ranked and bottom ranked deciles;
set  EvalReturn;
if   RetRanks in (0,9);
run;

data LongRet  (keep=AvgLongRet retranks  where=(retranks=9))
     ShortRet (keep=AvgShortRet retranks where=(retranks=0))
	 ;
set  EvalFinal;*Get results onto a single record;
run;

data  EvalSingleRecord;
merge LongRet ShortRet;
AvgShortRet=-AvgShortRet;
MonthlyAvgShortRet=(AvgShortRet)/6;*Divide by 6 to get average monthly return to compare to buy and hold;
MonthlyAvgLongRet =(AvgLongRet)/6;
MonthlyTotalRet=MonthlyAvgShortRet+MonthlyAvgLongRet;
drop RetRanks;
run;
%Mend MomentumEval;


*The macro DateSelect selects the proper monthly records for processing;
*It also invokes the macro MomentumEval (compiled above) to do the calculations;
*It then loops through and picks the next appropriate set of months;

%Macro DateSelect;*Set Up Macro;
options mprint;   *Turn on screen prints;

proc datasets lib=desk nolist;*Delete results file from previous run, if exist;
delete EvalSummary;
run;

proc freq data=desk.q091901495 (keep=date);*Get comprehensive set of unique dates from base data;
tables date/out=DateList;
run;

data datelist;*place values of dates in a single file;
set  datelist;
keep date;
run;

%do i=1 %to 120;*Begin Looping;

 %let j=%eval (&i+5);*get record that is 5 down from ith record;
 %let k=%eval (&j+6);*get record 12 down;
 %let l=%eval (&i+6);*get record that is 6 down;

data newdates;
set  datelist;
if _n_ in (&i,&j,&l,&k);*pick those records from the date list file;
run;

data newdates;*Put the dates from those records into macro variables;
set  newdates;
if   _n_=1 then call symput ('PastBegDate',date);
if   _n_=2 then call symput ('PastEndDate',date);
if   _n_=3 then call symput ('FutureBegDate',date);
if   _n_=4 then call symput ('FutureEndDate',date);
run;
%put &i &j &l &k &pastbegdate &pastenddate &FutureBegDate &FutureEndDate;
*write macro variables to log to track process;

data Past   (where=(&PastBegDate<=date<=&PastEndDate   and shrcd in (10,11)))
     Future (where=(&PastEndDate< date<=&FutureEndDate and shrcd in (10,11)));
set  desk.q091901495 (keep=permno date shrcd RET RETx);
run;
*Select records from base data with proper dates using indexes to save time;

%MomentumEval;*Evaluate performance of stocks with highest and lowest momentum;
data EvalSingleRecord;*Store results of performance of 0 and 9 ranked portfolio in a single record;
format date YYMMDDN8. PastBegDate PastEndDate FutureBegDate FutureEndDate monyy7.;
set  EvalSingleRecord;
PastBegDate=&PastBegDate;
PastEndDate=&PastEndDate;
FutureBegDate=&FutureBegDate;
FutureEndDate=&FutureEndDate;
date=FutureBegDate;
run;
proc append data=EvalSingleRecord base=desk.EvalSummary;*Append these results to file containing previous results;
run;
%end;*loop back to begin with next month;
options nomprint;
%Mend DateSelect;
%DateSelect;




data EvalSP500;*Get file to evaluate performance of SP500 for buy and hold comparison;
set  desk.q091901495 (keep=date permno vwretd);*vwretd is return from SP500;
where PERMNO=10001;
run;

proc sort nodupkey data=EvalSP500;
by date;
run;

proc freq data=EvalSP500;
tables date;
run;


data  desk.Compare (drop=permno);*Match to results of momentum strategy by date to compare;
merge desk.evalsummary (in=ineval)
	  EvalSP500 (in=insp)
	  ;
by    date;
if    insp and ineval;
run;

proc means data=desk.compare n mean std p50 maxdec=4;
var MonthlyTotalRet vwretd MonthlyAvgLongRet MonthlyAvgShortRet;
run;

