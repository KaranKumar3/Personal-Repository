public class Rectangle implements Shape {

	double l;
	double w;

	public Rectangle() {
		this(1.0,1.0);
	}
	
	public Rectangle(double l, double w) {
		super();
		this.l = l;
		this.w = w;
	}

	@Override
	public double calculateArea() {
		return l * w;
	}

	@Override
	public double calculatePerimeter() {
		return (2 * w) + (2 * l);
	}
	
	@Override
	public String toString() {
		return "Rectangle [l=" + l + " w=" + w + " perimeter=" + calculatePerimeter() + " area=" + calculateArea() + "]";
	}

}
