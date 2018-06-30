package Generics;

import java.util.ArrayList;
import java.util.List;

public class Crate<T extends Box<?>> {
	
	List<T> list = new ArrayList<>();
	
	public Crate() {
		
	}

	/**
	 * @return the list
	 */
	public List<T> getList() {
		return list;
	}

	/**
	 * @param list the list to set
	 */
	public void setList(ArrayList<T> list) {
		this.list = list;
	}

	public void add(T t) {
		list.add(t);
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("Crate [list=");
		builder.append(list);
		builder.append("]");
		return builder.toString();
	}
	

}
