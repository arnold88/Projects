// Arnold Lee
// UIN #665453451
// CS 385 PROG 2
// CS ACCOUNT ID: temp109

// 10/17/2006

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
#include <iostream.h>
#include <string.h>
#include <vector>
#include <strings.h>
#include <unistd.h>
#include <assert.h>
#include <iomanip.h>
#include <string>
using std::string;



union semun 
{
      int val;
      struct semid_ds * buf;
      ushort * array;
};


void msg_stats (const msqid_ds & , const key_t & );
// function for message queue stats


void shared_mem_stats (const shmid_ds &,const key_t &); 
// function for shared memory stats



int main()
{

	int nBuffer;  // # of buffers
    char semlock; // option... lock enabled or no?
	key_t key; // key # for all IPC
	int * shm_addr_temp = NULL; // temprary shared memory address
    int msqID; // message queue ID
    msgbuf send, receive; // message buffer for send/receive
    pid_t processID; // process ID
    int waitstatus; // wait status
    msqid_ds msq_stats; // message queue stats
    
  
	cout << endl;
	cout << "*************************************************************"<<endl;
    cout << "Name: Arnold Lee" <<endl;
    cout << "CS Account ID: temp109"<<endl;
    cout << endl;
	cout << "*************************************************************"<<endl;
	cout << "*************************************************************"<<endl;
    cout << "Process synchtonization and intercommunications simulator" << endl;

    // main program start

	cout << endl;
	cout << "Enter a number of buffers that will be used, PRIME number please-->";
	cin >> nBuffer;

	while (nBuffer < 1)
	{
		cout << "invalid entry. Please try again." << endl;
	    cout << "Enter a number of buffers that will be used, PRIME number please-->";
	    cin >> nBuffer;
	}
	
	int nChild = nBuffer / 2; // divide by 2 then truncate
    
	int shmID[nBuffer];
    shmid_ds BufferInfo [nBuffer];
    int shm_addr [nBuffer];
    int childID[nChild];

    shmid_ds shm_stats[nBuffer];

	cout << endl;
	cout << "Activate Semaphore Lock ? ( Enter 'Y','y','N' or 'n' ONLY) --->";
	cin >> semlock;

    while ( (semlock != 'Y') && (semlock != 'y') && (semlock != 'N') && (semlock != 'n'))
	{
		cout << "invalid entry. Please try again." << endl;
	    cout << "Activate Semaphore Lock ? ( Enter 'Y','y','N' or 'n' ONLY) --->";
	    cin >> semlock;
	}

	cout << endl;

	
	cout << "Enter a random interger that is unique enough." << endl;
	cout << "For example, your last 4 digit of your SSN." << endl;
	cout << "---->";
	cin >> key;
	cout << endl;
	
// main program starts


if ((semlock == 'N') || (semlock == 'n'))  // No semaphore lock
{
	 cout << "creating buffers........." <<endl;
     for (int i = 0 ; i < nBuffer; i++) // creating buffer begins
	 {
		 shmID[i] = shmget (key+i, 128, ( IPC_CREAT | 0777 ) );  
		 // shared memory creation,  all access enabled

         shmctl (shmID[i], IPC_STAT , & shm_stats[i]);

         // shared memory stats can add here

		 if (shmID[i] < 0)
		 {
			 perror("shmget");
			 exit (1);
		 }
		 cout << "shmID[" << i << "]=" << shmID[i] << endl;

         if ( shmctl(shmID[i], IPC_STAT , &BufferInfo[i]) == -1) // obtain stats with shmctl()
		 {
			 perror("shmctl");
			 exit(1);
			 
		 }
		 else
		 {
			 // display newly created buffer info for testing only
			 cout << endl;
			 cout << "Shared Memory Stats for buffer #"<< i+1 << endl;
			 shared_mem_stats(BufferInfo[i],key+i);
			 cout << endl;
			
		 } 

         shm_addr_temp = (int *)shmat(shmID[i],NULL,0);
         shm_addr[i] = *shm_addr_temp;
		 


      } // buffer creating for-loop ends
	  cout << "Creating all buffers succesfully." << endl;
	  
	  cout << endl;
	  
	  cout << "Initializing Buffer...." << endl;
	  
	  for (int y=0;y < nBuffer ; y++)
	  {
          shm_addr[y] = 123; // all buffer value initiated to 123
                             // instead of zeroes to avoid possible bugs 
      }
          
      cout << "Creating message queue..." << endl;   

	  msqID = msgget(key,(IPC_CREAT | 0777)); // create message queue
    
       if (msqID < 0)
       {
           perror("msgget");
           exit(1);
       }
       
       // you can add message stats here
       
       msgctl (msqID,IPC_STAT,&msq_stats);
       
       cout << endl;
       cout << "Message queue stats:" << endl;
       cout << endl;
       
       msg_stats (msq_stats , msqID);
       
       cout << endl;

       for (int x=0;x < nChild; x++) // initiate fork process
       {
           
           childID[x] = x+1;
           int next = childID[x];
           
           switch(processID=fork()) // fork off child
           {
                 case -1: 
                      cout << "Fork error, please restart your computer.";
                      break;
                 case 0 : //child process
                 
                      int jump = childID[x];
                      
                      for (int a=0;a < (3*nBuffer);a++) // start read-write phase
                      {
                       
                        if (a % 3 != 2) // read phase (first two access for reading)
                        {
                         int temp1 = shm_addr[next-1];
                         cout << "Buffer #" << next << " -->" << shm_addr[next-1] << endl;
                         sleep( int(double(2/nBuffer) * jump));
                         
                         if (shm_addr[next-1] != temp1)
                         {
                          
                          // value changed when sleeping! ALERT!  
                          
                          send.mtype = childID[x];
                          cout << endl;
                          sprintf(send.mtext, "Warning: Value Changed at child ID#%d",childID[x]);
                          cout << endl; 
                          
                          if (msgsnd(msqID,&send,strlen(send.mtext)+1,0) < 0) // send message
                          {
                               perror("msgsnd");
                               exit(1);                                          
                          }
                                             
                         }// end alerts
                         
                        }// end read phase
                        else // write phase 
                        {
                             
                         cout << "Write phase begins!" << endl;
                         int temp1 = shm_addr[next-1];
                         cout << "Buffer #" << next << " -->" << shm_addr[next-1] << endl;    
                         sleep( int(double(2/nBuffer) * jump));
                         
                          
                         shm_addr[next-1] = temp1 + jump; //write to buffer 
                         
                         cout << "( After write) Buffer #" << next << " -->" << shm_addr[next-1] << endl;
                            
                        }// end write phase
                         
                         next = next + jump;
                         
                         if (next > nBuffer)  // loop back counter
                         {
                                  next = next - nBuffer;
                         }
                      }// end read-write phase
                      
                      
                      //final confirmation before child exits
                      
                          send.mtype = childID[x];
                          sprintf(send.mtext, "Child #%d finish its job.",childID[x]);
                          if (msgsnd(msqID,&send,strlen(send.mtext)+1,0) < 0) // send message
                          {
                               perror("msgsnd");
                               exit(1);                                          
                          }
                          cout << endl;
                       
                      exit(3); 
                      
                      
                 default: 
                      int waitcode = wait(&waitstatus); 
                      // retrieve message
                      if ( (msgrcv( msqID, &receive, 1024, childID[x], 0)) < 0)    ;\
                      {
                           perror ("msgrcv");
                           exit(1);
                      }
                      
                      printf ("%s\n",receive.mtext);
                      
                      
                       
            } // end switch (fork process)
        
           cout << endl;    
        
        } // end for loop (for each child)
           
        
        msgctl(msqID,IPC_RMID,&msq_stats);  // message queue removal
     
        
        
        
        
        for (int f=0;f<nBuffer;f++)
        {
             cout << endl;
			 cout << "Shared Memory Stats (Aftermath) for buffer #"<< f+1 << endl;
			 shared_mem_stats(BufferInfo[f],key+f);
			 cout << endl;
         
         
            shmctl (shmID[f],IPC_RMID,&BufferInfo[f]); 
            // remove shared memory segment
        }
        
        cout << endl;
}// end program ---- no semaphore lock
else // **************semaphore lock enabled*********
{
    // create message queue
    msqID = msgget(key,(IPC_CREAT | 0777)); // create message queue
    
       if (msqID < 0)
       {
           perror("msgget");
           exit(1);
       }
       
       // you can add message stats here
       
       msgctl (msqID,IPC_STAT,&msq_stats);
       
       cout << endl;
       cout << "Message queue stats:" << endl;
       cout << endl;
       
       msg_stats (msq_stats , msqID);
       
       cout << endl;
       
       // create semaphore buffers
     
       int semID;
       
       //acquire sempahore 
       cout << "Creating semaphores....." << endl;
       semID = semget(key,nBuffer,(IPC_CREAT | 0777));

        union semun sem_options;    

        sem_options.val = 1 ; // only one process can read/write a single buffer
                              // each time
                        
        for (int g=0 ; g < nBuffer; g++)      // initialize all semaphores in
          {                                    // the set
            semctl( semID, g, SETVAL, sem_options);
          } 
        
        struct sembuf LOCK = { 0 , -1 , IPC_NOWAIT };
        struct sembuf RELEASE = { 0 , 1 , IPC_NOWAIT };
        
       cout << "creating buffers........." <<endl;
     for (int i = 0 ; i < nBuffer; i++) // creating buffer begins
	 {
		 shmID[i] = shmget (key+i, 128, ( IPC_CREAT | 0777 ) );  
		 // shared memory creation,  all access enabled

         shmctl (shmID[i], IPC_STAT , & shm_stats[i]);

         // shared memory stats can add here

		 if (shmID[i] < 0)
		 {
			 perror("shmget");
			 exit (1);
		 }
		 cout << "shmID[" << i << "]=" << shmID[i] << endl;

         if ( shmctl(shmID[i], IPC_STAT , &BufferInfo[i]) == -1) // obtain stats with shmctl()
		 {
			 perror("shmctl");
			 exit(1);
			 
		 }
		 else
		 {
			 // display newly created buffer info for testing only
			 cout << endl;
			 cout << "Shared Memory Stats for buffer #"<< i+1 << endl;
			 shared_mem_stats(BufferInfo[i],key+i);
			 cout << endl;
			
		 } 


         // acquire shared memory address and store in array
         shm_addr_temp = (int *)shmat(shmID[i],NULL,0);
         shm_addr[i] = *shm_addr_temp;
		 


      } // buffer creating for-loop ends
	  cout << "Creating all buffers succesfully." << endl;
	  
	  cout << endl;
	  
	  cout << "Initializing Buffer...." << endl;
	  
	  for (int y=0;y < nBuffer ; y++)
	  {
          shm_addr[y] = 123;  // all buffer value initiated to 123
                             // instead of zeroes to avoid possible bugs 
          
          
      }
          

       for (int x=0;x < nChild; x++) // initiate fork process
       {
           
           childID[x] = x+1;
           int next = childID[x];
           
           switch(processID=fork()) // fork off child
           {
                 case -1: 
                      cout << "Fork error, please restart your computer.";
                      break;
                 case 0 : //child process
                 
                      int jump = childID[x];
                      
                      for (int a=0;a < (3*nBuffer);a++) // start read-write phase
                      {
                       
                       LOCK.sem_num = x; 
                       if (semop(semID,&LOCK,1) == -1)//CHECK resource
                        perror("semop");                     //LOCKED!!!
                       else // NOT LOCKED!
                       { 
                           if (a % 3 != 2) // read phase (first two access for reading)
                           {
                           int temp1 = shm_addr[next-1];
                          cout << "Buffer #" << next << " -->" << shm_addr[next-1] << endl;
                           sleep( int(double(2/nBuffer) * jump));
                         
                         if (shm_addr[next-1] != temp1)
                         {
                          
                          // value changed when sleeping! ALERT!  
                          
                          send.mtype = childID[x];
                          cout << endl;
                          sprintf(send.mtext, "Warning: Value Changed at child ID#%d",childID[x]);
                          cout << endl; 
                          
                          if (msgsnd(msqID,&send,strlen(send.mtext)+1,0) < 0) // send message
                          {
                               perror("msgsnd");
                               exit(1);                                          
                          }
                                             
                         }// end alerts
                         
                        }// end read phase
                        else // write phase 
                        {
                             
                         cout << "Write phase begins!" << endl;
                         int temp1 = shm_addr[next-1];
                         cout << "Buffer #" << next << " -->" << shm_addr[next-1] << endl;    
                         sleep( int(double(2/nBuffer) * jump));
                         
                          
                         shm_addr[next-1] = temp1 + jump; //write to buffer 
                         
                         cout << "( After write) Buffer #" << next << " -->" << shm_addr[next-1] << endl;
                            
                        }// end write phase
                         
                         next = next + jump;
                         
                         if (next > nBuffer)  // loop back counter
                         {
                                  next = next - nBuffer;
                         }
                         
                      RELEASE.sem_num = x;
                      semop (semID,&RELEASE,1);
                      }// end read-write phase
                     
                     }// end else (semaphore lock) 
                      
                      //final confirmation before child exits
                      
                          send.mtype = childID[x];
                          sprintf(send.mtext, "Child #%d finish its job.",childID[x]);
                          if (msgsnd(msqID,&send,strlen(send.mtext)+1,0) < 0) // send message
                          {
                               perror("msgsnd");
                               exit(1);                                          
                          }
                          cout << endl;
                       

                      
                      exit(3); 
                      
                      
                 default: 
                      //int waitcode = wait(&waitstatus); 
                      // retrieve message
                      if ( (msgrcv( msqID, &receive, 1024, childID[x], 0)) < 0)    
                      {
                           perror ("msgrcv");
                           exit(1);
                      }
                      
                      printf ("%s\n",receive.mtext);
                      
                      
                       
            } // end switch (fork process)
        
           cout << endl;    
        
        } // end for loop (for each child)
        
        
           
        
        msgctl(msqID,IPC_RMID,&msq_stats);  // message queue removal
     
        
        for (int f=0;f<nBuffer;f++)
        {
             cout << endl;
			 cout << "Shared Memory Stats (Aftermath) for buffer #"<< f+1 << endl;
			 shared_mem_stats(BufferInfo[f],key+f);
			 cout << endl;
         
            shmctl (shmID[f],IPC_RMID,&BufferInfo[f]); 
            // remove shared memory segment
        }
        
        cout << endl;
       
       



}

	return 0;
} // end main program


//*************************SUB-FUNCTIONS*********************************


void shared_mem_stats (const shmid_ds & info, const key_t & key) 
// used to display shared memory parameters and stats
{
	         cout << "Key #                -->" << key << endl;        
	         cout << "size in bytes        -->" << info.shm_segsz << endl;
			 cout << "Last attached time   -->" << info.shm_atime << endl;
			 cout << "Last detached time   -->" << info.shm_atime << endl;
			 cout << "Last changed time    -->" << info.shm_ctime << endl;
			 cout << "PID of creator       -->" << info.shm_cpid << endl;
			 cout << "PID of last operator -->" << info.shm_lpid << endl;
			 cout << "# of current attach  -->" << info.shm_nattch << endl;
			 cout << "owner EGID           -->" << info.shm_perm.gid << endl;
			 cout << "owner UGID           -->" << info.shm_perm.uid << endl;
			 cout << "Creator EGID         -->" << info.shm_perm.cgid << endl;
			 cout << "Creator UGID         -->" << info.shm_perm.cuid << endl;
             cout << "lower 9 bit acc. mode-->" << info.shm_perm.mode << endl;

}

void msg_stats (const msqid_ds & info, const key_t & key) 
// used to display message queue parameters and stats
{
	         cout << "Key #                -->" << key << endl;        
	         cout << "size in bytes        -->" << info.msg_cbytes << endl;
			 cout << "Last send time       -->" << info.msg_stime << endl;
			 cout << "Last received time   -->" << info.msg_rtime << endl;
			 cout << "Last changed time    -->" << info.msg_ctime << endl;
			 cout << "PID of last sender   -->" << info.msg_lspid << endl;
			 cout << "PID of last receiver -->" << info.msg_lrpid << endl;
			 cout << "# of max bytes allow -->" << info.msg_qbytes << endl;
			 cout << "owner EGID           -->" << info.msg_perm.gid << endl;
			 cout << "owner UGID           -->" << info.msg_perm.uid << endl;
			 cout << "Creator EGID         -->" << info.msg_perm.cgid << endl;
			 cout << "Creator UGID         -->" << info.msg_perm.cuid << endl;
             cout << "lower 9 bit acc. mode-->" << info.msg_perm.mode << endl;

}
