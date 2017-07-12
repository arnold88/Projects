/*
Arnold Lee
CS 411 Project #2
Main Program
Date: 10/08/2010
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

using namespace::std;

#include "puzzle.h"

int main(int argc, char** argv) 
{
	string infile_name ("input.txt");
	string outfile_name ("output.txt");
	vector <int> puzzle_input (16);
	vector <int> solution;
	string temp;
	
	time_t begin,end;
   
     ifstream infile;
	 ofstream outfile;
	 

	 infile.open(infile_name.c_str(),ios::in);
	 outfile.open(outfile_name.c_str(),ios::out);

	 //re-arrange the input puzzle into a vector 
		 for (int z=0;z<16;z++) 
		 {
		    infile >> temp;

			if (temp == "X")
               puzzle_input[z] = 0;
			else
			   puzzle_input[z] = atoi(temp.c_str()); 
		 }
	
     puzzle problem(puzzle_input); // create the puzzle object
   

	 //select the heristic type
	 int heuristic_type;

	 cout << "Please enter heuristic type. Either 1 or 2." << endl;
	 cout << "Type 1: Based on Manhattan Distance, sometimes known as block distance." << endl;
	 cout << "Type 2: Based pm Diagonal Distance." << endl;
	 cout << "---->";
	 cin >> heuristic_type;

	 time(&begin); // timer starts

	 problem.start(heuristic_type); //algorithm starts

	 time(&end); // timer ends

	 solution = problem.solution(); // output solution

	 //parsing the solution vector into human-readable format
	 //all output will be sent to the output file
		 for (int x=0 ; x < solution.size(); x++)
		 {
			 switch (solution[x])
			 {
			 case 1:
				 outfile << "Right";
				 break;
			 case 2:
				 outfile << "Down";
				 break;
			 case 3:
				 outfile << "Left";
				 break;
			 case 4:
				 outfile << "Up";
				 break;
			 }

			 if (x % 4 == 3)
				 outfile << endl;
		 }

	 outfile << "Running time for Heuristics 1 in seconds -->" << difftime(begin,end) << endl;
	 outfile << "Memory Usage in bytes -> " << problem.memory_used() << endl; 


     char stuff;
     cin.clear();
     cin.ignore(cin.rdbuf()->in_avail());
     cout << "\n**************Press any key to exit***************" << flush;
     cin.get(stuff);
     cin.clear();
     cin.ignore(cin.rdbuf()->in_avail());

	infile.close();
	outfile.close();

	return 0;
}

