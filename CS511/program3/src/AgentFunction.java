//Arnold Lee
//CS 511 Program 3 - Forward search reflex agent
//03/01/2012

//Abstract:
//This build on the "shachar" model
//but with incorporated the use of risk score
//to implement a forward, recursive search
//The selection criteria is a variant of the "greedy" method

//TO DO LIST:
//simplfy action table
//assign score for each potential problematic branch
//choose highest score of each branch and push to stack
//push current action to best action stack

// this library will give all the tools we need
import java.util.*;
import java.lang.Math;

class AgentFunction 
 {
    // string to store the agent's name
    // do not remove this variable
    private String agentName = "NewAge2012";
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
    
    
    //The below comprises the MODEL
    private boolean hasArrow = true;
    private int direction = north;
    private int currPos = 24;
    private MNODE[] model = new MNODE[49];
    //

  
    
    //A score array that will store risk score for each cell
    private int [] risk_score = new int [49];
    
    
    
    // recording sequence of best moves;
    private Stack<Integer> best_move = new Stack<Integer>();
    private Stack<Integer> inv_best_move = new Stack<Integer>(); // an inverted version of the stack
    
    // this is a flag for "ready to move"
    // if true, the agent will perform the next action according to the risk score with the squares
    // around him
    // if false, the risk score is still being generated
    private boolean ready = false;
    
    private boolean next_step = false;
    
    
    //search depth limit
    private int move_limit = 0;

    public AgentFunction()
    {
     
    	
    	
        // this integer array will store the agent actions
        
        model = new MNODE[49]; //Every 7 represents a row.  By starting in the 4th position of the 4th row (24), we can move
                               //3 squares in any direction without falling off and while still having wall squares, allowing us to start in any location.
        int count = 0;
        while (count < 49)
        {
          model[count] = new MNODE();
          ++count;
        }
                               
        actionTable = new int[9];
                  
        actionTable[0] = Action.GO_FORWARD;
        actionTable[1] = Action.GO_FORWARD;
        actionTable[2] = Action.GO_FORWARD;
        actionTable[3] = Action.GO_FORWARD;
        actionTable[4] = Action.TURN_RIGHT;
        actionTable[5] = Action.TURN_LEFT;
        actionTable[6] = Action.GRAB;
        actionTable[7] = Action.SHOOT;
        actionTable[8] = Action.NO_OP;
        
    
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
        
        if (glitter == true)
        {
        	
             return actionTable[6]; //Game over, you get gold!  In this case nothing else matters.
            
        }
               
        
        // if nothing happens, mark current square as clean, worth 100 points
        if (model[currPos] == null)
         {
                       System.out.println("WTF " + currPos);
                       
                       risk_score [currPos] = 100;
                       
                       //return actionTable[1];
                      best_move.push(1);
                       
         }
        model[currPos].setSaftey(safe); //If we are in the square and not dead, it is safe.
                    
 
        
        /////If no glitter, then update the model///////////////////////////////////
        
        
        // all walls will be assigned a risk score of -1;
        if (bump == true)
        {   = ==
          currPos = currPos - direction;    
          if((currPos + direction) < 49 && (currPos + direction) > -1)
          {
           // model[currPos + direction].setSaftey(danger); //We don't want the agent to try to enter this wall again.
            risk_score[currPos+direction]= -1;
            
            if(direction == east || direction == west)
              {
                count = currPos + direction;            
                while(count > 7)
                {
                    count = count + south; //if East/west is blocked, then all positions south of that block are also blocked.
                    model[count].setSaftey(danger); //We don't want the agent to try to enter this wall again.
                    
                    risk_score[count]= -1;
                    
                    if((count - (direction * 5)) < 49 && (count - (direction * 5)) > -1)
                    {
                      model[count - (direction * 5)].setSaftey(danger); //We can also infer where the opposite wall is.
                      
                      risk_score[count - (direction * 5)]=-1;
                    }
                }
                count = currPos + direction;
                while(count < 42)
                {
                    count = count + north; //if East/west is blocked, then all positions north of that block are also blocked.
                    model[count].setSaftey(danger); //We don't want the agent to try to enter this wall again. 
                    
                    risk_score[count]= -1;
                    
                    if((count - (direction * 5)) < 49 && (count - (direction * 5)) > -1)
                    {
                      model[count - (direction * 5)].setSaftey(danger); //We can also infer where the opposite wall is.
                      
                      risk_score[count-(direction*5)] = -1;
                      
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
                    
                    risk_score[count]=-1;
                    
                    if((count - (direction * 5)) < 49 && (count - (direction * 5)) > -1)
                    {
                      model[count - (direction * 5)].setSaftey(danger); //We can also infer where the opposite wall is.
                      
                      risk_score[count-(direction*5)] = -1;
                      
                    }
                }
                count = currPos + direction;
                while((count % 7) != 0)
                {
                    count = count + west; //if north/south is blocked, then all positions west of that block are also blocked.
                    model[count].setSaftey(danger); //We don't want the agent to try to enter this wall again. 
                    
                    risk_score[count]=-1;
                    
                    if((count - (direction * 5)) < 49 && (count - (direction * 5)) > -1)
                    {
                      //model[count - (direction * 5)].setSaftey(danger); //We can also infer where the opposite wall is.
                      
                      risk_score[count-(direction*5)] = -1;
                      
                    }
                }
              }
            }      
          }

        // if no breeze, mark all surrounding square as no pit 
        // breeze square worth 50 points
        // confirmed no pit square worth 75 points
        if (breeze == true)
        {
           model[currPos].setBreeze(yes); 
           
           risk_score[currPos] = 50;
           
        }
        else
        {
           model[currPos].setBreeze(no);
           if(currPos < 42)
           {
            model[currPos + north].setPit(safe);
            risk_score[currPos+north] = 75;
            
           }
           if((currPos + 1) % 7 != 0)
           {
            model[currPos + east].setPit(safe);
            risk_score[currPos+east] = 75;
            
           }
           if(currPos % 7 != 0)
           {
            model[currPos + west].setPit(safe);
            risk_score[currPos+west] = 75;
           }
           if(currPos > 6)
           {
            model[currPos + south].setPit(safe);
            risk_score[currPos+south] = 75;
           }
        }
     
        // if no stench, mark all surrounding square as no wumpus
        // 20 point for stench
        // 30 point for wumpus free
       if (!scream)
       {
        if (stench == true)
         {
           model[currPos].setStench(yes); 
           
           risk_score[currPos] = 20;
         }
        else
         {
           model[currPos].setStench(no); 
           if(currPos < 42)
           {
            model[currPos + north].setWumpus(safe);
            risk_score[currPos+north] = 30;
           }
           if((currPos + 1) % 7 != 0)
           {
            model[currPos + east].setWumpus(safe);
            risk_score[currPos+east] = 30;
           }
           if(currPos % 7 != 0)
           {
            model[currPos + west].setWumpus(safe);
            risk_score[currPos+west] = 30;
           }
           if(currPos > 6)
           {
            model[currPos + south].setWumpus(safe);
            risk_score[currPos+south] = 30;
           }          
         } 
       }
           
         updateModelInferences(); //uses model data to infer pit/wumpus/safe sqaures/etc
          

         //Shoots if it has an arrow, smells a stench, is facing a square that is not known to
         // be wumpus free, and is not facing a sqaure that might have a pit.  
         // It also will not shoot a known wall (a square that is labeled "dangerous" but is not a pit/wumpus)
         
         // Add 30 points to the current score of the current cell if wumpus_clear
         
         if((scream==false) && model[currPos].getStench() == yes && (currPos + direction) > -1 && (currPos + direction) < 49)
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
                       
                       risk_score[count] +=30; // add 30 points to the current risk score of that poistion
                       
                       count = count + direction;
                     }
                  }
                  if(direction == east)
                  {
                    count = currPos + direction;
                    while (count % 7 != 0) //Update model - all squares in path of arrow are safe.
                     {
                       model[count].setWumpus(safe);
                       
                       risk_score[count] +=30; // add 30 points
                       
                       count = count + direction;
                     }
                  }
                  if(direction == west)
                  {
                    count = currPos + direction;
                    while ((count + 1) % 7 != 0) //Update model - all squares in path of arrow are safe.
                     {
                       model[count].setWumpus(safe);
                       
                       risk_score[count] +=30; // add 30 points
                       
                       count = count + direction;
                     }
                  }
                  
                  best_move.push(7); // record the arrow shooting
               }
            }
            
        //Here, we check each adjacent square. The one with the highest risk score will be the one will move 
         //into in the next step 
         
        if ( ( risk_score[currPos+west] > risk_score[currPos+north]) ) 	
        {
        			best_move.push(4);
        			  	
        }
        else
        	best_move.push(5);
        
        if ( ( risk_score[currPos+north] > risk_score[currPos+east]) ) 	
        {
        			best_move.push(4);
        			  	
        }
        else
        	best_move.push(5);
        
        if ( ( risk_score[currPos+east] > risk_score[currPos+south]) ) 	
        {
        			best_move.push(4);
        			  	
        }
        else
        	best_move.push(5);
        
        if ( ( risk_score[currPos+south] > risk_score[currPos+west]) ) 	
        {
        			best_move.push(4);
        			  	
        }
        else
        	best_move.push(5);
        
        
        int directionChoice =0;
        
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
         
        
        
        move_limit++;
        
        // ready to execute all remaining move in the queue IF:
        // 1. Search depth exceeds 1000 move
        if (move_limit > 1000)
        {
        	ready = true;
        }
        else ready = false;
        
        // when the agent is ready to execute the best action from the best move stack
        if (ready)
        {
        	if (best_move.empty() == false)
        	{
        		// the best move stack has the last action on top --- we need to invert it
        		// so that it is first action on top
        		
        		while (best_move.empty() == false)
        		{
        			inv_best_move.push(best_move.pop());
        		}
        		
        	}
        	else if (inv_best_move.empty()==false)
        	{
        		//execute the action
        		return actionTable[inv_best_move.pop()];
        	}
        	else
        	{
        		// in most cases after all best move has been performed
        		// you should be end up in the gold
        		// otherwise go back to the grid
        		
        		if (glitter) return actionTable[6];
        		else ready = false;
        		
        	}
        	
        }
         
        // other wise just return the next move with the top score
        return best_move.pop();
         
 }
 
 //*******************************************************************************************************
    //****************************************************************************************************
    
 // updated model inferences , from original shachar module
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
             
    }
    
       
    
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
