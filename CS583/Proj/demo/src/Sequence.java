import java.util.*;
import java.math.*;

public class Sequence {

	private ArrayList<Itemset> _sequence = new ArrayList<Itemset>();
	private Integer _count = 0;
	// must be reset when adding/removing
	private Integer _minIndex = -1;
	private Integer _length = 0; //# of items
	private Itemset _minItemset = null;
	private Sequence _rest = null;
	private boolean _frequent = false;
	private double _support = 0.0;
	//private BigDecimal _support = BigDecimal.valueOf(0.0d);
	private double _minsup = 1.01;
	//private BigDecimal _minsup = BigDecimal.valueOf(1.01d);
	
	public Sequence() {
	}
	
	public Sequence reverse() {
		Sequence reversed = new Sequence();
		Itemset rev = new Itemset();
		for (int i = _sequence.size() - 1; i >= 0; i--) {
			Itemset is = _sequence.get(i);
			for (int j = is.getSize() - 1; j >= 0; j--) {
				rev.addItem(is.getItem(j));
			}
			reversed.addItemset(rev);
			rev = new Itemset();
		}
		reversed.setLength();
		reversed.setMinsup();
		return reversed;
	}
	
	public Sequence getRest() {
		return _rest;
	}
	
	public void setRest() {
		if (_length >= 2)
			_rest = this.copy();
			_rest.removeMin();
	}
	
	public Sequence removeMin() {
		this.setMinsup();
		if (_sequence.get(this.getMinIndex()).getSize() == 1) {
			_sequence.remove(this.getMinIndex());
			this.setLength();
			this.setMinsup();
		} else {
			this.removeItem(_minIndex, _minItemset.getMinIndex());
			this.setLength();
			this.setMinsup();
		}
		return this;
	}
	
	// sets count based on dbase of Sequences
	public void setCount(ArrayList<Sequence> dbase, Integer n) {
		_count = 0;
		for (Sequence s : dbase) {
			if (this.isSubsequenceOf(s)) 
				this.incCount();
		}
		this.setLength();
		this.setMinsup();
     
        //_support = BigDecimal.valueOf(_count).divide(BigDecimal.valueOf(n), 3, BigDecimal.ROUND_HALF_UP);
		_support = _count * 1.0 / n;
        
		if (_support >= this.getMinsup())
        //if (_support.compareTo(this.getMinsup()) >= 0)
			_frequent = true;
		else
			_frequent = false;
	}
	
	public void setFreq(boolean f) {
		_frequent = f;
	}
	
	public void setCount(int c) {
		_count = c;
	}
	
//	public void setSup(BigDecimal s) {
//		_support = s;
//	}
	
	public void setSup(Double s) {
		_support = s;
	}
	
//	public BigDecimal getSup() {
//		return _support;
//	}
	
	public Double getSup() {
		return _support;
	}
	
	public boolean getFrequent() {
		return _frequent;
	}
	
	// need to add function that removes second item in cases where first element has only one item
	public Sequence removeSecond() {
		if (_sequence.size() > 1) { // more than one element
			if (_sequence.get(0).getSize() == 1 && _sequence.get(1).getSize() == 1) {
				_sequence.remove(1);
				this.setMinsup();
				this.setLength();
			} 
			else if (_sequence.get(0).getSize() == 1 && _sequence.size() >= 2) // only one Item in the first Itemset and at least 2 Itemsets in Sequence 
				this.removeItem(1, 0);
			else
				this.removeItem(0, 1);
		}
		else if (_sequence.get(0).getSize() > 1) { // only one element
			this.removeItem(0, 1);
		}
		return this;
	}
	
	// checks if the sequence calling the function is a subsequence of s
	public boolean isSubsequenceOf(Sequence data) {
		 boolean result = true;
         int m = _sequence.size();
         int n = data.getSize();
         int i = 0, j = 0;
         for(i = 0; i < m; i++) {
             Itemset is = _sequence.get(i);
             do {
                 if (m - i > n - j) {        //The number of rest elements in current sequence is greater than the number of rest elements in data
                     result = false;
                     break;
                 }
                 if (is.isContained(data.getItemset(j))) {        //find an element in data which is the super set of current element in current sequence
                     j++;
                     break;
                 }
                 j++;
             } while (j < n);
             if (result == false) 
            	 break;
             if (i == m - 1 && j == n) 
            	 result = is.isContained(data.getItemset(j - 1));
         }
         return result;
	}
	
	// checks if the sequence is within the support difference constraint
//	public boolean isInSDC(BigDecimal sdc, Integer n, HashMap<Item, BigDecimal> supports) {
	public boolean isInSDC(Double sdc, Integer n, HashMap<Item, Double> supports) {
		ArrayList<Item> allItems = new ArrayList<Item>();
		for (Itemset is : _sequence) {
			for (Item i : is.getItems()) {
				allItems.add(i);
			}
		}
		for (int i = 0; i < allItems.size(); i++) {
			for (int j = 0; j < allItems.size(); j++) {
				//if (allItems.get(i).getSup(supports).subtract(allItems.get(j).getSup(supports)).compareTo(sdc) > 0)
				if (allItems.get(i).getSup(supports) - allItems.get(j).getSup(supports) > sdc)
					return false;
			}
		}
		return true;
	}
	
	// returns copy of sequence calling function
	public Sequence copy() {
		Sequence newSequence = new Sequence();
		for (int i = 0; i < _sequence.size(); i++) {
			Itemset newItemset = new Itemset();
			for (int j = 0; j < _sequence.get(i).getSize(); j++) 
				newItemset.addItem(_sequence.get(i).getItem(j));
			newSequence.addItemset(newItemset);
		}
		newSequence.setSup(this.getSup());
		newSequence.setCount(this.getCount());
		newSequence.setFreq(this.getFrequent());
		newSequence.setMinsup(this.getMinItemset(), this.getMinIndex(), this.getMinsup());
		newSequence.setLength(this.getLength());
		return newSequence;
	}
	
	public String toString() {
		String sequence_name = "<";
		for (Itemset i: _sequence) {
			sequence_name += i.toString();
		}
		sequence_name += ">";
		return sequence_name;
	}
	
	// remove last item
	public Sequence removeLast() {
		if (_sequence.get(_sequence.size() - 1).getSize() == 1) {
			_sequence.remove(_sequence.size() - 1);
			this.setMinsup();
			this.setLength();
		} else {
			this.removeItem(_sequence.size() - 1, _sequence.get(_sequence.size() - 1).getItems().size() - 1);
		}
		return this;
	}
	
	// returns last item
	public Item getLast() {
		ArrayList<Item> i = _sequence.get(_sequence.size() - 1).getItems();
		Item last = i.get(i.size() - 1);
		return last;
	}
	
	// returns first item
	public Item getFirst() {
		ArrayList<Item> i = _sequence.get(0).getItems();
		Item first = i.get(0);
		return first;
	}
	
	// remove first item
	public Sequence removeFirst() {
		if (_sequence.get(0).getSize() == 1) {
			_sequence.remove(0);
			this.setMinsup();
			this.setLength();
		} else {
			this.removeItem(0, 0);
		}
		return this;
	}
	
	// sets the minsup for the sequence as a whole
	public void setMinsup() {
		if (_sequence.size() > 0) {
			_minItemset = _sequence.get(0);
			_minIndex = 0;
			//_minsup = BigDecimal.valueOf(1.01d);
			_minsup = 1.01;
			for (int i = 0; i < _sequence.size(); i++) {
				//if (_sequence.get(i).getMinItem().getMinsup().compareTo(_minItemset.getMinItem().getMinsup()) < 0) {
				if (_sequence.get(i).getMinItem().getMinsup() < _minItemset.getMinItem().getMinsup()) {	
					_minItemset = _sequence.get(i);
					_minIndex = i;
					_minsup = _sequence.get(i).getMinItem().getMinsup();
				}
			}
		} else {
			_minItemset = null;
			_minIndex = -1;
			//_minsup = BigDecimal.valueOf(1.01d);
			_minsup = 1.01;
		}
	}
	
//	public void setMinsup(Itemset is, int i, BigDecimal d) {
//		_minItemset = is;
//		_minIndex = i;
//		_minsup = d;
//	}
	
	public void setMinsup(Itemset is, int i, Double d) {
		_minItemset = is;
		_minIndex = i;
		_minsup = d;
	}
	
	public Item getMin() {
		return _minItemset.getMinItem();
	}
	
//	public BigDecimal getMinsup() {
//		return this.getMin().getMinsup();
//	}
	
	public Double getMinsup() {
		return this.getMin().getMinsup();
	}
	
	// removes an item at an itemIndex in an itemset at an itemsetIndex
	// returns the Sequence that called this method
	public Sequence removeItem(int itemsetIndex, int itemIndex) {
		if (_sequence.get(itemsetIndex).getItems().size() == 1) {
			if (_minIndex == itemsetIndex) {
				_sequence.remove(itemsetIndex);
				this.setLength();
				this.setMinsup();
			} else {
				_sequence.remove(itemsetIndex);
				this.setLength();
			}
		} else {
			if (_minIndex == itemsetIndex) {
				_sequence.get(itemsetIndex).removeItem(itemIndex);
				this.setLength();
				this.setMinsup();
			} else {
				_sequence.get(itemsetIndex).removeItem(itemIndex);
				this.setLength();
			}
		}
		return this;
	}
	
	// adds an item to an itemset at index i
	// returns true if successful
	public boolean addItem(Item e, int itemsetIndex) {
		Itemset indexed = _sequence.get(itemsetIndex);
		
		if (!indexed.addItem(e))
			return false;
		
		indexed.addItem(e);
		_length++;
		
		if (_minItemset == null || (_minItemset != null && (e.getMinsup().compareTo(_sequence.get(itemsetIndex).getMinItem().getMinsup()) < 0))) {
			_minItemset = indexed;
			_minIndex = itemsetIndex;
			_minsup = e.getMinsup();
		}
		
		return true;
		
	}
	
	// equals method
	public boolean equals(Sequence s) {
		if ((s.getLength() != this.getLength()) || (s.getSize() != this.getSize()))
			return false;
		
		for (int i = 0; i < _sequence.size(); i++) {
			Itemset a = this.getItemset(i);
			Itemset b = s.getItemset(i);
			
			if (a.getItems().size() != b.getItems().size())
				return false;
			
			for (int j = 0; j < a.getItems().size(); j++) {
				if (!a.getItems().get(j).equals(b.getItems().get(j)))
					return false;
			}
		}
		
		return true;
	}
	
	//appends an itemset to the sequence
	public boolean addItemset(Itemset i) {
		_sequence.add(i);
		_length += i.getItems().size();
		
		if (_minItemset == null || (_minItemset != null && _minItemset.getMinItem().getMinsup().compareTo(i.getMinItem().getMinsup()) > 0)) {
			_minItemset = i;
			_minIndex = _sequence.size() - 1;
			_minsup = i.getMinItem().getMinsup();
		}
		return true;
	}
	
	public void incCount() {
		_count++;
	}
	
	public Integer getCount() {
		return _count;
	}
	
	public ArrayList<Itemset> getSequence() {
		return _sequence;
	}
	
	public Integer getSize() {
		return _sequence.size();
	}
	
	public Integer getLength() {
		return _length;
	}
	
	public void setLength() {
		_length = 0;
		for (Itemset i : _sequence) {
			for (Item e : i.getItems())
				_length++;
		}
	}
	
	public void setLength(int l) {
		_length = l;
	}
	
	public Itemset getItemset(int index) {
		return _sequence.get(index);
	}
	
	public Integer getMinIndex() {
		return _minIndex;
	}
	
	public Itemset getMinItemset() {
		return _minItemset;
	}
}
