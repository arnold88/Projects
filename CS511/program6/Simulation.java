/*
 * Class that defines the simulation environment.
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

class Simulation {

	private double currScore = 0;
	private double prevScore = 0.0;
	private static double actionCost = -0.04;
	private static double goldValue = 1.0;
	private static double deathCost = -1.0;
	private static double shootCost = -9999;
	private int stepCounter = 0;
	private int lastAction = 0;
	private double lastScore = 0.0;
	private boolean verbose = true;

	private boolean simulationRunning;

	private Agent agent;
	private Environment environment;
	private TransferPercept transferPercept;
	//private BufferedWriter outputWriter;

	public Simulation(Environment wumpusEnvironment, int maxSteps, Agent Smith, boolean verbosity) { //, BufferedWriter outWriter, boolean nonDeterministic) {

		// start the simulator
		simulationRunning = true;
		verbose = verbosity;

		//outputWriter = outWriter;
		transferPercept = new TransferPercept(wumpusEnvironment);
		environment = wumpusEnvironment;

		agent = Smith;

		agent.reset(environment, transferPercept);
		environment.placeAgent(agent);
		if(verbose)environment.printEnvironment();

		if(verbose)printCurrentPerceptSequence();

		try {

			if(verbose)System.out.println("Current score: " + currScore);
			//outputWriter.write("Current score: " + currScore + "\n");

			while (simulationRunning == true) { // && stepCounter < maxSteps

				if(verbose)System.out.println("Last action: " + Action.printAction(lastAction));
				if(verbose)System.out.println("Reward: " + (currScore-prevScore));
				//outputWriter.write("Last action: " + Action.printAction(lastAction) + "\n");

				if(verbose)System.out.println("Time step: " + stepCounter);
				//outputWriter.write("Time step: " + stepCounter + "\n");

				if(verbose)System.out.println();

				wumpusEnvironment.setLastReward(currScore-prevScore);
				prevScore = currScore;
				handleAction(agent.chooseAction());
				wumpusEnvironment.placeAgent(agent);

				if(verbose)environment.printEnvironment();
				//printCurrentPerceptSequence();

				if(verbose)System.out.println("Current score: " + currScore);
				//outputWriter.write("Current score: " + currScore + "\n");

				//Scanner in = new Scanner(System.in);
				//in.next();

				stepCounter += 1;

				if (stepCounter == maxSteps || simulationRunning == false) {
					wumpusEnvironment.setLastReward(currScore-prevScore);
					agent.terminate(); //Allow them to see their final reward

					if(verbose)System.out.println("Last action: " + Action.printAction(lastAction));
					//outputWriter.write("Last action: " + Action.printAction(lastAction) + "\n");

					if(verbose)System.out.println("Time step: " + stepCounter);
					//outputWriter.write("Time step: " + stepCounter + "\n");

					lastAction = Action.END_TRIAL;
				}

				if (agent.getHasGold() == true) {
					if(verbose)System.out.println("\n" + agent.getName() + " found the GOLD!!");
					//outputWriter.write("\n" + agent.getName() + " found the GOLD!!\n");
				}
				if (agent.getIsDead() == true) {

					if(verbose)System.out.println("\n" + agent.getName() + " is DEAD!!");
					//outputWriter.write("\n" + agent.getName() + " is DEAD!!\n");
				}

			}

		}
		catch (Exception e) {
			System.out.println("An exception was thrown: " + e);
			e.printStackTrace();
		}

		if(verbose)printEndWorld();

	}

	public void printEndWorld() {

		try {

			environment.printEnvironment();

			System.out.println("Final score: " + currScore);
			//outputWriter.write("Final score: " + currScore + "\n");

			System.out.println("Last action: " + Action.printAction(lastAction));
			//outputWriter.write("Last action: " + Action.printAction(lastAction) + "\n");

		}
		catch (Exception e) {
			System.out.println("An exception was thrown: " + e);
			e.printStackTrace();
		}

	}

	public void printCurrentPerceptSequence() {

		try {

			System.out.print("Percept: <");
			//outputWriter.write("Percept: <");

			if (transferPercept.getBump() == true) {
				System.out.print("bump,");
				//outputWriter.write("bump,");
			}
			else if (transferPercept.getBump() == false) {
				System.out.print("none,");
				//outputWriter.write("none,");
			}
			if (transferPercept.getGlitter() == true) {
				System.out.print("glitter,");
				//outputWriter.write("glitter,");
			}
			else if (transferPercept.getGlitter() == false) {
				System.out.print("none,");
				//outputWriter.write("none,");
			}
			if (transferPercept.getBreeze() == true) {
				System.out.print("breeze,");
				//outputWriter.write("breeze,");
			}
			else if (transferPercept.getBreeze() == false) {
				System.out.print("none,");
				//outputWriter.write("none,");
			}
			if (transferPercept.getStench() == true) {
				System.out.print("stench,");
				//outputWriter.write("stench,");
			}
			else if (transferPercept.getStench() == false) {
				System.out.print("none,");
				//outputWriter.write("none,");
			}
			if (transferPercept.getScream() == true) {
				System.out.print("scream>\n");
				//outputWriter.write("scream>\n");
			}
			else if (transferPercept.getScream() == false) {
				System.out.print("none>\n");
				//outputWriter.write("none>\n");
			}

		}
		catch (Exception e) {
			System.out.println("An exception was thrown: " + e);
			e.printStackTrace();
		}

	}

	public void handleAction(int action) {

		try {

			if (action == Action.GO_NORTH) {
				agent.goNorth();
				environment.placeAgent(agent);

				lastAction = action;
			}

			else if (action == Action.GO_EAST) {
				agent.goEast();
				environment.placeAgent(agent);

				lastAction = action;
			}

			else if (action == Action.GO_SOUTH) {
				agent.goSouth();
				environment.placeAgent(agent);

				lastAction = action;
			}
			else if (action == Action.GO_WEST) {
				agent.goWest();
				environment.placeAgent(agent);

				lastAction = action;
			}

			if (environment.checkDeath() == true) {

				currScore += deathCost;
				simulationRunning = false;

				agent.setIsDead(true);
			}
			else if (environment.checkWin() == true) {

				currScore += goldValue;
				simulationRunning = false;

				agent.setHasGold(true);
			}
			else {
				currScore += actionCost;
			}

		}
		catch (Exception e) {
			System.out.println("An exception was thrown: " + e);
			e.printStackTrace();
		}
	}

	public double getScore() {

		return currScore;

	}

}