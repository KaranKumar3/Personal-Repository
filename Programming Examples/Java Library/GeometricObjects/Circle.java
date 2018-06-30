public class Circle implements Shape{
	
	double r;

	public Circle() {
		this(1);
	}

	public Circle(double r) {
		super();
		this.r = r;
	}

	public double getR() {
		return r;
	}

	public void setR(double r) {
		this.r = r;
	}

	@Override
	public double calculateArea() {
		return Math.PI * Math.pow(r,2);
	}

	@Override
	public double calculatePerimeter() {
		return r * 2.0 * Math.PI;
	}

	public String toString() {
		return "Circle [r=" + r + " perimeter=" + calculatePerimeter() + " area=" + calculateArea() + "]";
	}

}
