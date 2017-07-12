import java.math.*;
import java.util.*;

public class Item {

	private String _name;
	private Integer _count = 0;
	private double _minsup = 1.01;
	//private BigDecimal _minsup = BigDecimal.valueOf(1.01d);
	private double _support = 0.0;
	
	//default constructor
//	public Item() {	
//		this._name = "0";
//		this._minsup = BigDecimal.valueOf(1.01d);	
//	}
	
	public Item() {	
		this._name = "0";
		this._minsup = 1.01;	
	}
	
//	public Item(String name, BigDecimal minsup) {
//		this._name = name;
//		this._minsup = minsup;
//	}
	
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
	
//	public BigDecimal getMinsup() {
//		return _minsup;
//	}
	
	public Double getMinsup() {
		return _minsup;
	}
	
//	public void setMinsup(BigDecimal minsup) {
//		_minsup = minsup;
//	}
	
	public void setMinsup(Double minsup) {
		_minsup = minsup;
	}
	
	public Integer getCount() {
		return _count;
	}
	
	public void setCount(int n) {
		_count = n;
	}
	
//	public void setSup(HashMap<Item, BigDecimal> supports) {
//		
//		_support = supports.get(this);
//        //_support = BigDecimal.valueOf(_count).divide(BigDecimal.valueOf(transactions), 25, BigDecimal.ROUND_HALF_UP).doubleValue();
//		//_support = _count * 1.0 / transactions; 
//       
//	}
	
//	public BigDecimal getSup(HashMap<Item, BigDecimal> supports) {
//		return supports.get(this);
//	}
	
	public Double getSup(HashMap<Item, Double> supports) {
		return supports.get(this);
	}
	
	public void incCount() {
		_count++;
	}
}
