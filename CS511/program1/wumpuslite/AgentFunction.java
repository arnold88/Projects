

/* Agent Function written by Arnold Lee
 *  alee29@uic.edu
 *   for CS511 Artificial Intelligence II
 * at The University of Illinois at Chicago
 * 
 *   Last updated January 24th, 2012 
 */

import java.util.Random;

class AgentFunction {
	
	// string to store the agent's name
	// do not remove this variable
	private String agentName = "NewAge2012";
	
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

	
	private int [][] field  = new int [11][11];
	//field indicator:
	// 0 = boundary
	// 1 = breeze detected
	// 2 = stench detected
	// 3 = potential pit
	// 4 = potential wumpus
	// 5 = confirmed pit
	// 6 = confirmed wumpus
	// 7 = clean room
	// 9 = undiscovered room
	
	
	private int x = 6;
	private int y = 6;
	
	private int decision=0;
	private boolean previous_bump=false;
	private boolean previous_stench=false;
	private boolean previous_breeze=false;

	private int dir_indicator = 0;
	private boolean repeat=false;
	private boolean wumpus_dead = false;
	
	public AgentFunction()
	{
		// for illustration purposes; you may delete all code
		// inside this constructor when implementing your 
		// own intelligent agent

		// this integer array will store the agent actions
		actionTable = new int[8];
				  
		actionTable[0] = Action.GO_FORWARD;
		actionTable[1] = Action.GO_FORWARD;
		actionTable[2] = Action.GO_FORWARD;
		actionTable[3] = Action.GO_FORWARD;
		actionTable[4] = Action.TURN_RIGHT;
		actionTable[5] = Action.TURN_LEFT;
		actionTable[6] = Action.GRAB;
		actionTable[7] = Action.SHOOT;
		
		for (int i=0;i<11;i++)
			for (int j=0;j<11;j++)
				field[i][j] = 9;
		
		
		
		//initialize
		repeat = false;
		field [5][5]=7; // assume at center
		x = 5;
		y = 5;
		
		// new random number generator, for
		// randomly picking actions to execute
		rand = new Random();
		
	}

	public int process(TransferPercept tp)
	{
		// To build your own intelligent agent, replace
		// all code below this comment block. You have
		// access to all percepts through the object
		// 'tp' as illustrated here:
		
		
		
		// read in the current percepts
		bump = tp.getBump();
		glitter = tp.getGlitter();
		breeze = tp.getBreeze();
		stench = tp.getStench();
		scream = tp.getScream();
		
		// if previous action needs to be repeated one more time
		// only used if need to turn opposite direction
		if (repeat == true)
		{
		    repeat = false;
		    dir_indicator = (dir_indicator+2) % 4;
			return actionTable[decision];
		}
		
		if (bump == true || glitter == true || breeze == true || stench == true || scream == true)
		{
			if (scream == true)
			{
				wumpus_dead = true;
			}
			
			
			// either one condition exist after going forward
			
			if (glitter == true) // found gold
			{
				decision = 6; 
			} // game over for getting gold
			else // no gold
			{
			   if ((stench == true) && (previous_stench==false) && (wumpus_dead == false)) 
			   {
				   field [x][y] = 2;
				   decision = 4;
				   
				   repeat = true;
				   previous_stench=true;
			   }
			   
			   if ((breeze == true) && (previous_breeze==false))
			   {
				   field [x][y] = 1;
				   decision = 4;
				   repeat = true;
				   previous_breeze = true;
			   }
			   
			   if ((breeze == true) && (stench==true) && (previous_breeze || previous_stench) && (wumpus_dead==false))
			   {
				   field [x+1][y] = 4;
				   field [x][y+1] = 3;
				   
				   decision = 4; 
				   repeat = true;
				     
			   }
			   
			   if ((stench==true)&&(wumpus_dead==false)&& (previous_stench))
			   {
				   field [x+1][y] = 6;
				   decision = 7;
				   
			   }
			   
			   if ((breeze==true)&&(previous_breeze))
			   {
				   field [x+1][y]=5;
				   decision = 4;
				   repeat = true;
			   }
			   
			   if ( (breeze) && (previous_breeze == false))
			   {
				   previous_breeze = true;
				   field [x+1][y] = 3;
				   decision = 5;
				   
			   }
			   
			   if ( (stench) && (previous_stench == false))
			   {
				   previous_stench = true;
				   field [x+1][y] = 3;
				   decision = 5;
				   
			   }
			   
			   
			} // end sub for other condition
			
		}
		else // if no gold and no condition exist - keep walking
		{
			decision = 0;
			
			field [x][y] = 7;
			
			previous_breeze = false;
			previous_stench = false;
			
			switch (dir_indicator)
			{
			case 0:
				y=y+1;
				break;
			case 1:
				x=x+1;
				break;
			case 2:
				y=y-1;
				break;
			case 3:
				x=x-1;
				break;
			default:
				y=y+1;
				dir_indicator = 0;
			}
			
		}
		
		
		// return action to be performed
	    return actionTable[decision];	    
	}
	
	// public method to return the agent's name
	// do not remove this method
	public String getAgentName() {
		return agentName;
	}
}