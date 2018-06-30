public class Square extends Rectangle {
	
	public Square () {
		this(1);
	}

	public Square(double s) {
		super(s,s);
	}
	
	@Override
	public String toString() {
		return "Square [s=" + w + " perimeter=" + calculatePerimeter() + " area=" + calculateArea() + "]";
	}

}
