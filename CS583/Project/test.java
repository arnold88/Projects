import java.util.*;

public class test
{

    public static  ArrayList<Sequence> createDataSample()
    {
        ArrayList<Sequence> data = new ArrayList<Sequence>();
        Item[] items = new Item[10];

        for ( int i = 10 ; i < 101 ; i = i+10)
        {
            items[(i/10)-1] = new Item(Integer.toString(i), 1.0);
            System.out.println(items[(i/10)-1].getName()); 
        }

        ItemSet is = new ItemSet();
        is.addItem(items[0]);
        is.addItem(items[1]);
        is.addItem(items[2]);
        Sequence s = new Sequence();
        s.addItemSet(is);
        data.add(s);

        is = new ItemSet();
        is.addItem(items[1]);
        is.addItem(items[2]);
        s = new Sequence();
        s.addItemSet(is);
        data.add(s);


        return data;

    }


    public static void setCount(ArrayList<Sequence> data, ArrayList<Sequence> candidateSeq)
    {
        //Go through the datasets
        for ( int a=0; a < data.size(); a++)
        {
            Sequence s = data.get(a); 
            for ( int b=0; b < candidateSeq.size(); b++)
            {
                if ( isContained(s,candidateSeq.get(b)) )
                {
                    candidateSeq.get(b).incrementCount();
                }
            }
        }

        //System.out.println("Candidate");
        //test.ps(candidateSeq);	

    }

    public void Test(ArrayList<Sequence> data)
    {





    }

    public static boolean isContained(Sequence data, Sequence candidate)
    {
        int i,j;

        //test.p1s(data);
        //test.p1s(candidate);
        for ( i=0,j=0; i< data.getItemSets().size() && j < candidate.getItemSets().size() ; )
        {
            if ( isItemSetContained(data.getItemSets().get(i), candidate.getItemSets().get(j) ) )
            {
                i++;
                j++;
            }
            else
                i++;
        }

        if ( j >= candidate.getItemSets().size() )
            return true;
        else
            return false;

    }






    public static boolean isItemSetContained(ItemSet data, ItemSet candidate)
    {

        int i, j=0;

        for ( ; j < candidate.getItems().size(); j++ )
        {
            for ( i=0; i < data.getItems().size();i++)
            {
                if (  data.getItems().get(i).getName().equalsIgnoreCase(candidate.getItems().get(j).getName()) )
                {
                    break;
                }
            }
            if ( i >= data.getItems().size() )
            {
                return false;
            }
        }
        return true;


        //test.printItemSet(data);
        //test.printItemSet(candidate);

        /*
           for ( i=0; i < data.getItems().size() && j < candidate.getItems().size(); )
           {
           if ( data.getItems().get(i).getName().equalsIgnoreCase(candidate.getItems().get(j).getName()) )
           {
           i++; j++;
           }
           else
           i++;
           }*/

        /*
           if ( j >= candidate.getItems().size())
           return true;

           return false;
           */
    }

    public static void ps(ArrayList<Sequence> data)
    {
        printAllSequences(data);
    }

    public static void p1s(Sequence s)
    {
        ArrayList<ItemSet> itemSet = s.getItemSets();
        System.out.print("<");

        for ( int k = 0 ; k < itemSet.size(); k++ )
        {
            printItemSet(itemSet.get(k)); 
        }

        System.out.println(">  (" + s.getCount() + ")" );

    }

    public static void printItemSet(ItemSet itemSet)
    {
        ArrayList<Item> items = itemSet.getItems();
        System.out.print("{");
        for ( int j =0;  j < items.size() ; j++)
        {
            System.out.print(items.get(j).getName());	
            if ( j+1 < items.size() )
                System.out.print(",");		
        }

        System.out.print("}");
    }



    public static void printAllSequences(ArrayList<Sequence> data )
    {
        for ( int i =0; i < data.size(); i++ )
        {
            test.p1s(data.get(i));
        }	
    }


    public static void main(String[] args)
    {
        System.out.println("test");

        ArrayList<Sequence> data = createDataSample();
        printAllSequences(data );

        ArrayList<Sequence> candidate = new ArrayList<Sequence>();
        candidate.add(data.get(1));

        setCount(data,candidate);

        System.out.println("Count " +  candidate.get(0).getCount() );

    }

    public static char getNextToken(String s, int i)
    {
        char[] c = s.substring(i,i+1).toCharArray();
        return c[0];
    }


    public static ArrayList<Sequence> createTestSequences(String s, HashMap m)
    {

        System.out.println(s);
        ArrayList<Sequence> seqList = new ArrayList<Sequence>();
        Sequence seq = new Sequence();
        ItemSet itemSet = new ItemSet();

        for ( int i=0; i < s.length(); i++)
        {
            char token  = getNextToken(s,i); 

            switch (token){
                case '<':
                    seq = new Sequence();
                    break;
                case '>':
                    seqList.add(seq);
                    break;
                case '{':
                    itemSet = new ItemSet();
                    break;
                case '}':
                    seq.addItemSet(itemSet);
                    break;
                default:
                    int index = s.indexOf("}",i);
                    String subStr = s.substring(i, index);
                    String[] items =  subStr.split(",");
                    for ( int j= 0 ; j < items.length; j++ )
                    {
                        Item item = new Item();
                        item.setName(items[j]);
                        item.setMinSup((Double)m.get(items[j]));
                        itemSet.addItem(item);
                    }

                    i = index-1; 
            }
        }

        return seqList;
    }

	public static boolean isValidSupportDifference(Sequence candidate, double SDC, Integer transCount)
	{
		double minSupport = candidate.getMinItem().getCount()/Double.valueOf(transCount);
		
		for ( int i=0 ; i < candidate.getItemSets().size() ; i++ )
		{
			for ( int j=0; j < candidate.getItemSets().get(i).getItems().size() ; j++)
			{
				//if ( Math.abs(candidate.getItemSets().get(i).getItems().get(j).getMinSup() - minSupport ) > SDC )	
				if ( Math.abs(candidate.getItemSets().get(i).getItems().get(j).getCount()/Double.valueOf(transCount) - minSupport ) > SDC )	
				{
					//System.out.println(candidate.getItemSets().get(i).getItems().get(j).getName() + ": " + candidate.getMinItem().getName()) ;	
					//System.out.println(Math.abs(candidate.getItemSets().get(i).getItems().get(j).getCount()/Double.valueOf(transCount)));
					return false;
				}
			}
		}
		return true;
	}


}
