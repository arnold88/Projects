/*
Arnold Lee
CS 340 Program #3
CS user id: temp563
Block class header
Date: 02/28/2010
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <vector>

using namespace::std;

class block
{
private:
    int r,c,w,h; //starting row, starting column, width, height
    char m,lbl; // legal moves, label (i.e. Z,1,2,3 etc.)

public: // access by anyone

	block(); // default

	// constructor with given varaibles r,c,w,h,m,lbl
	explicit block (int ,int ,int ,int ,char, char);


	// return approrpiate values
    int row();
	int col();
	int width();
	int height();
	char label();

	// these following two classes can access the private members
	friend class puzzle;
	friend class snapshot;

	// determine if certain move is legal
    bool movable(int,int);

	//place the block into new location
	void new_loc(int,int);

};


#endif