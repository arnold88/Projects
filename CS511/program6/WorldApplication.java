/*
 * Wumpus-Lite, version 0.21 alpha
 * A lightweight Java-based Wumpus World Simulator
 *
 * Written by James P. Biagioni (jbiagi1@uic.edu)
 * for CS511 Artificial Intelligence II
 * at The University of Illinois at Chicago
 *
 * Thanks to everyone who provided feedback and
 * suggestions for improving this application,
 * especially the students from Professor
 * Gmytrasiewicz's Spring 2007 CS511 class.
 *
 * Last modified 4/20/11 by Sean Deitz
 *
 * DISCLAIMER:
 * Elements of this application were borrowed from
 * the client-server implementation of the Wumpus
 * World Simulator written by Kruti Mehta at
 * The University of Texas at Arlington.
 *
 */


//import java.io.BufferedWriter;
//import java.io.FileWriter;
import java.util.Random;

class WorldApplication {

	private static String VERSION = "v0.21a";

	public static void main (String args[]) {

		int worldWidth = 4;
		int worldHeight = 3;
		int numTrials = 1;
		int numTests = 1;
		int maxSteps = 50;
		double[] nondeterminism = new double[4];
		boolean verbose = false;

		boolean nonDeterministicMode = false;
		boolean randomAgentLoc = false;
		boolean userDefinedSeed = false;

		//String outFilename = "wumpus_out.txt";

	    Random rand = new Random();
	    int seed = rand.nextInt();


		// iterate through command-line parameters
	    for (int i = 0; i < args.length; i++) {

	    	String arg = args[i];

	    	// if the world dimension is specified
	    	if (arg.equals("-d") == true) {

	    		if (Integer.parseInt(args[i+1]) > 1) {

	    			worldHeight = Integer.parseInt(args[i+1]);
					worldWidth = Integer.parseInt(args[i+2]);
	    		}

	    		i++;
	    	}
	    	// if the maximum number of steps is specified
	    	else if (arg.equals("-s") == true) {

	    		maxSteps = Integer.parseInt(args[i+1]);
	    		i++;

	    	}
	    	// if the number of trials is specified
	    	else if (arg.equals("-t") == true) {

	    		numTrials = Integer.parseInt(args[i+1]);
	    		i++;

	    	}
	    	else if (arg.equals("-te") == true) {

	    		numTests = Integer.parseInt(args[i+1]);
	    		i++;

	    	}
	    	// if the random agent location value is specified
	    	else if (arg.equals("-a") == true) {

	    		randomAgentLoc = Boolean.parseBoolean(args[i+1]);
	    		i++;

	    	}
	    	// if the random number seed is specified
	    	else if (arg.equals("-r") == true) {

	    		seed = Integer.parseInt(args[i+1]);
	    		userDefinedSeed = true;
	    		i++;

	    	}
	    	// if the output filename is specified
	    	//else if (arg.equals("-f") == true) {
	    	//
	    	//	outFilename = String.valueOf(args[i+1]);
	    	//	i++;
	    	//
	    	//}
	    	// if the non-determinism is specified
	    	else if (arg.equals("-n") == true) {

	    		nonDeterministicMode = true;
				for(int k = 0; k<4; ++k)
				{
					nondeterminism[k] = Double.parseDouble(args[i+1+k]);
				}
	    		i++;

	    	}
	    	else if (arg.equals("-v") == true) {

	    		verbose = true;
	    		i++;

	    	}

	    }

	    try {

		    //BufferedWriter outputWriter = new BufferedWriter(new FileWriter(outFilename));

			if(verbose)System.out.println("Wumpus-Lite " + VERSION + "\n");
			//outputWriter.write("Wumpus-Lite " + VERSION + "\n\n");

			if(verbose)System.out.println("Dimensions: " + worldHeight + "x" + worldWidth);
		    //outputWriter.write("Dimensions: " + worldSize + "x" + worldSize + "\n");

		    if(verbose)System.out.println("Maximum number of steps: " + maxSteps);
		    //outputWriter.write("Maximum number of steps: " + maxSteps + "\n");

		    if(verbose)System.out.println("Number of trials: " + numTrials);
		    //outputWriter.write("Number of trials: " + numTrials + "\n");

		    if(verbose)System.out.println("Random Agent Location: " + randomAgentLoc);
		    //outputWriter.write("Random Agent Location: " + randomAgentLoc + "\n");

			if(verbose)System.out.println("Random number seed: " + seed);
			//outputWriter.write("Random number seed: " + seed + "\n");

		    //System.out.println("Output filename: " + outFilename);
		    //outputWriter.write("Output filename: " + outFilename + "\n");

		    if(verbose)System.out.println("Non-Deterministic Behavior: " + nonDeterministicMode + "\n");
		    //outputWriter.write("Non-Deterministic Behavior: " + nonDeterministicMode + "\n\n");


		    char[][][] wumpusWorld = generateNormalMazeWorld(seed, worldHeight, worldWidth, randomAgentLoc);
		    Environment wumpusEnvironment = new Environment(worldHeight, worldWidth, wumpusWorld); //, outputWriter);
		    Agent wumpusAgent = new Agent(wumpusEnvironment, new TransferPercept(wumpusEnvironment), nonDeterministicMode, nondeterminism);
		    double trialScores[] = new double[numTrials];
			double testScores[] = new double[numTests];
		    int totalScore = 0;

		    for (int currTrial = 0; currTrial < numTrials; currTrial++) {

		    	Simulation trial = new Simulation(wumpusEnvironment, maxSteps, wumpusAgent, verbose); //, outputWriter, nonDeterministicMode);
		    	trialScores[currTrial] = trial.getScore();

		    	if(verbose)System.out.println("\n\n___________________________________________\n");
		    	//outputWriter.write("\n\n___________________________________________\n\n");

			    if (userDefinedSeed == true) {
			    	wumpusWorld = generateNormalMazeWorld(++seed, worldHeight, worldWidth, randomAgentLoc);
			    }
			    else {
			    	wumpusWorld = generateNormalMazeWorld(rand.nextInt(), worldHeight, worldWidth, randomAgentLoc);
			    }

			    wumpusEnvironment = new Environment(worldHeight, worldWidth, wumpusWorld); //, outputWriter);

		    	System.runFinalization();
		    }

		    for (int i = 0; i < numTrials; i++) {

		    	System.out.println("Trial " + (i+1) + " score: " + trialScores[i]);
		    	//outputWriter.write("Trial " + (i+1) + " score: " + trialScores[i] + "\n");
		    	totalScore += trialScores[i];

		    }

		    for (int i = 0; i < numTests; i++) {

		    	System.out.println("Trial " + (i+1) + " score: " + testScores[i]);
		    	//outputWriter.write("Trial " + (i+1) + " score: " + trialScores[i] + "\n");
		    	totalScore += testScores[i];

		    }

		    System.out.println("\nTotal Score: " + totalScore);
		    //outputWriter.write("\nTotal Score: " + totalScore + "\n");

		    System.out.println("Average Score: " + ((double)totalScore/(double)numTrials));
		    //outputWriter.write("Average Score: " + ((double)totalScore/(double)numTrials) + "\n");


			wumpusAgent.printStateDiagram();
		    //outputWriter.close();

	    }
	    catch (Exception e) {
	    	System.out.println("An exception was thrown: " + e);
			e.printStackTrace();
	    }

	    System.out.println("\nFinished.");
	}

	public static char[][][] generateRandomWumpusWorld(int seed, int height, int width, boolean randomlyPlaceAgent) {

		char[][][] newWorld = new char[height][width][4];
		boolean[][] occupied = new boolean[height][width];

		int x, y;

		Random randGen = new Random(seed);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				for (int k = 0; k < 4; k++) {
					newWorld[i][j][k] = ' ';
				}
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				occupied[i][j] = false;
			}
		}

		int pits = 2;

		// default agent location
		// and orientation
		int agentXLoc = 0;
		int agentYLoc = 0;
		char agentIcon = '>';

		// randomly generate agent
		// location and orientation
		if (randomlyPlaceAgent == true) {

			agentXLoc = randGen.nextInt(height);
			agentYLoc = randGen.nextInt(width);

			switch (randGen.nextInt(4)) {

				case 0: agentIcon = 'A'; break;
				case 1: agentIcon = '>'; break;
				case 2: agentIcon = 'V'; break;
				case 3: agentIcon = '<'; break;
			}
		}

		// place agent in the world
		newWorld[agentXLoc][agentYLoc][3] = agentIcon;

		// Pit generation
		for (int i = 0; i < pits; i++) {

			x = randGen.nextInt(height);
			y = randGen.nextInt(width);

			while ((x == agentXLoc && y == agentYLoc) | occupied[x][y] == true) {
				x = randGen.nextInt(height);
				y = randGen.nextInt(width);
			}

			occupied[x][y] = true;

			newWorld[x][y][0] = 'P';

		}

		// Wumpus Generation
		x = randGen.nextInt(height);
		y = randGen.nextInt(width);

		while (x == agentXLoc && y == agentYLoc) {
			x = randGen.nextInt(height);
			y = randGen.nextInt(width);
		}

		occupied[x][y] = true;

		newWorld[x][y][1] = 'W';

		// Gold Generation
		x = randGen.nextInt(height);
		y = randGen.nextInt(width);

		//while (x == 0 && y == 0) {
		//	x = randGen.nextInt(size);
		//	y = randGen.nextInt(size);
		//}

		occupied[x][y] = true;

		newWorld[x][y][2] = 'G';

		return newWorld;
	}


	public static char[][][] generateNormalMazeWorld(int seed, int height, int width, boolean randomlyPlaceAgent) {

		char[][][] newWorld = new char[height][width][4];
		boolean[][] occupied = new boolean[height][width];

		int x, y;

		Random randGen = new Random(seed);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				for (int k = 0; k < 4; k++) {
					newWorld[i][j][k] = ' ';
				}
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				occupied[i][j] = false;
			}
		}

		// Insert a wall at 2,2
		newWorld[1][1][0]='O';
		occupied[1][1] = true;

		int pits = 0;

		// default agent location
		// and orientation
		int agentXLoc = 0;
		int agentYLoc = 0;
		char agentIcon = '>';

		// randomly generate agent
		// location and orientation
		if (randomlyPlaceAgent == true) {

			agentXLoc = randGen.nextInt(height);
			agentYLoc = randGen.nextInt(width);

			switch (randGen.nextInt(4)) {

				case 0: agentIcon = 'A'; break;
				case 1: agentIcon = '>'; break;
				case 2: agentIcon = 'V'; break;
				case 3: agentIcon = '<'; break;
			}
		}

		// place agent in the world
		newWorld[agentXLoc][agentYLoc][3] = agentIcon;

		// Pit generation
		for (int i = 0; i < pits; i++) {

			x = randGen.nextInt(height);
			y = randGen.nextInt(width);

			while ((x == agentXLoc && y == agentYLoc) | occupied[x][y] == true) {
				x = randGen.nextInt(height);
				y = randGen.nextInt(width);
			}

			occupied[x][y] = true;

			newWorld[x][y][0] = 'P';

		}

		// Wumpus Generation
		//x = randGen.nextInt(size);
		//y = randGen.nextInt(size);
	    x = 1;
		y = 3;

		while (x == agentXLoc && y == agentYLoc) {
			x = randGen.nextInt(height);
			y = randGen.nextInt(width);
		}

		occupied[x][y] = true;

		newWorld[x][y][1] = 'W';

		// Gold Generation
		//x = randGen.nextInt(size);
		//y = randGen.nextInt(size);
	    x = 2;
		y = 3;

		//while (x == 0 && y == 0) {
		//	x = randGen.nextInt(size);
		//	y = randGen.nextInt(size);
		//}

		occupied[x][y] = true;

		newWorld[x][y][2] = 'G';

		return newWorld;
	}


}