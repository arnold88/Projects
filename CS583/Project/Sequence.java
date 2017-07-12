import java.util.*;

/*
 *
 * Sequence Class
 *
 */

public class Sequence {

    private ArrayList<ItemSet> _itemSets = new ArrayList<ItemSet>();
    private Integer _count=0;

    /* These 3 values have to reset after remove operation*/
    private Integer  _minItemSetIndex=-1;
    private ItemSet _minItemSet = null;  //changed by Guru
    private Integer _itemSetCount = 0;


    public void incrementCount()
    {
        _count++;
    }

    public Integer getCount() { return _count; }

    /* Adds a new ItemSet to the sequence*/
    public void addItemSet(ItemSet s)
    {
        _itemSets.add(s);
        _itemSetCount = _itemSetCount + s.getItems().size();

        if ( _minItemSet == null 
                || ( _minItemSet != null && _minItemSet.getMinItem().getMinSup() >  s.getMinItem().getMinSup() ))
        {
            _minItemSet = s;
            _minItemSetIndex = _itemSets.size()-1;
        }

    }	


    public ArrayList<ItemSet> getItemSets()
    {
        return _itemSets;
    }

    public Integer seqSize(){

        return _itemSets.size();
    }


    public Integer seqLength(){
              return _itemSetCount;

    }


    public ItemSet getItemSets(int index){

        return _itemSets.get(index);
    }


    /* Adds a new item to the last ItemSet*/
    public boolean addNewItemAtLastSet(Item newItem){

        ItemSet lastItemSet = _itemSets.get(_itemSets.size()-1);	

        if ( ! lastItemSet.addItem(newItem) ) return false;

        _itemSetCount = _itemSetCount + 1;

        /* Change the minItemSet if the new item that was added has the least MIS value among all itemsets in the sequence*/
        if ( _minItemSet == null 
                || ( _minItemSet != null && _minItemSet.getMinItem().getMinSup() >  lastItemSet.getMinItem().getMinSup() ))
        {
            _minItemSet = lastItemSet;
            _minItemSetIndex = _itemSets.size()-1;
        }

        return true;
    }


    /* Gets the last item in the sequence. */
    public Item getLastItem(){

        ItemSet lastItemSet = _itemSets.get(_itemSets.size()-1);
        Item lastItem = lastItemSet.getItem(lastItemSet.getItems().size()-1);

        return lastItem;

        //return _itemSets.get(_itemSets.size()-1).getItem(_itemSets.get(_itemSets.size()-1).getItems().size()-1);

    }

    
    /* Remove an item based in the itemSetIndex and itemIndex*/
    public Sequence removeItem(int itemSetIndex,int itemIndex){

        if (this._itemSets.get(itemSetIndex).getItems().size()==1){
            if (_minItemSetIndex==itemSetIndex){
                this._itemSets.remove(itemSetIndex);
                _itemSetCount--; 			   
                setMinSupItemSet();
            }
            else
                this._itemSets.remove(itemSetIndex);	
        }	
        else{
            if (_minItemSetIndex==itemSetIndex){
                this._itemSets.get(itemSetIndex).removeItem(itemIndex);
                setMinSupItemSet();
            }
            else
                this._itemSets.get(itemSetIndex).removeItem(itemIndex);	
        }
        return this;
    }

    public Sequence removeSecItem(){
        //Sequence newSeq=old.copySeq(old);
        if (_itemSets.get(0).getItems().size()==1)
            removeItem(1,0);
        else
            removeItem(0,1);
        return this;
    }
    public Sequence removeLastItem(){
        removeItem(seqSize()-1,getLastItemSet().getItems().size()-1);
        return this;
    }
 
    /* Resets min support item reference in the sequence, when an item in the
     * sequence is removed*/
    public void setMinSupItemSet(){                     //setMinSupItem()
        if (_itemSets.size()>0){
            _minItemSet=_itemSets.get(0);
            _minItemSetIndex = 0;
            for (int z=1; z< _itemSets.size();z++)	        	
                if (_itemSets.get(z).getMinItem().getMinSup().intValue()
                        < _minItemSet.getMinItem().getMinSup().intValue()){
                    _minItemSetIndex = z;
                    _minItemSet = _itemSets.get(z);
                        }


        }
        else{
            _minItemSet=null;
            _minItemSetIndex=-1;	 

        } 

    }

    public int getMinItemSetIndex()
    {
        return _minItemSetIndex;
    }

    public ItemSet getMinItemSet()
    {
        return _minItemSet;
    }

    public Item getMinItem(){
        return _minItemSet.getMinItem(); 
    }

    public Item getItem(int _itemSetsIndex, int itemIndex){
        return this._itemSets.get(_itemSetsIndex).getItem(itemIndex);
    }

    public ItemSet getLastItemSet(){
        return getItemSets(this.seqSize()-1);
    }
    
    /* Creates a deep copy of the sequence*/
    public Sequence copySeq(Sequence oldSeq){

        Sequence newSeq = new Sequence();
        for (int s=0;s<oldSeq.getItemSets().size();s++){
            ItemSet newItemSet = new ItemSet();
            for ( int i=0;i<oldSeq.getItemSets(s).getItems().size();i++){
                newItemSet.addItem(oldSeq.getItemSets(s).getItem(i));
            }    
            newSeq.addItemSet(newItemSet);
        }
        newSeq.setItemSetCount(oldSeq.seqLength());  //Maybe this one is not necessary.

        return newSeq;
    }


    public void setItemSetCount(Integer n){_itemSetCount=n;}

    /* Reverses a given sequence*/
    public Sequence reVerse(Sequence oldSeq){

        Sequence newSeq = new Sequence();
        for (int s=oldSeq.getItemSets().size()-1; s>-1;s--){
            ItemSet newItemSet = new ItemSet();
            for ( int i=oldSeq.getItemSets(s).getItems().size()-1 ;i>-1;i--){
                newItemSet.addItem(oldSeq.getItemSets(s).getItem(i));
            }
            newSeq.addItemSet(newItemSet);
        }
        return newSeq;
    }


    /* Compares 2 sequences to see if they are similar*/
    public boolean isSequenceSame(Sequence s2)
    {

        if ( this.getItemSets().size() != s2.getItemSets().size() )
            return false;

        for ( int i=0; i < this.getItemSets().size() ; i++ )
        {
            ItemSet is1 = this.getItemSets().get(i);
            ItemSet is2 = s2.getItemSets().get(i);

            if ( is1.getItems().size() != is2.getItems().size() ) return false;

            for ( int j=0; j < is1.getItems().size(); j ++ )
            {
                if ( ! is1.getItems().get(j).getName().equalsIgnoreCase(is2.getItems().get(j).getName()))
		   {
                    return false;
		   }
            }		

        }

        return true;	

    }

}
