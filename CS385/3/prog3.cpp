// Arnold Lee
// UIN #665453451
// CS 385 PROG 3
// CS ACCOUNT ID: temp109

// 11/28/2006

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

#include "process.h"

struct events
{
       
  int eventtype; // event type identifier
  // 1 = process arrival
  // 2 = time slice completetion
  // 3 = I/O wait
  // 4 = I/O completion
  // 5 = Page Completion
  // 6 = Process comepletion
  
  int use_pid; // pid associated with this event
  timer entry; // timer for entry
  bool valid;
  
  friend bool operator < (const events &, const events &);
  
};

bool operator < (const events & x, const events & y)
{
    if (x.entry.return_timer() >= y.entry.return_timer())
      return true;
    else
      return false;
}




int main()
{
   
    priority_queue < events > eventspace;
     
    int cpupid = -1;  
     
    int loopcount = 0; // use for the process loop to count # of processes
   
    events placeholder; // for temporaily storage
    
   	cout << endl;
	cout << "*************************************************************"<<endl;
    cout << "Name: Arnold Lee" <<endl;
    cout << "CS Account ID: temp109"<<endl;
    cout << endl;
	cout << "*************************************************************"<<endl;
	cout << "*************************************************************"<<endl;
    cout << "Discrete event simulation of memory paging system" << endl;
    cout << endl;
    

   int process_size_total = 0;
   int page_hit_total = 0;
   int page_miss_total = 0;
   timer paging;
   int totalprocess;
   int framesize;
   int swap_count = 0;
   
   cout << "Enter # of processes for the simulation-->";
   cin >> totalprocess;
   
   cout << "Enter frame size in pages -->";
   cin >> framesize;
   
    vector <process> environment (totalprocess);  // process table
    matrix <int> frametable (framesize,4);
    // frame table matrix:
             // the four columns are:
                    // 1: PID
                    // 2: Page number in the process
                    // 3: dirty bits
                    // 4: last pid used !?
    
   
    queue <process> ioqueue;
    queue <process> readyqueue;
   
    // set up the queue for process
    
    for (int x = 0; x < totalprocess; x++)
    {
        placeholder.eventtype = 1;
        placeholder.use_pid = x + 1;
        environment[x].pidentry(x+1);
        placeholder.valid = true;
        placeholder.entry.start();
        
        eventspace.push(placeholder);
        
    }
    
    // process loop starts
    
   // general algo.... start the timer of the process. Randomly choose jobs between 
   // event type 2/3/4/5, and then at the predetermine point (event start time + 200)
   // the respective process will be terminiated.
   
   
   
   
   
   
   
   // cout staticstics. Display only end times for each process sub-function.
   // Total process time: add up all indivdual process time
   
    
   cout << "****************************************************" << endl;
   cout << "*             Session Summary                      *" << endl;
   cout << "****************************************************" << endl;
   cout << " # of process run-->" << loopcount  << endl;
   cout << " frame table size-->" << framesize << endl; 
   cout << " average process size-->" <<  double (process_size_total) /  double(loopcount) << endl;
   cout << " # of page hits -->" << page_hit_total << endl;
   cout << " # of page miss -->" << page_miss_total << endl;     
   cout << " Time loss due paging -->" << paging.return_timer() << endl;
   cout << " # of page swapped--->" << swap_count << endl;
   cout << endl;
   

  return 0;
}
