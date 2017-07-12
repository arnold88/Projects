// Arnold Lee
// UIN #665453451
// CS 385 PROG 1
// CS ACCOUNT ID: temp109

// 9/24/2006

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

const char pline = '|';

const char space = ' '; 






int main(int argc, char * argv[])
{
	cout << endl;
	cout << "*************************************************************"<<endl;
    cout << "Name: Arnold Lee" <<endl;
    cout << "CS Account ID: temp109"<<endl;
    cout << endl;
	cout << "*************************************************************"<<endl;
	cout << "*************************************************************"<<endl;
    cout << setw(15) << "WELCOME TO STATSH V0.9" <<endl;  
	cout << endl;
    
    string cmd;
    string subcmd;
    string subarg;
    


    cout << "Enter command (enter EXIT to finish)-->";

    getline (cin,cmd);

    int piperecord[1000]; // record location of pipes in string
    int numpipe = 0; // record number of pipe

    int spacerecord[1000];    // record location of dash in string
    int numspace = 0; //record number of dash

    int response = 0; // for holding execvp() return values
     
   
 
    while  (cmd != "EXIT") // not exit command .... shell keeps going
    {
       

       numpipe = 0;
       numspace = 0;
       

      for (int count = 0; count < cmd.length(); count++)
      {
         if (cmd[count] == pline)
         {
            piperecord[numpipe] = count;
            numpipe = numpipe + 1;
         }

         if (cmd[count] == space)
         {
            spacerecord[numspace] = count;
            numspace = numspace + 1;
         }   
      } // end for loop
     
	 
	  
	 cout << endl;
	 cout << "test numpipe -->" << numpipe << endl;
     cout << "test numspace -->" << numspace << endl;
     cout << endl;


    
   if (numpipe != 0) // multiple commands linked with pipe
   {
    /*for (int countx=0; countx < numpipe; countx ++)
    {
         if (countx==0) // first command
         {
           if (piperecord[countx] < spacerecord[countx])
            subcmd = cmd.substr(0,piperecord[countx]-1);
           else
           {
            subcmd = cmd.substr(0,spacerecord[countx]-2);          
            subarg = cmd.substr(spacerecord[countx],piperecord[countx]-1);
        
           }
         }
         else
         {
           if (piperecord[countx] < spacerecord[dashcounter])
            subcmd = cmd.substr(piperecord [countx-1]+1,piperecord[countx]-1);
           else
           {
             subcmd = cmd.substr(piperecord [countx-1]+1,spacerecord[dashcounter]-1);
             subarg = cmd.substr(spacerecord[ ],piperecord[countx]-1);
        
           }
 
         }

      cout << "command " << countx+1 << " -->" << subcmd << " " << " Arg-->" << subarg << endl; 
         

	  char * newarg[]={subarg.c_str()};
      response = execvp(subcmd.c_str(),newarg);
	  
     }*/      
   }
   else // single command , no pipe
   {
      if (numspace==0) // no arguments
	  {
	    
		char *newarg[]={"0"};     
		
		response = execvp(cmd.c_str(),newarg);
		
		if (response==-1)
		{
		cout << "Invalid command ("<< cmd << ")! Please try again! "<< endl;
		}

	  }
	  else // contains arguments
	  {
		  int countz=0;
 
		  subcmd=cmd.substr(0,spacerecord[0]);
          subarg=cmd.substr(spacerecord[0]+1,cmd.length());

          cout << "command-->" << subcmd << endl;
		  cout << "respective arguments-->" << subarg << endl;


		  cout << endl;


          char tempcmdstringholder[cmd.length()];
           

          strcpy (tempcmdstringholder,cmd.c_str()); // convert a string-type C string (const char *) into char *

		  char * argarray[numspace+2];

		  argarray[numspace+1] = NULL;

          cout << "tempcmdstringholder-->" << tempcmdstringholder << endl; // copied string still OK

		  argarray[0] = strtok(tempcmdstringholder," ");

		  for (countz = 1; countz <=numspace; countz++)
		  {
			  
              argarray[countz]=strtok(NULL, " ,.");
		  }
		  

		  cout << "*argarray[0]-->" << *argarray[0] << endl;
		  cout << "*argarray[1]-->" << *argarray[1] << endl;
		  

         
		  response = execvp(subcmd.c_str(),argarray);

		if (response==-1)
		{
		cout << "Invalid command ("<< cmd << ")! Please try again! "<< endl;
		}


	  }

   }

     
   
     cout << endl;
     cmd = "EXIT"; 
     cout << "Enter command (enter EXIT to finish)-->";
     getline (cin,cmd);
     cout << endl;
     cout << "Command Entered-->" << cmd << endl;

     response = 0;
   
    }

   
	return 0;
}


