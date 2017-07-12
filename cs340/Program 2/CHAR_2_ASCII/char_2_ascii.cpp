/*
Arnold Lee
CS 340 Program #2
UIN:665453451
Character to ASCII conversion program
Date: 02/02/2010
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// argc = # of arguments
// argv[0] = program name
// argv[1] and above = arguments
// input = a file with ASCII character decimal values
// output = a file with ASCII text
int main(int argc, char *argv[])
{ 
	string file_name;
	
     if (argc == 1)
	 {
		 cout << "ERROR: No file name specified." << endl; 
		 return 0;
	 }
	 else if (argc != 2)
	 {
		 cout << "ERROR: Invalid argument specified." << endl;
		 cout << "Correct Usage:  CHAR_2_ASCII <filename>" << endl;
		 return 0;
	 }
	 else
	 {
         file_name = argv[1];
	 }
   
     ifstream infile;
	 ofstream outfile;
	 int temp;

	 infile.open(file_name.c_str(),ios::in); 
	 outfile.open("msg_output.txt",ios::out); 

     if (infile.is_open())
	 {
		 while (!infile.eof())
		 {
				infile >> temp;

				if (!infile.eof())
				  outfile << char(temp%128);
		 }

	 }
	 else
	 {
		 cout << "ERROR: File does not exist. " << endl;
		 return 0;
	 }
    
     infile.close();
	 outfile.close();

     cout << "Content has been succesfully written to file 'msg_output.txt'." << endl;

	return 0;
}