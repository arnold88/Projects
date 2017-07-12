import java.util.*;

/*
 *
 * ItemSet class
 *
 */

public class ItemSet {

    private ArrayList<Item> _items = new ArrayList<Item>();

    /* These 2 values have to reset after remove operation*/
    private Item _minItem = null;
    private int _minItemIndex;

    /* Adds an item to the itemset, and also update the minItem property*/
    public boolean addItem(Item i)
    {
        if ( isItemAlreadyInItemSet(i) )
            return false;

        _items.add(i);
        if (  (_minItem == null ) 
                || (_minItem != null &&  _minItem.getMinSup() >= i.getMinSup() ) )
        {
            _minItem = i;
            _minItemIndex = _items.size()-1;
        }

        return true;
    }	


    /* Checks if items already present in ItemSet*/
    public boolean isItemAlreadyInItemSet(Item item)
    {
        for ( int i=0; i < getItems().size(); i++ )
        {
            if ( getItems().get(i).getName().equalsIgnoreCase(item.getName()))	
                return true;
        }		 
        return false;

    }	

    public Item getItem(int index){
        Item result=null;
        if (index < _items.size() )
            result= _items.get(index);
        return result;

    }

    /* removes a particular item from the itemset based on the provided index*/
    public void removeItem(int index){
        if (_items.get(index).equals(_minItem)){
            // if min item is removed, find the next minItem and set the support
            // variables.
            _items.remove(index);
            _minItem = _items.get(0);
            for (int i=1; i< this._items.size();i++)
                if (_minItem.getMinSup()>_items.get(i).getMinSup()){
                    _minItem = _items.get(i);
                    _minItemIndex = i;
                }    
        }
        else
            _items.remove(index);
    }  

    /* Returns reference to the item with the min MIS value in the ItemSet*/
    public Item getMinItem() {  return _minItem; } 

    /* Return index of the min item in the ItemSet */
    public Integer getMinItemIndex() { return _minItemIndex; }
   
    /* Returns a reference to the items in the ItemSet */
    public ArrayList<Item> getItems() { return _items; }

}
