import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

/*
 * This is the class used to read input from files
 */

public class ReadFileInput {
	
	/*
	 * @Func: Read MIS vector from input file
	 * @Param: File name
	 * @Return: A HashMap whose key is the itemID(Integer), value is corresponding minimum support(Float) 
	 */
	public static HashMap<Integer,Float> readParameters(String filename){
		HashMap<Integer,Float> mis=new HashMap<Integer,Float>();
		try{
			
			
				
				
				/*String record=f.nextLine(); //read each line in parameter-file.txt
				if(f.hasNextLine()){
					// extract the itemID
					Integer itemID=Integer.valueOf(record.substring(record.indexOf('(')+1, record.indexOf(')')));
					// extract the minimum item support
					Float itemMIS=Float.valueOf(record.substring(record.indexOf('=')+2)); // There must be a space after '=' to make this line work
					mis.put(itemID,itemMIS);
				}else{ // last line, read SDC
					MSGSP.SDC=Float.valueOf(record.substring(record.indexOf('=')+2));
					break;*/
					
			boolean SDC_FLAG = false;
			
			FileInputStream FIS = new FileInputStream(filename);
			 
	        BufferedInputStream BIS = new BufferedInputStream(FIS);
	        DataInputStream DIS = new DataInputStream(BIS);
	        
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
	     		 MSGSP.SDC = Double.valueOf(line.substring(j+1, line.length()));
	     		 //System.out.println ("SDC="+SDC); // output to console - for debug purpose only
	     		 break; // break out the for loop; parameter reading is over
	     	  }
	     	  else
	     	  {
	     		 int j = line.indexOf('=');
	        	 //MIS.add(Double.valueOf(line.substring(j+1, line.length())));
	     		 mis.put(printcount, Float.valueOf(line.substring(j+1, line.length())));
	        	 //System.out.println ("MIS"+printcount+"="+MIS.get(printcount-1)); // output to console - for debug purpose only
	     	  }
	     	  printcount=printcount+1;
	     	  
	     	} // end while(DIS.avaliable)
	         
	        FIS.close();
	        BIS.close();
	        DIS.close();	
			
			
				
				
			
			return mis;
		}catch(IOException e){
			e.printStackTrace();
		}
		return null;
	}
	
	/*
	 * @Func: Read MIS vector from input file
	 * @Param: File name
	 * @Return: A HashMap whose key is the itemID(Integer), value is corresponding minimum support(Float) 
	 */
	public static ArrayList<Transaction> readData(String filename){
		ArrayList<Transaction> trans=new ArrayList<Transaction>();
		try{
			File file = new File(filename);
			BufferedReader f=new BufferedReader(new FileReader(file));
			String record=f.readLine();
			while(record != null){
				Transaction transaction=new Transaction(); // create a new transaction 
				//index for next open parenthesis in current line
				int idxOpenParen=record.indexOf('{'); 
				//index for next closed parenthesis in current line
				int idxClosedParen=record.indexOf('}');
				
				while(idxOpenParen<record.length()-1){
					ItemSet is=new ItemSet(); // create an new itemset for this transaction 
					//index for next comma between current open parentheses
					int idxComma=record.indexOf(',',idxOpenParen); 
					//index indicating the starting position of next number within current parentheses
					int idxNumStart=idxOpenParen+1;
					//index indicating the ending position of next number within current parentheses. The character on this position is either a '}' or ','.
					int idxNumEnd=min(idxClosedParen,idxComma);
										
					while(idxNumEnd<=idxClosedParen){
						is.items.add(Integer.valueOf(record.substring(idxNumStart,idxNumEnd).trim())); // add an item to the itemset
						if(idxNumEnd==idxClosedParen) //reach the end of the itemset
							break;
						// locate beginning and ending positions for next item in the current itemset
						idxNumStart=idxComma+1;
						idxComma=record.indexOf(',',idxNumStart); 
						idxNumEnd=min(idxClosedParen,idxComma);
					}
																
					// locate beginning and ending positions for next itemSet
					idxOpenParen=idxClosedParen+1;
					idxClosedParen=record.indexOf('}',idxOpenParen);
					transaction.itemSets.add(is); // add an itemSet to the current transaction
				}
				
				trans.add(transaction);  // add an transaction to the database
				record=f.readLine();
			}
			return trans;
		}catch(IOException e){
			e.printStackTrace();
		}
		return null;
	}
	
	public static int min(int idxClosedParen, int idxComma){
		if(idxComma<0)
			return idxClosedParen;
		else
			return idxClosedParen<idxComma?idxClosedParen:idxComma;
	}
	
	 	

}
