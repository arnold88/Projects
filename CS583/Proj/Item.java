public class Item {

	private String _name;
	private Integer _count = 0;
	private Double _minsup = 0.00;
	
	//default constructor
	public Item() {
		
		this._name = "0";
		this._minsup = 0.000;
		
	}
	
	public Item(String name, Double minsup) {
		this._name = name;
		this._minsup = minsup;
	}
	
	public boolean equals(Item i) {
		if (i.getName().equals(this.getName()))
			return true;
		return false;
	}
	
	public String toString() {
		return _name;
	}
	
	public String getName() {
		return _name;
	}
	
	public void setName(String name) {
		_name = name;
	}
	
	public Double getMinsup() {
		return _minsup;
	}
	
	public void setMinsup(Double minsup) {
		_minsup = minsup;
	}
	
	public Integer getCount() {
		return _count;
	}
	
	public void incCount() {
		_count++;
	}
}
