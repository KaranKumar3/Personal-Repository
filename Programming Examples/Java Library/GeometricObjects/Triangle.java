public class Triangle implements Shape{
	
	private double base;
	private double height;
	
	public Triangle() {
		this(1.0, 1.0);
	}
	
	/**
	 * 
	 * @param base
	 * @param height
	 */
	public Triangle(double base, double height) {
		super();
		this.base = base;
		this.height = height;
	}

	@Override
	public double calculateArea() {
		
		return (0.5 * this.base * this.height);
	}

	@Override
	public double calculatePerimeter() {
		
		double hyp = Math.sqrt(Math.pow(this.base, 2) + Math.pow(this.height, 2));
		return (this.base + this.height + hyp);
	}

	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("Triangle [base=");
		builder.append(base);
		builder.append(", height=");
		builder.append(height);
		builder.append("]");
		return builder.toString();
	}
	
	
	

}
