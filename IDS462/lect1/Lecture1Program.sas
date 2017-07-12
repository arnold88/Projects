
libname storage "H:\IDS462\lect1";
*	Note: adjust this as necessary;

proc contents data=storage.dmefzip;
title "Contents of Zipcode Demographic File";
run;
title;

proc means data=storage.dmefzip;
title "Summary Statistics for Zipcode File";
run;
title;

proc means data=storage.dmefzip n nmiss maxdec=0;
title "Missing Values Report for Zipcode File";
run;
title;


*Drop variables that are not quantitative, even though some use numbers;
data prefactor;
set  storage.dmefzip (drop=adicode branchcd countycd countynm dmacode filetype     
msa multzip nielcode poffname rectype stateabr statecd);
run;


proc format;
value showmiss
.='Missing'
other='NonMissing';
run;
options ls=120 ps=40;
proc freq data=PreFactor;
tables INCMINDX*PERPERHH*MEDSCHYR*ISPSA*HHMEDAGE*CEMI*POPULAT/list missing missprint;
format _numeric_ showmiss.;
run;
options ls=78 ps=60;


proc means data=prefactor n nmiss maxdec=0;
title "Missing Values Report for Zipcode File AFTER Dropping Non-Quant Vars";
title2 "BEFORE Mean Replacement";
run;
title;
title2;

proc standard data=prefactor replace out=prefactor;
run;

proc means data=prefactor n nmiss maxdec=0;
title "Missing Values Report for Zipcode File After Mean Replacement";
run;
title;

proc standard data=prefactor out=storage.standard mean=0 std=1;
var _numeric_;
run;

proc means data=storage.standard nmiss mean std maxdec=0;
title "Report for Zipcode File After Standardization";
run;
title;

proc contents data=storage.standard;
run;



ods trace on/listing;
proc factor data=storage.standard rotate=varimax scree;
ods output OrthRotFactPat=Rotated;
run;
ods trace off;

