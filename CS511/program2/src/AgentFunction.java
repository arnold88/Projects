//Arnold Lee
//UIN: 665453451 
//CS 511 Program 2
//Wumpus World - Model based reflex agent



import java.util.Random;

class AgentFunction {
	
	// string to store the agent's name
	// do not remove this variable
	private String agentName = "Agent Smith";
	
	// all of these variables are created and used
	// for illustration purposes; you may delete them
	// when implementing your own intelligent agent
	private int[] actionTable;
	private boolean bump;
	private boolean glitter;
	private boolean breeze;
	private boolean stench;
	private boolean scream;
	private Random rand;

	private int [][] grid  = new int [11][11];
	// a 11x11 field display
	// Allow the grid to be reconstucted no matter where the agent starts and its direction
	// 0 = Undiscovered
	// 1 = breeze detected
	// 2 = stench detected
	// 3 = potential pit
	// 4 = potential wumpus
	// 5 = confirmed pit
	// 6 = confirmed wumpus
	
	// 8 = Wall/Boundary (agent cannot exist in this "room")
	
	
	// agent starting position, always at middle of the grid
	// x_pos is East-West, with larger number towards east
	// y_pos is north-south, larger number towards north
	private int x_pos = 5;
	private int y_pos = 5;
		
	private int direction = 0;
	//arbitrary compass, 0 = North, 1 = East , 2 = south, 3 = west
	private int previous_dir = 0;
	
	
	// some functional flags
	private int next_step = 0;
	private boolean u_turn = false;
	private boolean wumpus_detected = false;
	
	public AgentFunction()
	{
		// for illustration purposes; you may delete all code
		// inside this constructor when implementing your 
		// own intelligent agent

		// this integer array will store the agent actions
		actionTable = new int[8];
				  
		actionTable[0] = Action.GO_FORWARD;
		actionTable[1] = Action.TURN_RIGHT;
		actionTable[2] = Action.TURN_LEFT;
		actionTable[3] = Action.GRAB;
		actionTable[4] = Action.SHOOT;
		
		
		
	// initialize the grid
		for (int i=0;i<11;i++)
			for (int j=0;j<11;j++)
			{
				grid[i][j]=0;
			}
		
	}

	public int process(TransferPercept tp)
	{
		// To build your own intelligent agent, replace
		// all code below this comment block. You have
		// access to all percepts through the object
		// 'tp' as illustrated here:
		
		direction = previous_dir;
		
		// read in the current percepts
		bump = tp.getBump();
		glitter = tp.getGlitter();
		breeze = tp.getBreeze();
		stench = tp.getStench();
		scream = tp.getScream();
		
		grid[x_pos][y_pos]=7;
		
//****************** Priority Action Phrase *****************************************************
		
		//if glitter, the goal has been met. Perform grab action and ends the program
		if (glitter)
		{
			return actionTable[4];
		}
		
		//repeat last action if the u_turn flag is on 
		//only works with the turn_left and turn_right command
		if (u_turn)
		{
			u_turn = false;
			return actionTable[next_step];
			
		}
				
		if( bump ) 
		{
			switch (direction)
			{
			case 0:
				grid[x_pos][y_pos+1]=8;
				break;
			case 1:
				grid[x_pos+1][y_pos]=8;
				break;
			case 2:
				grid[x_pos][y_pos-1]=8;
				break;
			case 3:
				grid[x_pos-1][y_pos]=8;
				break;
			
			}
			
			direction = scanwall(x_pos,y_pos);
			
		}
		
		if (scream) wumpus_detected = false;
		
//****************************************************************************************************************************
		if ((breeze) && (!stench))
		{
			grid[x_pos][y_pos]=1;
			
			direction = scanpit(x_pos,y_pos,direction);
			
			
		}
		else if ( (stench) && (!breeze))
		{
			grid[x_pos][y_pos]=2;
			
			
			if (!scream) direction = scanwumpus(x_pos,y_pos,direction);
			
			
			
		}
		else if (breeze&&stench)
		{
		    
            grid[x_pos][y_pos]=1;
			
			direction = scanpit(x_pos,y_pos,direction);
			if (!scream)direction = scanwumpus(x_pos,y_pos,direction);
		
			
		}

		if (wumpus_detected) return actionTable[4];
		else
		{
			if (previous_dir != direction)
			{
				direction = (direction+1)%4;
				u_turn = true;
				next_step = 1;
			}
			else next_step = 0;
			
		}
		
	//*******************************************************************************************************
		// action execution
	    return actionTable[next_step];	    
	}
// end agent function implementation
	
	
	
	
	
	// public method to return the agent's name
	// do not remove this method
	public String getAgentName() {
		return agentName;
	}
	
//*************************************************
	// scan functions
	public int scanwall(int x,int y)
	{
		int dir = 0;
		
		// four corner case
		if ( (grid[x][y+1] == 8) && (grid[x+1][y] == 8))
		{
			dir = 2;
		}
		else if ((grid[x][y-1] == 8) && (grid[x+1][y] == 8))
		{
			dir = 3;
		}
		else if ((grid[x][y-1] == 8) && (grid[x-1][y] == 8))
		{
			dir = 0;
		}
		else if ((grid[x][y+1] == 8) && (grid[x-1][y] == 8))
		{
			dir = 1;
		}
		else // non-corner case
		{
		
		if (grid[x][y+1] == 8)
		{
			dir = 1;
		}
		
			if (grid[x+1][y] == 8)
		{
			dir = 2;
		}
		
			if (grid[x][y-1] == 8)
		{
			dir = 3;
		}
		
		   if (grid[x-1][y] == 8)
		{
			dir = 0;
		}
			
		}// end non-corner case
		
		return dir;
		
	}
	
	
	public int scanpit(int x,int y,int dir)
	{
		
		// mark potential pits and confirmed pits
		
		switch (dir)
		{
		case 0:
			if (grid[x][y+1]!=3) grid[x][y+1]=5;
			if (grid[x+1][y]!=3) grid[x+1][y]=5;
			if (grid[x-1][y]!=3) grid[x-1][y]=5;
			
			if (grid[x][y+1]!=8) grid[x][y+1]=3;
			if (grid[x+1][y]!=8) grid[x+1][y]=3;
			if (grid[x-1][y]!=8) grid[x-1][y]=3;
			
			if (grid[x][y+1]!=5) dir=1;
			if (grid[x+1][y]!=5) dir=2;
			if (grid[x-1][y]!=5) dir=3;
			
			break;
		case 1:
			
			if (grid[x+1][y]!=3) grid[x+1][y]=5;
			if (grid[x][y-1]!=3) grid[x][y-1]=5;
			if (grid[x][y+1]!=3) grid[x][y+1]=5;
			
			if (grid[x+1][y]!=8) grid[x+1][y]=3;
			if (grid[x][y-1]!=8) grid[x][y-1]=3;
			if (grid[x][y+1]!=8) grid[x][y+1]=3;
			
			if (grid[x+1][y]!=5) dir=0;
			if (grid[x][y-1]!=5) dir=2;
			if (grid[x][y+1]!=5) dir=3;
			
			break;
		case 2:
			
			if (grid[x+1][y]!=3) grid[x+1][y]=5;
			if (grid[x][y-1]!=3) grid[x][y-1]=5;
			if (grid[x-1][y]!=3) grid[x-1][y]=5;
			
			if (grid[x+1][y]!=8) grid[x+1][y]=3;
			if (grid[x][y-1]!=8) grid[x][y-1]=3;
			if (grid[x-1][y]!=8) grid[x-1][y]=3;
			
			if (grid[x+1][y]!=5) dir = 0;
			if (grid[x][y-1]!=5) dir = 1;
			if (grid[x-1][y]!=5) dir = 3;
			
			break;
		case 3:
			
			if (grid[x][y+1]!=3) grid[x][y+1]=5;
			if (grid[x][y-1]!=3) grid[x][y-1]=5;
			if (grid[x-1][y]!=3) grid[x-1][y]=5;
			
			if (grid[x][y+1]!=8) grid[x][y+1]=3;
			if (grid[x][y-1]!=8) grid[x][y-1]=3;
			if (grid[x-1][y]!=8) grid[x-1][y]=3;
			
			if (grid[x][y+1]!=5) dir = 0;
			if (grid[x][y-1]!=5) dir = 1;
			if (grid[x-1][y]!=5) dir = 2;
			
			break;
		default:
		
		}
		
		
		return dir;
		
	}
	
	
	public int scanwumpus(int x,int y,int dir)
	{
		// only mark a square as confirmed wumpus location IF it is not confirmed pit location
		// only mark a square as potential wumpus if:
		   // 1. Not a wall
		   // 2. Not a potential pit or confirmed pit
		   // 3. Not a known wumpus
		
		switch (dir)
		{
		case 0:
			if ( (grid[x][y+1]!=4) && (grid[x][y+1]!=5)) 
			{
				grid[x][y+1]=6;
			    wumpus_detected = true;
			}
			else if ( (grid[x+1][y]!=4) && (grid[x+1][y]!=5))
			{
				grid[x+1][y]=6;
				wumpus_detected = true;
			}
			else if ((grid[x-1][y]!=4) && (grid[x-1][y]!=5)) 
				{grid[x-1][y]=6;
				wumpus_detected = true;
				}
			
			
			else if (grid[x][y+1]!=8) grid[x][y+1]=4;
			else if (grid[x+1][y]!=8) grid[x+1][y]=4;
			else if (grid[x-1][y]!=8) grid[x-1][y]=4;
			
			 if (grid[x][y+1]!=6) dir=1;
			 if (grid[x+1][y]!=6) dir=2;
			 if (grid[x-1][y]!=6) dir=3;
			
			 
			 
			break;
		case 1:
			
			if ((grid[x+1][y]!=4) && (grid[x+1][y]!=5)) 
				{grid[x+1][y]=6;
				wumpus_detected = true;
				}
			else if ((grid[x][y-1]!=4) && (grid[x][y-1]!=5)) 
				{grid[x][y-1]=6;
				wumpus_detected = true;
				}
			else if ((grid[x][y+1]!=4) && (grid[x][y+1]!=5)) 
				{grid[x][y+1]=6;
				wumpus_detected = true;
				}
				
			else if ((grid[x+1][y]!=8) && (grid[x][y+1]!=5)) grid[x+1][y]=4;
			else if ((grid[x][y-1]!=8) && (grid[x][y-1]!=5))grid[x][y-1]=4;
			else if ((grid[x][y+1]!=8) && (grid[x][y+1]!=5)) grid[x][y+1]=4;
			
			 if (grid[x+1][y]!=6) dir=0;
			 if (grid[x][y-1]!=6) dir=2;
			 if (grid[x][y+1]!=6) dir=3;
			
			break;
		case 2:
			
			if ((grid[x+1][y]!=4) && (grid[x+1][y]!=5))
				{grid[x+1][y]=6;
				wumpus_detected = true;
				}
			else if ((grid[x][y-1]!=4) && (grid[x][y-11]!=5)) 
				{grid[x][y-1]=6;
				wumpus_detected = true;
				}
			else if ((grid[x-1][y]!=4) && (grid[x-1][y]!=5)) 
				{grid[x-1][y]=6;
				wumpus_detected = true;
				}
			
			else if ((grid[x+1][y]!=8) && (grid[x+1][y]!=5))grid[x+1][y]=4;
			else if ((grid[x][y-1]!=8) && (grid[x][y-11]!=5))grid[x][y-1]=4;
			else if ((grid[x-1][y]!=8) && (grid[x-1][y]!=5))grid[x-1][y]=4;
			
			 if (grid[x+1][y]!=6) dir = 0;
			 if (grid[x][y-1]!=6) dir = 1;
			 if (grid[x-1][y]!=6) dir = 3;
			
			break;
		case 3:
			
			if ( (grid[x][y+1]!=4) && (grid[x][y+1]!=5)) 
				{grid[x][y+1]=6;
				wumpus_detected = true;
				}
			else if ( (grid[x][y-1]!=4) && (grid[x][y-1]!=5)) 
				{grid[x][y-1]=6;
				wumpus_detected = true;
				}
			else if ( (grid[x-1][y]!=4) && (grid[x-1][y]!=5)) 
				{grid[x-1][y]=6;
				wumpus_detected = true;
				}
			
			else if ( (grid[x][y+1]!=8) && (grid[x][y+1]!=5)) grid[x][y+1]=4;
			else if ( (grid[x][y-1]!=8) && (grid[x][y-1]!=5)) grid[x][y-1]=4;
			else if ( (grid[x-1][y]!=8) && (grid[x-1][y]!=5)) grid[x-1][y]=4;
			
			if (grid[x][y+1]!=6) dir = 0;
			if (grid[x][y-1]!=6) dir = 1;
			if (grid[x-1][y]!=6) dir = 2;
			
			break;
		default:
		
		}
		
		
		return dir;
		
	}
	
}




