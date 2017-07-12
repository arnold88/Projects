/*
Arnold Lee
CS 411 Project #1
Puzzle Class Implementation
Date: 09/29/2010
*/

#include "puzzle.h"


puzzle::puzzle (vector<int> & input)
{
	
	the_board = input;
	original = input;
	depth_entered = 0;
	depth_limit = 0;
	goal_found = false;
	header = new node[32]; // 32 byte allocated per node
	header->depthlevel = 1;
	header->expand = 0;
	header->state = input;
	global_serial = 0;

}


bool puzzle::goal_state()
{
	return goal_found;
}

vector <int> puzzle::solution()
{
	return steps;
}


// type 1= BFS, type 2 = DFS
void puzzle::start(int type,int limit)
{

	if (type == 1) // bfs selected by user
	{
        bfs();
	}
	else // dfs selected by user
	{
	    depth_limit = limit;
		dfs(header);
	}


}

// breadth first search algorithm core
void puzzle::bfs()
{
	
	node *next;

	// if the puzzle is already in goal state -> break
	check_goal();
	if (goal_found) 
	{
		goal_found = true;
		return;
	}

	// push the initial state into explored queue
	bfs_explored.push(header);

	// detect all possible move from the initial state
	valid_move(header);

	// attach a "Serial number" to the node representing the intial state
	// for determing the solution later
    header -> serial_number = global_serial;

	// if the initial state is dead end, get out
	if ((!header->right) && (!header->left) && (!header->down) && (!header->up))
	{
		bfs_explored.pop();
		return;
	}

	// increment the global node serial number
	global_serial++;

	// for the following four modules, it push it the valid moves to the "frontier queue"
	// "right" or "east" means moving the piece to the right/east of the blank box
	if (header->right)
	{
			header -> east = new node [512]; // allocate 512B for the new node
	
			header ->expand++; // record number of expansion for statistical purpose

			the_board = header -> state; // copy the state of the board to a temp variable

			move(2); // make that move on the temporary board

			header -> east -> state = the_board; // store the new state of the board into the "east" child of the node

			header -> east -> serial_number = global_serial; // assign a new serial number to the "east" child

			check_goal(); // check if the goal state is reached (with the temporary board)

	    if (goal_found)  // in goal state? flip the flag and leave! we are done!
	    {
		goal_found = true;
		return;
	    }

        bfs_frontier.push(header->east); // otherwise, push the child into the frontier
	}

	// same as above, this time deal with down/south direction
	global_serial++;
	if (header->down)
	{
			header -> south = new node [512];
	
			header ->expand++;

			the_board = header -> state;

			move(3);

			header -> south -> state = the_board;

			header -> south -> serial_number = global_serial;

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			bfs_frontier.push(header->south);

	}

	// same as above, this time deal with left/west direction
	global_serial++;
	if (header->left)
	{
			header -> west = new node [512];
	
			header ->expand++;

			the_board = header -> state;

			move(4);

			header -> west -> state = the_board;

			header -> west -> serial_number = global_serial;

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			bfs_frontier.push(header->west);

	}

	//this time deal with up/north direction
	global_serial++;
	if (header->up)
	{
			header -> north = new node [512];
	
			header ->expand++;

			the_board = header -> state;

			move(1);

			header -> north -> state = the_board;

			header -> north -> serial_number = global_serial;

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			bfs_frontier.push(header->north);

	}



// This is from second level onward
	while (true)
	{

		if (bfs_frontier.empty()) break;

		next = bfs_frontier.front(); // put "next" pointer point to the top of the frontier queue
		bfs_frontier.pop(); // pop the frontier
		bfs_explored.push(next); // push whatever we just poped from the frontier queue to the "explored" queue

		valid_move(next); // check for valid move

		depth_entered++; // tracking the depth level for statistical purpose
		
		// no valid moves? skip here and pop the next frontier
	if ((!next->right) && (!next->left) && (!next->down) && (!next->up))
	{
		bfs_explored.pop();
		break;
	}


	// Again, like the header node, processing each of the four possible directions
	// but we are now processing the "next" node instead
	global_serial++;
	if (next->right)
	{
			next -> east = new node [512];
	
			next ->expand++;

			the_board = next -> state;

			move(2);

			next -> east -> state = the_board;

			next -> east -> serial_number = global_serial;

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			bfs_frontier.push(next->east);

	}

	global_serial++;
	if (next->down)
	{
			next -> south = new node [512];
	
			next ->expand++;

			the_board = next -> state;

			move(3);

			next -> south -> state = the_board;

			next -> south -> serial_number = global_serial;

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			bfs_frontier.push(next->south);

	}

	global_serial++;
	if (next->left)
	{
			next -> west = new node [512];
	
			next ->expand++;

			the_board = next -> state;

			move(4);

			next -> west -> state = the_board;

			next -> west -> serial_number = global_serial;

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			bfs_frontier.push(next->west);

	}

	global_serial++;
	if (next->up)
	{
			next -> north = new node [512];
	
			next ->expand++;

			the_board = next -> state;

			move(1);

			next -> north -> state = the_board;

			next -> north -> serial_number = global_serial;

					check_goal();
	    if (goal_found) 
	    {
		goal_found = true;
		return;
	    }

			bfs_frontier.push(next->north);

	} 



	} // end while loop
	// you only get here if you found the goal, or nothing is left at the frontier

}// end BFS algorithm core

// DFS algorithm core
void puzzle::dfs(node * local_head)
{
	node *next; // next node pointer

	// if depth of node > global depth limit, then break;
	if (local_head->depthlevel > depth_limit)
	{
		return;
	}
	
		// if the puzzle is already in goal state -> break
	check_goal();
	if (goal_found) 
	{
		goal_found = true;
		return;
	}
	else
	{
		valid_move(local_head); // check valid move

		if (local_head->right) // if the tile can move to the right, move
		{
			the_board = local_head -> state;

			move(2);

			local_head -> east = new node[512]; // allocate memory for child nore

			local_head -> east -> state = the_board; // update the state in the child

			local_head -> east ->depthlevel = local_head -> depthlevel + 1; // increase the depth count

			next = local_head -> east; // point the "next" node to the child

			dfs(next); // recursive call to this function

		}

		// same as above, just for different direction 
		if (local_head->down)
		{
			the_board = local_head -> state;

			move(3);

			local_head -> south = new node[512];

			local_head -> south -> state = the_board;

			local_head -> south ->depthlevel = local_head -> depthlevel + 1;

			next = local_head -> south;

			dfs(next);

		}

		if (local_head->left)
		{
			the_board = local_head -> state;

			move(4);

			local_head -> west = new node[512];

			local_head -> west -> state = the_board;

			local_head -> west ->depthlevel = local_head -> depthlevel + 1;

			next = local_head -> west;

			dfs(next);

		}

		if (local_head->up)
		{
			the_board = local_head -> state;

			move(1);

			local_head -> north = new node[512];

			local_head -> north -> state = the_board;

			local_head -> north ->depthlevel = local_head -> depthlevel + 1;

			next = local_head -> north;

			dfs(next);

		}
	}

}// end DFS algorithm core

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