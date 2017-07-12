Name: Arnold Lee
CS Account ID: temp109
    


IPC DEMO DOCUMENTATION

To compile type:

g++ prog2.cpp -Wno-deprecated -o prog2

To execute the shell type:

./prog2


NOTE : AT CURRENT TIME THERE IS A BUG ON THE COMPLILER THAT REFUSE TO COMPILE THIS SOURCE CODE IF THERE IS
       ARGUMENTS CARRIED INTO int main. SO THEREFORE THE CODE WILL NOT ACCEPT COMMAND LINE ARGUMENTS, RATHER
       PROMPT USER TO ENTER THE VALUES WHEN EXECUTING THE PROGRAM.

1. Insturctions.

     A.) You will be prompted to enter number of buffers to be used. PRIME NUMBERS ONLY. USING OTHER NUMBER MAY RESULT IN NON-PREDICTABLE
         OPERATION!

     B.) Next choose Y or N to select the semaphore lock. More on this later.

     C.) Choose an integer number of any kind as a "key". For example, your last 4 digits of your UIN or SSN. This number should be large enough to 
         avoid a segmentation fault. Or you can use 0 if you want.

     D.) The program will now execute.  

2. Expected Output

A normal operation should look like this: 
(Chosen value: # of buffers = 7 , semaphore lock = Y,"key" = 145967)


***********************************************

creating buffers.........
shmID[0]=36602325

Shared Memory Stats for buffer #1
Key #                -->145967
size in bytes        -->128
Last attached time   -->0
Last detached time   -->0
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

shmID[1]=36635094

Shared Memory Stats for buffer #2
Key #                -->145968
size in bytes        -->128
Last attached time   -->0
Last detached time   -->0
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

shmID[2]=36667863

Shared Memory Stats for buffer #3
Key #                -->145969
size in bytes        -->128
Last attached time   -->0
Last detached time   -->0
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

shmID[3]=36700632

Shared Memory Stats for buffer #4
Key #                -->145970
size in bytes        -->128
Last attached time   -->0
Last detached time   -->0
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

shmID[4]=36733401

Shared Memory Stats for buffer #5
Key #                -->145971
size in bytes        -->128
Last attached time   -->0
Last detached time   -->0
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

shmID[5]=36766170

Shared Memory Stats for buffer #6
Key #                -->145972
size in bytes        -->128
Last attached time   -->0
Last detached time   -->0
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

shmID[6]=36798939

Shared Memory Stats for buffer #7
Key #                -->145973
size in bytes        -->128
Last attached time   -->0
Last detached time   -->0
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

Creating all buffers succesfully.

Initializing Buffer....
Creating message queue...

Message queue stats:

Key #                -->5668866
size in bytes        -->0
Last send time       -->0
Last received time   -->0
Last changed time    -->1162503685
PID of last sender   -->0
PID of last receiver -->0
# of max bytes allow -->16384
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

Buffer #1 -->123
Buffer #2 -->123
Write phase begins!
Buffer #3 -->123
( After write) Buffer #3 -->124
Buffer #4 -->123
Buffer #5 -->123
Write phase begins!
Buffer #6 -->123
( After write) Buffer #6 -->124
Buffer #7 -->123
Buffer #1 -->123
Write phase begins!
Buffer #2 -->123
( After write) Buffer #2 -->124
Buffer #3 -->124
Buffer #4 -->123
Write phase begins!
Buffer #5 -->123
( After write) Buffer #5 -->124
Buffer #6 -->124
Buffer #7 -->123
Write phase begins!
Buffer #1 -->123
( After write) Buffer #1 -->124
Buffer #2 -->124
Buffer #3 -->124
Write phase begins!
Buffer #4 -->123
( After write) Buffer #4 -->124
Buffer #5 -->124
Buffer #6 -->124
Write phase begins!
Buffer #7 -->123
( After write) Buffer #7 -->124

Child #1 finish its job.
Child #2 finish its job.
Child #3 finish its job.


Shared Memory Stats (Aftermath)  for buffer #1
Key #                -->145967
size in bytes        -->128
Last attached time   -->1161440028
Last detached time   -->1163502091
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511



Shared Memory Stats (Aftermath)  for buffer #2
Key #                -->145968
size in bytes        -->128
Last attached time   -->1161440177
Last detached time   -->1163502266
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511



Shared Memory Stats (Aftermath)  for buffer #3
Key #                -->145969
size in bytes        -->128
Last attached time   -->1161440265
Last detached time   -->1163502428
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511



Shared Memory Stats   for buffer #4
Key #                -->145970
size in bytes        -->128
Last attached time   -->1161440298
Last detached time   -->1163502660
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511

shmID[4]=36733401

Shared Memory Stats   for buffer #5
Key #                -->145971
size in bytes        -->128
Last attached time   -->1161440320
Last detached time   -->1163502889
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511



Shared Memory Stats   for buffer #6
Key #                -->145972
size in bytes        -->128
Last attached time   -->1161440503
Last detached time   -->1163503134
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511



Shared Memory Stats  for buffer #7
Key #                -->145973
size in bytes        -->128
Last attached time   -->1161440524
Last detached time   -->1163503850
Last changed time    -->1162503685
PID of creator       -->24222
PID of last operator -->0
# of current attach  -->0
owner EGID           -->6000
owner UGID           -->6109
Creator EGID         -->6000
Creator UGID         -->6109
lower 9 bit acc. mode-->511



***********************************************************************************

3. KNOWN ISSUES / DEFICIENCIES

   A.) Using a low number for key may result in insuffcient memory.

   B.) This program does not show time used for each process, but rather time between a memory segment is attached,
       modified, or detached.

   C.) This program parent process does not track how many read errors occured in child, but when read errors occured, 
      it will say something like:

           Warning: Value Changed at child ID#6

   
