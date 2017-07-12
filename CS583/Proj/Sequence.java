import java.util.*;

public class Sequence {

	private ArrayList<Itemset> _sequence = new ArrayList<Itemset>();
	private Integer _count = 0;
	// must be reset when adding/removing
	private Integer _minIndex = -1;
	private Integer _length = 0; //# of items
	private Itemset _minItemset = null;
	
	public Sequence() {
		
	}
	
	public Sequence copy() {
		Sequence newSequence = new Sequence();
		Sequence error = new Sequence();
		String errMessage = "Error";
		for (int i = 0; i < _sequence.size(); i++) {
			Itemset newItemset = new Itemset();
			for (int j = 0; j < _sequence.get(i).size(); j++) 
				newItemset.addItem(_sequence.get(i).getItem(j));
			newSequence.addItemset(newItemset);
		}
		Itemset errSet = new Itemset();
		for (int k = 0; k < errMessage.length(); k++) {
			Item err = new Item();
			err.setName(errMessage);
			errSet.addItem(err);
		}
		if (newSequence.equals(this))
			return newSequence;
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
		this.removeItem(_sequence.size() - 1, _sequence.get(_sequence.size() - 1).getItems().size() - 1);
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
		ArrayList<Item> i = _sequence.get(_sequence.size() - 1).getItems();
		Item first = i.get(0);
		return first;
	}
	
	// remove first item
	public Sequence removeFirst() {
		this.removeItem(0, 0);
		return this;
	}
	
	// sets the minsup for the sequence as a whole
	public void setMinsup() {
		if (_sequence.size() > 0) {
			_minItemset = _sequence.get(0);
			_minIndex = 0;
			for (int i = 0; i < _sequence.size(); i++) {
				if (_sequence.get(i).getMinItem().getMinsup() < _minItemset.getMinItem().getMinsup()) {
					_minItemset = _sequence.get(i);
					_minIndex = i;
				}
			}
		} else {
			_minItemset = null;
			_minIndex = -1;
		}
	}
	
	public Item getMin() {
		return _minItemset.getMinItem();
	}
	
	// removes an item at an itemIndex in an itemset at an itemsetIndex
	// returns the Sequence that called this method
	public Sequence removeItem(int itemsetIndex, int itemIndex) {
		if (_sequence.get(itemsetIndex).getItems().size() == 1) {
			if (_minIndex == itemsetIndex) {
				_sequence.remove(itemsetIndex);
				_length--;
				this.setMinsup();
			} else {
				_sequence.remove(itemsetIndex);
				_length--;
			}
		} else {
			if (_minIndex == itemsetIndex) {
				_sequence.get(itemsetIndex).removeItem(itemIndex);
				_length--;
				this.setMinsup();
			} else {
				_sequence.get(itemsetIndex).removeItem(itemIndex);
				_length--;
			}
		}
		return this;
	}
	
	// adds an item to an itemset at index i
	// returns true if successful
	public boolean addItem(Item e, int i) {
		Itemset indexed = _sequence.get(i);
		
		if (!indexed.addItem(e))
			return false;
		
		_length++;
		
		if (_minItemset == null || (_minItemset != null && _minItemset.getMinItem().getMinsup() > _sequence.get(i).getMinItem().getMinsup())) {
			_minItemset = indexed;
			_minIndex = i;
		}
		
		return true;
		
	}
	
	// equals method
	public boolean equals(Sequence s) {
		if (s._length != this._length)
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
	public void addItemset(Itemset i) {
		_sequence.add(i);
		_length += i.getItems().size();
		
		if (_minItemset == null || (_minItemset != null && _minItemset.getMinItem().getMinsup() > i.getMinItem().getMinsup())) {
			_minItemset = i;
			_minIndex = _sequence.size() - 1;
		}
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
		for (Itemset i : _sequence) {
			for (Item e : i.getItems())
				_length++;
		}
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
