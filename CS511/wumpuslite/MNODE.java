
/**
 * Write a description of class Model here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

public class MNODE
{
  private static final int unkown = 0;
  int safety = unkown;
  int wumpus = unkown;
  int pit = unkown;
  int breeze = unkown;
  int stench = unkown;
 // double wumpusChance = unkown;
 // double noPitChance = unkown;
 // int numAdjacentBreeze = unkown;
 // double pitChance = unkown;
  
  public MNODE()
  {
     safety = unkown;
     wumpus = unkown;
     pit = unkown;
     breeze = unkown;
     stench = unkown;
   }
 
  public void setSaftey(int value)
  {
    safety = value;  
  }
  
  public void setWumpus(int value)
  {
    wumpus = value; 
   // wumpusChance = wumpus - 1; //Safe = 1, so chance = 0.  Danger = 2, so chance = 1;
  }
  
  public void setPit(int value)
  {
    pit = value;
   // pitChance = pit - 1; //Safe = 1, so chance = 0.  Danger = 2, so chance = 1;
  }
  
  public void setBreeze(int value)
  {
    breeze = value;  
  }
  
  public void setStench(int value)
  {
    stench = value;  
  }
/*  
  public void addAdjacentBreeze()
  {
    numAdjacentBreeze = numAdjacentBreeze + 1;  
  }
  
  public void changeNoPitChance(int numPotentialPit, int numPitsFound)
  {
    if(pit == unkown && numPitsFound < 2)
     {
       noPitChance = 1;
       int count = 0;
       while (count < numAdjacentBreeze)
       {
        noPitChance = noPitChance * .75;
        count = count + 1;
       }
       if(numPitsFound == 0)
        {
          noPitChance = noPitChance * ((numPotentialPit - 1) / numPotentialPit);
        }
       pitChance = noPitChance - 1;
     }
  }
  
  public void changeWumpusChance()
  {
    if(wumpus == unkown)
     {
       wumpusChance = wumpusChance + .25;
     }
  }
  
  public double getPitChance()
  {
      return pitChance;
  }
  
  public double getWumpusChance()
  {
      return wumpusChance;
  }
*/  
  public int getSafety()
  {
      return safety;
  }
  
    public int getWumpus()
  {
      return wumpus;
  }
  
  public int getPit()
  {
      return pit;
  }
  
    public int getStench()
  {
      return stench;
  }
  
    public int getBreeze()
  {
      return breeze;
  }
  
  

}
