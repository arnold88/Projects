* Lecture 9 program;


libname ids462 "H:\IDS462\lect9";

%let dsn=ids462.q071421574;   /*  specify the dataset to use      */
%let var=FSPCOM;              /*  specify the variable to model   */
%let sym=SP500;              /*  specify name of underlying security*/

proc sort data=&dsn (keep=date &var);
by date;
run;

data &dsn;
set  &dsn;
if   &var>.;
run;

%macro ObsAndVars(dsn);
%global nobs nvars;
%let dsid=%sysfunc(open(&dsn));   
%let nobs=%sysfunc(attrn(&dsid,nobs));     
%let nvars=%sysfunc(attrn(&dsid,nvars));   
%let rc=%sysfunc(close(&dsid));            
%put nobs=&nobs nvars=&nvars;   
%mend ObsAndVars;

%obsAndVars(&dsn);

%let fitobs=246;  /*  specify number of obs to use to fit model   */
%let lastobs=&nobs; /*  specify number of obs in the data set       */
%let noest=;       /*specify if model is to not be re-estimated when computing outofsample forecasts*/
					/*use noest to abstain from re-estimating.  Leave blank to re-estimate  */
%let trailnum=240;   /*specify the number of trailing observations used to calculate the residuals
                       or evaluate the model-- the size of the out of sample forecast sample*/

*options symbolgen;
*ods trace on/listing;

proc arima data=&dsn (obs=&fitobs);
identify var=&var(1) scan stationarity=(adf=4); /* the one in here is number of differecing*/  
estimate q=1 outest=est;
forecast out=firstout lead=1 nooutall noprint id=date interval=month;
run;
quit;
*ods trace off;

data _null_;
  set est(where=(_type_='EST'));
  call symput('mu',mu);
  call symput('theta',MA1_1);
run;


options nomprint nosymbolgen nonotes;
%macro onestep;
%global begin end; 
proc datasets;   /*  use this step to delete results of previous */
delete final;  /*  executions of the macro                     */
run;

**Redirect log message to the file to prevent log buffer overrun***;
/*   
proc printto log="C:\StockResearch\HistoricalPricing\Programs\WeekdayWarnings.log";
run;
*/

%do i = %eval(&fitobs) %to &lastobs; /* create macro variable to use in selecting obs */
   proc arima data=&dsn(obs=&i);       /* use OBS= option to subset data  */
         i var=&var(1) noprint;         
         e q=1 noprint mu=&mu ma=&theta &noest; 
         f out=out lead=1 nooutall noprint id=date interval=month;  
   run;
   quit;

   data last;
   set  &dsn;
   if   _n_=%eval(&i+1);
   run;

data out2;
	merge out last;
	residual=&var-forecast;
	run;

   /*  use PROC APPEND to append the results from the iterations  */
  proc append base=final data=out2;
  run;
%end;

/*proc printto;*/

options mprint symbolgen notes;
data _null_;
set  &dsn;
if   _n_=%eval(&fitobs+1);
call symput('begin',put(date,mmddyy10.));
run;

data last;
set  &dsn;
if   _n_=&lastobs;
call symput('end',put(date,mmddyy10.));
run;
%put &begin &end;
%mend onestep;
%onestep;


data final2 (drop=STD L95 U95 RESIDUAL SqrdResid);
set  final;
PricePrev=lag(FSPCOM);
year=Year(date);
if forecast>PricePrev then do;
	Invest=PricePrev;
	earn=FSPCOM-PricePrev;
end;
else if forecast<PricePrev then do;
	Invest=PricePrev/2;
	Earn=PricePrev-FSPCOM;
end;
PctReturn=Earn/Invest;
GeometricReturn=1+PctReturn;
LogGeometricReturn=Log(GeometricReturn);
run;


%Macro YearLoop;
options mprint;

proc datasets;          /*  use this step to delete results of previous */
delete ResultsCompare;  /*  executions of the macro                     */
run;

%do Year=1986 %to 2004;

data Y&Year;
set  Final2;
if   year=&Year;
run;

proc summary data=Y&Year;
var LogGeometricReturn;
output out=SumLogGeometricReturn sum=SumLogGeometricReturn;
run;

Data TimeSeriesReturn;
set  SumLogGeometricReturn;
TimeSeriesReturn=(exp(SumLogGeometricReturn))-1;
run;

/*proc print data=TimeSeriesReturn;
run;*/

data Beginning (rename=(FSPCOM=Beginning)) 
     Ending    (rename=(FSPCOM=Ending));
set  Y&Year (keep=FSPCOM);
if   _n_=1  then output Beginning;
if   _n_=12 then output Ending;
run;

Data  BuyAndHoldReturn;
merge Beginning
      Ending;
BuyAndHoldReturn=(Ending-Beginning)/Beginning;
run;

/*proc print data=BuyAndHoldReturn;
run;*/

data Results;
merge BuyAndHoldReturn (keep=BuyAndHoldReturn)
      TimeSeriesReturn (keep=TimeSeriesReturn)
	  ;
Year=&Year;
run;

   /*  use PROC APPEND to append the results from the iterations  */
  proc append base=ResultsCompare data=Results;
  run;

%end;
options nomprint;
%Mend YearLoop;
%YearLoop;


proc means data=ResultsCompare mean p50 std;
var BuyAndHoldReturn TimeSeriesReturn;
run;

/*
PROC EXPORT DATA= WORK.RESULTSCOMPARE 
            OUTFILE= "H:\IDS462\lect9\ResultsCompare.xls" 
            DBMS=EXCEL2000 REPLACE;
RUN;
*/
