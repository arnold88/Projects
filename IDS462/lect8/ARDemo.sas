

data ar;
period=_n_;
input ar;
datalines;
10.00
9.46
10.19
13.87
17.97
19.88
20.73
22.74
20.98
24.16
24.04
26.64
24.15
25.97
24.14
23.06
22.85
23.33
22.63
25.28
25.40
26.72
29.52
28.07
25.74
24.46
21.16
22.33
23.62
25.84
22.72
19.73
17.55
21.87
24.71
23.59
26.58
23.86
22.73
20.76
19.79
22.54
23.71
23.31
25.02
26.36
26.13
28.99
28.83
26.64
27.76
28.72
31.10
30.78
32.73
29.79
28.14
28.82
28.20
27.93
28.42
25.85
24.17
;
run;

proc gplot data=ar;
plot ar*period;
title "Original AR Series";
run;
quit;

data diff;
set  ar;
lagar=lag(ar);
diff=ar-lagar;
run;

proc gplot data=diff;
plot diff*period;
title "Differenced AR Series";
run;
quit;

proc corr data=diff;
var ar lagar;
run;

proc arima data=diff;
identify var=ar scan stationarity=(adf=4);
title "Original Series";
run;
title;
quit;
/*Stop Here For First Part*/


proc arima data=diff;
identify var=ar(1) scan stationarity=(adf=4);
*ar(1) above indicates to evaluate the series named ar after taking first difference;
title "Differenced Series";
run;
title;
quit;


proc arima data=diff;
identify var=ar(1) scan stationarity=(adf=4);
estimate p=1;
title "Differenced Series";
run;
quit;
title;