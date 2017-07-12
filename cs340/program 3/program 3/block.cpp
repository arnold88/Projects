/*
Arnold Lee
CS 340 Program #3
CS user id: temp563
Block class implementation
Date: 02/28/2010
*/

#include "block.h"

block::block()
{

}

block::block(int row,int col, int width, int height, char movement,char label)
{
    r=row;
    c=col;
	w=width;
	h=height;
	m=movement;
	lbl=label;
}

int block::col()
{
   return c;
}

int block::height()
{
   return h;
}

int block::width()
{
   return w;
}

int block::row()
{
   return r;
}

char block::label()
{
    return lbl;
}

// verification that the move is allowed by block type
bool block::movable(int horz,int verz)
{
   switch (m)
   {
   case 'n':
	   return false;
   case 'h':
	   if (verz !=0) return false;
	   c = c + horz;
	   return true;
    case 'v':
	   if (horz !=0) return false;
	   r = r + verz;
	   return true;
	case 'b':
       c = c + horz;
	   r = r + verz;
	   return true;
	default:
		return false;
   }
}

void block::new_loc(int x, int y)
{
   c = x;
   r = y; 
}
