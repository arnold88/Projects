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

class AgentFunction 
 {
    // string to store the agent's name
    // do not remove this variable
    private String agentName = "Shachar";
    private static final int unkown = 0;
    private static final int safe = 1;
    private static final int no = 1;
    private static final int danger = 2;
    private static final int yes = 2;
    private static final int north = 7;
    private static final int east = 1;
    private static final int south = -7;
    private static final int west = -1; 
    
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
    
    //The below comprises the MODEL
    private boolean hasArrow = true;
    private int direction = north;
    private int currPos = 24;
    private MNODE[] model = new MNODE[49];
    //


    public AgentFunction()
    {
        // for illustration purposes; you may delete all code
        // inside this constructor when implementing your 
        // own intelligent agent

        // this integer array will store the agent actions
        
        model = new MNODE[49]; //Every 7 represents a row.  By starting in the 4th position of the 4th row (24), we can move
                               //3 squares in any direction without falling off and while still having wall squares, allowing us to start in any location.
        int count = 0;
        while (count < 49)
        {
          model[count] = new MNODE();
          ++count;
        }
                               
        actionTable = new int[8];
                  
        actionTable[0] = Action.GO_FORWARD;
        actionTable[1] = Action.GO_FORWARD;
        actionTable[2] = Action.GO_FORWARD;
        actionTable[3] = Action.GO_FORWARD;
        actionTable[4] = Action.TURN_RIGHT;
        actionTable[5] = Action.TURN_LEFT;
        actionTable[6] = Action.GRAB;
        actionTable[7] = Action.SHOOT;
        
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
        int count;
        
        
        if (model[currPos] == null)
         {
                       System.out.println("WTF " + currPos);
                       return actionTable[1];
         }
        model[currPos].setSaftey(safe); //If we are in the square and not dead, it is safe.

                    
        if (glitter == true)
        {
            return actionTable[6]; //Game over, you get gold!  In this case nothing else matters.
        }
        
        /////If no glitter, then update the model///////////////////////////////////
        
        if (bump == true)
        {
          currPos = currPos - direction;    
          if((currPos + direction) < 49 && (currPos + direction) > -1)
          {
            model[currPos + direction].setSaftey(danger); //We don't want the agent to try to enter this wall again.
            if(direction == east || direction == west)
              {
                count = currPos + direction;            
                while(count > 7)
                {
                    count = count + south; //if East/west is blocked, then all positions south of that block are also blocked.
                    model[count].setSaftey(danger); //We don't want the agent to try to enter this wall again.
                    if((count - (direction * 5)) < 49 && (count - (direction * 5)) > -1)
                    {
                      model[count - (direction * 5)].setSaftey(danger); //We can also infer where the opposite wall is.
                    }
                }
                count = currPos + direction;
                while(count < 42)
                {
                    count = count + north; //if East/west is blocked, then all positions north of that block are also blocked.
                    model[count].setSaftey(danger); //We don't want the agent to try to enter this wall again. 
                    if((count - (direction * 5)) < 49 && (count - (direction * 5)) > -1)
                    {
                      model[count - (direction * 5)].setSaftey(danger); //We can also infer where the opposite wall is.
                    }
                }
              }
            else //Facing south or north
              {
                count = currPos + direction;            
                while(((count + 1) % 7) != 0)
                {
                    count = count + east; //if north/south is blocked, then all positions east of that block are also blocked.
                    model[count].setSaftey(danger); //We don't want the agent to try to enter this wall again.
                    if((count - (direction * 5)) < 49 && (count - (direction * 5)) > -1)
                    {
                      model[count - (direction * 5)].setSaftey(danger); //We can also infer where the opposite wall is.
                    }
                }
                count = currPos + direction;
                while((count % 7) != 0)
                {
                    count = count + west; //if north/south is blocked, then all positions west of that block are also blocked.
                    model[count].setSaftey(danger); //We don't want the agent to try to enter this wall again. 
                    if((count - (direction * 5)) < 49 && (count - (direction * 5)) > -1)
                    {
                      model[count - (direction * 5)].setSaftey(danger); //We can also infer where the opposite wall is.
                    }
                }
              }
            }      
          }

 
        if (breeze == true)
        {
           model[currPos].setBreeze(yes); 
        }
        else
        {
           model[currPos].setBreeze(no);
           if(currPos < 42)
           {
            model[currPos + north].setPit(safe);
           }
           if((currPos + 1) % 7 != 0)
           {
            model[currPos + east].setPit(safe);
           }
           if(currPos % 7 != 0)
           {
            model[currPos + west].setPit(safe);
           System.out.println("AND HERE");
           }
           if(currPos > 6)
           {
            model[currPos + south].setPit(safe);
           }
        }
     
        if (stench == true)
         {
           model[currPos].setStench(yes); 
         }
        else
         {
           model[currPos].setStench(no); 
           if(currPos < 42)
           {
            model[currPos + north].setWumpus(safe);
           }
           if((currPos + 1) % 7 != 0)
           {
            model[currPos + east].setWumpus(safe);
           }
           if(currPos % 7 != 0)
           {
            model[currPos + west].setWumpus(safe);
           }
           if(currPos > 6)
           {
            model[currPos + south].setWumpus(safe);
           }          
         } 
        
        if (scream == true)
         {
            count = 0;
            while (count < 49)
             {
                 model[count].setWumpus(safe);
                 ++count;
              }
           }

           
           
         updateModelInferences(); //uses model data to infer pit/wumpus/safe sqaures/etc
          

         //Shoots if it has an arrow, smells a stench, is facing a square that is not known to
         // be wumpus free, and is not facing a sqaure that might have a pit.  
         // It also will not shoot a known wall (a square that is labeled "dangerous" but is not a pit/wumpus)
         if(model[currPos].getStench() == yes && (currPos + direction) > -1 && (currPos + direction) < 49)
           {
             if(hasArrow == true && model[currPos + direction].getWumpus() != safe && model[currPos + direction].getPit() == safe
                && (model[currPos + direction].getSafety() != danger || model[currPos + direction].getWumpus() == danger)) // don't want to shoot a wall or a pit.  
               {
                  hasArrow = false; 
                  if(direction == north || direction == south)
                  {
                    count = currPos + direction;  
                    while (count < 49 && count > -1) //Update model - all squares in path of arrow are safe.
                     {                               //(Wumpus(safe) that is.)
                       model[count].setWumpus(safe);
                       count = count + direction;
                     }
                  }
                  if(direction == east)
                  {
                    count = currPos + direction;
                    while (count % 7 != 0) //Update model - all squares in path of arrow are safe.
                     {
                       model[count].setWumpus(safe);
                       count = count + direction;
                     }
                  }
                  if(direction == west)
                  {
                    count = currPos + direction;
                    while ((count + 1) % 7 != 0) //Update model - all squares in path of arrow are safe.
                     {
                       model[count].setWumpus(safe);
                       count = count + direction;
                     }
                  }
                  
                  return actionTable[7];
               }
            }
            
         int directionChoice = 0; 
         //Checks model for ajacent sqaures.
         //Will not enter a square that is not safe.
         //If facing sqaure, goes forward.  Otherwise it turns toward square.
         //Turning if statements seperated from other if statements and put
         //at end to make the code a lot easier to read.
         //The below is otherwise the same as putting the turning statement
         //and return value inside each and every nested if statement in addition to
         // having each if statement include a version that adds
         // "&& direction == <direction this if statement is for>" before checking the other statements.
         // The below could have also been written as one giant if statement.     
         //It does not plan ahead nor does it calculate the results of future movements.
         if(currPos < 42)
          {
            if(model[currPos + north].getSafety() == safe && model[currPos + north].getBreeze() == unkown)
             {
               directionChoice = north;
            }
          }
         if(currPos > 6 && (directionChoice == 0 || directionChoice != direction))
          {
            if(model[currPos + south].getSafety() == safe && model[currPos + south].getBreeze() == unkown)
             {
               directionChoice = south;
            }
          }
          if(currPos < 49 && (directionChoice == 0 || directionChoice != direction))
          {
            if(model[currPos + east].getSafety() == safe && model[currPos + east].getBreeze() == unkown)
             {
               directionChoice = east;
            }
          }
          if(currPos > -1 && (directionChoice == 0 || directionChoice != direction))
          {
            if(model[currPos + west].getSafety() == safe && model[currPos + west].getBreeze() == unkown)
             {
               directionChoice = west;
            }
          }
          
         int noUnkown = directionChoice;    //noUnkown == 0 means that none of the above if statments
                                            //were true.
         if(currPos < 42 && noUnkown == 0)
          {
            if(model[currPos + north].getSafety() == safe)
             {
               directionChoice = north;
            }
          }
         if(currPos > 6 && noUnkown == 0 && (directionChoice == 0 || directionChoice != direction))
          {
            if(model[currPos + south].getSafety() == safe)
             {
               directionChoice = south;
            }
          }
          if(currPos < 49 && noUnkown == 0 && (directionChoice == 0 || directionChoice != direction))
          {
            if(model[currPos + east].getSafety() == safe)
             {
               directionChoice = east;
            }
          }
          if(currPos > -1 && noUnkown == 0 && (directionChoice == 0 || directionChoice != direction))
          {
            if(model[currPos + west].getSafety() == safe)
             {
               directionChoice = west;
            }
          }
          
         //Turning if statements.  Again, putting them here to make the code more readable. 
          
         if (directionChoice == direction)
         {
           currPos = currPos + direction;
           return actionTable[1];
         }
        if (directionChoice != west && direction == north)
         {
           turnedRight();   
           return actionTable[4]; //Turn right if facing north and want to be facing east/south
         }
        if (directionChoice != north && direction == east)
         {
           turnedRight();
           return actionTable[4]; //Turn right if facing east and want to be facing south/west
         }
        if (directionChoice != east && direction == south)
         {
           turnedRight();
           return actionTable[4]; //Turn right if facing south and want to be facing west/north
         }
        if (directionChoice != south && direction == west)
         {
           turnedRight();
           return actionTable[4]; //Turn right if facing west and want to be facing north/east
         }
         
        turnedLeft(); //If we reach this point there is no safe square so we spin in place.
        return actionTable[5];          
          

 /* Asked professor - the below involved to much planning.  Saving it as a start for next project.
         int directionChoice = chooseDirection(currPos, 0, 0, false); //Calculate shortest path to a square with breeze = unkown.,
                                                             //Returns first step, discards other steps. (No memory)
         if (directionChoice == 16) //no known path to a sqaure with breeze = unkown. 
          {
            directionChoice = chooseDirection(currPos, 0, 0, true); //Seek a square with stench = Yes. Wumpus hunting.
            if(directionChoice == 0) //This square has a stench
             {
               //determineShootDirection();
               //if facing that direction, shoot.  Otherwise, turn towards that direction.
               return actionTable[4];
             }
          }
 System.out.println("WE GOT HERE_" + directionChoice + "__" + direction);

        */
       
    }
    
    public void updateModelInferences()
     {
       int currColumn = 0;
       int currRow = 0;
       int checkPos = 0;
       int wumpusFound = 1;  //a value of 2 will mean the wumpus was found

       // We start in the bottom right corner of potential squares and move -> though each row from 0 to 6.
       while(currRow < 49) //currRow is incremented by 7 each time each loop.
       {
         currColumn = 0;
         while(currColumn < 7)
          {
             checkPos = currRow + currColumn;
             //Check for wumpus Inferences.  ***************************************************************************************
             if(currColumn < 5)
              {
                 if(model[checkPos].getStench() == model[checkPos + 2].getStench() && model[checkPos].getStench() != unkown)
                  {
                      model[checkPos + 1].setWumpus(model[checkPos].getStench()); //  If both are true, wumpus = danger. [S]?S must be [S]WS
                      wumpusFound = wumpusFound * model[checkPos + 1].getWumpus(); // Safe = 1*1 = 1, A "danger" result will increase value above 1.
                  }
              }
             if(currRow < 35)
              {
                 if(model[checkPos].getStench() == model[checkPos + 14].getStench() && model[checkPos].getStench() != unkown)
                  {
                      model[checkPos + 7].setWumpus(model[checkPos].getStench()); //  If both are true, wumpus = danger. [S]?S^T must be [S]WS^T
                      wumpusFound = wumpusFound * model[checkPos + 7].getWumpus();
                  }
              }
       
              if(currRow < 42 && currColumn < 6)
               {
                 if(model[checkPos].getStench() == model[checkPos + 8].getStench() && model[checkPos +7].getWumpus() == safe && model[checkPos].getStench() != unkown)
                  {                                                              //  Checks  O S -> 0 S
                      model[checkPos + 1].setWumpus(model[checkPos].getStench()); //  Case: [S]?    S W
                      wumpusFound = wumpusFound * model[checkPos + 1].getWumpus();
                  }
                 if(model[checkPos].getStench() == model[checkPos + 8].getStench() && model[checkPos + 1].getWumpus() == safe && model[checkPos].getStench() != unkown)
                  {                                                              //  Checks  ? S -> W S
                      model[checkPos + 7].setWumpus(model[checkPos].getStench()); //  Case:  [S]0    S 0
                      wumpusFound = wumpusFound * model[checkPos + 7].getWumpus();
                  }
               }
              if(currRow < 42 && currColumn > 0)
               {
                 if(model[checkPos].getStench() == model[checkPos + 6].getStench() && model[checkPos +7].getWumpus() == safe && model[checkPos].getStench() != unkown)
                  {                                                              //  Checks  S 0 -> S 0
                      model[checkPos - 1].setWumpus(model[checkPos].getStench()); //  Case:  ?[S]   W S
                      wumpusFound = wumpusFound * model[checkPos - 1].getWumpus();
                  }
                 if(model[checkPos].getStench() == model[checkPos + 6].getStench() && model[checkPos - 1].getWumpus() == safe && model[checkPos].getStench() != unkown)
                  {                                                               //  Checks  S ? -> S W
                      model[checkPos + 7].setWumpus(model[checkPos].getStench()); //  Case:   0[S]   0 S
                      wumpusFound = wumpusFound * model[checkPos + 7].getWumpus();
                  }
               }
            //Check for Pit Inferenses ******************************************************************************
            //Unlike wumpus, with two pits it is easier to figure out where a pit is not, although the agent also tries to figure out where pits are.
             if(currColumn > 1 && currColumn > 0 && currRow < 35)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 6].getBreeze() 
                 && model[checkPos + 14].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 7].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  - ? B    - ? B
                  {                                                             //  ? B 0 -> 0 B 0
                      model[checkPos + 5].setPit(safe);                         //  - ?[B]   - ?[B]
                  }
                }  
              if(currColumn < 5 && currColumn > 0 && currRow < 35)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 14].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 7].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  B ? -    B ? -
                  {                                                             //  0 B ? -> 0 B 0
                      model[checkPos + 9].setPit(safe);                         // [B]? -   [B]? -
                  }
                }
             if(currColumn < 5 && currRow < 35)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 2].getBreeze() 
                 && model[checkPos + 8].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 1].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  - ? -    - 0 -
                  {                                                             //  ? B ? -> ? B ?
                      model[checkPos + 15].setPit(safe);                        // [B]0 B   [B]0 B
                  }
                }  
             if(currColumn < 6 && currColumn > 0 && currRow > 6 && currRow < 42)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 6].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 7].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  B 0 B -     B 0 B
                  {                                                             //  ?[B] ? ? -> ?[B]?
                      model[checkPos - 7].setPit(safe);                         //  - ? -       - 0 -
                  }
                } 
              if(currColumn < 5 && currRow < 35)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 14].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 7].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  B ? -    B ? -
                  {                                                             //  0 B ? -> 0 B 0
                      model[checkPos + 9].setPit(safe);                         // [B]? -   [B]? -
                  }
                }
                
                
              if(currColumn < 6 && currColumn > 0 && currRow < 35)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 6].getBreeze() 
                 && model[checkPos + 8].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 7].getBreeze() == yes && model[checkPos].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  - ? -    - P -
                  {                                                             //  0 B 0 -> 0 B 0
                      model[checkPos + 14].setPit(danger);                       // -[0]-    -[0]-
                  }
                }
              if(currColumn < 6 && currColumn > 0 && currRow < 35)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 6].getBreeze() 
                 && model[checkPos + 14].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 7].getBreeze() == yes && model[checkPos].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  - 0 -    - 0 -
                  {                                                             //  0 B ? -> 0 B P
                      model[checkPos + 8].setPit(danger);                       //  -[0]-    -[0]-
                  }
                }
              if(currColumn < 6 && currColumn > 0 && currRow < 35)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 14].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 7].getBreeze() == yes && model[checkPos].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  - 0 -     - 0 -
                  {                                                             //  ? B 0 ->  P B 0
                      model[checkPos + 6].setPit(danger);                       //  -[0]-     -[0]-
                  }
                }
              if(currColumn < 5 && currRow < 42 && currRow > 6)
                {
                 if(model[checkPos].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 2].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 1].getBreeze() == yes && model[checkPos].getBreeze() == no
                 && model[checkPos].getBreeze() != unkown)                      //  - 0 -     - 0 -
                  {                                                             // [0]B 0 -> [0]B 0
                      model[checkPos - 6].setPit(danger);                       //  - ? -     - P -
                  }
                }              

                
                   
             if(currColumn < 5 && currRow < 42)
              {
                 if(model[checkPos].getBreeze() == model[checkPos + 2].getBreeze() 
                 && model[checkPos + 8].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos + 7].getBreeze() == no && model[checkPos + 9].getBreeze() == no
                 && model[checkPos].getBreeze() == yes)
                  {                                                             // 0 B 0 -> 0 B 0
                      model[checkPos + 1].setPit(danger);                       // [B]? B   [B]P B
                  }
              }
       
             if(currColumn < 6 && currColumn > 0 && currRow < 42)
              {
                 if(model[checkPos].getBreeze() == model[checkPos + 6].getBreeze() 
                 && model[checkPos + 8].getBreeze() == model[checkPos].getBreeze() 
                 && model[checkPos - 1].getBreeze() == no && model[checkPos + 1].getBreeze() == no
                 && model[checkPos].getBreeze() == yes)
                  {                                                             // B ? B -> B P B
                      model[checkPos + 7].setPit(danger);                      //  0[B]0    0[B]0
                  }
              }
              
             if(currColumn < 6 && currColumn > 0 && currRow < 35)
              {
                 if(model[checkPos].getBreeze() == model[checkPos + 7].getBreeze() 
                 && model[checkPos + 15].getBreeze() == model[checkPos].getBreeze()
                 && model[checkPos + 14].getBreeze() == no
                 && model[checkPos].getBreeze() == yes)                          //  0 B    0 B
                  {                                                              //  B ? -> B P
                      model[checkPos + 8].setPit(danger);                       //  [B]-   [B]-
                     
                  }
              }             
             if(currColumn < 6 && currColumn > 0 && currRow < 35)
              {
                 if(model[checkPos + 1].getBreeze() == model[checkPos + 7].getBreeze() 
                 && model[checkPos + 14].getBreeze() == model[checkPos].getBreeze()
                 && model[checkPos].getBreeze() == no
                 && model[checkPos + 1].getBreeze() == yes)                      //  B -    B -
                  {                                                              //  B ? -> B P
                      model[checkPos + 8].setPit(danger);                       //  [0]B   [0]B
                     
                  }
              }
             if(currColumn < 6 && currColumn > 0 && currRow < 35)
              {
                 if(model[checkPos].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 15].getBreeze() == model[checkPos].getBreeze()
                 && model[checkPos + 1].getBreeze() == no
                 && model[checkPos].getBreeze() == yes)                          //  - B    - B
                  {                                                              //  ? B -> P B
                      model[checkPos + 7].setPit(danger);                       //  [B]0   [B]0
                     
                  }
              }
             if(currColumn < 6 && currColumn > 0 && currRow < 35)
              {
                 if(model[checkPos + 1].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 14].getBreeze() == model[checkPos].getBreeze()
                 && model[checkPos + 15].getBreeze() == no
                 && model[checkPos + 1].getBreeze() == yes)                      //  B 0    B 0
                  {                                                              //  ? B -> P B
                      model[checkPos + 7].setPit(danger);                       //  [-]B   [-]B
                     
                  }
              }
             if(currColumn < 5 && currColumn > 0 && currRow < 42)
              {
                 if(model[checkPos + 7].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 2].getBreeze() == model[checkPos].getBreeze()
                 && model[checkPos + 9].getBreeze() == no
                 && model[checkPos + 7].getBreeze() == yes)                    // B B 0     B B 0
                  {                                                            //[-]? B  ->[-]P B
                      model[checkPos + 1].setPit(danger);                     
                     
                  }
              }
             if(currColumn < 5 && currColumn > 0 && currRow < 42)
              {
                 if(model[checkPos].getBreeze() == model[checkPos + 1].getBreeze() 
                 && model[checkPos + 9].getBreeze() == model[checkPos].getBreeze()
                 && model[checkPos + 8].getBreeze() == no
                 && model[checkPos].getBreeze() == yes)                        // - ? B     - P B
                  {                                                            //[B]B 0  ->[B]B 0
                      model[checkPos + 8].setPit(danger);                     
                     
                  }
              }
             if(currColumn < 5 && currColumn > 0 && currRow < 42)
              {
                 if(model[checkPos].getBreeze() == model[checkPos + 8].getBreeze() 
                 && model[checkPos + 9].getBreeze() == model[checkPos].getBreeze()
                 && model[checkPos + 7].getBreeze() == no
                 && model[checkPos].getBreeze() == yes)                        // 0 B B     0 B B
                  {                                                            //[B]? -  ->[B]P -
                      model[checkPos + 1].setPit(danger);                     
                     
                  }
              }
             if(currColumn < 5 && currColumn > 0 && currRow < 42)
              {
                 if(model[checkPos + 1].getBreeze() == model[checkPos + 2].getBreeze() 
                 && model[checkPos + 7].getBreeze() == model[checkPos].getBreeze()
                 && model[checkPos].getBreeze() == no
                 && model[checkPos + 1].getBreeze() == yes)                    // B ? -     B P -
                  {                                                            //[0]B B  ->[0]B B
                      model[checkPos + 8].setPit(danger);                     
                     
                  }
              }
             
                        
           //++count;
          ++checkPos;
          ++currColumn;
        } // end while(currColumn < 7)
        currRow = currRow + 7;
      }  // end while(currRow < 49)
       //*/

      int count = 0;
      if(wumpusFound > 1)
       {
         while(count < 49)
         {
           if(model[count].getWumpus() != danger)
            {
              model[count].setWumpus(safe);
            }
          ++count;
        } //end while(count < 49)
      } //End if
      
      count = 0;
      int pitFound = 0;
      while(count < 49) //Much harder to detemrine if two pits have been found, so we just use a loop here.
       {
         if(model[count].getPit() == danger)
           {
             ++pitFound;
            }
         ++count;   
       }
      count = 0;
      if(pitFound > 1)
      {
        while(count < 49)
         {
           if(model[count].getPit() != danger)
            {
              //model[count].setPit(safe);
            }
          ++count;
       } //end while(count < 49)
      } // End if
      
      count = 0;
      while(count < 49)
        {
          if(model[count].getWumpus() == safe && model[count].getPit() == safe && model[count].getSafety() == unkown)
            {
              model[count].setSaftey(safe);
            }
          ++count;
        } //end while (count < 49)
              //*/
    }
    
    
    /* Ignore this commented out method.
    //Calculates shortest path to unkown square, returns first step. 
    //(Other steps are forgotten since agent has no memory of its own actions)
    public int chooseDirection(int pos, int step, int lastDirection, boolean findStench)
     { 
       //The second and third if statements will never be true the first time this method is called.
       //The first if statement might be true the first time, as we might start off in a stench square.  
       if(findStench == true && model[pos].getStench() == yes)
        {
          return step;
        }
       if(model[pos].getSafety() == safe && model[pos].getBreeze() == unkown) //Breeze = unkown means it has never been to this square
        {                                                                 //(Not that the agent remembers this [it does not], it's just factually true.)
            return step; 
        }       
       if (model[pos].getSafety() != safe || step > 15) // more than 16 steps means we are looping.
        {
          return 20;  
        } 
       int currStep = step + 1; 
       int currChoice = 16;
       int otherChoice = 16;
       int bestDirection = 16;
        //Choosing the best direction - the method favors the direction agent is facing.
        if(pos > 0 && lastDirection != east)
        {
          currChoice = chooseDirection((pos + west), currStep, west, findStench);
          bestDirection = west;
         // System.out.println("YEAH, YEAH_" + model[pos -1].getSafety());
        }
        if(pos < 48 && lastDirection != west)
        {
          otherChoice = chooseDirection((pos + east), currStep, east, findStench);   
        }
        if(currChoice > otherChoice || (currChoice == otherChoice && direction == east))
         {
          currChoice = otherChoice; 
          bestDirection = east;
         }
        if(pos < 42 && lastDirection != south)
        {
          otherChoice = chooseDirection((pos + north), currStep, north, findStench);   
        }
        if(currChoice > otherChoice || (currChoice == otherChoice && direction == north) )
         {
          currChoice = otherChoice; 
          bestDirection = north;
         }
        if(pos < 6 && lastDirection != north)
        {
          otherChoice = chooseDirection((pos + south), currStep, south, findStench);   
        } 
        if(currChoice > otherChoice || (currChoice == otherChoice && direction == south))
         {
          currChoice = otherChoice; 
          bestDirection = south;
         }
         
        if(step == 0) //this is the first iteration - picking which direction to go in.
         {
           if(currChoice == 20)
           {
             return 16; //There is no best direction to reach a safe breeze unkown square.
            }
           return bestDirection;
         }
         
        return currChoice;   //For the recursive calls we only care about how many steps it took to
                            //reach square.
     }*/
    
    
    public void turnedRight()
    {
        if(direction == north)
        {
          direction = east;
          return;
        }
        if(direction == east)
        {
          direction = south;
          return;
        }
        if(direction == south)
        {
            direction = west;
            return;
        }
        if(direction == west)
        {
            direction = north;
            return;
        }
    }
    
    public void turnedLeft()
    {
        if(direction == north)
        {
          direction = west;
          return;
        }
        if(direction == west)
        {
          direction = south;
          return;
        }
        if(direction == south)
        {
          direction = east;
          return;
        }
        if(direction == east)
        {
          direction = north;
          return;
        }
    }
    
    // public method to return the agent's name
    // do not remove this method;
    public String getAgentName() {
        return agentName;
    }
}
