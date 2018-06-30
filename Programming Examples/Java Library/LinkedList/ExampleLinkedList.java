package LinkedList;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class ExampleLinkedList<E> implements Iterable<E>{
	
	private int size;
	private Node<E> head;
	private Node<E> tail;
	
	public ExampleLinkedList () {
		size = 0;
		head = null;
		tail = null;
	}

	public void addToFront(E e) {
		
		Node<E> newNode = new Node<>(); //1
		newNode.element = e;
		
		if(isEmpty()) {
			// corner case when list is empty
			head = tail = newNode;
			head.next = null;
		}
		else {
			newNode.next = head; //2
			head = newNode; //3
		}
		
		this.size++;
	}
	
	public void addToRear(E e) {
		
		Node<E> newNode = new Node<>(); //1
		newNode.element = e;
		
		if(isEmpty()) {
			// corner case when list is empty
			head = tail = newNode;
			head.next = null;
		}
		else {
			tail.next = newNode;
			this.tail = newNode;
		}
	
		this.size++;
	}
	
	public E removeFirst() {

		if(isEmpty()) {
			// is list empty?
			throw new NoSuchElementException("Empty List");
		}
		
		E temp = head.element;
		
		head = head.next;
		size--;
		
		if(isEmpty()) {
			tail = null;
		}
		if (this.size == 1) {
			tail = head;
		}
		return null;
	}
	
	public E removeLast() {
		if(isEmpty()) {
			// is list empty?
			throw new NoSuchElementException("Empty List");
		}
		
		E ret = tail.element;//1
		
		if (size == 1) {
			ret = removeFirst();
		}
		else {
			Node <E> newLast = head;
			 
			while(newLast.next != tail) {
				newLast = newLast.next;
			}
			
			tail = newLast;//2
			tail.next = null;//3
			size--;
		}
		return ret;
	}
	
	public E first() {
		
		if(isEmpty()) {
			return null;
		}
		else {
			return this.head.element;
		}
	}
	
	public E last() {
		
		if(isEmpty()) {
			return null;
		}
		else {
			return this.tail.element;
		}
	}
	
	public int size() {
		
		return size;
	}
	
	public boolean isEmpty() {
		
		return (this.size == 0);
	}
	
	public String toString() {
		
		return head.element.toString();	
	}
	
	private class Node<E> {
		
		private Node<E> next;
		private E element;
		
	}
	

	@Override
	public Iterator<E> iterator() {


		return new ListIterator<E>(head);
	}
	
	public class ListIterator<E> implements Iterator<E> {

		private Node<E> current;
		
		public ListIterator(Node<E> start) {
			
			this.current = start;
		}
		
		@Override
		public boolean hasNext() {
			
			return (current != (null));
		}

		@Override
		public E next() {
			
			if(hasNext()) {
				throw new NoSuchElementException("No more elements");
			}
			
			E ref = current.element;
			current = current.next;
			
			return ref;
		}
		
	}
	

}
