/*
Arnold Lee
CS 340 Program #2
UIN:665453451
Character Encrypt/Decrypt Program - Main Module
Date: 02/15/2010
*/

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <vector>

using namespace std;

long long calculation(long long,long long,long long);
bool prompt(string & , string &, string &);

int main(int argc, char *argv[])
{
   string key_file,msg_file,output_file;
   string system_call;
   vector <string> arguments;
   fstream key,input,output;
   string dummy,key_sub;
   bool encode(true);
   int end;
   unsigned long long m,n,k,mp;
   
  

  if (argc == 1)
  {
	 // collect varaible manually
     encode = prompt(key_file,msg_file,output_file); 
  }
  else
  {
   arguments.resize(argc-1); 
  
   for (int i=1; i < argc; i++)
   {
        arguments[i-1] = argv[i];

   }

   if (arguments[0] == "-e") 
   {
      encode = true;
   }
   else if (arguments[0] == "-d")
   {
      encode = false;
   }
   else
   {
	   encode = true;
   }

   for (unsigned int j = 0; j < arguments.size();j++)
   {
        if (arguments[j] == "-f")
		{
            if (j == arguments.size()-1) 
			{
				cout << "Error! No file name specified for message input!" << endl;
				return 0;
			}
			else msg_file = arguments[j+1];
			
		}

        if (arguments[j] == "-k")
		{
            if (j == arguments.size()-1) 
			{
				cout << "Error! No file name specified for key file!" << endl;
				return 0;
			}
			else key_file = arguments[j+1];
			
		}
 
		if (arguments[j] == "-o")
		{
            if (j == arguments.size()-1) 
			{
				cout << "Error! No file name specified for output file!" << endl;
				return 0;
			}
			else output_file = arguments[j+1];
			
		}
   }

  }// done argument processing

  
   
   key.open(key_file.c_str(),ios::in);
   input.open(msg_file.c_str(),ios::in);
   output.open(output_file.c_str(),ios::out);

   //use external system calls


   if (encode)
   {
   system_call = "./a2c ";
   system_call += msg_file;
   system(system_call.c_str());
   }
   
   

   // Key file processing
       getline(key,dummy);
	   getline(key,dummy);
	   key_sub = dummy.substr(8);
	   for (unsigned int i=0;i<key_sub.length();i++)
	   {
             if (key_sub[i]=='<')
			 {
                end = i;
				break;
			 }
	   }
       key_sub = dummy.substr(8,end);
	   k=atoi(key_sub.c_str());
	   getline(key,dummy);
	   getline(key,dummy);
	   key_sub = dummy.substr(8);
	   for (unsigned int i=0;i<key_sub.length();i++)
	   {
             if (key_sub[i]=='<')
			 {
                end = i;
				break;
			 }
	   }
	   key_sub = dummy.substr(8,end);
	   n=atoi(key_sub.c_str());
	  // end key file processing

       while  (!input.eof())
	   {
           input >> m;
		   
           mp = calculation(m,n,k);

		   output << mp;
		   output << '\n';

	   }

  if (!encode)
  {
   system_call = "./c2a ";
   system_call += output_file;
   system(system_call.c_str());

  }

  cout << "Your output message has been saved to '" << output_file << "'." << endl;
  cout << "If you used your public key file, this output will contain encrypted message." << endl;
  cout << "If you used your private key file, this output will contain plain text message." << endl;

  key.close();
  input.close();
  output.close();

  return 0;
}

long long calculation (long long m,long long n,long long k)
{
    long long temp;
	
	if (k==0)
		return 1;
	else if (k==1)
		return (m%n);
	else
	{
         //odd exponent
		 if (k%2==1)
			 return (m*calculation(m,n,k-1))%n;
		 else
		 {
             temp = (m^2) % n;
			 return (calculation(temp,n,k/2));

		 }
                   
	}

}

bool prompt(string & key_file,string & msg_file, string & output_file)
{
   bool temp;
   string dummy;

   cout << endl;
   cout << "Please Enter the file name of the public or private key -->";
   getline (cin,key_file);
   cout << endl;
   cout << "Please Enter the file name of the message input -->";
   getline (cin,msg_file);
   cout << endl;
   cout << "Please Enter the desired file name of the output file -->";
   getline (cin,output_file);
   cout << "Please indicate if this is a message file or a character-encoded file." << endl;
   cout << "Enter 1 for Plain text, 0 for encoded message." << endl;
   cout << "--->";
   cin >> temp; 
   getline (cin,dummy);

   return temp;

}