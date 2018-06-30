package Generics;

public class CollectionsExample {

	public static void main(String[] args) {
		
		Box<Integer> b1 = new Box<Integer>();
		Box<Double> b2 = new Box<Double>();
		Box<Box<Integer>> b3 = new Box<Box<Integer>>();
		
		b1.setT(new Integer(42));
		b2.setT(new Double(4.2));
		b3.setT(b1);
		
		Crate<Box<?>> crate = new Crate<>();
		crate.add(b1);
		crate.add(b2);
		crate.add(b3);
		
		System.out.println(b1);
		System.out.println(b2);
		System.out.println(b3);
		
		System.out.println(crate);
	}

}
