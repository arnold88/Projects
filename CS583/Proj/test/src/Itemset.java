import java.util.*;
import java.math.*;

public class Itemset {

	private ArrayList<Item> _itemset = new ArrayList<Item>();
	//must be reset when adding/removing
	private Item _minItem = new Item();
	private int _minIndex = -1;
	
	public Itemset() {
	}
	
	public Itemset(ArrayList<Item> a) {
		_itemset = a;
		this.setMin();
	}
	
	public boolean isInSDC(double sdc, int n) {
		if (_itemset.size() > 1) {
			for (int i = 0; i < _itemset.size(); i++) {
				for (int j = 0; j < _itemset.size(); j++) {
					if (Math.abs(_itemset.get(i).getSup() - _itemset.get(j).getSup()) > sdc) {
						System.out.println(_itemset.get(i).toString() + " Support = " + _itemset.get(i).getSup());
						System.out.println(_itemset.get(j).toString() + " Support = " + _itemset.get(j).getSup());
						return false;
					}
				}
			}
			return true;
		}
		else
			return true;
	}
	
	public void sort() {
		ItemComp comp = new ItemComp();
		Collections.sort(_itemset, comp);
	}
	
	public boolean isContained(Itemset s) {
		for (Item i : _itemset) {
			if (!s.isInSet(i)) 
				return false;
			else
				continue;
		}
		return true;
	}
	
	// gets Item at index
	public Item getItem(int index) {
		Item result = null;
		if (index < _itemset.size() && index >= 0)
			result = _itemset.get(index);
		return result;
	}
	
	// adds an item
	// returns true if successful
	public boolean addItem(Item e) {
		if (this.isInSet(e))
			return false;
		_itemset.add(e);
		if (e.getMinsup() < _minItem.getMinsup()) {
			_minItem = e;
			_minIndex = _itemset.size() - 1;
		}
		this.sort();
		return true;
	}
	
	//removes an item
	public void removeItem(int index) {
		if (index == _minIndex) {
			_itemset.remove(index);
			this.setMin();
		}
		else
			_itemset.remove(index);
	}
	
	public Item getMinItem() {
		return _minItem;
	}
	
	public Integer getMinIndex() {
		return _minIndex;
	}
	
	// sets the min item
	public void setMin() {
		if (_itemset.size() != 0) {
			_minItem = _itemset.get(0);
			_minIndex = 0;
			for (int i = 0; i < _itemset.size(); i++) {
				if (_itemset.get(i).getMinsup() < _minItem.getMinsup()) {
					_minItem = _itemset.get(i);
					_minIndex = i;
				}
			}
		}
	}
	
	public ArrayList<Item> getItems() {
		return _itemset;
	}
	
	// checks if item is already in itemset
	public boolean isInSet(Item e) {
		for (Item i : _itemset) {
			if (i.equals(e))
				return true;
		}
		return false;
	}
	
	public String toString() {
		String itemset_name = "{";
		for (int i = 0; i < _itemset.size(); i++) {
			if (i == _itemset.size() - 1) 
				itemset_name += _itemset.get(i).toString();
			else
				itemset_name += _itemset.get(i).toString() + ",";
		}
		itemset_name += "}";
		return itemset_name;
	}

	public int getSize() {
		return _itemset.size();
	}
}
