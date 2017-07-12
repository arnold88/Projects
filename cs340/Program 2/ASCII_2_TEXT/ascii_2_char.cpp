/*
Arnold Lee
CS 340 Program #2
UIN:665453451
ASCII to Character conversion
Date: 02/02/2010
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// argc = # of arguments
// argv[0] = program name
// argv[1] and above = arguments
// input = a file with ASCII characters
// output = a file with ASCII decimal values
int main(int argc, char *argv[])
{ 
	string file_name;
	string text;
	
     if (argc == 1)
	 {
		 cout << "ERROR: No file name specified." << endl; 
		 return 0;
	 }
	 else if (argc != 2)
	 {
		 cout << "ERROR: Invalid argument specified." << endl;
		 cout << "Correct Usage:  ASCII_2_CHAR <filename>" << endl;
		 return 0;
	 }
	 else
	 {
         file_name = argv[1];
	 }
   
     ifstream infile;
	 ofstream outfile;

	 infile.open(file_name.c_str(),ios::in); 
	 outfile.open("char_output.txt",ios::out); 

     if (infile.is_open())
	 {
		 while (!infile.eof())
		 {
				getline(infile,text);
                
				for (unsigned int i=0;i<text.length();i++)
				{
				  if (text[i] == ' ')
				  {
                    outfile << 32 << '\n';
				  }
				  else
				  {
			     	outfile << int(text[i]) << '\n';
				  }
				}
                 
			    outfile << 10 << '\n';
			    // carriage return for each new line
 
		 }

	 }
	 else
	 {
		 cout << "ERROR: File does not exist. " << endl;
		 return 0;
	 }
    
     infile.close();
	 outfile.close();

     cout << "Content has been succesfully written to file 'char_output.txt'." << endl;

	return 0;
}