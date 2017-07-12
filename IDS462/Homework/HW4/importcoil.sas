PROC IMPORT OUT= WORK.COIL
            DATAFILE= "H:\IDS462\Homework\HW4\Coil1.csv" 
            DBMS=CSV REPLACE;
     GETNAMES=YES;
     DATAROW=2; 
RUN;
