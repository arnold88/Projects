/*
Arnold Lee
CS 411 Project #1
Main Program
Date: 09/29/2010
*/



//#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

using namespace::std;

// remaining
// time function
// node class
// depth first breadth first algo
// display

#include "puzzle.h"


int main(int argc, char** argv) 
{
	string infile_name ("input.txt");
	string outfile_name ("output.txt");
	vector <int> puzzle_input (16);
	vector <int> solution;
	string temp;
	
	time_t begin,end;

	/*
     if (argc == 1)
	 {
		 cout << "ERROR: No file name specified." << endl; 
		 return 0;
	 }
	 else if (argc == 2)
	 {
		 cout << "ERROR: No output file name specified." << endl; 
		 return 0;
	 }
	 else if (argc != 3)
	 {
		 cout << "ERROR: Invalid argument specified." << endl;
		 cout << "Correct Usage:  bfs <input filename> <output filename>" << endl;
		 return 0;
	 }
	 else
	 {
         infile_name = argv[1];
		 outfile_name = argv[2];
	 }*/
   
     ifstream infile;
	 ofstream outfile;
	 

	 infile.open(infile_name.c_str(),ios::in);
	 outfile.open(outfile_name.c_str(),ios::out);


		 for (int z=0;z<16;z++)
		 {
		    infile >> temp;

			if (temp == "X")
               puzzle_input[z] = 0;
			else
			   puzzle_input[z] = atoi(temp.c_str()); 
         }

		 int search_type;
		 int depth_limit;

	 cout << " Enter the type of search. 1 for BFS, 2 for DFS --> ";
	 cin >> search_type;

	 if (search_type ==2)
	 {
		 cout << " Enter the depth limit for DFS ---->";
		 cin >> depth_limit;
	 }
	 else
	 {
		 depth_limit = 0;
	 }
	 
     puzzle problem(puzzle_input); // the puzzle object

	 outfile << "BFS Search Detail" << endl << endl;

	 time(&begin);

	 problem.start(search_type,depth_limit); // BFS

	 if (problem.goal_state())
	 {
		 cout << "BFS: Solution has been found!" << endl;
		 cout << "Writing Output....." << endl;

		 solution = problem.solution();

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

	 }
	 else
	 {
		 outfile << "BFS: No solution exist. " << endl;
	 }

	 time(&end);

	 outfile << "Running time for DFS in seconds -->" << difftime(begin,end) << endl;
	 outfile << "DFS Memory Usage in bytes -> " << problem.memory_used() << endl; 
	
	 outfile << endl << endl;

	 outfile << "DFS Search Detail" << endl << endl;

	 time(&begin);

	 problem.start(search_type,depth_limit); 

	 if (problem.goal_state())
	 {
		 cout << "DFS: Solution has been found!" << endl;
		 cout << "Writing Output....." << endl;

		 solution = problem.solution();

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

	 }
	 else
	 {
       cout << "DFS: No solution found with the given depth limit. " << endl;
	 }

	 time(&end);

	 cout << "Running time for DFS in seconds -->" << difftime(begin,end) << endl;
	 cout << "DFS Memory Usage in bytes -------->"<< problem.memory_used() << endl;

	char pause;
	cout << "Press any key to exit..." << endl;
	cin >> pause;
	infile.close();
	outfile.close();

	return 0;
}

