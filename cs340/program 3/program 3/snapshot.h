/*
Arnold Lee
CS 340 Program #3
CS user id: temp563
Snapshot class header
Date: 02/28/2010
*/

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "block.h"
#include <queue>

using namespace std;

class snapshot
{
private:
	//list of blocks in the snapshot
    vector<block> grid_list;

	//move history so far
	string move_info;


public:
	//default constructor, requires the grid list and move history string
	explicit snapshot(vector<block>& , string &);

    // return the move history, useful when poping snapshot queue
	string movelist();

	//return the block object, given its label
	block grid_num(int);
      

};


#endif