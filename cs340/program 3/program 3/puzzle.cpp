/*
Arnold Lee
CS 340 Program #3
CS user id: temp563
Puzzle class implementation
Date: 02/28/2010
*/

#include "puzzle.h"

puzzle::puzzle(fstream & file)
{
    string dummy_string;

	num_blocks = 0;

	grid_data.resize(128);

	file >> grid_height >> grid_width;

	int r,c,w,h;
	char m;

	cout << "Grid dimension: " << grid_height << "x" << grid_width << endl;;

	if ((grid_height <= 0) || (grid_width <= 0)) 
	{
		cout << "Error: Invalid number of rows or columns in the input file. " << endl;
		exit(1);

	}

    the_grid.resize(grid_width+2);

	for (int x=0;x<grid_width+2;x++)
	{
          the_grid[x].resize(grid_height+2);
	}


	for (int x=0;x<grid_width+2;x++)
		for (int y=0;y<grid_height+2;y++)
		{

			 if ( (y == 0) || (y == grid_height+1) )
				 the_grid[x][y] = '*';
			 else if ( (x==0) || (x== grid_width+1) )
				 the_grid[x][y] = '*';
			 else the_grid[x][y] = '-';
		}

 
	while (!file.eof())
	{
         file >> r >> c >> w >> h >> m;
         
		 if (num_blocks == 0) label = 'Z';
		 else
		 {
			 if (label =='Z') label = '1';
			 else if (label == '9') label = 'a';
			 else if (label == 'z') label = 'A';
			 else label = label + 1;
		 }

         temp = block(r,c,w,h,m,label);

		 if (!init_error_check())
		 {
               cout << "Block ";
			   
			   if (num_blocks == 0)
			    cout << 'Z';
			   else
				cout << num_blocks;
				   
			   cout << " has a placement error. Skipping to next one." << endl;
			   num_blocks = num_blocks + 1;
			   cout << r << " " << c << " " << w << " " << h << " " << m << " " << label << endl;
			   
		 }
		 else
		 {
		  block_placement();    
		  grid_data[num_blocks] = temp;
		  num_blocks = num_blocks + 1;
		 }

	}

	num_blocks = num_blocks - 1; //adjustment

	grid_data.resize(num_blocks);

	 
   grid_string = "";

   for (unsigned int x=1; x<the_grid.size()-1;x++)
	   for (unsigned int y=1; y<the_grid[1].size()-1;y++)
	   {
          grid_string += the_grid[y][x];
	   }
 
}

bool puzzle::init_error_check()
{
	// out of bounds
	if ((temp.r <=0) || (temp.c <=0) || ( grid_height <= temp.r+temp.h-2) || (grid_width <= temp.c+temp.w-2)) 
		return false;

	//overlap with existing piece
  for (int i=temp.r;i<temp.c+temp.w;i++)
		for (int j=temp.c;j<temp.r+temp.h;j++)
	    {
            // Occupied?
			if ( the_grid[i][j] != '-') return false;

	    }

    return true;
}

void puzzle::block_placement()
{
	
	for (int i=temp.c;i<temp.c+temp.w;i++)
	 for (int j=temp.r;j<temp.r+temp.h;j++)
	   the_grid[i][j] = temp.lbl;     
}


void puzzle::display_grid()
{  
	

	 for (int j=0;j<grid_height+2;j++)
	 {
       cout << "     ";
	   for (int i=0;i<grid_width+2;i++)
	   {
		  cout << the_grid[i][j];
	   }
	   cout << endl;
	 }

}

void puzzle::display_grid_html(fstream & output)
{
   	 for (int j=0;j<grid_height+2;j++)
	 {
       output << "<TR>";
	   for (int i=0;i<grid_width+2;i++)
	   {
		  output << "<TD>" << the_grid[i][j] << "</TD>" ;
	   }
	   output << endl;
	 }
	

}

string puzzle::grid_list()
{
   return grid_string;
}

vector <block> puzzle::block_list()
{ 
   return grid_data;
}

int puzzle::height()
{
   return grid_height;

}

int puzzle::width()
{
   return grid_width;
}

void puzzle::process(string & solution)
{
  int x_coord;
  int y_coord;



  for (int x=0;x<num_blocks;x++)
  {
       srand ( static_cast<unsigned int> ( time ( 0 ) ) );
       x_coord = rand() / ( RAND_MAX / (grid_width+1 ));
       y_coord = rand() / ( RAND_MAX / (grid_height+1));

	   grid_data[x].new_loc(x_coord,y_coord);
	   temp = grid_data[x];
	   block_placement();

  }


}

void puzzle::clear_board()
{
    for (int j = 1 ; j < grid_width-1;j++)
		for (int  i = 1 ; i < grid_height-1 ; i++)
			 the_grid[i][j] = '-';

}