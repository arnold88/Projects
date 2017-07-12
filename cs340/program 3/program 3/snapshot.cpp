/*
Arnold Lee
CS 340 Program #3
CS user id: temp563
Snapshot class implementation
Date: 02/28/2010
*/

#include "snapshot.h"

snapshot::snapshot(vector<block> & x, string & m)
{
  grid_list = x;
  move_info = m;
}

string snapshot::movelist()
{
   return move_info;
}

block snapshot::grid_num(int x)
{
   return grid_list[x];
}