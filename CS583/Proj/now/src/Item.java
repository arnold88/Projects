import java.math.*;

public class Item {

	private String _name;
	private Integer _count = 0;
	private double _minsup = 1.01;
	private double _support = 0.0;
	
	//default constructor
	public Item() {
		
		this._name = "0";
		this._minsup = 1.01;
		
	}
	
	public Item(String name, double minsup) {
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
	
	public double getMinsup() {
		return _minsup;
	}
	
	public void setMinsup(double minsup) {
		_minsup = minsup;
	}
	
	public Integer getCount() {
		return _count;
	}
	
	public void setCount(int n) {
		_count = n;
	}
	
	public void setSup(int transactions) {
		//double Support = new double (0);
        
//        double Count = new double(_count);
//       
//        double Trans = new double (transactions);
      
        //Support = Count.divide(Trans, 8, double.ROUND_CEILING);
        _support = BigDecimal.valueOf(_count).divide(BigDecimal.valueOf(transactions), 10, BigDecimal.ROUND_HALF_UP).doubleValue();
       
	}
	
	public double getSup() {
		return _support;
	}
	
	public void incCount() {
		_count++;
	}
}
