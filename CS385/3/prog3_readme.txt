Name: Arnold Lee
CS Account ID: temp109
    


Memory paging system simulation

To compile type:

g++ prog3.cpp -o prog3

To execute the shell type:

./prog3


NOTE : AT CURRENT TIME THERE IS A BUG ON THE COMPLILER THAT REFUSE TO COMPILE THIS SOURCE CODE IF THERE IS
       ARGUMENTS CARRIED INTO int main. SO THEREFORE THE CODE WILL NOT ACCEPT COMMAND LINE ARGUMENTS, RATHER
       PROMPT USER TO ENTER THE VALUES WHEN EXECUTING THE PROGRAM.

1. Insturctions.

     A.) You will be prompted to enter number of process used in the simulation.

     B.) Next choose # of frame size in pages. There may be a maximum limit, depend on amount of 
         memory installed in your computer.




     D.) The program will now execute.  

2. Expected Output

A normal operation should look like this: 
(Chosen value:         )


***********************************************


****************************************************" << endl;
*             Session Summary                      *" << endl;
****************************************************" << endl;
# of process run-->
frame table size-->
average process size-->
# of page hits -->
# of page miss -->
Time loss due paging -->
# of page swapped--->


***********************************************************************************

3. KNOWN ISSUES / DEFICIENCIES

   A.) This program only uses FIFO to process events. Random processing 
       and other algorithms may be included later.

   B.) If you enter a value for frame pages or processes that are too high, your computer
       may not respond or performing unpredicted behavior.

   C.) The following critical functionality (Events) is not implemented at this point due to time constraint, therefore no time has been recorded:

           - I/O wait
           - I/O completion
           - Page Access

       
   
