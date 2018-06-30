public class AreaCalculator {

	public static void main(String[] args) {
		Square s1 = new Square(3);
		Circle c1 = new Circle(3);
		Rectangle r1 = new Rectangle(2,5);
		
		Shape[] shapes = new Shape[3];
		
		shapes[0] = s1;
		shapes[1] = c1;
		shapes[2] = r1;
		
		for(Shape s : shapes) {
			
			System.out.println(s);
		}
		
        //System.out.println(s1);
        //System.out.println(c1);
        //System.out.println(r1);
	}

}
