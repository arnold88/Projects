//new MSGSP

// 2013-09-25

import java.io.*;
import java.math.*;
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
	    String Output = "C:\\users\\user\\output.txt";
	    int MAX_LIMIT = 10; // initial item variety limit, set this low
	    int total_item_count = 0;
	    int total_cust_count = 0;
        
    	//double[] MIS = new double [MAX_LIMIT];
	    ArrayList <Double> MIS = new ArrayList<Double>();
	    
	    
    	float SDC = (float) 0.0;
    	
    	
    	
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
     		 
     		 BigDecimal tempSDC = new BigDecimal(Float.parseFloat(line.substring(j+1, line.length())));
     		 
     		 // SDC = Float.parseFloat(line.substring(j+1, line.length()));
     		 
     		 BigDecimal tempmult = new BigDecimal (10000);
     		 
     		 
    
     		 SDC = tempSDC.floatValue();
     		 
     		 System.out.println ("SDC="+SDC); // output to console - for debug purpose only
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
//        int [] frequency = new int [MIS.size()]; // get item frequency count
//        
//        for (int x=0;x<MIS.size();x++) // initialization
//        {
//        	
//        	frequency[x] = 0;
//        	
//        }
        HashMap<Item, Boolean> items = new HashMap<Item, Boolean>();
        for (int i = 1; i < 50; i++) {
        	Item item = new Item(Integer.toString(i), MIS.get(i - 1));
        	items.put(item, false);
        	
        	
        	
        }
        
        dbase = createDB(items,Data,MIS); // list of all sequences
        
        //test output of frequency and calculate aggregate item total
        
//        for (int x=0;x<frequency.length;x++)
//        {
//     	   int z = x+1;
//     	   //System.out.println ("freq of "+z+" is: " + frequency[x]);
//     	   total_item_count = total_item_count + frequency[x];
//     	   
//        }
        
        for (Item i : items.keySet()) {
        	total_item_count += i.getCount();
        }
        
        //System.out.println ("total item count is: " + total_item_count);
        
        
        
        //******************************************************************************
        
        
        
        // sort item according to frequency on ascending order
//        for (int x = 0; x<=MIS.size()-1 ; x++)
//        {
//        	Item new_Stuff = new Item ();
//        	
//        	new_Stuff.setName( Integer.toString(x+1) );
//        	new_Stuff.setMinsup(MIS.get(x));
//        	new_Stuff.setCount(frequency[Integer.parseInt(new_Stuff.getName()) - 1]);
//        	
//        	sortedItem.add(new_Stuff);
//        	
//        	
//        }
//        
//        sortedItem = sortItems(sortedItem);
        // item list is finally sorted by MIS
        
     //   int[]itemCount = new int [MIS.size()+1];
        
     
     //  itemCount = makeCount (sortedItem,dbase);
        
        
        //test print the items
//       for (int i = 0; i < dbase.size() ; i++)
//       {
//    	   System.out.println ("Customer "+(Integer.toString(i+1)));
//    	   
//    	   for (int j = 0; j < dbase.get(i).getSize()  ; j++)
//    	   {
//    		   
//    		   System.out.println ("Itemset "+(Integer.toString(j+1)));
//    		   
//    		   for (int k = 0; k < dbase.get(i).getItemset(j).getSize(); k++)
//    		    
//    		   {
//    			   
//    			   
//    		   System.out.print (dbase.get(i).getItemset(j).getItem(k).getName());
//    		   System.out.print ("("+dbase.get(i).getItemset(j).getItem(k).getMinsup()+")");
//    		   
//    		   
//    		   
//    		   
//    		   }
//    		   
//    		   System.out.println ("");
//    		   
//    	   }
//    		 
//    	   
//    	   
//       }// end test output  --- comment this entire section in real mode
       
    
     total_cust_count = dbase.size(); // total amount of customers (lines in the input data file)  
     
     // L generation
     ArrayList<Item> map = new ArrayList<Item>();
     for (Item i : items.keySet())
    	 map.add(i);
     L = L_Generation(map,total_cust_count);
     
     //***** 
     
     //F1 generation
    
     ArrayList <Sequence> F_one = new ArrayList <Sequence>();
     
     // this is line 3, p.46 in the book
     
     for (int x=0; x < L.size(); x++)  
     {
    	  BigDecimal ans = new BigDecimal (0);
		  
		  BigDecimal lhs = new BigDecimal(L.get(x).getCount());
		  
		  BigDecimal rhs = new BigDecimal (total_cust_count);
		 
		  ans = lhs.divide(rhs, 8, BigDecimal.ROUND_FLOOR);
    	 
    	  float temp2 = ans.floatValue();
		  
    	// float temp2 = (float)L.get(x).getCount() / (float)total_cust_count;
    	 
    	 int temp_index = Integer.parseInt(L.get(x).getName()) -1;
    	 
    	 if (temp2 >= MIS.get(temp_index)) // single-item sequence will be included in F_one
    	 {
    		 
    		 
    		 Sequence temp_seq = new Sequence();
    	     Itemset temp_set = new Itemset();
    	     
    	     temp_set.addItem(L.get(x));
    	     temp_seq.addItemset(temp_set);
    	     temp_seq.setCount(dbase, total_cust_count);
    	     F_one.add(temp_seq);
    	     
    		 
    	 }
    	 
    	 
     }
     
//     System.out.println("total size F_one:" + F_one.size());
//     System.out.println("total size L:"+L.size());
     
	 
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
     
    int max_length = -1;
    for (Sequence s : dbase) {
    	s.setLength();
    	if (s.getLength() > max_length)
    		max_length = s.getLength();
    }
    
     
     ArrayList < ArrayList<Sequence> > F_higher = new ArrayList <ArrayList<Sequence>>();
     //ArrayList < ArrayList<Sequence> > candidate = new ArrayList < ArrayList < Sequence >> ();
   
    // This is storing all higher level F's beyond level 1 and all level of candidates
    
    
    // Set the for loop to end at some arbitrary high value
     // The loop will break out when F[k] is a NULL sequence set
     // remember to minus K by 2 when using it as array index
     // here, MAX_LIMIT is the lowest integer divisible by 10, that is greater than total_cust_count
     for (int k=2 ; k <= MAX_LIMIT ; k++ )  // this is line 4 in p.46 in the book
     {
    	 ArrayList<Sequence> temp_candidate = new ArrayList<Sequence>();
    	 ArrayList<Sequence> temp_f = new ArrayList<Sequence>();

    	 if (k==2) // line 5 
    	 {
    	   temp_candidate = level2CandidateGen(L, dbase, SDC, total_cust_count);
//    	   countSequences(dbase, temp_candidate, total_cust_count);
    	   //candidate.add(l2);  // Note: Level 2 candidate stored at index 0
    	 }
    	 else
    	 {
                   
    	
    	   // Your MS Candidate generation goes here
    	   // Your input: F_higher.get(k-3);  // the previous level F is stored at index k - 3
    	   // Your Output: a temporary arraylist stored to temp_candidate
    	
    	   // temp_candidate = level2CandidateGen(L, dbase, SDC, total_cust_count);
    		 
    	   temp_candidate = MScandidateGen(F_higher.get(k - 3), dbase, total_cust_count);
           //candidate.add(temp_candidate);	  
    	
    	 } // this is line 8
    	 
    	 System.out.println("Generated length " + k + " candidates.");
    	  
    	 //line 9 - 12
    	 countSequences(dbase, temp_candidate, total_cust_count);
    	 
    	 //line 13 - 14
//    	 for (Sequence c : temp_candidate) {
//    		 boolean inSDC;
////    		 System.out.println(c.toString() + "\t: " + c.getCount() + "\t: " + (double)c.getCount() / (double)total_cust_count + "\t: " + c.getMinsup());
//   			 if (c.getFrequent()) {
//   				 inSDC = true;
//   				 for (Itemset is : c.getSequence()) {
//   					 if (!is.isInSDC(SDC, total_cust_count))
//   						 inSDC = false;
//   				 }
//   			 	 if (inSDC) temp_f.add(c);
//   				//if (c.isInSDC(SDC, total_cust_count)) temp_f.add(c);
//   			 	 	
//   			 }
//   		 }
    	 temp_f = pruneCandidates(temp_candidate, dbase, SDC, total_cust_count);
    	 
    	 if (temp_f.size() == 0)
    		 break;
    	 
    	 System.out.println("Added " + temp_f.size() + " length-" + k + " frequent sequences.");
    	 F_higher.add(temp_f);

     }
    }
    
  
     /*
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
     */
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
		for (Sequence c : candidates) {
			c.setCount(dbase, n);
		}
	}
	//*******************************************************
	
	
	/*
	 * Generates F2 candidate sequences
	 */
	public static ArrayList<Sequence> level2CandidateGen(ArrayList<Item> L, ArrayList<Sequence> dbase, float sdc, int n) {
		ArrayList<Sequence> candidates = new ArrayList<Sequence>();
		ItemComp comp = new ItemComp();
		
		for (int i = 0; i < L.size(); i++) {
			if (L.get(i).getSup() >= L.get(i).getMinsup()) {
				for (int j = i; j < L.size(); j++) {
						if (L.get(j).getSup() >= L.get(i).getMinsup()) {
							Sequence candidate = new Sequence();
							Itemset l = new Itemset(); // {l}
							Itemset h = new Itemset(); // {h}
							Itemset lh = new Itemset();// {l, h}
							l.addItem(L.get(i));
							h.addItem(L.get(j));
							if (Math.abs(L.get(j).getSup() - L.get(i).getSup()) <= sdc) {
								if (comp.compare(L.get(i), L.get(j)) <= 0) {
									lh.addItem(L.get(i));
									lh.addItem(L.get(j));
								} else {
									lh.addItem(L.get(j));
									lh.addItem(L.get(i));
								}
								if (!L.get(i).equals(L.get(j))) {
									candidate.addItemset(lh);
									candidates.add(candidate);
								}
								candidate = new Sequence();
								candidate.addItemset(l); candidate.addItemset(h); // <{l}{h}>
								candidates.add(candidate);
								
								if (!L.get(i).equals(L.get(j))) {
									candidate = new Sequence();
									candidate.addItemset(h); candidate.addItemset(l); // <{h}{l}>
									candidates.add(candidate);
								}
							}
						}
				}
			}
		}
//		for (Sequence c : candidates)
//			System.out.println(c.toString() + "\t:\t" + c.getFrequent());
		return candidates;
	}
	//*******************************************************
	
	public static ArrayList<Sequence> MScandidateGen(ArrayList<Sequence> f, ArrayList<Sequence> dbase, int n) {
		ArrayList<Sequence> candidates = new ArrayList<Sequence>();
		ItemComp comp = new ItemComp();
		// Join step
		for (int i = 0; i < f.size(); i++) {
			for (int j = 0; j < f.size(); j++) { // line 1
				Sequence s_1 = f.get(i); Sequence s_2 = f.get(j);
				s_1.setLength(); s_1.setMinsup(); s_2.setLength(); s_2.setMinsup();
				Sequence c_1 = s_1.copy(); Sequence c_2 = s_2.copy();
				
				if (s_1.getFirst().equals(s_1.getMin())) { //line 2
					if (c_1.removeSecond().equals(c_2.removeLast()) && // (1)
							s_2.getLast().getMinsup() > s_1.getFirst().getMinsup()) { // (2)
						Sequence candidate_a = s_1.copy();
						//Sequence candidate = s_1.copy();
						if (s_2.getItemset(s_2.getSize() - 1).getSize() == 1) { // last item {l} in s_2 is a separate element
							candidate_a.addItemset(s_2.getItemset(s_2.getSize() - 1)); // adds single-Item Itemset {l} to the end of s_1 as a candidate
							candidates.add(candidate_a); 
							if ((s_1.getLength() == 2 && s_1.getSize() == 2) && // if s_1 has two Itemsets with one Item in each e.g., <{x}{y}> AND
									(comp.compare(s_2.getLast(), s_1.getLast()) > 0)) {
								Sequence candidate_2 = s_1.copy();
								candidate_2.getItemset(s_1.getSize() - 1).addItem(s_2.getLast());
								candidates.add(candidate_2);
							}
						}
						else if (((s_1.getLength() == 2 && s_1.getSize() == 1) && // length of s_1 is 2 and size is 1 e.g., <{x, y}> AND
								(comp.compare(s_2.getLast(), s_1.getLast()) > 0)) || // last item in s_2 > last item in s_1 OR
										(s_1.getLength() > 2)) { // s_1 length is greater than 2
							candidate_a.getItemset(candidate_a.getSize() - 1).addItem(s_2.getLast());
							candidates.add(candidate_a.reverse());
						}	
					}
				}
				else if (s_2.getLast().equals(s_2.getMin())) { // line 3 if the MIS value of the last item in s_2 is the minsup of s_2
					Sequence candidate_b = s_2.reverse().copy();
					if (s_1.reverse().getItemset(0).getSize() == 1) { // the last item in s_1 is a separate element
						candidate_b.addItemset(s_1.reverse().getItemset(0)); // that itemset is appended to s_2 for a candidate
						candidates.add(candidate_b.reverse());
						if (s_2.getLength() == 2 && s_2.getSize() == 2 && comp.compare(s_1.reverse().getLast(), s_2.reverse().getLast()) > 0) { // the length of s_2 is 2 and size of s_2 is 1 AND last item of s_1 > last item of s_2
							Sequence candidate_2 = s_2.reverse().copy();
							candidate_2.addItem(s_1.reverse().getLast(), candidate_2.getSize() - 1); // add last item of s_1 to end of s_2 to form candidate
							candidates.add(candidate_2.reverse());
						}
					}
					else if ((s_2.reverse().getLength() == 2 && s_2.reverse().getSize() == 1 && comp.compare(s_2.reverse().getLast(), s_1.reverse().getLast()) > 0) || // the length of s_2 is 2 and size of s_2 is 1 AND last item of s_1 > last item of s_2 s_2 is 1
							s_2.getLength() > 2) {
						candidate_b.getItemset(candidate_b.getSize() - 1).addItem(s_1.reverse().getLast()); // last item of s_1 is added to end of last item of s_2
						candidates.add(candidate_b.reverse());
					}
				}
				else { // line 4
					if (c_1.removeFirst().equals(c_2.removeLast())) { // if the s_1 minus first = s_2 minus last
						//Sequence candidate_7 = s_1.copy();
						Sequence candidate_a = s_1.copy();
						if (s_2.getItemset(s_2.getSize() - 1).getSize() == 1) { // if the last item in s_2 was a separate element
							candidate_a.addItemset(s_2.getItemset(s_2.getSize() - 1)); // last itemset is appended to s_1
							candidates.add(candidate_a);
						} else { // otherwise
							candidate_a.getItemset(candidate_a.getSize() - 1).addItem(s_2.getLast()); // last item of s_2 is added to end of last itemset of s_1
							candidates.add(candidate_a);
						}
					}
				}
			}
		}
		// Prune Step
		ArrayList<Sequence> prunedCandidates = new ArrayList<Sequence>();
		//countSequences(candidates, dbase, n);
		for (Sequence s : candidates) prunedCandidates.add(s);
		for (Sequence c : candidates) {
			for (int j = 0; j < c.getSize(); j++) {
				for (int k = 0; k < c.getItemset(j).getSize(); k++) { 
					Sequence temp = c.copy();
					temp.removeItem(j, k);
					temp.setCount(dbase, n);
					// subsequence where item at j, k is removed
					if (temp.getMin().equals(c.getMin())) { // if subsequence contains item with lowest MIS
						if (!temp.getFrequent()) {
							prunedCandidates.remove(c);
							break;
						}
					}
				}
			}
		}
//		for (Sequence c : prunedCandidates)
//			System.out.println(c.toString());
		return prunedCandidates;
	}
	//**************************************************************
	
	public static ArrayList<Sequence> pruneCandidates(ArrayList<Sequence> candidates, ArrayList<Sequence> dbase, double sdc, int n) {
		ArrayList<Sequence> prunedCandidates = new ArrayList<Sequence>();
		
		for (Sequence c : candidates) {
		   		 
			 //System.out.println(c.toString() + "\t:" + c.getFrequent() + "\t: " + c.getCount() + "\t: " + (double)c.getCount() / (double)n + "\t: " + c.getMinsup());
			 //boolean inSDC = false;
			 if (c.getFrequent()) {
//				for (Itemset is : c.getSequence()) {
//					if (is.isInSDC(sdc, n)) {
//						inSDC = true;
//						continue;
//					} else {
//						inSDC = false;
//					}
//				}
				if (c.isInSDC(sdc, n)) prunedCandidates.add(c);
					
				//if (c.isInSDC(SDC, total_cust_count)) temp_f.add(c);
			 	 	
			 }
		 }
		for (Sequence c : prunedCandidates) 
			System.out.println(c.toString());
		return prunedCandidates;
	}
	
// return L value
	// preconditon: sorted Item list by MIS, item frequency array, total item count
	
	public static ArrayList<Item> L_Generation(ArrayList<Item> items, int total_count) {
		
		ArrayList <Item> temp = new ArrayList <Item>();
	
//		double dummy = 0.0;
//		double temp_MIS = 0.0;
//		int temp1 = 0;
//		
		
		for (Item i : items)
		{
//			temp1 = Integer.parseInt(sortedItem.get(x).getName())-1;
			
//			dummy = (double)frequency[temp1] / (double)total_count;
//			temp_MIS = sortedItem.get(x).getMinsup();
			
//			System.out.println(temp1+" "+dummy+" "+temp_MIS+" ");
//			System.out.println(sortedItem.get(x).getMinsup());
			
			// add item to L if item count divided by total is greater than MIS
			//if (dummy >= temp_MIS) 
			i.setSup(total_count);
			temp.add(i);
			
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
                	//What the hell is going on here?
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
 
    public static Itemset createItemSet(HashMap<Item, Boolean> items, String itemSetString, ArrayList<Double> MIS)
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
            //Item item = new Item();
            String itemName = itemSetString.substring(beginIndex, i);
            //item.setName(itemName);
            
            String parsedName;
            
            if (itemName.length() >= 2) // get rid of leading space
            {
                parsedName = itemName.trim();
            
            }
            else parsedName = itemName;
                                
			//item.setMinsup(MIS.get( Integer.parseInt(parsedName) -1 ));
			Item item = new Item(parsedName, MIS.get(Integer.parseInt(parsedName) - 1));
			
			//item.setCount(frequency[Integer.parseInt(parsedName) -1]);
			for (Item t : items.keySet()) {
				if (t.getName().equals(parsedName))
					items.put(t, true);
			}
            
            itemSet.addItem(item);

            i = i + 1;
        }
        return itemSet;
    }
    
// ********************************************    
//  building the database
//  Precondition: input file name, MIS array
    
    public static ArrayList<Sequence> createDB(HashMap<Item, Boolean> items, String Data, ArrayList <Double> MIS)
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

                        itemSet =  createItemSet(items,itemSetString, MIS);

                        //Add to sequences -  changed
                        sequence.addItemset(itemSet);
                    }
                }
                for (Item t : items.keySet()) {
                	if (items.get(t) == true) t.incCount();
                	items.put(t, false);
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

