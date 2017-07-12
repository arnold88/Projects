//new MSGSP

import java.io.*;
import java.util.*;
import java.lang.*;


public class msgsp {

	
	
    
   static File file = null;
   static FileInputStream FIS = null;
   static BufferedInputStream BIS = null;
   static  DataInputStream DIS = null;
    
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		
		  //if ( args.length < 1 )
	      //  {
	      //      System.out.println("Provide a file name damn it!");
	      //      System.exit(0);
	      //  }

	    //String folder = args[0] + "\\"  ;
	    //String Data = folder + "data.txt";
	    //String Param = folder + "para.txt";
		//String Output = folder + "output.txt"
		
		
		//comment this out at demo
		
		String Data = "C:\\data.txt";
		String Param = "C:\\para.txt";
	    String Output = "C:\\Users\\user\\Desktop\\output.txt";
	    int MAX_LIMIT = 10; // initial item variety limit, set this low
    
        
    	double[] MIS = new double [MAX_LIMIT];
    	double SDC;
    	
    	
    	
    	// This is your main database
    	ArrayList <Sequence> dbase = new ArrayList<Sequence>();
    	
    	// List of sorted item varieties by MIS
    	ArrayList <Item> sortedItem = new ArrayList<Item>();
    	
    	//load the MIS and SDC values from parameter file
    	
    try{
    	
    	File datafile = null;
        FileInputStream FIS = null;
        BufferedInputStream BIS = null;
        DataInputStream DIS = null;
        boolean SDC_FLAG = false;
    	
        
        // start parameter reading
        
        datafile = new File (Param);
        
		FIS = new FileInputStream(datafile);
		 
        BIS = new BufferedInputStream(FIS);
        DIS = new DataInputStream(BIS);
        
        int printcount = 1;
        
        while (DIS.available() != 0)
	    {
        	
         
         for (int index = 0; index < MAX_LIMIT; index++)
         {
        	 	 
     	       if ((index % 100 == 99) && (SDC_FLAG == false))
     		   {
     		      //expand array slots each time if the array is full
     		      MAX_LIMIT = MAX_LIMIT + 1; 
     		      MIS = (double[])resizeArray(MIS,MAX_LIMIT);
     		   }
     	   
     	   // check if SDC line is reached
     	   
     	       String line = DIS.readLine();
     	 
     	  
     	  if ( line.startsWith("M") ) SDC_FLAG = false;
     	  else if ( line.startsWith("S") ) SDC_FLAG = true;
     	  else SDC_FLAG = false;
     		
     	// read in MIS value or SDC value
     	  
     	  if (SDC_FLAG)
     	  {
     		 int j = line.indexOf('=');
     		 SDC = Double.valueOf(line.substring(j+1, line.length()));
     		 System.out.println ("SDC="+SDC); // output to console - for debug purpose only
     		 break; // break out the for loop; parameter reading is over
     	  }
     	  else
     	  {
     		 int j = line.indexOf('=');
        	 MIS[index] = Double.valueOf(line.substring(j+1, line.length()));
        	 System.out.println ("MIS"+printcount+"="+MIS[index]); // output to console - for debug purpose only
     	  }
     	  printcount=printcount+1;
     	  
          		     
     	 } // end for loop (reading MIS / SDC)
     	} // end while(DIS.avaliable)
         
        FIS.close();
        BIS.close();
        DIS.close();
        
        // end parameter reading
   
        
        //*****************************************************************************
        
        dbase = createDB(Data,MIS); // list of all sequences
        
        //******************************************************************************
        
        
        // this sort is to guard against out of order item lists
        for (int x = 1; x<=MIS.length ; x++)
        {
        	Item new_Stuff = new Item ();
        	
        	new_Stuff.setName( Integer.toString(x) );
        	new_Stuff.setMinsup(MIS[x]);
        	
        	sortedItem.add(new_Stuff);
        	
        	
        }
        
        sortedItem = sortItems(sortedItem);
        // item list is finally sorted by MIS
        
        int[]itemCount = new int [MIS.length];
        
     // item count acquired
        itemCount = makeCount (sortedItem,dbase);
        
        
        //test print the items
       
       for (int i = 0; i < dbase.size() ; i++)
       {
    	   for (int j = 0; j < dbase.get(i).getLength(); j++)
    	   {
    		   
    		   for (int k=0; k< dbase.get(i).getItemset(j).size(); k++)
    		    
    		   {
    		   System.out.println (dbase.get(i).getItemset(j).getItem(k));
    		   
    		   
    		   
    		   }
    		   
    		   
    	   }
    		 
    	   
    	   
       }
       
        
        
        
    // Parsing input file complete,  begin remaining code here    
        
        
        
        
     
        
        
    	}
    catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
	     }
    catch (IOException e) {
        e.printStackTrace();
    }
      
    
    
      
    
    
	}

	
	//resize array, internal use only
	
	private static Object resizeArray (Object oldArray, int newSize)
    {
		   int oldSize = java.lang.reflect.Array.getLength(oldArray);
		   Class elementType = oldArray.getClass().getComponentType();
		   Object newArray = java.lang.reflect.Array.newInstance(
		         elementType, newSize);
		   int preserveLength = Math.min(oldSize, newSize);
		   if (preserveLength > 0)
		      System.arraycopy(oldArray, 0, newArray, 0, preserveLength);
		   return newArray; 
		}
	
	
	
	//*****************************************
	
	// sort a list of items based on its MIS values, ascending order
    // precondition: list of items
	// postcondition: list of items shuffled
	// (USE THIS after a sequence is created)
	
	public static ArrayList<Item> sortItems(ArrayList<Item> items)
    {
       
        for(int i = 0; i < items.size() - 1; i++)
        {
            Item temp = new Item();

            for (int j = i + 1; j < items.size(); j++)
            {
                if(items.get(j).getMinsup() < items.get(i).getMinsup())
                {
                    //swap between i and j items.
                    temp.setName(items.get(i).getName());
                    temp.setMinsup(items.get(i).getMinsup());

                    items.get(i).setName(items.get(j).getName());
                    items.get(i).setMinsup(items.get(j).getMinsup());

                    items.get(j).setName(temp.getName());
                    items.get(j).setMinsup(temp.getMinsup());	
                }
            }
        }
        return items;
    }

    
 //*********************************************
	//Get the items count for each item
  // precondition: list of items, DB

    public static int [] makeCount(ArrayList<Item> items, ArrayList<Sequence> DB)
    {   
        
    	int[] count = new int [items.size()];
    	
    	// count array initialization
    	for (int l=1 ; l<=items.size() ; l++)
    	{
    		
    		count [l] = 0;
    		
    	}
    	
    	
    	
        
        for (int l = 0; l < items.size(); l ++)
        {
     nextSequence:
            for(int i = 0; i < DB.size(); i ++)
            {
                Sequence sequence = DB.get(i);
                for(int j = 0; j < sequence.getSequence().size(); j++)
                {
                    Itemset itemSet = sequence.getItemset(j);
                    for(int k = 0; k < itemSet.getItems().size(); k++)
                    {
                        if(items.get(l).getName().equalsIgnoreCase(itemSet.getItem(k).getName()))
                        {
                            count[l+1]++;
                            continue nextSequence;				
                        }
                    }
                }
            }
        }
        
        
        
		return count;
   
    	
    }
	
    //******************************
    //create an itemset (part of DB creation process)
    //precondition: name string (which is just a number in this case), and the MIS array
 
    public static Itemset createItemSet(String itemSetString, double [] MIS)
    {
        Itemset itemSet = new Itemset();

        int beginIndex = 0;
        int i = 0;

        while (i < itemSetString.length())
        {
            while(itemSetString.charAt(i) == ' ')
            {
                i = i + 1;
            }

            beginIndex = i;
            while((i < itemSetString.length()) && (itemSetString.charAt(i) != ','))
            {
                i = i + 1;
            }

            //Create new item
            Item item = new Item();
            item.setName(itemSetString.substring(beginIndex, i));

            for (int j = 0; j < MIS.length; j++)
            {
                /*if(M.get(j).getName().equalsIgnoreCase(item.getName()))
                {
                    item.setMinsup(M.get(j).getMinsup());
                	item.setMinsup(MIS[j]);
                }
                else
                {
                    if(j == (MIS[j])) item.setMinsup(1.1);
                }*/
            	
            	if (j==(MIS[j])) item.setMinsup(1.1);
            	else item.setMinsup(MIS[j]);
            	
            	
            }

            itemSet.addItem(item);

            i = i + 1;
        }    	
        return itemSet;
    }
    
// ********************************************    
//  building the database
//  Precondition: input file name, MIS array
    
    public static ArrayList<Sequence> createDB(String Data, double [] MIS)
    {
        ArrayList<Sequence> DB = new ArrayList<Sequence>();

        try {
        	
            file = new File(Data);
            FIS = new FileInputStream(file);
            BIS = new BufferedInputStream(FIS);
            DIS = new DataInputStream(BIS);

            // dis.available() returns 0 if the file does not have more lines.
            while (DIS.available() != 0) {

                String line = DIS.readLine();

                Sequence sequence = new Sequence();

                for (int i = 0; i < line.length(); i++)
                {
                    if(line.charAt(i) == '{')
                    {
                        int beginIndex = i;

                        
                        Itemset itemSet = new Itemset();

                        while(line.charAt(i) != '}')
                        {       	
                            i++;
                        }

                        String itemSetString = line.substring(beginIndex + 1, i);

                        itemSet =  createItemSet(itemSetString, MIS);

                        //Add to sequences -  changed
                        sequence.addItemset(itemSet);
                    }
                }
                //Add new sequence to the DB if non-zero sequence
                if ( sequence.getSize() > 0 )
                    DB.add(sequence);
            }

            // dispose all the resources after using them.
            FIS.close();
            BIS.close();
            DIS.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return DB; // back to main
    }

}

