import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.lang.Math;
import java.util.*;



/*
 *
 * The core class that does most of the MS-GSP computation
 * This class implements the sequence generation logic for both level2 and
 * higher k-itemset sequences.
 */

public class MSGSP {

    public static void main(String[] args) {


        if ( args.length < 1 )
        {
            System.out.println("Usage: java MSGSP <folder path>");
            System.exit(0);
        }

        String folderPath = args[0] + "\\"  ;
        String pathData = folderPath + "data.txt";
        String pathParam = folderPath + "parameter-file.txt";
        String pathOut = folderPath + "pattern-output.txt";
        String pathTestCandidate = folderPath + "candidate.txt";

        ArrayList<Item> MS = new ArrayList<Item>();
        ArrayList<Item> M = new ArrayList<Item>();
        ArrayList<Item> L = new ArrayList<Item>();
        ArrayList<Sequence> data = new ArrayList<Sequence>();
        ArrayList FinalSequence = new ArrayList();

        double[] mySDC = new double[1];
        double SDC = 0.0;

        //TestCandidateGen();
        //if ( 1==1 ) System.exit(1);

        Init init = new Init();

        // Load all items - from parameter-file.txt without sorting
        MS = init.createMS(pathParam, mySDC);
        SDC = mySDC[0];

        //After here, you can get SDC by using SDC[0]
        System.out.println(SDC);

        // List of items sorted by min sup
        M = init.sortItems(MS);

        // Load all the sequences into S - from data.txt
        data = init.createSequences(pathData, M);

        System.out.println("Data");
        Util.ps(data);

        // calculate item count.
        L = init.initPass(M, data);

        // create F1
        ArrayList<Sequence> F1 = calculateF1(L, data);
        Util.setCount(data, F1);
        System.out.println("F_1");
        Util.ps(F1);
        FinalSequence.add(F1);

        ArrayList<Sequence> prevF = F1;
        for ( int k = 2; prevF.size() > 0 ; k++ )
        {
            ArrayList<Sequence> candidate = new ArrayList<Sequence>();
            if ( k==2 )
            {
                candidate = level2_candidate_gen_SPM(L, data.size(), SDC );
                //Util.ps(candidate);
            }
            else
            {
                //if ( k>2 ) System.exit(1);
                System.out.println("\n\n***Generating F"+k + "****");
                candidate =   MScandidateGenSPM(prevF, SDC, data.size());
            }

            Util.setCount(data, candidate);	

            ArrayList<Sequence> nextF = new ArrayList<Sequence>();
            for ( int kk=0 ; kk < candidate.size(); kk++ )
            {
                Sequence s = candidate.get(kk);
                if ( Double.valueOf(s.getCount())/data.size() >= s.getMinItem().getMinSup() )
                {
                    nextF.add(s);

                    /*if ( k==3)
                    {
                        System.out.println( "value" +  Double.valueOf(s.getCount())/data.size() + "," +  s.getMinItem().getMinSup() );
                        Util.p1s(s);
                    }*/
                }
                else
                {
                     /*if ( k==2)
                       {
                       System.out.println("Candidate dropped :" + (double)s.getCount()/data.size() + ", " + s.getMinItem().getMinSup() );
                       Util.p1s(s);
                       }*/
                }
            }	
            prevF = nextF;
            System.out.println("\n\nFrequencySet_k-"+k);
            Util.printAllSequences(nextF);


            FinalSequence.add(nextF);
        }	

        //Write F1 to file
        try
        {
            File outputFile = new File(pathOut);
            BufferedWriter output = null;
            output = new BufferedWriter(new FileWriter(outputFile));

            for(int i = 0; i < FinalSequence.size(); i++)
            {
                ArrayList<Sequence> sequence = (ArrayList<Sequence>)FinalSequence.get(i);
                init.writeOutput(sequence, i+1, output,  data.size());
            }

            output.close();
        }
        catch(IOException e){
            System.err.println("Cannot save file");
        }

    }

    /* Generates the sequences for level2_candidates*/
    public static ArrayList<Sequence> level2_candidate_gen_SPM(ArrayList<Item> L, Integer transCount, double SDC){
        ArrayList<Sequence> C2=new ArrayList<Sequence>();
        for (int i=0; i< L.size();i++)
        {
            
                for (int j=0;j< L.size();j++)
                {

                    if ( Double.valueOf(L.get(i).getCount())/transCount >=L.get(i).getMinSup() 
                         || Double.valueOf(L.get(j).getCount())/transCount >=L.get(j).getMinSup() 
                         ) 
                    {
                    if ( 
                            ( Math.abs ( (Double.valueOf(L.get(j).getCount())/transCount) - (Double.valueOf(L.get(i).getCount())/transCount) ) <= SDC  )
                       )
                    {

                        //System.out.println(L.get(j).getName() + ": " + L.get(j).getCount() + " , "  + L.get(i).getName() + " : " + L.get(i).getCount()  );	
                        //System.out.println(  Math.abs((Double.valueOf(L.get(j).getCount())/transCount) - (Double.valueOf(L.get(i).getCount())/transCount) ))  ;

                        Sequence c1=new Sequence();         //create <>
                        ItemSet nci1=new ItemSet();         //create {}
                        nci1.addItem(L.get(i));             //create {x} 
                        c1.addItemSet(nci1);                //create <{x}>
                        ItemSet ncj1=new ItemSet();         //create {} 
                        ncj1.addItem(L.get(j));             //create {y}
                        c1.addItemSet(ncj1);                //create <{x},{y}> 
                        C2.add(c1);                         //C2= <{x},{y}> 

                        if ( L.get(i).getName().compareTo(L.get(j).getName()) < 0 ) 
                        {

                            Sequence c2=new Sequence();         //create another <>
                            ItemSet nci2=new ItemSet();         //create another {}
                            nci2.addItem(L.get(i));             //create {x}
                            c2.addItemSet(nci2);                //create <{x}>

                            c2.addNewItemAtLastSet(L.get(j));   //create <{x,y}>
                            C2.add(c2);                         //C2= <{x},{y}> <{x,y}>

                            /*
                            Sequence c3=new Sequence();
                            ItemSet nci3=new ItemSet();
                            nci3.addItem(L.get(j));
                            c3.addItemSet(nci3);
                            c3.addItemSet(new ItemSet().addItem(L.get(i)));
                            C2.add(c3);        
                            */
                        
                        }
                    }
                }
            }
        }
        return C2;
    }


   
    public static ArrayList<Sequence> MScandidateGenSPM(ArrayList<Sequence> Fk_1, double SDC, Integer transCount){
        ArrayList<Sequence> CK=new ArrayList<Sequence>();

        int prevSize = 0;
        String trace = "";
        for (int i=0; i< Fk_1.size();i++){                 
            for (int j=0; j< Fk_1.size();j++){        


                trace = ""; // this variable is used to trace the creation of sequence. for debugging only
                /* Copy Sequence*/
                Sequence s1=Fk_1.get(i);
                Sequence s2=Fk_1.get(j);

                //System.out.println("Comparing sets..");
                //Util.p1s(s1);
                //Util.p1s(s2);

                //System.out.println("next...");
                Sequence c1 =s1.copySeq(s1);
                Sequence c2 =s1.copySeq(s1);

                Sequence ss2=s1.reVerse(s1);                           
                Sequence ss1=s2.reVerse(s2);                         

                if ( checkAbsoluteMinSup(s1)  //If the 1st item's MIS is the minimum
                        &&	 
                        ( s1.copySeq(s1).removeSecItem().isSequenceSame(s2.copySeq(s2).removeLastItem()))
                        &&
                        (s2.getLastItem().getMinSup() > s1.getItem(0,0).getMinSup()) )
                {

                    trace = trace.concat("a");
                    
                    if ( s2.getLastItemSet().getItems().size()==1 ){
                        ItemSet newTemp = new ItemSet();
                        newTemp.addItem(s2.getLastItem());
                        c1.addItemSet(newTemp);
                        CK.add(c1);

                        //System.out.println("In condition      ..............3.2");
                        trace = trace.concat("b");

                        if ( ((s1.seqSize()==2) && (s1.seqLength()==2))
                                && (s2.getLastItem().getName().compareTo(s1.getLastItem().getName()) > 0 )){

                            //System.out.println("In condition      ..............3.4");
                            //Util.p1s(c2);
                            trace = trace.concat("c");
                            if ( c2.addNewItemAtLastSet(s2.getLastItem()) )
                            {

                                trace = trace.concat("d");
                                CK.add(c2);
                            }
                                }

                    }
                    else if(
                            (
                             ( (s1.seqLength()==2) && (s1.seqSize()==1) )
                             && 
                             ( s2.getLastItem().getName().compareTo(s1.getLastItem().getName()) > 0 )
                            )
                            ||( s1.seqLength()>2 )){
                        trace = trace.concat("e");			


                        //System.out.println("Condition..3.5");
                        //Util.p1s(c1);        
                        if ( c1.addNewItemAtLastSet(s2.getLastItem()))
                        {
                            trace  = trace.concat("f");

                            CK.add(c1);
                        }
                            }	   
                }
                else if (checkAbsoluteMinSup(s2.reVerse(s2))
                        &&  
                        ( ss1.copySeq(ss1).removeSecItem().isSequenceSame(ss2.copySeq(ss2).removeLastItem()))
                        &&
                        (ss2.getLastItem().getMinSup() > ss1.getItem(0,0).getMinSup()) )
                { 

                    trace = trace.concat("g");
                    Sequence newSS1 = ss1.copySeq(ss1);
                    Sequence newSS2 = ss2.copySeq(ss2);

                    //System.out.println(trace);
                    //Util.p1s(ss2);

                    if ( ss2.getLastItemSet().getItems().size()==1 ){
                        ItemSet newTemp = new ItemSet();
                        newTemp.addItem(ss2.getLastItem());
                        newSS1.addItemSet(newTemp);
                        CK.add(newSS1.reVerse(newSS1));

                        trace = trace.concat("2");

                        if ( ((ss1.seqSize()==2) && (ss1.seqLength()==2))
                                && (ss2.getLastItem().getName().compareTo(ss1.getLastItem().getName()) < 0  )){
                            trace = trace.concat("h");							  

                            //System.out.println("overe here");
                            //Util.p1s(ss1);
                            //Util.p1s(ss2);
                            System.out.println("..");
                            if ( ss1.addNewItemAtLastSet(ss2.getLastItem()) )
                            {
                                trace = trace.concat("i");
                                CK.add(ss1.reVerse(ss1));
                            }
                                }

                    }
                    else if((( (ss1.seqLength()==2) && (ss1.seqSize()==1) )
                                &&( ss2.getLastItem().getName().compareTo(ss1.getLastItem().getName()) < 0 ))
                            ||( ss1.seqLength()>2 )){

                        trace = trace.concat("j");
                        //System.out.println(trace);						   

                        if ( ss1.addNewItemAtLastSet(ss2.getLastItem()) )
                        {
                            trace = trace.concat("k");
                            //Util.p1s(ss1);
                            CK.add(ss1.reVerse(ss1));
                        }
                            }	   
                }	
                else{


                    trace = trace.concat("l");

                    /*
                       System.out.println("In condition      ..............3");
                       Util.p1s(s1);
                       Util.p1s(s2);
                       System.out.println("In condition      ..............3.1");
                       */

                    if (s1.copySeq(s1).removeItem(0,0)
                            .isSequenceSame(s2.copySeq(s2).removeLastItem()))
                    {

                        trace = trace.concat("3");
                        if (s2.getItemSets(s2.seqSize()-1).getItems().size()==1 ){
                            ItemSet newTemp = new ItemSet();
                            newTemp.addItem(s2.getLastItem());
                            c1.addItemSet(newTemp);
                            CK.add(c1);

                            trace = trace.concat("m");
                            //System.out.println("In condition      ..............3.2");
                        }
                        else{
                            trace = trace.concat("n");
                            //Util.p1s(c1);						    
                            if ( c1.addNewItemAtLastSet(s2.getLastItem()) )
                            {
                                trace = trace.concat("o");
                                //  Util.p1s(c1);	
                                CK.add(c1);
                                //System.out.println("In condition      ..............3.3");
                            }
                        }
                    }
                }

                if ( prevSize < CK.size() && prevSize > 0)
                {
                    int currentSize = CK.size();
                    //System.out.println("Candidate generated with trace... = " + trace + ", " + CK.size() + ", " + prevSize);
                    //Util.p1s(CK.get(CK.size()-1));

                    for ( int jj = currentSize -1 ; jj > prevSize - 1 ; jj--)
                    {
                        for ( int ii=0; ii < prevSize ; ii++ )
                        {
                            //System.out.println("over here__ " + ii + ", "  + jj);
                            //Util.p1s(CK.get(jj));
                            //Util.p1s(CK.get(ii));

                            if ( CK.get(ii).isSequenceSame(CK.get(jj)))
                            {
                                CK.remove(jj);
                                //System.out.println("Duplicate removed");
                                break;
                            }
                            else
                            {
                                //Util.p1s(CK.get(jj));
                                if ( ! Util.isValidSupportDifference(CK.get(jj), SDC, transCount ))
                                {
                                    
                                    CK.remove(jj);
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    //System.out.println("No candidate was generated");
                }

                prevSize = CK.size();
            }


        }

        //System.out.println("Final result-semi");
        //Util.ps(CK);	

        //Util.consolidatedSequences(CK);

        //System.out.println("Before prunning..");
        //Util.ps(CK);
        //System.out.println("...");
nextSequence: for ( int z=CK.size()-1; z > -1; z--)
              {
                  //Util.p1s(CK.get(z));
                  for ( int x=0; x < CK.get(z).getItemSets().size() ; x++ )
                  {
                      //System.out.println(CK.get(z).getItemSets(x).getItems().size());
                      for ( int y=0; y < CK.get(z).getItemSets(x).getItems().size(); y++ )
                      {
                          //System.out.println(y);
                          Sequence tempSeq = CK.get(z).copySeq(CK.get(z));

                          if ( x==0 && y==0 && checkAbsoluteMinSup(tempSeq)) continue;
                          if ( x== CK.get(z).seqSize()-1 && y == CK.get(z).getItemSets().get(x).getItems().size()-1
                                  && checkAbsoluteMinSup(tempSeq.reVerse(tempSeq)) )  continue;

                          if (  CK.get(z).getMinItemSetIndex() == x && CK.get(z).getMinItemSet().getMinItemIndex()== y ) continue;

                            //System.out.println(CK.get(z).getMinItemSetIndex());
                            //System.out.println( CK.get(z).getMinItemSet().getMinItemIndex());

                          tempSeq.removeItem(x,y);           
                          //Util.p1s(tempSeq);

                          for ( int p=0; p < Fk_1.size() ; p++)
                          {
                              if ( Util.isContained(Fk_1.get(p), tempSeq ) ) 
                                  break;   

                              if ( p+1 == Fk_1.size() )
                              {
                                  //System.out.println("removing ");
                                  //Util.p1s(CK.get(z));
                                  CK.remove(z);
                                  continue nextSequence;
                              }
                          }

                      }
                  }
              }

              //System.out.println("Final result");
              //Util.ps(CK);	
              return CK;
    }

    public static boolean checkAbsoluteMinSup(Sequence s){

        for (int x=0;x<s.seqSize();x++)
        {
            for (int y=0;y<s.getItemSets(x).getItems().size();y++)
            {	
                //System.out.println(s.getItem(0,0).getMinSup());
                //System.out.println(s.getItem(x,y).getMinSup());
                if ( x==0 && y==0 ) continue;  //&& s.getItemSets(x).getItems().size() > 1  ) y=1;
                if ( s.getItem(0,0).getMinSup() >= s.getItem(x,y).getMinSup())
                    //if any item's MIS <= the MIS of the 1st item in s, it means that
                    //It's absolutely not "less than".
                    return false;      	
            }
        }	


        //System.out.println("returning true for ");
        //Util.p1s(s);

        return true;
    }

  public static ArrayList<Sequence> calculateF1(ArrayList<Item> items, ArrayList<Sequence> sequences)
    {
        ArrayList<Sequence> F1 = new ArrayList<Sequence>();

        int n = sequences.size();

        for(int i = 0; i < items.size(); i++)
        {
            if((Double.valueOf(items.get(i).getCount())/n) >= items.get(i).getMinSup())
            {
                ItemSet itemSet = new ItemSet();
                itemSet.addItem(items.get(i));
                Sequence sequence = new Sequence();
                sequence.addItemSet(itemSet);
                F1.add(sequence);
            }
        }

        return F1;
    }

 /* This function can be used to generate k+1 sequence items by passing
     * k-sequence items*/
    public static void TestCandidateGen()
    {
        HashMap m = new HashMap();
        m.put("1",0.2);
        m.put("5",0.4);
        m.put("6",0.6);
        m.put("7",0.8);

        String l = "<{1}><{5}><{6}><{7}>";	


        HashMap m1 = new HashMap();
        m1.put("40",0.40);
        m1.put("90",0.20);
        m1.put("10",0.43);
        //String input = "<{40}{90}><{40,90}><{10}{90}><{10}{40}>";
        String input = "<{10,40}{90}><{40}{40,90}>";

        //String input = "<{10}{40}><{40,90}>";
        //String input = "<{40,90}>";

        //ArrayList<Sequence> s = Util.createTestSequences(l,m);
        //Util.ps(s);
        //System.out.println("Calling..generation");
        //Util.ps( level2_candidate_gen_SPM(s,));   


        /**/
        String FK1 = "<{1}{5}><{1}{6}>";
        String FK2 = "<{1,5}><{1,6}>";
        String FK3 = "<{1}{5}><{1,6}>";
        String FK4 = "<{1,5}><{1}{6}>";

        String FK11 = "<{6}{1}><{5}{1}>";
        String FK21 = "<{6,1}><{5,1}>";
        String FK31 = "<{6}{1}><{5,1}>";
        String FK41 = "<{6,1}><{5}{1}>";


        String FK12 = "<{6,5}><{5,7}>";
        String FK22 = "<{6,5}><{5}{7}>";


        ///*  First condition - part a
        ArrayList<Sequence> s = Util.createTestSequences(input,m1);
        Util.ps(s);
        System.out.println("Calling..generation");
        ArrayList<Sequence> result =  MScandidateGenSPM(s,1.0,6);   
        System.out.println("Test Result..........");
        Util.ps(result);

        /*
           ArrayList<Sequence> s1 = Util.createTestSequences(FK11,m);
           Util.ps(s1);
           System.out.println("Calling..generation_2");
           Util.ps(MScandidateGenSPM(s1));   
        /**/

        /* First condition - part a
           ArrayList<Sequence> s = Util.createTestSequences(FK4,m);
           Util.ps(s);
           System.out.println("Calling..generation");
           Util.ps(MScandidateGenSPM(s));
           */

        /* First condition - part b
           ArrayList<Sequence> s = Util.createTestSequences(FK2,m);
           Util.ps(s);
           System.out.println("Calling..generation");
           Util.ps(MScandidateGenSPM(s));
           */

        /* First condition - part b
           ArrayList<Sequence> s = Util.createTestSequences(FK3,m);
           Util.ps(s);
           System.out.println("Calling..generation");
           Util.ps(MScandidateGenSPM(s));
           */
    }
}
