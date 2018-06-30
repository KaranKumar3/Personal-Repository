package Stacks;

public class StackDriver {

	public static void main(String[] args) {
		
		Stack<Integer> stack = new ArrayStack<>(100);
		
		stack.push(new Integer(100));
		stack.push(new Integer(50));
		
		System.out.println(stack.peek());
		System.out.println(stack.peek());
	}

}
