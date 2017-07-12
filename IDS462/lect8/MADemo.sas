

data ma;
period=_n_;
input ma;
datalines;
10
9.223443242
9.563923818
9.859744667
10.11629452
9.692399032
9.614820573
9.716772467
9.986317524
10.18832227
10.07691549
9.950958962
9.931889268
9.648428975
9.78488741
9.943177712
9.512229842
10.17320507
9.610879332
10.00983907
10.19340202
9.965164656
9.446009858
9.826735425
9.932537594
10.0156332
10.09760033
10.09678184
10.05841513
9.258890963
10.13207559
9.678321682
9.36115996
9.515892141
10.14063896
9.779104964
10.15377152
9.754045241
10.04223594
9.363058181
10.15831622
9.387554457
9.736242882
10.20526936
9.514262896
10.13982251
9.760751182
9.901286674
10.10035127
10.11375892
9.790245288
9.562892936
9.735452493
9.442859673
9.888771375
10.18760141
9.997337109
9.411667312
9.548599664
9.361219784
10.10342297
9.280873981
10.02728916
;
run;

/*Clear Graphic Output Window*/
proc greplay igout=work.gseg nofs;
delete _all_;
run; 
quit;

proc gplot data=ma;
plot ma*period;
title "Original MA Series";
run;
quit;


proc arima data=ma;
identify var=ma scan stationarity=(adf=3);
title "MA Original Series";
run;
title;
quit;
/*First Block*/

/*Skip This
data new;
set  ma;
ma2=ma-10;
run;

proc arima data=new;
identify var=ma2 scan stationarity=(adf=4);
title "MA Of Centered Series";
run;
title;
quit;
*/

proc arima data=ma;
identify var=ma scan stationarity=(adf=3);
title "MA Original Series";
run;
title;
quit;

proc arima data=ma;
identify var=ma scan stationarity=(adf=3);
estimate q=1;
title "Esimation for MA(1) Series";
run;
quit;
title;