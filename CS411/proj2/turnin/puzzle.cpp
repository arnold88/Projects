/*
Arnold Lee
CS 411 Project #2
Puzzle Class Implementation
Date: 10/08/2010
*/

#include "puzzle.h"
#include <math.h>

puzzle::puzzle (vector<int> & input)
{
	// initial conditions
	the_board = input;
	goal_found = false;
	header = new node[32]; // 32 byte allocated per node
	header->state = input;
	global_serial = 0;
	header->path_cost = 0;
	header->est_cost  = 0;
	next = header;
	explored.resize(1000);

}


// check if the goal has been found
bool puzzle::goal_state()
{
	return goal_found;
}


// return the steps towards the solution
// the solution node will have an unique serial number
// The serial number indicates an unique path to the solution
vector <int> puzzle::solution()
{
	int A;

	A = log(double(global_serial)) / log(4.0);

	

	steps.resize(A); 

	for (int x = steps.size()-1 ; x >= 0 ; x--)
	{
		steps[x] = (A / 4) % 5;
		A = A / 4;
	}

	return steps;
}


// a_star search algorithm core
void puzzle::start(int heur)
{

	while (true) // loop starts
	{
		// is there a frontier? pop it out and check!
		// note that the frontier is a priority queue based on estimated cost of the node
		if (!frontier.empty())
		{
			next = frontier.top();
			frontier.pop();
		}
		

		// copy the current node state to a dummy variable
		// for goal checking
		the_board = next->state;
	
		// goal found? get out!
	    check_goal();
    	if (goal_found) 
    	{
		 goal_found = true;
		 return;
	    }

		// otherwise, check for valid move for the current state of the board
	    valid_move(header);

	// attach a "Serial number" to the node representing the intial state
	// for determing the solution later
    header -> serial_number = global_serial;

	// add current node to the "explored" list
	explored[global_serial] = header;

    // for the following four modules, it push it the valid moves to the "frontier queue"
	// "right" or "east" means moving the piece to the right/east of the blank box
	global_serial++;

	// if sliding to the right is valid + the state has not been visited before
	if ((next->right) && (visited (next->east)) )
	{
		
		    // allocate a new childe node for the new state
			next -> east = new node [512];


			the_board = next -> state;

			move(2); // make the move

			next -> east -> state = the_board; // put the new state back to the child node

			next -> east -> serial_number = global_serial; // attach an incremented serial number

			next -> east -> path_cost = next -> path_cost + 1; // add 1 to path cost

			next -> east -> est_cost = estimate(heur); // calculate estimate cost based on heuristic type chosen

			// again, goal check
					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }
		    // if no goal, push the child node into the frontier queue
			frontier.push(next->east);
		
	}


	// for the following three modules, they are the same as above, just different directions
	global_serial++;
	if ( (next->down)  && (visited (next->south)))
	{
			next -> south = new node [512];

			the_board = next -> state;

			move(3);

			next -> south -> state = the_board;

			next -> south -> serial_number = global_serial;

			next -> south -> path_cost = next -> path_cost + 1;

			next -> south -> est_cost = estimate(heur);

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }
		    
			frontier.push(next->south);

	}


	global_serial++;
	if ((next->left) && (visited (next->west)))
	{
			next -> west = new node [512];
		
			the_board = next -> state;

			move(4);

			next -> west -> state = the_board;

			next -> west -> serial_number = global_serial;

			next -> west -> path_cost = next -> path_cost + 1;

			next -> west -> est_cost = estimate(heur);

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			frontier.push(next->west);

	}

	global_serial++;
	if ((next->up) &&   (visited (next->north)))
	{
			next -> north = new node [512];
	
			
			the_board = next -> state;

			move(1);

			next -> north -> state = the_board;

			next -> north -> serial_number = global_serial;

			next -> north -> path_cost = next -> path_cost + 1;

			next -> north -> est_cost = estimate(heur);

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			frontier.push(next->north);

	} 

} // end loop

} // end a* algorithm core


// check for valid move for 'X' and record it to the node
void puzzle::valid_move (node * local_head)
{
	the_board = local_head ->state;

	for (int x=0; x < the_board.size(); x++)
	{
		if (the_board[x] == 0) // where is the blank slot located?
		{
			switch (x) // determine valid moves 
			{
			case 0: // this is slot 0 -- the upper left corner
				local_head -> left = false; // you can't move  the piece from your left (this is boundary)
				local_head ->right = true; // you can move the piece from your right
				local_head ->up = false; // you can't move the piece above you (boundary)
				local_head ->down = true; // you can move the piece below you
				break;
		// same logic below for other 15 slots on the board
			case 1:
			case 2:
			local_head -> left = true;
				local_head ->right = true;
				local_head ->up = false;
				local_head ->down = true;
				break;
			case 3:
				local_head -> left = true;
				local_head ->right = false;
				local_head ->up = false;
				local_head ->down = true;
				break;
			case 4:
			case 8:
				local_head -> left = false;
				local_head ->right = true;
				local_head ->up = true;
				local_head ->down = true;
				break;
			case 5:
			case 6:
			case 9:
			case 10:
				local_head -> left = true;
				local_head ->right = true;
				local_head ->up = true;
				local_head ->down = true;
				break;
			case 7:
			case 11:
				local_head -> left = true;
				local_head ->right = false;
				local_head ->up = true;
				local_head ->down = true;
				break;
			case 12:
				local_head -> left = false;
				local_head ->right = true;
				local_head ->up = true;
				local_head ->down = false;
				break;
			case 13:
			case 14:
				local_head ->left = true;
				local_head ->right = true;
				local_head ->up = true;
				local_head ->down = false;
				break;
			case 15:
				local_head ->left = true;
				local_head ->right = false;
				local_head ->up = true;
				local_head ->down = false;
				break;

			}// end switch

		} // end if

	} // end for loop
}// end the validation function

void puzzle::check_goal()
{
	for (int x=0; x < the_board.size(); x++)
	{
		// the correct position will be something like:
		// tile 1 in slot 1
		// tile 2 in slot 2
		// .....
		// tile 15 in slot 15
		if (the_board [x] != x)  
		{
			goal_found = false;
			return;
		}
	}

	goal_found = true;
}

void puzzle::move(int move_type)
{


	//To make a move, swap the tiles
	//according to the move type

	// Move Type:
	// 1 = north = up
	// 2 = east = right
	// 3 = south = down
	// 4 = west = left

    for (int x=0; x < the_board.size(); x++)
	{
		if (the_board[x] == 0)
		{
			switch (move_type)
			{
			case 1:
				 the_board[x] = the_board[x-4];
				 the_board[x-4] = 0;
				 break;
			case 2:
				 the_board[x] = the_board[x+1];
				 the_board[x+1] = 0;
				 break;
			case 3:
				the_board[x] = the_board[x+4];
				 the_board[x+4] = 0;
				 break;
			case 4:
				the_board[x] = the_board[x-1];
				 the_board[x-1] = 0;
				 break;
			}

		}

	}
}

// return memory usage
int puzzle::memory_used()
{
	return global_serial*512;
}

// provide estimate path cost based on heuristics chosen
int puzzle::estimate(int heur)
{
	int value;

	if (heur == 1) // first heuristic - manhattan distance
	{
		for (int x=0;x<the_board.size();x++)
		{
			if (the_board[x] == 0) // where does the target piece occurs
			{
				switch (x) // determine distance from current blank to its final destination
				{
				case 0: // if the target piece is at its intended destination, there is no estimate cost
					value = 0; 
					break;
				case 1: // otherwise, a manhattan distance between the two locations will be returned
				case 4:
					value = 1;
					break;
				case 2:
				case 5:
				case 8:
					value = 2;
					break;
				case 3:
				case 6:
				case 9:
				case 12:
					value = 3;
					break;
				case 7:
				case 10:
				case 13:
					value = 4;
					break;
				case 11:
				case 14:
					value = 5;
					break;
				case 15:
					value = 6;
					break;

				}//end switch
			}// end if
		}// end for

	}// end if
	else // second heuristic - diagonal distance
	{
	    for (int x=0;x<the_board.size();x++)
		{
			if (the_board[x] == 0)
			{
				switch (x)
				{
				case 0:
					value = 0;
					break;
				case 1:
				case 4:
				case 5:
					value = 1;
					break;
				case 2:
				case 6:
				case 8:
				case 9:
				case 10:
					value = 2;
					break;
				default:
					value = 3;
					break;
				}
			}
		}
	}

	return value;
}

// check if a certain node is in the explored list or not
bool puzzle::visited(node * point)
{
	for (int x = 0 ; x < explored.size(); x++)
	{
		if (explored[x] == point)
			return true;
	}

	return false;
}