/*
Arnold Lee
CS 340 Program #3
CS user id: temp563
Puzzle class header
Date: 02/28/2010
*/

#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <queue>
#include <stack>
#include "block.h"
#include "snapshot.h"

class puzzle
{
private:

	// the 2D array acting as a map
	vector < vector<char> > the_grid;

	// map width and height
	int grid_width,grid_height;

	// total number of blocks in the map 
	int num_blocks;

	// temporary storage of label
	char label;

	// temporary storage of block object
	block temp;

	// list of blocks as an array
	vector <block> grid_data;

	// solution move history as a string
	string solution_string;

	// current map as a string
	string grid_string;

    // check for input errors (i.e. overlapping blocks)
	bool init_error_check();

	// place the block
	void block_placement();

	// clear the map, for display purpose
	void clear_board();

	

public:

	// generate a map given a valid file input
	explicit puzzle(fstream &);

	// display the map
    void display_grid();

	// return the current map as a string
	string grid_list();
	
	// return list of blocks as an array
    vector <block> block_list();

	// return the map dimensions
	int height();
	int width();

	// write the map to the file in HTML format
	void display_grid_html(fstream &);

	//post-solution processing and map updating
	void process(string &);

};

#endif