import java.util.*;

public class ItemComp implements Comparator<Item> {

	public ItemComp() {
	}
	
	public int compare(Item i1, Item i2) {
		if (Integer.parseInt(i1.getName().trim()) < Integer.parseInt(i2.getName().trim()))
			return -1;
		if (Integer.parseInt(i1.getName().trim()) > Integer.parseInt(i2.getName().trim()))
			return 1;
		return 0;
	}
}
