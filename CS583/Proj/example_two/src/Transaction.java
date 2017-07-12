

import java.util.ArrayList;

@Deprecated
public class Transaction {

	private ArrayList<Integer> items;
	
	public void setItems(ArrayList<Integer> _items){
		
		items = _items;		
	}
	
	public ArrayList<Integer> getItems(){
		
		return items;
	}	
}
