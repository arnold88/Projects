/*
Arnold Lee
CS 340 Program #3
CS user id: temp563
Main Program
Date: 02/28/2010
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include "puzzle.h"

using namespace std;

string solver(puzzle&,string, vector<block>&, queue<snapshot>&, bool,int );

int main(int argc, char *argv[])
{
    fstream input; //input file object
    string file_name; //input file name
	string output_file_name; // output HTML file name
	vector <block> original_blist; // original list of blocks and its locations
	string original_list; //original list of blocks in string format
	string solution_state; //final-state list of blocks in string format
	queue <snapshot> temporary; //snapshot queue for temporary storage of block movement states
	string move_list; // move history in string format
	fstream output; // output HTML file object
	bool html_output(false); // HTML initialization flag
	bool sol_found(false); // 'solution found' flag
	int strike_counter(0); // # of grid boxes traveled

	if (argc > 1)
	{

		if (! strcmp(argv[1],"-h") )
		{
             html_output = true; //want HTML file?
		}
		else 
		{
            cout << "ERROR! Invalid argument. Please refer to readme.txt for correct syntax." << endl;
			exit(1);
		}
	}

	cout << "Please enter the input file name-->";
	getline(cin,file_name);

    int found=file_name.find(".");

    output_file_name = file_name.substr(0,found) + ".html";

	input.open(file_name.c_str());

   if (input.fail())
   {
        cout << "Error opening input file. This program will now exit." <<endl;
		exit(1);
   }

   puzzle board(input); // create puzzle object

   	int board_height(board.height());
	int board_width(board.width());

   cout << "Grid Status:" << endl << endl;
   board.display_grid();

   move_list = "";

   // HTML code generation section
   if (html_output)  // HTML output
   {

	   output.open(output_file_name.c_str(),ios::out);

   if (output.is_open())
   {
   output << " Original Grid: <BR>" << endl;
   output << " <BR> <BR> <BR> " << endl;
   output << " <TABLE BORDER=2> " << endl;
   
   board.display_grid_html(output);

   output << " </TABLE> <BR>" << endl;

   }
   else
	   cout << "HTML file cannot be written. Make sure your disk is not full. " << endl;

   }//end HTML code generation

   // find solution move in terms of strings
   solution_state = solver(board, move_list, original_blist,temporary,
	            sol_found,strike_counter);   

   if ((!sol_found) || (solution_state == "\0"))
   {
        cout << "Solution does not exist!" << endl;

		if (html_output)
			 output << " Solution does not exist! <BR>" << endl;
   }

    // update actual move on the board
   board.process(solution_state);

   // output solution string
   cout << "Solution String:" << endl;

   cout << "Solution State:" << endl;
   board.display_grid(); 

   input.close();
    
   //HTML code generation section
   if (html_output)  // HTML output
   {



   output << " Solution Grid: <BR>" << endl;
   output << " <BR> <BR> <BR> " << endl;
   output << " <TABLE BORDER=2> " << endl;
   
   board.display_grid_html(output);

   output << " </TABLE>" << endl;

   cout << "The HTML output has been written to file name " << output_file_name << endl;
   output.close();
   }
  
	return 0;
}


// the solver, will be used recursively
// returns the string for solution steps
string solver(puzzle & board, string move_list,vector<block> & block_list,
			    queue<snapshot> & temporary, bool sol_found,int strike_counter)
{
   
    strike_counter++;

	vector <bool> can_move (block_list.size());

	int board_height(board.height());
	int board_width(board.width());
	
	int x_coord; 
    int y_coord;

    // find Z and check that first
    for (unsigned int x=0;x<block_list.size();x++)
	{
		if (block_list[x].label() == 'Z')
		{
			if ( (block_list[x].movable(1,0)) || (block_list[x].movable(0,1)) || (block_list[x].movable(1,0)) ) 
               can_move[0] = true;
			else
			{
				can_move[0] = false;
				move_list = temporary.front().movelist();
				temporary.pop();
			}

		}
		else // moving Z doesn't solve, or Z is not movable, check elsewhere
		{
            if ( (block_list[x].movable(1,0)) || (block_list[x].movable(0,1)) || (block_list[x].movable(1,0)) ) 
               can_move[x] = true;
			else 
			{
				can_move[x] = false;
				move_list = temporary.front().movelist();
				temporary.pop();
			}    
		} 
 	}
  
	// determine move direction
     for (unsigned int y=0;y<can_move.size();y++)
	 {
		  srand ( static_cast<unsigned int> ( time ( 0 ) ) );
          x_coord = rand() % board_width + 1;
		  y_coord = rand() % board_height + 1;


          if (can_move[y])
		  {
			  block_list[y].new_loc(x_coord,y_coord);
			  move_list = move_list + block_list[y].label();
			  move_list = move_list +'^';
			  move_list = move_list + char(x_coord);
			  move_list = move_list +'>';
			  move_list = move_list + char(y_coord);
			  move_list = move_list + ' ';
				 
		  }

		  // block Z on right edge?
		  if (block_list[y].col() == board_width) 
		  {
			  sol_found = true; // turn on the 'solution found' flag
			  // and break the loop
			  break;
		  }

	 }
	
    // save snapshot

  // if solution still not found and still have pieces undiscovered
  if ( (!sol_found) && ( strike_counter < board.width()*board.height()))
  {
    snapshot temp_snap(block_list,move_list);	
    
    //queue the snapshot
	temporary.push(temp_snap);

	// process partial string and recusive call to this function
    return solver(board,move_list,block_list,temporary,sol_found,strike_counter);
  }
  else //solution found or do not exist
  {
	// return move history string
    return move_list;
  }
}