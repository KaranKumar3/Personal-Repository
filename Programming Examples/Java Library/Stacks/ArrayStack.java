package Stacks;

public class ArrayStack<T> implements Stack<T>{

	private T[] arr;
	int top = 0;
	
	
	public ArrayStack() {
		arr = (T[]) (new Object[10]);
	}
	
	public ArrayStack(int size) {
		arr = (T[]) (new Object[size]);
	}
	
	@Override
	public void push(T t) {
		top++;
		arr[top] = t;
		
	}

	@Override
	public T pop() {
		 T temp = arr[top];
		 arr[top] = null;
		 top--;
		 
		return temp;
	}

	@Override
	public T peek() {
		return arr[top];
	}

	@Override
	public boolean isEmpty() {

		return (arr.length == 0);
	}

	@Override
	public int size() {
		
		return arr.length;
	}

}
