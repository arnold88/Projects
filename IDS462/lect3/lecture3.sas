proc contents data=coil;
run;

proc freq data=coil;
run;

%FreqReport(coil);

%DissGraphMakerLogOdds(coil,10,pwapar,resp);

data indep;                                                                   
set  coil (drop=resp seqnum);                                                 
run;                                                                          
                                                                              
%ObsAndVars(indep);                                                           
%varlist(indep);                                                              


%macro GraphLoop;                                                             
 %do i=1 %to &nvars;                                                               
   %let variable=%scan(&varlist,&i);                                          
%DissGraphMakerLogOdds(coil,10,&variable,resp);
 %end;                                                                        
%mend GraphLoop;                                                              
%GraphLoop; 

data temp;
set  coil;
DifMoshoo=abs(Moshoo-6);
SqrMoshoo=(Moshoo-6)**2;
run;


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


