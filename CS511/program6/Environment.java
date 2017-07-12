/*
 * Class that defines the environment.
 * 
 * Written by James P. Biagioni (jbiagi1@uic.edu)
 * for CS511 Artificial Intelligence II
 * at The University of Illinois at Chicago
 * 
 * Last modified 4/14/08 
 * 
 * DISCLAIMER:
 * Elements of this application were borrowed from
 * the client-server implementation of the Wumpus
 * World Simulator written by Kruti Mehta at
 * The University of Texas at Arlington.
 * 
 */

//import java.io.BufferedWriter;

class Environment {
	
	private char[][][] wumpusWorld;
	private char[][][] percepts;	
	private int worldHeight;
	private int worldWidth;
	private String bar;
	
	private Agent agent;
	//private BufferedWriter outputWriter;
	
	private int[] prevAgentPosition;
	private boolean bump;
	private boolean scream;
	private double lastReward;
	
	
	public Environment(int height, int width, char[][][] world) { //, BufferedWriter outWriter) {
	
		worldHeight = height;
		worldWidth = width;
		
		wumpusWorld = new char[worldHeight][worldWidth][4];
		percepts = new char[worldHeight][worldWidth][4];
		//outputWriter = outWriter;
		
		prevAgentPosition = getAgentLocation();
		
		bump = false;
		scream = false;
		lastReward = 0;
		
		// store world definition
		for (int i = 0; i < worldHeight; i++) {
			for (int j = 0; j < worldWidth; j++) {
				for (int k = 0; k < 4; k++) {
					wumpusWorld[i][j][k] = world[i][j][k];	
				}
			}
		}
		
		// initialize percept map
		for (int i = 0; i < worldHeight; i++) {
			for (int j = 0; j < worldWidth; j++) {
				for (int k = 0; k < 4; k++) {
					percepts[i][j][k] = ' ';
				}
			}
		}
		
		setPerceptMap();
		
		// initialize bar to the empty string
		bar = "";
		
		// create divider bar for display output
		for (int i = 0; i < (worldWidth * 5) + worldWidth - 1; i++) {
			bar = bar + "-";
		}
				
	}

	public int getWorldHeight() {
		return worldHeight;
	}
	
	public int getWorldWidth() {
		return worldWidth;
	}
	
	public char getAgentDirection() {
		
		for (int i = 0; i < worldHeight; i++) {
			for (int j = 0; j < worldWidth; j++) {
				if (wumpusWorld[i][j][3] == 'A') return 'N';
				if (wumpusWorld[i][j][3] == '>') return 'E';
				if (wumpusWorld[i][j][3] == 'V') return 'S';
				if (wumpusWorld[i][j][3] == '<') return 'W';
			}
		}
		
		return '@';
	}
	
	public int[] getAgentLocation() {
		
		int[] agentPos = new int[2];
		
		for (int i = 0; i < worldHeight; i++) {
			for (int j = 0; j < worldWidth; j++) {
				if (wumpusWorld[i][j][3] != ' ') {
					agentPos[0] = i;
					agentPos[1] = j;
				}
			}
		}
		
		return agentPos;		
	}
	
	public void setLastReward(double r)
	{
		lastReward = r;
	}
	
	public double getLastReward()
	{
		return lastReward;
	}
	
	public void placeAgent(Agent theAgent) {
		
		wumpusWorld[prevAgentPosition[0]][prevAgentPosition[1]][3] = ' ';
		
		agent = theAgent;		
		wumpusWorld[agent.getLocation()[0]][agent.getLocation()[1]][3] = agent.getAgentIcon();
		
		prevAgentPosition[0] = agent.getLocation()[0];
		prevAgentPosition[1] = agent.getLocation()[1];
		
	}
	
	public void setBump(boolean bumped) {
		bump = bumped;
	}
	
	public boolean getBump() {
		return bump;
	}
	
	public void setScream(boolean screamed) {
		scream = screamed;
	}
	
	public boolean getScream() {
		return scream;
	}
	
	public boolean getBreeze() {
		
		if (percepts[agent.getLocation()[0]][agent.getLocation()[1]][0] == 'B') return true;
		else return false;
		
	}
	
	public boolean getStench() {
		
		if (percepts[agent.getLocation()[0]][agent.getLocation()[1]][1] == 'S') return true;
		else return false;
		
	}
	
	public boolean getGlitter() {
		
		if (percepts[agent.getLocation()[0]][agent.getLocation()[1]][2] == 'G') return true;
		else return false;
		
	}

	public boolean grabGold() {
		
		if (percepts[agent.getLocation()[0]][agent.getLocation()[1]][2] == 'G') {
			percepts[agent.getLocation()[0]][agent.getLocation()[1]][2] = ' ';
			wumpusWorld[agent.getLocation()[0]][agent.getLocation()[1]][2] = ' ';
			return true;
		}
		return false;
		
	}
	
	public boolean checkDeath() {
		
		if (wumpusWorld[agent.getLocation()[0]][agent.getLocation()[1]][0] == 'P') return true;
		else if (wumpusWorld[agent.getLocation()[0]][agent.getLocation()[1]][1] == 'W') return true;
		
		return false;
		
	}
	
	public boolean checkWin() {
	
		return this.getGlitter();

	}
	
	public boolean shootArrow() {
		
		if (agent.getDirection() == 'N') {
			
			for (int i = agent.getLocation()[0]; i < worldHeight; i++) {
				if (wumpusWorld[i][agent.getLocation()[1]][1] == 'W') {
					wumpusWorld[i][agent.getLocation()[1]][1] = '*';
					
					int x = i;
					int y = agent.getLocation()[1];
					
					if (x-1 >= 0) percepts[x-1][y][1] = ' ';
					if (x+1 < worldHeight) percepts[x+1][y][1] = ' ';
					if (y-1 >= 0) percepts[x][y-1][1] = ' ';
					if (y+1 < worldWidth) percepts[x][y+1][1] = ' '; 
					
					//printPercepts();
					
					return true;
				}
			}
		}
		else if (agent.getDirection() == 'E') {
			
			for (int i = agent.getLocation()[1]; i < worldWidth; i++) {
				if (wumpusWorld[agent.getLocation()[0]][i][1] == 'W') {
					wumpusWorld[agent.getLocation()[0]][i][1] = '*';
					
					int x = agent.getLocation()[0];
					int y = i;
					
					if (x-1 >= 0) percepts[x-1][y][1] = ' ';
					if (x+1 < worldHeight) percepts[x+1][y][1] = ' ';
					if (y-1 >= 0) percepts[x][y-1][1] = ' ';
					if (y+1 < worldWidth) percepts[x][y+1][1] = ' '; 
								
					//printPercepts();
					
					return true;
				}
			}
		}
		else if (agent.getDirection() == 'S') {
			
			for (int i = agent.getLocation()[0]; i >= 0; i--) {
				if (wumpusWorld[i][agent.getLocation()[1]][1] == 'W') {
					wumpusWorld[i][agent.getLocation()[1]][1] = '*';
					
					int x = i;
					int y = agent.getLocation()[1];
					
					if (x-1 >= 0) percepts[x-1][y][1] = ' ';
					if (x+1 < worldHeight) percepts[x+1][y][1] = ' ';
					if (y-1 >= 0) percepts[x][y-1][1] = ' ';
					if (y+1 < worldWidth) percepts[x][y+1][1] = ' '; 
					
					//printPercepts();
					
					return true;
				}
			}
		}
		else if (agent.getDirection() == 'W') {
			
			for (int i = agent.getLocation()[1]; i >= 0; i--) {
				if (wumpusWorld[agent.getLocation()[0]][i][1] == 'W') {
					wumpusWorld[agent.getLocation()[0]][i][1] = '*';
					
					int x = agent.getLocation()[0];
					int y = i;
					
					if (x-1 >= 0) percepts[x-1][y][1] = ' ';
					if (x+1 < worldHeight) percepts[x+1][y][1] = ' ';
					if (y-1 >= 0) percepts[x][y-1][1] = ' ';
					if (y+1 < worldWidth) percepts[x][y+1][1] = ' '; 
			
					//printPercepts();
					
					return true;
				}
			}			
		}
		
		return false;
		
	}
	
	public void setPerceptMap() {
		
		// World: Pit,Wumpus,Gold,Agent
		// Percepts: Breeze,Stench,Glitter,Scream
		
		for (int i = 0; i < worldHeight; i++) {
			for (int j = 0; j < worldWidth; j++) {
				for (int k = 0; k < 4; k++) {
										
					if (wumpusWorld[i][j][k] == 'P') {
						if (j-1 >= 0) percepts[i][j-1][k] = 'B';
						if (i+1 < worldHeight) percepts[i+1][j][k] = 'B';
						if (j+1 < worldWidth) percepts[i][j+1][k] = 'B';
						if (i-1 >= 0) percepts[i-1][j][k] = 'B';
					}
					else if (wumpusWorld[i][j][k] == 'W') {
						if (j-1 >= 0) percepts[i][j-1][k] = 'S';
						if (i+1 < worldHeight) percepts[i+1][j][k] = 'S';
						if (j+1 < worldWidth) percepts[i][j+1][k] = 'S';
						if (i-1 >= 0) percepts[i-1][j][k] = 'S';
					}
					else if (wumpusWorld[i][j][k] == 'G') percepts[i][j][k] = 'G';
					
				}
			}
		}	
	}
	
	public void printPercepts() {
		
		//System.out.println(" -----------------------");
		System.out.println(" " + bar);
		
		for (int i = worldHeight-1; i > -1; i--) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < worldWidth; k++) {
					
					if (j == 0) {
						System.out.print("| " + percepts[i][k][0] + " " + percepts[i][k][1] + " ");	
					}
					else {
						System.out.print("| " + percepts[i][k][2] + " " + percepts[i][k][3] + " ");
					}
					
					if (k == worldWidth-1) {
						System.out.print("|");
					}
					
				}
				System.out.print("\n");
			}
			//System.out.println(" -----------------------");
			System.out.println(" " + bar);
		}
		System.out.print("\n");
		
	}
	
	public void printEnvironment() {
		
		//   -----------------------
		//  | P W | P W | P W | P W |
 		//  | G A | G A | G A | G A |
		//   -----------------------
		//  | P W | P W | P W | P W |
 		//  | G A | G A | G A | G A |
		//   -----------------------
		//  | P W | P W | P W | P W |
 		//  | G A | G A | G A | G A |
		//   ----------------------- 23
		//  | P W | P W | P W | P W | A A |
 		//  | G A | G A | G A | G A | A A |
		//   ----------------------------- 29
		//
		// P,W,G,A

		try {
			
			//System.out.println("\n -----------------------");
			//outputWriter.write("\n -----------------------" + "\n");
			
			System.out.println("\n " + bar);
			//outputWriter.write("\n " + bar + "\n");
			
			for (int i = worldHeight-1; i > -1; i--) {
				for (int j = 0; j < 2; j++) {
					for (int k = 0; k < worldWidth; k++) {
						
						if (j == 0) {
							System.out.print("| " + wumpusWorld[i][k][0] + " " + wumpusWorld[i][k][1] + " ");
							//outputWriter.write("| " + wumpusWorld[i][k][0] + " " + wumpusWorld[i][k][1] + " ");
						}
						else {
							System.out.print("| " + wumpusWorld[i][k][2] + " " + wumpusWorld[i][k][3] + " ");
							//outputWriter.write("| " + wumpusWorld[i][k][2] + " " + wumpusWorld[i][k][3] + " ");
						}
						
						if (k == worldWidth-1) {
							System.out.print("|");
							//outputWriter.write("|");
						}
						
					}
					System.out.print("\n");
					//outputWriter.write("\n");
				}
				//System.out.println(" -----------------------");
				//outputWriter.write(" -----------------------" + "\n");
				
				System.out.println(" " + bar);
				//outputWriter.write(" " + bar + "\n");
			}
			System.out.print("\n");
			//outputWriter.write("\n");
		}
		catch (Exception e) {
			System.out.println("An exception was thrown: " + e);
			e.printStackTrace();
		}
	}
}