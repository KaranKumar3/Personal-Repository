/**
 * Point class that represents a coordinate plane
 * 
 * @author Karan Kumar
 *
 */
public class Point {

	private double x;
	private double y;
	
	public Point() {
		
		x = 0.0;
		y = 0.0;
	}

	public Point(double x, double y) {
		
		this.x = x;
		this.y = y;
	}

	public double distance(Point p2) {
		double distance = 0.0;
		
		
		return distance;
	}
	
	public double getX() {
		
		return x;
	}
	
	public void setX(double x){
		this.x = x;
	}

	public double getY() {
		
		return y;
	}
	
	public void setY(double y){
		this.y = y;
	}
	
	public void setPoint(double x, double y) {
		this.x = x;
		this.y = y;
	}

	public void shiftX(double n) {
		this.x = x + n;
		
	}

	public void shiftY(double n) {
		this.y = y + n;
		
	}
	public void rotate(double angle) {
		this.x = (x*Math.cos(angle)) - (x*Math.sin(angle));

		this.y = (y*Math.sin(angle)) + (y*Math.cos(angle));
		
	}

	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("Point [x=");
		builder.append(x);
		builder.append(", y=");
		builder.append(y);
		builder.append("]");
		return builder.toString();
	}

}
