/*
Arnold Lee
CS 411 Project #2
Puzzle Class Header
Date: 10/08/2010
*/

#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stack>
#include <queue>

using namespace::std;

struct node
{
   

	int path_cost; // cost of the path from start state - 1 per move in the puzzle
	int est_cost; // estimate cost from path to goal (varies depends on heuristic chosen)
	int serial_number; // the node serial number, used to determine solutions
	vector<int> state; // the state board in vector form, dynamically changing



	// check for valid move from each direction
	bool up;
	bool down;
	bool left;
	bool right;

	// node for the next level
	node *north;
	node *south;
	node *west;
	node *east;


	// implement a comparison function against two differnet node
	// in terms of path cost .... needed for priority queue

	bool operator < (node * rhs)
	{
		return ( (this->path_cost + this->est_cost) < (rhs->path_cost + rhs->est_cost) ); 
	}

};

class puzzle
{
public:
	
	puzzle(vector<int> &);
	
	void start(int);
	// integer indicate heruristics type
	// 1=Manhattan distance, 2= diagnoal distance

	bool goal_state();
	// true if solution reached
	// false if doesn't or the depth limit reached

	vector <int> solution();
	// return a solution in terms of direction taken 
	// returns a null vector if there is no solution
	// or depth limit reached

	int memory_used();
	// report memeory usage in terms of 512-byte units

private:


	vector<int> the_board; // Use as a place holder for verification steps

	vector<int> steps; // this is solution to be returned
	
	bool goal_found; // if the goal state is reached
	
	void move(int); // move the tiles 
	// 1 = north = up
	// 2 = east = right
	// 3 = south = down
	// 4 = west = left

	void check_goal(); // check for goal state

	void valid_move(node *);  //verification module

	node *header; // the root node

	node *next; // the frontier node

	priority_queue <node *> frontier; // the frontier priority queue

	vector <node *> explored; // the explored node array

	bool visited (node *); // verify if this particular state is already explored

	int estimate(int); //estimate cost generation function based on herusitic type

	int global_serial; // global serial number for a node , assist in determining the path of solution
};

#endif