/* Arnold Lee
   IDS 462 Lecture #5 models
   06/01/2009
*/


****FOR HW4 USE*****;
****RUN LECTURE 5 MACRO FIRST!!!****;

***AND THEN THIS MARCRO HERE!******;

%macro test (dsn,si,sq,cu,inv,sqrat,elog);




data &dsn;
set  &dsn;
&sq=&si**2;
&cu=&si**3;
&inv = 1/&si;
&sqrat = sqrt(&si);

if &si <= 0 the &si = .0001;

&elog = log(&si);

run;


****LINEAR****;
proc logistic data=&dsn;
model resp=&si;
run;

*****QUADRATIC****;
proc logistic data=&dsn;
model resp=&si &sq;
run;

*****CUBIC****;
proc logistic data=&dsn;
model resp=&si &sq &cu;
run;

*****INVERSE*****;
proc logistic data=&dsn;
model resp=&inv;
run;

*****SQUARE ROOT***;
proc logistic data=&dsn;
model resp=&sqrat;
run;

*****LOG BASE e****;
proc logistic data=&dsn;
model resp=&elog;
run;




%mend test;

***MACRO ENDS***;


****IMPORT FILE****;

PROC IMPORT OUT= WORK.COIL
            DATAFILE= "e:\IDS462\Homework\HW4\Coil1.csv" 
            DBMS=CSV REPLACE;
     GETNAMES=YES;
     DATAROW=2; 
RUN;




****CLEAN SOME VALUES - ASSIGN RESPHOLDOUT RANDOMLY****;

data coil2 (drop= MSKD MHKOOP MZFOND MZPART MKOOPK PWABED PWALAN
                 PBESAU PMOTSC AWABED AWALAN ABESAU);
set  coil (keep=seqnum--MGODPR mrelge MFALLE MFWEKI MOPLHO 
mska--mzpart 
minkge--PMOTSC PAANHA
AWAPAR--AMOTSC resp)
;
rand=ranuni(092765);
     if rand <=.7 then RespHoldout=.;
else if rand  >.7 then do;
   RespHoldout=Resp;
   Resp=.
   ;
end;
run;

proc contents data=coil2;
run;


/*transform of L4 variables from 0-9 scale to 0-30000 scale (see dictionary)*/
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

****MAKE TABLES***;

proc freq data=coil3;
tables 	pwapar*pwapar2
		PAANHA*PAANHA2
		PPERSA*PPERSA2
		/list;
run;

****OVERWRITE COIL3 DATA WITH ONLY THE TRANSFORMED L4 VARS.****;

data coil3;
set  coil3;
drop pwapar paanha ppersa;
run;


/* transform of L3 variables from 0-10 into 0 -100% (see dictionary) */
data coil4;
set  coil3;
array orig[10](0,  1, 2, 3, 4, 5, 6, 7, 8,  9);
array new[10] (0,5.5,17,30,43,56,69,82,94,100);
retain orig1-orig10 new1-new10; 
do i=1 to dim(orig); 
if MGODRK =orig[i] then MGODRK2 =new[i];
if MGODPR =orig[i] then MGODPR2 =new[i];
if MRELGE =orig[i] then MRELGE2 =new[i];
if MFALLE =orig[i] then MFALLE2 =new[i];
if MFWEKI =orig[i] then MFWEKI2 =new[i];
if MOPLHO =orig[i] then MOPLHO2 =new[i];
if MSKA =orig[i] then MSKA2 =new[i];
if MSKB1 =orig[i] then MSKB12 =new[i];
if MSKB2 =orig[i] then MSKB22 =new[i];
if MSKC =orig[i] then MSKC2 =new[i];
if MHHUUR =orig[i] then MHHUUR2 =new[i];
if MAUT1 =orig[i] then MAUT12 =new[i];
if MAUT2 =orig[i] then MAUT22 =new[i];
if MAUT0 =orig[i] then MAUT02 =new[i];
if MINKGE =orig[i] then MINKGE2 =new[i];
end;
drop orig1--orig10 new1--new10 i; 
run;

******MAKE A NEW TABLE*****;

proc freq data=coil4;
tables
MGODRK*MGODRK2
MGODPR*MGODPR2
MRELGE*MRELGE2
MFALLE*MFALLE2
MFWEKI*MFWEKI2
MOPLHO*MOPLHO2
MSKA*MSKA2
MSKB1*MSKB12
MSKB2*MSKB22
MSKC*MSKC2
MHHUUR*MHHUUR2
MAUT1*MAUT12
MAUT2*MAUT22
MAUT0*MAUT02
MINKGE*MINKGE2
/list;
run;

****MAKE A NEW DATA SET COIL 5 THAT CONTAINS ONLY TRANSFORMED L3 VARS ****;

data coil5;
set  coil4;
drop
MGODRK
MGODPR
MRELGE
MFALLE
MFWEKI
MOPLHO
MSKA
MSKB1
MSKB2
MSKC
MHHUUR
MAUT1
MAUT2
MAUT0
MINKGE
;


run;

%CatToBinWithDrop(coil5,seqnum,mostyp);
%CatToBinWithDrop(coil5,seqnum,MOSHOO);

proc contents data=coil5 varnum;
run;




****ADD ADDITONAL TRANSFORM HERE IF NEEDED******;


*********************************;
********MODEL TEST AREA**********;
*********************************;

*****ONLY USE TRANSFORMED VARAIBLES!!***;

****L3****;

%test(work.coil5,MGEMLE,MGEMLEsq,MGEMLEcu,MGEMLEinv,MGEMLEsqrt,MGEMLElog); 

%test(work.coil5,MGODPR2,MGODPR2sq,MGODPR2cu,MGODPR2inv,MGODPR2sqrt,MGODPR2log);

%test(work.coil5,MRELGE2,MRELGE2sq,MRELGE2cu,MRELGE2inv,MRELGE2sqrt,MRELGE2log);

%test(work.coil5,MFALLE2,MFALLE2sq,MFALLE2cu,MFALLE2inv,MFALLE2sqrt,MFALLE2log);

%test(work.coil5,MFWEKI2,MFWEKI2sq,MFWEKI2cu,MFWEKI2inv,MFWEKI2sqrt,MFWEKI2log);

%test(work.coil5,MOPLHO2,MOPLHO2sq,MOPLHO2cu,MOPLHO2inv,MOPLHO2sqrt,MOPLHO2log);

%test(work.coil5,MSKA2,MSKA2sq,MSKA2cu,MSKA2inv,MSKA2sqrt,MSKA2log);

%test(work.coil5,MSKB12,MSKB12sq,MSKB12cu,MSKB12inv,MSKB12sqrt,MSKB12log);

%test(work.coil5,MSKB22,MSKB22sq,MSKB22cu,MSKB22inv,MSKB22sqrt,MSKB22log);

%test(work.coil5,MSKC2,MSKC2sq,MSKC2cu,MSKC2inv,MSKC2sqrt,MSKC2log);

%test(work.coil5,MHHUUR2,MHHUUR2sq,MHHUUR2cu,MHHUUR2inv,MHHUUR2sqrt,MHHUUR2log);

%test(work.coil5,MAUT22,MAUT22sq,MAUT22cu,MAUT22inv,MAUT22sqrt,MAUT22log);

%test(work.coil5,MAUT12,MAUT12sq,MAUT12cu,MAUT12inv,MAUT12sqrt,MAUT12log);

%test(work.coil5,MAUT02,MAUT02sq,MAUT02cu,MAUT02inv,MAUT02sqrt,MAUT02log);

%test(work.coil5,MINKGE2,MINKGE2sq,MINKGE2cu,MINKGE2inv,MINKGE2sqrt,MINKGE2log);

****L4***;

%test(work.coil5,PWAPAR2,pwapar2sq,pwapar2cu,pwapar2inv,pwapar2sqrt,pwapar2log);

%test(work.coil5,PAANHA2,PAANHA2sq,PAANHA2cu,PAANHA2inv,PAANHA2sqrt,PAANHA2log);

%test(work.coil5,PPERSA2,PPERSA2sq,PPERSA2cu,PPERSA2inv,PPERSA2sqrt,PPERSA2log);

****NO TRANSFORM NEEDED***;

%test(work.coil5,AWAPAR,AWAPARsq,AWAPARcu,AWAPARinv,AWAPARsqrt,AWAPARlog);

%test(work.coil5,APERSA,APERSAsq,APERSAcu,APERSAinv,APERSAsqrt,APERSAlog);

%test(work.coil5,AMOTSC,AMOTSCsq,AMOTSCcu,AMOTSCinv,AMOTSCsqrt,AMOTSClog);



********************************;
********TEST AREA ENDS**********;
********************************;

***********NEW MODELING*********;

proc logistic data=coil5 desc;
model resp=
AWAPARlog
APERSA 
APERSAsq
AMOTSCsqrt
MAANTH
MGEMOM
MGEMLEinv
MGODRK2
MGODPR2log
MRELGE2log
MFALLE2log 
/*  */
MFWEKI2inv
MOPLHO2log
MSKA2log
MSKB12log
MSKB22log
MSKC2inv
MHHUUR2log
MAUT12log
/**/
MAUT22inv
MAUT02log
MINKGE2 
MINKGE2sq
/* */
PWAPAR2
PWAPAR2sq
PPERSA2
PAANHA2
PAANHA2sq
PAANHA2cu

MOSHOO_1 
MOSHOO_2 
MOSHOO_3 
MOSHOO_4 
MOSHOO_5 
MOSHOO_6 
MOSHOO_7 
MOSHOO_8 
MOSHOO_9 
MOSHOO_10
mostyp_1 
mostyp_2 
mostyp_3 
mostyp_4 
mostyp_5
mostyp_6 
mostyp_7 
mostyp_8 
mostyp_9 
mostyp_10 
mostyp_11 
mostyp_12 
mostyp_13 
mostyp_15 
mostyp_16 
mostyp_17 
mostyp_18 
mostyp_19 
mostyp_20 
mostyp_21 
mostyp_22 
mostyp_23 
mostyp_24 
mostyp_25 
mostyp_26 
mostyp_27 
mostyp_28 
mostyp_29 
mostyp_30 
mostyp_31 
mostyp_32 
mostyp_33 
mostyp_34 
mostyp_35 
mostyp_36 
mostyp_37 
mostyp_38 
mostyp_39 
mostyp_40 
mostyp_41

/selection=stepwise;
output out=scored p=pred;
run;


****POST PROCESSING BEGINS*****;


data holdout;
set  scored;
if   respholdout>.;
run;

proc sort data=holdout;
by descending pred;
run;

data RespAnal (keep=reccount respholdout cumcount cumresp);
set  holdout;
reccount=1;
cumcount+reccount;
cumresp+respholdout;
run;

data RespAnal;
set  RespAnal;
RespPct=cumresp/106;
CountPct=cumcount/1806;
run;


data cutpoint;
set  RespAnal;
lagCountPct=lag(CountPct);
if   CountPct ge .75 and lagCountPct lt .75 then output;
run;

proc print data=cutpoint;
run;


/* Now right click on dataset RespAnal and select Copy to Clipboard*/
/* Create gains chart in Excel.  MAKE SURE YOU UNDERSTAND!! */

PROC EXPORT DATA= WORK.RESPANAL 
            OUTFILE= "E:\IDS462\Homework\HW4\respanal.xls" 
            DBMS=EXCEL5 REPLACE;
RUN;

