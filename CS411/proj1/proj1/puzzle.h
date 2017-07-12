/*
Arnold Lee
CS 411 Project #1
Puzzle Class Header
Date: 09/29/2010
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
   
	int expand; // number of expansion
	int depthlevel; // how deep
	int serial_number; // the node serial number
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
};

class puzzle
{
public:
	
	puzzle(vector<int> &);
	
	void start(int,int);
	// first integer indicates search type (BFS,DFS)
	// second integer indicate depth limit (DFS only)

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

	vector<int> original; // the original input, will stay constant as reference

	vector<int> the_board; // Use as a place holder for verification steps

	vector<int> steps; // this is solution to be returned
	
	int depth_entered; // how deep the program has entered

	int depth_limit; // depth limit specified by the user
	
	bool goal_found; // if the goal state is reached
	
	void move(int); // move the tiles 
	// 1 = north = up
	// 2 = east = right
	// 3 = south = down
	// 4 = west = left

	void check_goal(); // check for goal state

	void valid_move(node *);  //verification module

	node *header; // the root node

	queue <node *> bfs_explored; //bfs explored queue

	queue <node *> bfs_frontier; //bfs frontier queue

	void bfs();

	void dfs(node *);

	int global_serial;
};

#endif