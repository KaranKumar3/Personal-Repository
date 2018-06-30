package LinkedList;

public class Driver {
	public static void main(String[] args) {
		/*
		ExampleLinkedList<String> list = new ExampleLinkedList();
		
		list.addToFront("Hello");
		list.addToFront("There");
		
		System.out.println(list);
		
		list.removeLast();
		
		System.out.println(list.size());
		System.out.println(list);
		*/
		
		ExampleLinkedList<Integer> list1 = new ExampleLinkedList<>();
		
		list1.addToFront(new Integer(1));
		list1.addToFront(new Integer(2));
		list1.addToFront(new Integer(3));
		list1.addToFront(new Integer(4));
		list1.addToFront(new Integer(5));
		
		for(Integer value : list1) {
			System.out.println(value);
		}
	
	}
}
