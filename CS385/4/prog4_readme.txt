Name: Arnold Lee
CS Account ID: temp109
    
CS 385

Program 4: Disk read/write simulation

To compile type:

g++ prog4.cpp -o prog4

To execute the shell type:

./prog4 (file name) (optional: number of disk access request)

e.g.  ./prog4 test.txt 3





1. Insturctions.

Just type the command above and the program will execute in its entirety.
No user interaction is required within the program.





2. Expected Output

A normal operation should look like this: 

test file used:

1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
17 18 19 20
21 22 23 24
25 26 27 28
29 30 31 32
33 34 35 36
37 38 39 40
41 42 43 44


Output:



*************************************************************
Name: Arnold Lee
CS Account ID: temp109

*************************************************************
*************************************************************
Discrete event simulation of Hard drive disk access

Process 1 run time:2
Process 2 run time:3
Process 3 run time:1
Process 4 run time:1
Process 5 run time:1
Process 6 run time:1
Process 7 run time:1
Process 8 run time:2
Process 9 run time:1
Process 10 run time:1
Process 11 run time:2
Process 12 run time:2
****************************************************
*             Session Summary                      *
****************************************************

FCFS algorithm                                     
total process -->12
total time in msec-->0.02
total pending request queued ---> 0
Max # of pending request at any given time -->0
*****************************************************
Process 1 run time:1
Process 2 run time:1
Process 3 run time:1
Process 4 run time:1
Process 5 run time:1
Process 6 run time:1
Process 7 run time:1
Process 8 run time:1
Process 9 run time:1
Process 10 run time:1
Process 11 run time:1
Process 12 run time:1
**************************************************
SSTF algorithm
total process -->12
total time in msec-->0.03
total pending request queued ---> 0
Max # of pending request at any given time -->0
*****************************************************
Process 1 run time:1
Process 2 run time:2
Process 3 run time:1
Process 4 run time:1
Process 5 run time:1
Process 6 run time:1
Process 7 run time:2
Process 8 run time:1
Process 9 run time:1
Process 10 run time:1
Process 11 run time:2
Process 12 run time:1
**************************************************
SCAN algorithm
total process -->12
total time in msec-->0.03
total pending request queued ---> 0
Max # of pending request at any given time -->0
*****************************************************
Process 1 run time:1
Process 2 run time:1
Process 3 run time:1
Process 4 run time:1
Process 5 run time:1
Process 6 run time:1
Process 7 run time:2
Process 8 run time:1
Process 9 run time:1
Process 10 run time:1
Process 11 run time:1
Process 12 run time:1
**************************************************
C-SCAN algorithm
total process -->12
total time in msec-->0.05
total pending request queued ---> 0
Max # of pending request at any given time -->0
*****************************************************




3. KNOWN ISSUES / DEFICIENCIES

   A.) Do not include empty files or it may cause undesirable operation.

   B.) This program contains algorithms for C-Scan , Scan , SSTF and FCFS.
       The timer may be displayed cumulatively instead of resetting to zero        everytime when an algorithm is changed/switched.

   C.) All time unit are in milliseconds.

   D.) The disk access request is input into the program in a uniform pattern with        constant timing between requests.
       
   
