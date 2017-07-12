// Arnold Lee
// UIN #665453451
// CS 385 PROG 4
// CS ACCOUNT ID: temp109

// 12/05/2006

#include <queue>
#include <stdio.h>
#include <cstdlib> 
#include <errno.h>
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

#include <sys/types.h>
#include <fstream>
#include "disk.h"
#include <signal.h>


struct events
{
       
  int eventtype; 
  //1= disk request arrival
  //2= disk request completion
  
  
  int head; 
  int sector;
  int cylinder;
  int launch_time;
  
  timer entry; // timer for entry
  bool valid;
  
  int algo_type;
  // 1 = FCFS
  // 2 = SSTF
  // 3 = SCAN
  // 4 = C-SCAN
  
  friend bool operator < (const events &, const events &);
  
};



bool operator < (const events & x, const events & y)
{
   switch (x.algo_type)
   {
          case 1:
         {
                  if (x.launch_time <= y.launch_time)
                        return true;
                  else return false;
              break;
        }
           case 2:
       {
           return (x.cylinder <= y.cylinder);
           break;
       }
       case 3:
            {
            return (x. head <= y. head);
            break;
            }
       case 4:
            {
                  return (x.sector <=y.sector) && (x.cylinder <= y.cylinder);
                  break;
            }
            default:
                    return false;
       }
}




int main(int argc,char *argv[])
{
    
    
    if ( (argc <= 1) || (argc >= 4) )
    {
           cout << "Invalid argument!" << endl;
           exit(0);     
    }
    
   
    timer programtime;
   
    priority_queue < events > eventspace;
    
    queue <events> pending;
    
    queue <events> tempqueue; // a temporary queue for switching algorithms
    
    
     
    ifstream file;
     
    int proccount = 0; // use for the process loop to count # of processes
   
    events current; // for temporaily storage
    
    srand((unsigned)time(0));  // random # generator seed
    
    int randnum;
    
    int busy_count = 0;
    
    pid_t pid;
    
    file.open(argv[1]);
    
    if (file.fail())
    {
        cout << "file open failure!" << endl;
        exit (0);
    }
    
    
    
    int request = 0;
    
    
    if (argc == 3)
       request = *argv[2];
    else
       request = 99999999;
    
    
    int filecounter = 0;
    int pending_top = 0;
    
    while ( (!file.eof()) && (filecounter < request)) 
    {
       current.algo_type = 1;
       current.eventtype = 1;
       current.valid = true;
       file >> current.launch_time >> current.head;
       file >> current.sector >> current.cylinder;
       filecounter++;   
       eventspace.push(current);
       tempqueue.push(current); // make a copy
    }
    
    file.close();
    
    programtime.start();
    
    disk hard_drive(10,16,1000);
    
   	cout << endl;
	cout << "*************************************************************"<<endl;
    cout << "Name: Arnold Lee" <<endl;
    cout << "CS Account ID: temp109"<<endl;
    cout << endl;
	cout << "*************************************************************"<<endl;
	cout << "*************************************************************"<<endl;
    cout << "Discrete event simulation of Hard drive disk access" << endl;
    cout << endl;
    
    while ( (! eventspace.empty()) || (! pending.empty()) )
    {
         
       if (pending.empty())
       {
         current = eventspace.top();
         eventspace.pop(); 
         current.entry.start();
       }
       else
       {
           current = pending.front();
           pending.pop();
           current.entry.start();
       }
                     
          
         switch (pid = fork())
         {
           case -1:
                cout << "Fork failed" << endl;
                break;
           case 0:
                {
                   if (hard_drive.busy())
                   {
                      current.entry.stop();
                      pending.push(current);
                      
                      if (pending_top < pending.size())
					  {
                         pending_top = pending.size();
					  }
                      
                      busy_count++;
                      _exit(0);
                   }
                   else
                   {
                      hard_drive.writedisk(1,current.head,current.sector,current.cylinder);
                      current.entry.stop();
                      _exit(0);
                   }          
                 break;                      
                }
           default:
                   proccount++;
                   
           }
       
       cout << "Process " << proccount << " run time:";
       cout << current.entry.return_timer() << endl;   

          
    }
    
    
   
   
   
   cout << "****************************************************" << endl;
   cout << "*             Session Summary                      *" << endl;
   cout << "****************************************************" << endl;
   cout << endl;
   cout << "FCFS algorithm                                     " << endl;
   cout << "total process -->" << proccount << endl;
   cout << "total time in msec-->" << programtime.return_timer() << endl;
   cout << "total pending request queued ---> " << busy_count << endl;
   cout << "Max # of pending request at any given time -->" << pending_top << endl;
   cout << "*****************************************************"<<endl;

   
  int mode = 2;

  while (mode <= 4) // for additional algorithms
  {
       
	  
	 proccount = 0;

    request = 0;
    
    pending_top = 0;


   

	for (int count = 0; count < filecounter; count ++)
    {

       current = tempqueue.front();
	   tempqueue.pop();

       current.algo_type = mode;
       current.eventtype = 1;
       current.valid = true;

       eventspace.push(current);
       tempqueue.push(current); // make a copy
    }
    
    
    programtime.start();



	 while ( (! eventspace.empty()) || (! pending.empty()) )
    {
         
       if (pending.empty())
       {
         current = eventspace.top();
         eventspace.pop(); 
         current.entry.start();
       }
       else
       {
           current = pending.front();
           pending.pop();
           current.entry.start();
       }
                     
          
         switch (pid = fork())
         {
           case -1:
                cout << "Fork failed" << endl;
                break;
           case 0:
                {
                   if (hard_drive.busy())
                   {
                      current.entry.stop();
                      pending.push(current);
                      
                      if (pending_top < pending.size())
					  {
                         pending_top = pending.size();
					  }
                      
                      busy_count++;
                      _exit(0);
                   }
                   else
                   {
                      hard_drive.writedisk(1,current.head,current.sector,current.cylinder);
                      current.entry.stop();
                      _exit(0);
                   }          
                 break;                      
                }
           default:
                   proccount++;
                   
           }
       
       cout << "Process " << proccount << " run time:";
       cout << current.entry.return_timer() << endl;   
	   
	 
	 }

	cout << "**************************************************" << endl;


	switch (mode)
	{
	case 2:
		cout << "SSTF algorithm" << endl;
		break;
	case 3:
		cout << "SCAN algorithm" << endl;
		break;
	case 4:
		cout << "C-SCAN algorithm" << endl;
		break;
	default:
		cout << "Error on switching algorithm" << endl;
	}





   cout << "total process -->" << proccount << endl;
   cout << "total time in msec-->" << programtime.return_timer() << endl;
   cout << "total pending request queued ---> " << busy_count << endl;
   cout << "Max # of pending request at any given time -->" << pending_top << endl;
   cout << "*****************************************************"<<endl;


   mode = mode + 1; // switch to next algorithm


  } // end while loop for algorithm switching



  kill(1,9);

  return 0;
}
