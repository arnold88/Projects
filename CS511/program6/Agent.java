/*
 * Class that defines the agent.
 *
 * Written by James P. Biagioni (jbiagi1@uic.edu)
 * for CS511 Artificial Intelligence II
 * at The University of Illinois at Chicago
 *
 * Last modified 3/5/07
 *
 * DISCLAIMER:
 * Elements of this application were borrowed from
 * the client-server implementation of the Wumpus
 * World Simulator written by Kruti Mehta at
 * The University of Texas at Arlington.
 *
 */

import java.util.Random;

class Agent {

	private boolean nonDeterministicMode;
	public double[] underlyingChaos;

	private int[] location;
	private char direction;
	private char agentIcon;

	private int numArrows = 1;
	private int worldHeight;
	private int worldWidth;

	private boolean isDead;
	private boolean hasGold;

	private Environment wumpusWorld;
	private TransferPercept percept;
	private AgentFunction agentFunction;

	public Agent(Environment world, TransferPercept perceptTrans, boolean nonDeterministic, double[] nondeterministicBehavior) {

		// set deterministic/non-deterministic
		nonDeterministicMode = nonDeterministic;
		underlyingChaos = new double[4];
		for(int k=0; k<4; ++k)
		{
			underlyingChaos[k]=nondeterministicBehavior[k];
		}

		// initial conditions
		isDead = false;
		hasGold = false;

		wumpusWorld = world;
		worldHeight = wumpusWorld.getWorldHeight();
		worldWidth = wumpusWorld.getWorldWidth();

		agentFunction = new AgentFunction();
		percept = perceptTrans;


		// initial location
		location = wumpusWorld.getAgentLocation();
		direction = wumpusWorld.getAgentDirection();
		setDirection(direction);
	}

	public void reset(Environment world, TransferPercept perceptTrans)
	{	//this should be clean enough

		isDead = false;
		hasGold = false;
		wumpusWorld = world;
		worldHeight = wumpusWorld.getWorldHeight();
		worldWidth = wumpusWorld.getWorldWidth();
		percept = perceptTrans;

		location = wumpusWorld.getAgentLocation();
		direction = wumpusWorld.getAgentDirection();
		setDirection(direction);

	//	agentFunction.reset();
	}

/*	public void updateValues(double end_Reward, TransferPercept Terminal_State)
	{
		agentFunction.updateValues(end_Reward, Terminal_State);
	}*/

	public void setIsDead(boolean dead) {
		isDead = dead;
	}

	public boolean getIsDead() {
		return isDead;
	}

	public void setHasGold(boolean possessGold) {
		hasGold = possessGold;
	}

	public boolean getHasGold() {
		return hasGold;
	}

	public String getName() {
		return agentFunction.getAgentName();
	}

	public void printStateDiagram() {
		agentFunction.printStateDiagram();
	}

	public int chooseAction() {
		return agentFunction.process(percept);
	}

	public void terminate() {
		agentFunction.terminate(percept);
	}

	public char getAgentIcon() {
		return agentIcon;
	}

	public void goNorth() {
		while(direction!='N') {
			turnRight();
		}
		goForward();
	}

	public void goEast() {
		while(direction!='E') {
			turnRight();
		}
		goForward();
	}

	public void goSouth() {
		while(direction!='S') {
			turnRight();
		}
		goForward();
	}

	public void goWest() {
		while(direction!='W') {
			turnLeft();
		}
		goForward();
	}


	public void goForward() {	//For arbitrary mazes, make better collision detection

		if (nonDeterministicMode == false) {

			if (direction == 'N') {
				if (!((location[0]==0) && (location[1]==1)) && location[0]+1 < worldHeight) location[0] += 1;
				else wumpusWorld.setBump(true);
			}
			else if (direction == 'E') {
				if (!((location[0]==1) && (location[1]==0)) && location[1]+1 < worldWidth) location[1] += 1;
				else wumpusWorld.setBump(true);
			}
			else if (direction == 'S') {
				if (!((location[0]==2) && (location[1]==1)) && location[0]-1 >= 0) location[0] -= 1;
				else wumpusWorld.setBump(true);
			}
			else if (direction == 'W') {
				if (!((location[0]==1) && (location[1]==2)) && location[1]-1 >= 0) location[1] -= 1;
				else wumpusWorld.setBump(true);
			}
		}
		else {

			char moveDirection = nonDeterministicMove();

			if (direction == 'N') {

				if (moveDirection == 'F') {
					if (!((location[0]==0) && (location[1]==1)) && location[0]+1 < worldHeight) location[0] += 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'L') {
					if (!((location[0]==1) && (location[1]==2)) && location[1]-1 >= 0) location[1] -= 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'R') {
					if (!((location[0]==1) && (location[1]==0)) && location[1]+1 < worldWidth) location[1] += 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'B') {
					if (!((location[0]==2) && (location[1]==1)) && location[0]-1 >= 0) location[0] -= 1;
					else wumpusWorld.setBump(true);
				}
			}
			else if (direction == 'E') {

				if (moveDirection == 'F') {
					if (!((location[0]==1) && (location[1]==0)) && location[1]+1 < worldWidth) location[1] += 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'L') {
					if (!((location[0]==0) && (location[1]==1)) && location[0]+1 < worldHeight) location[0] += 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'R') {
					if (!((location[0]==2) && (location[1]==1)) && location[0]-1 >= 0) location[0] -= 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'B') {
					if (!((location[0]==1) && (location[1]==2)) && location[1]-1 >= 0) location[1] -= 1;
					else wumpusWorld.setBump(true);
				}
			}
			else if (direction == 'S') {

				if (moveDirection == 'F') {
					if (!((location[0]==2) && (location[1]==1)) && location[0]-1 >= 0) location[0] -= 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'L') {
					if (!((location[0]==1) && (location[1]==0)) && location[1]+1 < worldWidth) location[1] += 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'R') {
					if (!((location[0]==1) && (location[1]==2)) && location[1]-1 >= 0) location[1] -= 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'B') {
					if (!((location[0]==0) && (location[1]==1)) && location[0]+1 < worldHeight) location[0] += 1;
					else wumpusWorld.setBump(true);
				}
			}
			else if (direction == 'W') {

				if (moveDirection == 'F') {
					if (!((location[0]==1) && (location[1]==2)) && location[1]-1 >= 0) location[1] -= 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'L') {
					if (!((location[0]==2) && (location[1]==1)) && location[0]-1 >= 0) location[0] -= 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'R') {
					if (!((location[0]==0) && (location[1]==1)) && location[0]+1 < worldHeight) location[0] += 1;
					else wumpusWorld.setBump(true);
				}
				else if (moveDirection == 'B') {
					if (!((location[0]==1) && (location[1]==0)) && location[1]+1 < worldWidth) location[1] += 1;
					else wumpusWorld.setBump(true);
				}
			}
		}
	}

	///  TTTTTTTT	HH		HH	IIIIIIIIII	SSSSSSS
	///		TT		HHHHHHHHHH		II		  SS
	///		TT		HH		HH	IIIIIIIIII	SSSSSSS
	///				  AREA IS MY DOMAIN
	private char nonDeterministicMove() {	// SEAN DECIDES WHAT TO DO HERE (PROBABLY COMMAND LINE PARAMETERS)

		Random rand = new Random();
		char moveDir = 'F';
		double value = rand.nextDouble();

		if(value < underlyingChaos[0])
		{
			return 'F';
		}
		else if(value < underlyingChaos[0]+underlyingChaos[1])
		{
			return 'R';
		}
		else if(value < underlyingChaos[0]+underlyingChaos[1]+underlyingChaos[2])
		{
			return 'B';
		}
		else
		{
			return 'L';
		}
	}

	public boolean shootArrow() {

		if (numArrows == 1) {
			numArrows -= 1;
			return true;
		}
		else {
			return false;
		}

	}

	public void turnRight() {

		if (direction == 'N') setDirection('E');
		else if (direction == 'E') setDirection('S');
		else if (direction == 'S') setDirection('W');
		else if (direction == 'W') setDirection('N');

	}

	public void turnLeft() {

		if (direction == 'N') setDirection('W');
		else if (direction == 'E') setDirection('N');
		else if (direction == 'S') setDirection('E');
		else if (direction == 'W') setDirection('S');

	}

	public void setDirection(char newDirection) {
		direction = newDirection;

		if (direction == 'N') agentIcon = 'A';
		if (direction == 'E') agentIcon = '>';
		if (direction == 'S') agentIcon = 'V';
		if (direction == 'W') agentIcon = '<';

	}

	public char getDirection() {
		return direction;
	}

	public void setLocation(int[] newLocation) {
		location[0] = newLocation[0];
		location[1] = newLocation[1];
	}

	public int[] getLocation() {
		return location;
	}

}