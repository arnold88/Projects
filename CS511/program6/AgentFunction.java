/*
 * Class that defines the agent function.
 *
 * Written by James P. Biagioni (jbiagi1@uic.edu)
 * for CS511 Artificial Intelligence II
 * at The University of Illinois at Chicago
 *
 * Last modified 2/19/07
 *
 * DISCLAIMER:
 * Elements of this application were borrowed from
 * the client-server implementation of the Wumpus
 * World Simulator written by Kruti Mehta at
 * The University of Texas at Arlington.
 *
 */

import java.util.Random;

class AgentFunction {

	// string to store the agent's name
	// do not remove this variable
	private String agentName = "Agent Smith";

	// all of these variables are created and used
	// for illustration purposes; you may delete them
	// when implementing your own intelligent agent
	private int[] actionTable;
	private int[] location;
	private Random rand;
	private double[] UPlus;
	private int[][] State_Action_Counts;
	private int[][][] Transition_Matrix_Count;
	private double[][][] Transition_Matrix;

	private int Board_Width = 4;
	private int Board_Height = 3;
	private int curr_state;
	private int[] curr_location;
	private int curr_action;
	private double curr_reward;
	private int prev_action;
	private int prev_state;
	private int[] prev_location;
	private double prev_reward;
	private double discount_factor = 1;

	public AgentFunction()
	{
		// for illustration purposes; you may delete all code
		// inside this constructor when implementing your
		// own intelligent agent
		actionTable = new int[4];

		actionTable[0] = Action.GO_NORTH;
		actionTable[1] = Action.GO_EAST;
		actionTable[2] = Action.GO_SOUTH;
		actionTable[3] = Action.GO_WEST;

		Board_Height = 3;
		Board_Width = 4;
		UPlus = new double[3*4];
		for(int k = 0; k<UPlus.length; ++k)
		{	UPlus[k]=2.0;	}
		State_Action_Counts = new int[Board_Height*Board_Width][4];
		Transition_Matrix_Count = new int[Board_Height*Board_Width][4][Board_Height*Board_Width];
		Transition_Matrix = new double[Board_Height*Board_Width][4][Board_Height*Board_Width];
		discount_factor = 1;

		prev_state = 0;

		// new random number generator, for
		// randomly picking actions to execute
		rand = new Random();
	}

	public double f(double d, int a){
		if(a>5)
		{	return d;	}
		return 2.0;
	}

	public int state(int height, int width)
	{	return height*Board_Width + width;	}

	public int state(int[] loc)
	{	return loc[0]*Board_Width + loc[1];	}

	public int process(TransferPercept tp)
	{
		// To build your own intelligent agent, replace
		// all code below this comment block. You have
		// access to all percepts through the object
		// 'tp' as illustrated here:

		// read in the current percepts
		curr_location = tp.getAgentLocation();
		curr_state = state(curr_location);
		curr_reward = tp.getReward();

		// Update Transition Probabilities
		State_Action_Counts[prev_state][prev_action]++;
		Transition_Matrix_Count[prev_state][prev_action][curr_state]++;
		Transition_Matrix = Normalize(Transition_Matrix_Count);

		prev_location = curr_location;
		prev_state = curr_state;
		prev_reward = curr_reward;
		prev_action = actionTable[rand.nextInt(4)];

		// return action to be performed
	    return prev_action;
	}

	// When you reach a terminal state, this function will be called.
	// The reward will be either +1.0 or -1.0, depending on which location you landed in.
	public void terminate(TransferPercept tp)
	{
		// read in the current percepts
		curr_location = tp.getAgentLocation();
		curr_state = state(curr_location);
		curr_reward = tp.getReward();
	}

	// This method will take a 3D array of function counts, and return a 3D array of function probabilities
	//  You will likely find it useful for generating p(s'|s,a) from the counts of action movements
	//  As given, the method prevents 0 probability transitions, which may not be accurate for your environment
	//  Modify it as you please.
	public double[][][] Normalize(int[][][] I)
	{
		double[][][] D = new double[I.length][I[0].length][I[0][0].length];

		for(int a=0; a<I.length; ++a)
		{
			for(int b=0; b<I[a].length; ++b)
			{
				double sum = 0;
				for(int c : I[a][b])
				{
					sum += c;
				}
				for(int c = 0; c<I[a][b].length; ++c)
				{

					//if(I[a][b][c]>0){		// This commented out section gives you 0 probability for unvisited states,
					//D[a][b][c] = ((double) I[a][b][c])/(sum);		// but you need to be careful about sum being 0
					//}												// Thus the condition "such that Ns'|sa[t,s,a] is nonzero" in figure 21.2
					//else{D[a][b][c] = 0;}
					D[a][b][c] = ((double) I[a][b][c]+(1.0/((double) I[a][b].length)))/(sum+1);
				}
			}
		}
		return D;
	}

	// public method to return the agent's name
	// do not remove this method
	public String getAgentName() {
		return agentName;
	}

	// printStateDiagram is a method called at the end of the program, so you can print agent internals for debugging purposes
	// When you submit this project, it should output the utility value associated with each state and the recommended policy in the format given here.
	public void printStateDiagram()
	{
		try{
		int loc;
		double tempUtil;
		double[] maxUtil = new double[4];
		int[] maxAction = new int[Board_Width*Board_Height];

		System.out.println();
		System.out.println("-------------Utility of each state-----------------------------------------------------");
		//outputWriter.write("\n");
		//outputWriter.write("-------------Utility of each state-----------------------------------------------------\n");
		for(int y = 2; y>=0; --y)
		{
			for(int x = 0; x<4; ++x)
			{
				loc = x+4*y;
				tempUtil = UPlus[loc];
				maxAction[loc] = rand.nextInt(4);
				System.out.print(" | " + tempUtil);
				//outputWriter.write(" | " + tempUtil);
			}
			System.out.println(" | ");
			//outputWriter.write(" | \n");
			System.out.println("------------------------------------------------------------------------------");
			//outputWriter.write("------------------------------------------------------------------------------\n");
		}


		System.out.println();
		System.out.println("-------------Optimal Policy-----------------------------------------------------");
		//outputWriter.write("\n");
		//outputWriter.write("-------------Optimal Policy-----------------------------------------------------\n");

		String pS = "";
		for(int y = 2; y>=0; --y)
		{
			for(int x = 0; x<4; ++x)
			{
				loc = x+4*y;
				switch(maxAction[loc])
				{
					case 0: pS = "A"; break;
					case 1: pS = ">"; break;
					case 2: pS = "V"; break;
					case 3: pS = "<"; break;
					default: pS = "LOSS"; break;
				}

				System.out.print(" | " + pS);
				//outputWriter.write(" | " + pS);
			}
			System.out.println(" | ");
			System.out.println("-----------------------------------------");
			//outputWriter.write(" | ");
			//outputWriter.write("\n-----------------------------------------\n");

		}

/*	For debugging purposes
		System.out.println("-------------STATE VALUES-----------------");
		for(int a = 0; a<UPlus.length; ++a)
		{
			System.out.println(a+": \t " + UPlus[a]);
		}

		System.out.println();
		System.out.println("-------------TRANSITION MATRIX COUNTS-----------------");
		for(int a = 0; a<Transition_Matrix_Count.length; ++a)
		{
			System.out.print("S "+a + ":");
			for(int b = 0; b<Transition_Matrix_Count[0].length; ++b)
			{
				System.out.println("\t A "+b);
				for(int c = 0; c<Transition_Matrix_Count[0][0].length; ++c)
				{
					System.out.println("S' "+c+": \t " + Transition_Matrix_Count[a][b][c]);
				}
				System.out.println();
			}
		}

		System.out.println();
		System.out.println("-------------TRANSITION MATRIX-----------------");
		for(int a = 0; a<Transition_Matrix.length; ++a)
		{
			System.out.print("S "+a + ":");
			for(int b = 0; b<Transition_Matrix[0].length; ++b)
			{
				System.out.println("\t A "+b);
				for(int c = 0; c<Transition_Matrix[0][0].length; ++c)
				{
					System.out.println("S' "+c+": \t " + Transition_Matrix[a][b][c]);
				}
				System.out.println();
			}
		}*/

		}
		catch(Exception e)
		{e.printStackTrace();}
	}

	// If you are updating utilities as you go, a function such as this may be handy.
	public void updateUValues(int prev_state, int prev_action, int curr_state, double prev_reward)
	{
		UPlus[curr_state] = prev_reward;	// this is not correct.
	}

}