import java.math.*;

public class Item {

	private String _name;
	private Integer _count = 0;
	private Double _minsup = 1.01;
	private Double _support = 0.0;
	
	//default constructor
	public Item() {
		
		this._name = "0";
		this._minsup = 1.01;
		
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
	
	public void setCount(int n) {
		_count = n;
	}
	
	public void setSup(int transactions) {
		//BigDecimal Support = new BigDecimal (0);
        
//        BigDecimal Count = new BigDecimal(_count);
//       
//        BigDecimal Trans = new BigDecimal (transactions);
      
        //Support = Count.divide(Trans, 8, BigDecimal.ROUND_CEILING);
        _support = BigDecimal.valueOf(_count).divide(BigDecimal.valueOf(transactions), 25, RoundingMode.HALF_DOWN).doubleValue();
       
	}
	
	public Double getSup() {
		return _support;
	}
	
	public void incCount() {
		_count++;
	}
}
