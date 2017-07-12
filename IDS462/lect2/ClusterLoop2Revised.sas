
libname teach "H:\IDS462\lect2";


data prefactor;
set  teach.dmefzip (drop=adicode branchcd countycd countynm dmacode filetype
                         msa multzip nielcode poffname rectype stateabr statecd);
run;

proc contents data=prefactor;
run;

proc sort data=prefactor;
by zipcode;
run;

proc standard data=prefactor mean=0 std=1;
run;

*ods trace on/listing;
proc factor data=prefactor rotate=varimax nfactors=5 scree out=FactorScores;
var _numeric_;
title "Output Factor";
ods output OrthRotFactPat=FactorOutput;
run;
title;



options pageno=1;
%macro loop (c);
options mprint ;

%do s=1 %to 10;
%let rand=%eval(100*&c+&s);
proc fastclus data=FactorScores out=clus&Rand cluster=clus maxclusters=&c
converge=0 maxiter=100 replace=random random=&Rand;
ods output pseudofstat=fstat&Rand (keep=value);
var factor1--factor5;
title1 "Clusters=&c, Run &s";
run;
title1;

proc freq data=clus&Rand noprint;
tables clus/out=counts&Rand;
where clus>.;
run;
proc summary data=counts&Rand;
var count;
output out=m&Rand min=;
run;

data  Stats&Rand;
label count=' ';
merge fstat&rand
      m&rand (drop= _type_ _freq_)
	  ;
Iter=&rand;
Clusters=&c;
rename count=minimum value=PseudoF;
run;

proc append base=ClusStatHold data=Stats&Rand;
run;
%end;
options nomprint;
%Mend Loop;



%Macro OuterLoop;
proc datasets library=work;
delete ClusStatHold;
run;
%do clus=4 %to 8;
%Loop (&clus);
%end;
%Mend OuterLoop;

%OuterLoop;




proc gplot data=ClusStatHold;
plot pseudoF*minimum/haxis=axis1;
symbol value=dot color=blue pointlabel=("#clusters" color=black);
axis offset=(5,5)pct;
title "F by Min for Clusters";
run;
title;
quit;

*added lines;

%let varlist=INCMINDX PRCHHFM PRCRENT PRC55P PRC65P HHMEDAGE PRCUN18 PRC200K OOMEDHVL PRCWHTE;

proc summary data=Clus610 nway;
class clus;
var &varlist;
output out=ClusStats mean=;
run;

proc summary data=Clus610 nway;
where clus>.;
var &varlist;
output out=OverallStats mean=;
run;

proc print data=clusStats;run;
proc print data=OverallStats;run;

data  stats;
set ClusStats
      OverallStats
	 ;
run;

proc print data=stats;run;

proc means data=ClusterOut mean maxdec=0;
class clus;
var INCMINDX PRCRENT PRCUN18 PRC200K PRCWHTE;
title "Summary Statistics for 6 Clusters";
run;

proc summary data=ClusterOut nway;
class clus;
var INCMINDX PRCRENT PRCUN18 PRC200K PRCWHTE;
output out=ClusStats mean=;
run;

PROC EXPORT DATA=ClusStats
            OUTFILE= "h:\ClusStats.xls" 
            DBMS=EXCEL2000 REPLACE;
RUN; 

proc summary data=ClusterOut nway;
var INCMINDX PRCRENT PRCUN18 PRC200K PRCWHTE;
output out=OverallStats mean=;
run;

PROC EXPORT DATA=OverallStats
            OUTFILE= "h:\OverallStats.xls" 
            DBMS=EXCEL2000 REPLACE;
RUN; 





