package Generics;

public class Box<T> {
	
	T t;
	
	private int serialNumber;
	
	@SuppressWarnings("unchecked")
	public Box() {
		t = (T) new Object();
	}

	/**
	 * @return the int1
	 */
	public T getT() {
		return t;
	}

	/**
	 * @param int1 the int1 to set
	 */
	public void setT(T t) {
		this.t = t;
	}

	/**
	 * @return the serialNumber
	 */
	public int getSerialNumber() {
		return serialNumber;
	}

	/**
	 * @param serialNumber the serialNumber to set
	 */
	public void setSerialNumber(int serialNumber) {
		this.serialNumber = serialNumber;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("Box [t=");
		builder.append(this.t);
		builder.append("]");
		return builder.toString();
	}
	
	
	

}
