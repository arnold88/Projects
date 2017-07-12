// Arnold Lee
// UIN #665453451
// CS ACCOUNT ID: temp109


// 11/28/2006

//Process sub-class for Program #3


#ifndef _PROCESS_H
#define _PROCESS_H

#include <queue>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdio.h>
#include <cstdlib> 
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
using namespace::std;
#include <string.h>
#include <vector>
#include <strings.h>
#include <unistd.h>
#include <assert.h>
#include <iomanip>
#include "matrix.h"
#include <string>
using std::string;
#include "timer.h"




class process
{
        public:
               process(); //default constructor
               
               process(int); // process with default events (process arrival,
                          // time clice completetion,process completetion)
                          
               process(vector <int> ,int); 
               // dictate what type of action will the process takes.            
               
               
               
             // control function


              // the following still need to implement.

               void process_start(); // start process overall timer
               void process_stop(); // stop all timers

               void inc_page_hit(); // increase page hit counter
               void inc_page_fault(); // increase page fault counter
               
               void timer_ready(); // trigger ready queue timer
               void timer_io(); // trigger io queue timer
               void timer_cpu(); // trigger cpu timer
               
               void stop_timer_ready(); // atop ready queue timer
               void stop_timer_io(); // stop io queue timer
               void stop_timer_cpu(); // stop cpu timer

               void pidentry(int); // Enter PID
               
               void page_entry(int num,int framenum); // entry to page table

               void swapped(int); 
               // make corresponding entry in page table invalid

            // value return function

               int return_pid();
               double start_times();
               double finish_time();
               double r_queue_time(); // ready queue elapsedtime
               double io_queue_time(); // i/o queue elapsed time
               int page_fault_count(); // # of page fault count
               int page_hit_count(); // # of page hit count
               double cpu_time(); // time spent in CPU;
  
               
               
        
        private:
                int pid;  //current process PID
                double starttime; // time process starts (in queue)
                double finishtime; // time process ends (out of CPU)
                double readyqueuetime; // amount of time spent in ready queue
                double ioqueuetime; // amount time spent in I/O queue
                double cputime; // amount time spent in CPU
                int pagefaultcount; // # of page fault occured with this event
                int pagehitcount; // # of page hit occured with this event 
        
                
                
                timer proc_timer; // overall process
                timer cpu_timer; // CPU timer
                timer ready_timer; // ready queue timer
                timer io_timer; // i/o queue timer
                
                
                
                matrix <int> pagetable;
                // first column : frame #
                // second column: valid? 0 = invalid, 1 = valid
              
        
        
        
};
      
#endif

process::process()
{
                  
         pid = 0;
         starttime = 0.0;
         finishtime= 0.0;
         readyqueuetime = 0.0;
         ioqueuetime = 0.0;
         cputime = 0.0;
         pagefaultcount = 0;
         pagehitcount= 0;         
         
         pagetable.resize(100,2);         
         
         for (int g = 0; g < 100; g++)
         {
             pagetable[g][1] = 0;
         }
         
         
                  
}

process::process(int x)
{
                  
         pid = x;
         starttime = 0.0;
         finishtime= 0.0;
         readyqueuetime = 0.0;
         ioqueuetime = 0.0;
         cputime = 0.0;
         pagefaultcount = 0;
         pagehitcount= 0;         
         
         pagetable.resize(100,2);         
         
         for (int g = 0; g < 100; g++)
         {
             pagetable[g][1] = 0;
         }
         
         
                  
}
                  
process::process(vector <int> type,int x)   
{
         
         pid = x;
         starttime = 0.0;
         finishtime= 0.0;
         readyqueuetime = 0.0;
         ioqueuetime = 0.0;
         cputime = 0.0;
         pagefaultcount = 0;
         pagehitcount= 0;         


         pagetable.resize(100,2);  
         
         for (int g = 0; g < 100; g++)
         {
             pagetable[g][1] = 0;
         }
         
}


// ***********************IMPLEMENTATION******************************
                  
int process::return_pid() 
{
 return pid;   
}    
double process::start_times()
{
    return starttime;
} 

     
double process::finish_time()
{
    return finishtime;  
} 
  
double process::r_queue_time()  
{
     return readyqueuetime;       
}
double process::io_queue_time() 
{
     return ioqueuetime;       
}
int process::page_fault_count()
{
     return pagefaultcount;   
}
int process::page_hit_count()
{
     return pagehitcount;   
} 

double process::cpu_time()
{
     return cputime;       
} 
                       

void process::process_start()
{
     proc_timer.start();
}
     
void process::process_stop()
{
     proc_timer.stop();
     finishtime = proc_timer.return_timer();
     
     if (cpu_timer.active())
     {
        cpu_timer.stop();
     }
     
     if (ready_timer.active())
     {
        stop_timer_ready();
     }
     
     if (io_timer.active())
     {
        stop_timer_io();
     }
      
}

void process::inc_page_fault()
{
     pagefaultcount++;
}

void process::inc_page_hit()
{
     pagehitcount++;
}

void process::timer_ready() // trigger ready queue timer
{
      ready_timer.start();
           
}

void process::timer_io() // trigger io queue timer
{
       io_timer.start();                
}
               
          
void process::timer_cpu()// trigger cpu timer
{
       cpu_timer.start();
}               
              
void process::stop_timer_ready() // atop ready queue timer
{
        ready_timer.stop();
        readyqueuetime = ready_timer.return_timer();
}

void process::stop_timer_io() // stop io queue timer
{
        io_timer.stop();
        ioqueuetime = io_timer.return_timer();

}

void process::stop_timer_cpu() // stop cpu timer
{
        cpu_timer.stop();
        cputime = cpu_timer.return_timer();
}

void process::swapped (int x)
{
       pagetable[x][1] = 0;
}

void process::page_entry(int serial,int framenum)
{
     pagetable[serial][0] = framenum;
     pagetable[serial][1] = 1;
}

void process::pidentry(int x)
{
    pid = x;
}
