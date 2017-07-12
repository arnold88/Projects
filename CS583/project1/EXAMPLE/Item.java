
/*
 * Item class stores item specific information.
 *
 */
public class Item {

	private String _name;
	private Integer _count = 0;        //use it to count the number of this item in DB; 
	private Double _minsup =0.0;
	
	public Item(){
		
	}
	public Item(String name, Double minsup){
		this._name=name;
		this._minsup=minsup;
	}
	public String getName(){
		return _name;
	}
	
	public void setName(String name) {
		_name = name;
	}

	public Double getMinSup(){
		return _minsup;
	}
	
	public void setMinSup(Double minSup) {
		_minsup = minSup;
	}
	
	public Integer getCount(){
		return _count;
	}
	public void addCount(){
		_count++;
	}
}
