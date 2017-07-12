//new MSGSP

// 2013-09-25

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
	    int total_item_count = 0;
	    int total_cust_count = 0;
        
    	//double[] MIS = new double [MAX_LIMIT];
	    ArrayList <Double> MIS = new ArrayList<Double>();
	    
	    
    	double SDC = 0.0;
    	
    	
    	
    	// This is your main database
    	ArrayList <Sequence> dbase = new ArrayList<Sequence>();
    	
    	// List of sorted item varieties by MIS
    	ArrayList <Item> sortedItem = new ArrayList<Item>();
    	
    	
    	//load the MIS and SDC values from parameter file
    	
    	ArrayList <Item> L = new ArrayList<Item>();
    	
    	
    	
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
     		 //System.out.println ("SDC="+SDC); // output to console - for debug purpose only
     		 break; // break out the for loop; parameter reading is over
     	  }
     	  else
     	  {
     		 int j = line.indexOf('=');
        	 MIS.add(Double.valueOf(line.substring(j+1, line.length())));
        	 //System.out.println ("MIS"+printcount+"="+MIS.get(printcount-1)); // output to console - for debug purpose only
     	  }
     	  printcount=printcount+1;
     	  
     	} // end while(DIS.avaliable)
         
        FIS.close();
        BIS.close();
        DIS.close();
        
        // end parameter reading
   
        
        //*****************************************************************************
        int [] frequency = new int [MIS.size()]; // get item frequency count
        
        for (int x=0;x<MIS.size();x++) // initialization
        {
        	
        	frequency[x] = 0;
        	
        }
        
        dbase = createDB(frequency,Data,MIS); // list of all sequences
        
        //test output of frequency and calculate aggregate item total
        
        for (int x=0;x<frequency.length;x++)
        {
     	   int z = x+1;
     	  // System.out.println ("freq of "+z+" is: " + frequency[x]);
     	   total_item_count = total_item_count + frequency[x];
     	   
        }
        
        //System.out.println ("total item count is: " + total_item_count);
        
        
        
        //******************************************************************************
        
        
        
        // sort item according to frequency on ascending order
        for (int x = 0; x<=MIS.size()-1 ; x++)
        {
        	Item new_Stuff = new Item ();
        	
        	new_Stuff.setName( Integer.toString(x+1) );
        	new_Stuff.setMinsup(MIS.get(x));
        	new_Stuff.setCount(frequency[Integer.parseInt(new_Stuff.getName()) - 1]);
        	
        	sortedItem.add(new_Stuff);
        	
        	
        }
        
        sortedItem = sortItems(sortedItem);
        // item list is finally sorted by MIS
        
     //   int[]itemCount = new int [MIS.size()+1];
        
     
     //  itemCount = makeCount (sortedItem,dbase);
        
        
        //test print the items
       /*for (int i = 0; i < dbase.size() ; i++)
       {
    	   System.out.println ("Customer "+(Integer.toString(i+1)));
    	   
    	   for (int j = 0; j < dbase.get(i).getSize()  ; j++)
    	   {
    		   
    		   System.out.println ("Itemset "+(Integer.toString(j+1)));
    		   
    		   for (int k = 0; k < dbase.get(i).getItemset(j).size(); k++)
    		   {
    			    
    		   System.out.print (dbase.get(i).getItemset(j).getItem(k).getName());
    		   System.out.print ("("+dbase.get(i).getItemset(j).getItem(k).getMinsup()+")");
    		   
    		   }
    		   
    		   System.out.println ("");
    		   
    	   }
    		 
    	   
    	   
       }// end test output  --- comment this entire section in real mode */
       
    
     total_cust_count = dbase.size(); // total amount of customers (lines in the input data file)  
     
     // L generation
     
     L = L_Generation(sortedItem,frequency,total_cust_count);
     
     //***** 
     
     //F1 generation
    
     ArrayList <Sequence> F_one = new ArrayList <Sequence>();
     
     // this is line 3, p.46 in the book
     
     for (int x=0; x < L.size(); x++)  
     {
    	 double temp2 = (double)L.get(x).getCount() / (double)total_cust_count;
    	 
    	 int temp_index = Integer.parseInt(L.get(x).getName()) -1;
    	 
    	 if (temp2 >= MIS.get(temp_index)) // single-item sequence will be included in F_one
    	 {

    		 Sequence temp_seq = new Sequence();
    	     Itemset temp_set = new Itemset();
    	     
    	     temp_set.addItem(L.get(x));
    	     temp_seq.addItemset(temp_set);
    	     
    	     F_one.add(temp_seq);	 
    	 }
    	 
    	 
     }
     
    
     System.out.println("total size L:"+L.size());
     System.out.println("total size F_one:" + F_one.size());
	 
	 //***********************************************************************
	 // Parsing input file complete,  begin remaining code here    
        
	 /*
	
	 At this stage we have:
	 
	L
	F_one
	dbase (the entire input data, arraylist of sequences, one line per entry. Each line may contain one or more itemsets.
	MIS
	SDC
	  
	 */
	 
	//*****************************************************************************************   
    
    
    
     
     ArrayList < ArrayList<Sequence> > F_higher = new ArrayList <ArrayList<Sequence>>();
     ArrayList < ArrayList<Sequence> > candidate = new ArrayList < ArrayList < Sequence >> ();
     ArrayList <Sequence> temp_candidate = new ArrayList <Sequence>();
   
    // This is storing all higher level F's beyond level 1 and all level of candidates
    
    
    // Set the for loop to end at some arbitrary high value
     // The loop will break out when F[k] is a NULL sequence set
     // remember to minus K by 2 when using it as array index
     // here, MAX_LIMIT is the lowest integer divisible by 10, that is greater than total_cust_count
     
     //Uncomment the following line only as an estimate
     MAX_LIMIT = 5; // Assume largest sequence has the length of 5
     
     for (int k=2 ; k <= MAX_LIMIT ; k++ )  // this is line 4 in p.46 in the book
     {
    	     
    	 if (k==2) // line 5 
    	 {
    	   ArrayList<Sequence> l2 = level2CandidateGen(L, dbase, SDC, total_cust_count);
    	   candidate.add(l2);  // Note: Level 2 candidate stored at index 0
    	   F_higher.add(l2);
    	 }
    	 else
    	 {
    	   // Your MS Candidate generation goes here
    	   // Your input: F.get(k-3);  // the previous level F is stored at index k - 3
    	   // Your Output: a temporary arraylist stored to temp_candidate
    	
    	   temp_candidate = level2CandidateGen(L, dbase, SDC, total_cust_count);
    		 
           candidate.add(temp_candidate);	  
    	
    	 } // this is line 8
    
    	// define c_prime
		 ArrayList <Sequence> c_prime = new ArrayList <Sequence>();
		 
		 // make a copy of the c into c_prime
		 c_prime = candidate.get(k-2);
     
    	 //line 9
    	 for (int i=0; i < total_cust_count; i++) // number of transactions = total customer count
    	 {
    		 //line 10
    		 for (int j=0; j < candidate.size(); j++)
    		 {
    			 if ( dbase.contains( candidate.get(j ))) // line 11, if dbase contains any element member of candidate
    			 { 
    				 for (int x = 0; x<candidate.get(j).size(); x++)
    					 candidate.get(j).get(x).incCount();  // line 12
    				 
    				 
    				 
    			 }
				 // removal of lowest MIS item in c_prime
				for (int a=0;a<c_prime.size();a++)
 				{
 					
 					 for (int b=0;b<c_prime.get(a).getSize(); b++)
 					 {
 						 
 						 //because all itemsets are sorted by MIS at the beginning 
 						 //we assume the first item of the itemset is always have the lowest MIS value
 						 //c_prime.get(a).getItemset(b).removeItem(0); //c_prime generation
 					}
 				}
    				 
    				 
    			 if ( dbase.contains( c_prime.get(j) ))	 
    			 {
    				    //line 14
        				 c_prime.get(j).incCount(); 
        				 
        		 } // end line 14
                          
    			 
    			 
    		 }// end line 10 for loop
    		 
    	 }//end line 9 for loop
    
     
      
      /*for (int x=0; x< candidate.get(k-2).size(); x++)
      {
    	int temp4,temp5;
    	
    	// find lowest MIS item in the candidate sequence
    	temp4 = candidate.get(k-2).get(x).getMinIndex();
    	temp5 = Integer.parseInt(candidate.get(k-2).get(x).getItemset(temp4).getMinItem().getName());
    	  
    	// line 17
        if ( (candidate.get(k-2).get(x).getCount() / total_cust_count) != MIS.get(temp5)  )	 
            F_higher.add(candidate.get(k-2));	
      }*/
    	
    	 F_higher.add(candidate.get(k-2));	
    	 
    	 
	 /*
     if (l2.size() == 0)
    	 System.out.println("Fuck me.");
     else {
	     for (Sequence s : l2) {
	    	 System.out.println(s.toString());
	     }
     }*/
        
     }// end for-loop for Higher level-F generation (end line 4)
        
        
     
  // either return or output function goes here
     // the F_one and the F_higher arraylist contains your answer
    System.out.println("Results:");
 	System.out.println("The number of length 1-sequential patterns is "+ (F_one.size()));
 	System.out.println("Pattern:");
 	
 	for (int a=0;a<F_one.size();a++)
 	{
 	      System.out.print(F_one.get(a).toString() + "    ");
 	      System.out.print("Count = " + F_one.get(a).getCount());
 		  System.out.println("");
 	}
 	
 
     for (int b=0; b<F_higher.size(); b++)
     {
    	
    	 int length = b+2;
    	 System.out.println("The number of length "+length+"-sequential patterns is "+ (F_higher.get(b).size()));
    	 System.out.println("Pattern:");
   
    	      
    	      for (int c=0;c<F_higher.get(b).size(); c++)
    	      {
    	    	  System.out.print(F_higher.get(b).get(c).toString() + "    ");
    	 	      System.out.print("Count = " + F_higher.get(b).get(c).getCount());
    	 		  System.out.println("");
    	    	  
    	    	  
    	      }
    	 
     }
     
    }
    catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
	        }
           catch (IOException e) {
         e.printStackTrace();
    } // end main try
  } // end main function
	
	//***************************************************************************************************************************
    //Utility functions
	//*****************************************************************************************************************************
	
	/*
	 * Goes through database and adds counts to Sequences in candidates ArrayList
	 */
	public static void countSequences(ArrayList<Sequence> dbase, ArrayList<Sequence> candidates, int n) {
		for (int i = 0; i < dbase.size(); i++) {
			Sequence s = dbase.get(i);
			for (int j = 0; j < candidates.size(); j++) {
				if (s.isSupersequenceOf(candidates.get(j)))
					candidates.get(j).incCount();
			}
		}
	}
	//*******************************************************
	
	
	/*
	 * Generates F2 candidate sequences and prunes them based on MIS and SDC
	 */
	public static ArrayList<Sequence> level2CandidateGen(ArrayList<Item> cap_l, ArrayList<Sequence> dbase, Double sdc, int n) {
		ArrayList<Sequence> candidates = new ArrayList<Sequence>();
		for (int i = 0; i < cap_l.size(); i++) {
			if (Double.valueOf((double)cap_l.get(i).getCount() / (double)n) >= cap_l.get(i).getMinsup()) {
				for (int j = i + 1; j < cap_l.size(); j++) {
					if (Double.valueOf((double)cap_l.get(j).getCount() / (double)n) >= cap_l.get(j).getMinsup()
							&& Math.abs(Double.valueOf((double)cap_l.get(j).getCount() / (double)n) - Double.valueOf((double)cap_l.get(i).getCount() / (double)n)) <= sdc) {
						Sequence candidate = new Sequence();
						Itemset l = new Itemset();
						Itemset h = new Itemset();
						Itemset lh = new Itemset();
						
						l.addItem(cap_l.get(i));
						h.addItem(cap_l.get(j));
						candidate.addItemset(l);
						candidate.addItemset(h);
						candidates.add(candidate);
						
						lh.addItem(cap_l.get(i));
						lh.addItem(cap_l.get(j));
						candidate = new Sequence();
						candidate.addItemset(lh);
						candidates.add(candidate);
					}
				}
			}
		}
		// Prune step
		for (Sequence s : candidates) {
			s.setLength();
			s.setMinsup();
			countSequences(dbase, candidates, n);
			if ((double)s.getCount() / (double)n < s.getMinsup())
				candidates.remove(s);
		}
		for (int i = 0; i < candidates.size(); i++) {
			if (!candidates.get(i).isInSDC(sdc))
				candidates.remove(i);
		}
		return candidates;
	};
	//*******************************************************
	
// return L value
	// preconditon: sorted Item list by MIS, item frequency array, total item count
	
	public static ArrayList<Item> L_Generation(ArrayList<Item> sortedItem,
			int[] frequency, int total_count) {
		
		ArrayList <Item> temp = new ArrayList <Item>();
	
		double dummy = 0.0;
		double temp_MIS = 0.0;
		int temp1 = 0;
		
		
		for ( int x = 0 ; x < sortedItem.size(); x++)
		{
			temp1 = Integer.parseInt(sortedItem.get(x).getName())-1;
			
			dummy = (double)frequency[temp1] / (double)total_count;
			temp_MIS = sortedItem.get(x).getMinsup();
			
			System.out.println(temp1+" "+dummy+" "+temp_MIS+" ");
			
			// add item to L if item count divided by total is greater than MIS
			if (dummy >= temp_MIS) temp.add(sortedItem.get(x));
			
		}
		
		return temp;
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
                    temp.setCount(items.get(i).getCount());

                    items.get(i).setName(items.get(j).getName());
                    items.get(i).setMinsup(items.get(j).getMinsup());
                    items.get(i).setCount(items.get(j).getCount());

                    items.get(j).setName(temp.getName());
                    items.get(j).setMinsup(temp.getMinsup());	
                    items.get(j).setCount(temp.getCount());
                }
            }
        }
        return items;
    }

    
 //*********************************************
	//Get the items count for each item
  // precondition: list of items, DB

 /*   public static int [] makeCount(ArrayList<Item> items, ArrayList<Sequence> DB)
    {   
        
    	int[] count = new int [items.size()];
    	
    	// count array initialization
    	for (int l=0 ; l<=items.size()-1 ; l++)
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
                            count[l]++;
                            continue nextSequence;				
                        }
                    }
                }
            }
        }
        
       
		return count;
   
 }*/
	
    //******************************
    //create an itemset (part of DB creation process)
    //precondition: name string (which is just a number in this case), and the MIS array
 
    public static Itemset createItemSet(int[] frequency, String itemSetString, ArrayList<Double> MIS)
    {
        Itemset itemSet = new Itemset();

        int beginIndex = 0;
        int i = 0;

        while (i < itemSetString.length())
        {
            while(itemSetString.charAt(i) == '{')
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
            String itemName = itemSetString.substring(beginIndex, i);
            item.setName(itemName);
            
            String parsedName;
            
            if (itemName.length() >= 2) // get rid of leading space
            {
                parsedName = itemName.trim();
            
            }
            else parsedName = itemName;
                                
			item.setMinsup(MIS.get( Integer.parseInt(parsedName) -1 ));
			
			
			frequency[Integer.parseInt(parsedName) -1]++;
			item.setCount(frequency[Integer.parseInt(parsedName) -1]);
            		 	 
            itemSet.addItem(item);

            i = i + 1;
        }    	
        return itemSet;
    }
    
// ********************************************    
//  building the database
//  Precondition: input file name, MIS array
    
    public static ArrayList<Sequence> createDB(int[] frequency, String Data, ArrayList <Double> MIS)
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

                        itemSet =  createItemSet(frequency,itemSetString, MIS);

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

