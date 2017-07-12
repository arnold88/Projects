
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.io.BufferedInputStream;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;


/*
 * This class has methods to create the initial data sets and sorted list of
 * items based on the MIS values.
 *
 */

public class Init {

    File file = null;
    FileInputStream fis = null;
    BufferedInputStream bis = null;
    DataInputStream dis = null;

    public ArrayList<Item> createMS(String pathParam, double[] mySDC)
    {
        ArrayList<Item> items = new ArrayList<Item>();

        try {
            file = new File(pathParam);
            fis = new FileInputStream(file);

            // Here BufferedInputStream is added for fast reading.
            bis = new BufferedInputStream(fis);
            dis = new DataInputStream(bis);

            // dis.available() returns 0 if the file does not have more lines.
            while (dis.available() != 0) {

                // this statement reads the line from the file and print it to
                // the console.
                String line = dis.readLine();

                //Get the name and minSup of items
                int i = line.indexOf('(');
                int j = line.indexOf(')');

                if((i > 0) && (j > 0))
                {
                    String name = line.substring(i+1, j);
                    j = line.indexOf('=');
                    Double minSup = Double.valueOf(line.substring(j+1, line.length()));

                    Item item = new Item();
                    item.setName(name);
                    item.setMinSup(minSup);

                    //Add new item into item list
                    items.add(item);
                }
                else
                {
                    mySDC[0] = Double.valueOf(line.substring(line.indexOf('=') + 1, line.length()));
                }
            }

            // dispose all the resources after using them.
            fis.close();
            bis.close();
            dis.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return items;
    }

    public ArrayList<Item> sortItems(ArrayList<Item> items)
    {
        //Sort items
        for(int i = 0; i < items.size() - 1; i++)
        {
            Item temp = new Item();

            for (int j = i + 1; j < items.size(); j++)
            {
                if(items.get(j).getMinSup() < items.get(i).getMinSup())
                {
                    //swap between i and j items.
                    temp.setName(items.get(i).getName());
                    temp.setMinSup(items.get(i).getMinSup());

                    items.get(i).setName(items.get(j).getName());
                    items.get(i).setMinSup(items.get(j).getMinSup());

                    items.get(j).setName(temp.getName());
                    items.get(j).setMinSup(temp.getMinSup());	
                }
            }
        }
        return items;
    }

    public ArrayList<Sequence> createSequences(String pathData, ArrayList<Item> M)
    {
        ArrayList<Sequence> sequences = new ArrayList<Sequence>();

        try {
            file = new File(pathData);
            fis = new FileInputStream(file);

            // Here BufferedInputStream is added for fast reading.
            bis = new BufferedInputStream(fis);
            dis = new DataInputStream(bis);

            // dis.available() returns 0 if the file does not have more lines.
            while (dis.available() != 0) {

                // this statement reads the line from the file and print it to
                // the console.
                String line = dis.readLine();

                Sequence sequence = new Sequence();

                for (int i = 0; i < line.length(); i++)
                {
                    if(line.charAt(i) == '{')
                    {
                        int beginIndex = i;

                        //Create new itemset
                        ItemSet itemSet = new ItemSet();

                        while(line.charAt(i) != '}')
                        {       	
                            i++;
                        }

                        String itemSetString = line.substring(beginIndex + 1, i);

                        itemSet =  createItemSet(itemSetString, M);

                        //Add to sequences -  changed
                        sequence.addItemSet(itemSet);
                    }
                }
                //Add new sequence to the sequences
                if ( sequence.getItemSets().size() > 0 )
                    sequences.add(sequence);
            }

            // dispose all the resources after using them.
            fis.close();
            bis.close();
            dis.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return sequences;
    }

    public ItemSet createItemSet(String itemSetString, ArrayList<Item> M)
    {
        ItemSet itemSet = new ItemSet();

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

            for (int j = 0; j < M.size(); j++)
            {
                if(M.get(j).getName().equalsIgnoreCase(item.getName()))
                {
                    item.setMinSup(M.get(j).getMinSup());
                }
                else
                {
                    if(j == (M.size() - 1)) item.setMinSup(1.1);
                }
            }

            itemSet.addItem(item);

            i = i + 1;
        }    	
        return itemSet;
    }

    public ArrayList<Item> initPass(ArrayList<Item> items, ArrayList<Sequence> sequences)
    {   
        //Get the item count
        for (int l = 0; l < items.size(); l ++)
        {
nextSequence:
            for(int i = 0; i < sequences.size(); i ++)
            {
                Sequence sequence = sequences.get(i);
                for(int j = 0; j < sequence.getItemSets().size(); j++)
                {
                    ItemSet itemSet = sequence.getItemSets(j);
                    for(int k = 0; k < itemSet.getItems().size(); k++)
                    {
                        if(items.get(l).getName().equalsIgnoreCase(itemSet.getItem(k).getName()))
                        {
                            items.get(l).addCount();
                            continue nextSequence;				
                        }
                    }
                }
            }
        }

        return items;
    }

  
    public void writeOutput(ArrayList<Sequence> sequences, int level, BufferedWriter output, int dataSize)
    {
        try{
            output.write(level + "-Sequence\r\n\r\n");

            for(int i = 0; i < sequences.size(); i ++)
            {
                Sequence sequence = sequences.get(i);
                output.write("\t<");
                for(int j = 0; j < sequence.getItemSets().size(); j++)
                {
                    output.write("{");
                    ItemSet itemSet = sequence.getItemSets(j);
                    for(int k = 0; k < itemSet.getItems().size(); k++)
                    {
                        output.write(itemSet.getItem(k).getName());
                        if((k + 1) < itemSet.getItems().size())
                        {
                            output.write(',');
                        }
                    }
                    output.write("}");
                }
                output.write(">");

                //output.write( "( minSup=" + sequence.getMinItem().getMinSup() + ", support=" + Double.valueOf(sequence.getCount())/dataSize + ")");
                output.write("\r\n");
                
            }

            output.write("\r\n\tThe total number of " + level + "-Sequence = " + sequences.size() +"\r\n\r\n");
            output.flush();
        }
        catch(IOException e){
            System.err.println("Cannot save file");
        }


    }
}
