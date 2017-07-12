


/**Adjust Library Name  **/
*libname Lec7 "C:\Documents and Settings\jspark4\Desktop";
*libname Lec7 "D:\School\IDS462\Fall2007\Lectures\Lecture7";

libname Lec7 "H:\IDS462\lect7";

data holdout;
set  Lec7.ChaidOutput;
if   respholdout>.;
run;

proc sort data=holdout;
by descending VR_RESP;
run;

data RespAnalCHAID (keep=reccount respholdout cumcount cumresp);
set  holdout;
reccount=1;
cumcount+reccount;
cumresp+respholdout;
run;

data RespAnalCHAID;
set  RespAnalCHAID;
RespPct=cumresp/106;
CountPct=cumcount/1806;
run;


data cutpoint;
set  RespAnalCHAID;
lagCountPct=lag(CountPct);
if   CountPct ge .75 and lagCountPct lt .75 then output;
run;

proc print data=cutpoint;
run;

data holdout;
set  Lec7.NNOutput;
if   respholdout>.;
run;

proc sort data=holdout;
by descending VN_RESP;
run;

data RespAnalNN (keep=reccount respholdout cumcount cumresp);
set  holdout;
reccount=1;
cumcount+reccount;
cumresp+respholdout;
run;

data RespAnalNN;
set  RespAnalNN;
RespPct=cumresp/106;
CountPct=cumcount/1806;
run;


data cutpoint;
set  RespAnalNN;
lagCountPct=lag(CountPct);
if   CountPct ge .75 and lagCountPct lt .75 then output;
run;

proc print data=cutpoint;
run;

/*Assumes that RespAnalLR has been produced from a Logistic Regression model  */

data  compare;
merge Lec7.RespAnalLR    (keep=cumresp rename=(cumresp=LRCumResp))
           RespAnalNN    (keep=cumresp rename=(cumresp=NNCumResp))
	       RespAnalChaid (keep=cumresp rename=(cumresp=CHCumResp))
	  ;
mailed=10*_n_;

totalcost = mailed+10000;

LRrevenue = LRCumResp * 500;

NNrevenue = NNCumResp * 500;

CHrevenue = CHCumResp * 500;

LR_Profit =  LRrevenue - totalcost;
NN_Profit =  NNrevenue - totalcost;
CH_Profit =  CHrevenue - totalcost;

LR_ROI = LR_Profit / totalcost;
NN_ROI = NN_Profit / totalcost;
CH_ROI = CH_Profit / totalcost;

proc sql; *inline SQL statement**;

create table LRPmax as select * from compare having LR_Profit = max(LR_Profit);
create table NNPmax as select * from compare having NN_Profit = max(NN_Profit);
create table CHPmax as select * from compare having CH_Profit = max(CH_Profit);

create table LRRmax as select * from compare having LR_ROI = max(LR_ROI);
create table NNRmax as select * from compare having NN_ROI = max(NN_ROI);
create table CHRmax as select * from compare having CH_ROI = max(CH_ROI);


quit;

*Profit and ROI calulations here;;
run;

**Stop Here!!;
;


%macro ObsAndVars(dsn);
%global nobs nvars;
%let dsid=%sysfunc(open(&dsn));   
%let nobs=%sysfunc(attrn(&dsid,nobs));     
%let nvars=%sysfunc(attrn(&dsid,nvars));   
%let rc=%sysfunc(close(&dsid));            
%put nobs=&nobs nvars=&nvars;   
%mend ObsAndVars;


%Macro DecileReport(dsn,Dep,pred);
%ObsAndVars(&dsn);
proc sort data=&dsn;
by descending &pred;
run;

data gains;
set  &dsn;
if 0<_n_<=round(1*(&nobs/10)) then decile=1;
if round(1*(&nobs/10))<_n_<=round(2*(&nobs/10)) then decile=2;
if round(2*(&nobs/10))<_n_<=round(3*(&nobs/10)) then decile=3;
if round(3*(&nobs/10))<_n_<=round(4*(&nobs/10)) then decile=4;
if round(4*(&nobs/10))<_n_<=round(5*(&nobs/10)) then decile=5;
if round(5*(&nobs/10))<_n_<=round(6*(&nobs/10)) then decile=6;
if round(6*(&nobs/10))<_n_<=round(7*(&nobs/10)) then decile=7;
if round(7*(&nobs/10))<_n_<=round(8*(&nobs/10)) then decile=8;
if round(8*(&nobs/10))<_n_<=round(9*(&nobs/10)) then decile=9;
if round(9*(&nobs/10))<_n_<=round(10*(&nobs/10)) then decile=10;
count=1;
run;

proc summary data=gains nway;
class decile;
var &dep count;
output out=DecileReport sum(&dep)=Resp 
                        sum(count)=count
                        ;
run;

Data DecileReport;
set  DecileReport;
drop _type_ _freq_;
run;

proc print data=DecileReport;
run;

%Mend DecileReport;
