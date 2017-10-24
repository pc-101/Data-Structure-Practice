/***********************************************
	 Data Structure Practice: Linked List
	 LinkedList.cpp
	 Purpose: Simple implementation of an
	 integer-based linked list

	 @author Peter Chea
	 @version 1.0
***********************************************/

#include <iostream>
#include <stdio.h>

struct Node
{
	// Handle pointer initialization so we don't clutter in class constructor
	Node() : next(nullptr), prev(nullptr)
	{}
	int value = 0;
	Node* next, *prev;
};

class List
{
public:
	List() : tail(head)
	{}

	~List() {
		Node* curr = head; 
		while (curr != nullptr) {
			Node* temp = curr;
			curr = curr->next; 
			delete temp;
		}
		delete curr;
	}

	/**
		Lets user know if the list is empty or not
		
		@return result	Returns true if empty, otherwise false
	*/

	bool isEmpty() {
		bool result = size == 0 ? true : false; 
		return result; 
	}

	/**
		Inserts a Node at the end of the list

		@param ptr	The Node being inserted
	*/
	void insert_end(Node* ptr) {
		if (isEmpty())
		{
			head = ptr;
			tail = ptr;
		}
		else {
			Node* curr = tail; 
			curr->next = ptr; 
			ptr->prev = curr;
			ptr->next = nullptr;
			tail = ptr;
		}

		size++; 
	}

	/**
		Inserts a Node at the start of the list

		@param ptr	The Node being inserted
	*/
	void insert_start(Node* ptr) {
		if (isEmpty())
		{
			head = ptr; 
			tail = ptr; 
		}
		else {
			Node* curr = head;
			curr->prev = ptr; 
			ptr->next = curr;
			ptr->prev = nullptr;
			head = ptr;
		}
		
		size++; 
	}

	/** 
		Inserts a Node just after a Node with 
		the desired value. If multiple values 
		exist, it will insert it after the 
		first instance.
		If the Node does not exist, we will
		spit an error message letting the user
		know.
		
		@param val	The value we are searching for
		@param ptr	The node we are inserting
	*/
	void insert_after(int val, Node* ptr) {
		if (find(val)) {
			Node* curr = head;
			while (curr != nullptr) {
				if (curr->value == val)
					break;
				curr = curr->next;
			}
			ptr->next = curr->next;
			ptr->prev = curr;

			// In case user happens to use this method on an end node, update tail pointer
			if (curr->next == nullptr)
				tail = ptr; 
			else
				curr->next->prev = ptr;		// Only set the next pointer's prev pointer if next ptr isn't nullptr
			curr->next = ptr;
		}
		else
			std::cerr << "Failed to insert_after! Reason: "
			<< "No Node exists with value " << val << "!" << std::endl; 
	}

	/**
	Inserts a Node just before a Node with 
	the desired value. If multiple values 
	exist, it will insert it before the 
	first instance.
	If the Node does not exist, we will
	spit an error message letting the user
	know.

	@param val	The value we are searching for
	@param ptr	The node we are inserting
	*/
	void insert_before(int val, Node* ptr) {
		if (find(val)) {
			Node* curr = head;
			while (curr != nullptr) {
				if (curr->value == val)
					break;
				curr = curr->next;
			}
			ptr->next = curr;
			ptr->prev = curr->prev;

			// In case user happens to use this method on a start node, update head pointer
			if (curr->prev == nullptr)
				head = ptr;
			else
				curr->prev->next = ptr;		// Only set the next pointer's prev pointer if next ptr isn't nullptr
			curr->prev = ptr;
		}
		else
			std::cerr << "Failed to insert_before! Reason: " 
			<< "No Node exists with value " << val << "!" << std::endl;
	}

	/** 
		Tries to find a value, returning True if 
		found, False if not found
		
		@param val	The value we are searching for
		
		@return bool	True if found, else False
	*/
	bool find(int val) {
		Node* curr = head; 
		while (curr != nullptr) {
			if (curr->value == val)
				return true; 
			curr = curr->next;
		}
		return false; 
	}

	/**
		Deletes node with value val. If multiple values of value val 
		exist, delete the first instance. 

		@param val	The value we are trying to get rid of 		
	*/
	void delete_node(int val) {
		Node* curr = head; 
		if (find(val)) {
			while (curr != nullptr) {
				if (curr->value == val)
					break; 
				curr = curr->next; 
			}

			// If we only have 1 node to delete, just delete the node
			Node* temp = curr; 
			if (temp->prev == nullptr && temp->next == nullptr) 
			{
				head->next = nullptr; 
				tail = head; 
			}
			// Otherwise, by default try to set temp to the previous ptr
			else if (temp->prev != nullptr) 
			{
				curr = temp->prev;
				curr->next = temp->next; 
				temp->next->prev = curr; 
				delete temp; 
			}
			else
			{
				curr = temp->next;
				curr->prev = temp->prev; 
				temp->prev->next = curr; 
				delete temp; 
			}
		}
		else
			std::cerr << "Unable to delete_node with value: " << val
			<< ". Reason: value not found!" << std::endl; 
	}


	/** 
		Prints out the values and addresses of the head and tail pointers, essentially representing 
		the beginning and end of the list, respectively
	*/
	void print_info () {
		std::cout << "Head value: " << head->value << ", Tail value: " << tail->value << "\n"; 
		std::cout << "Head address: " << head << " and Tail address: " << tail << "\n"; 
	}

	/**
		Prints out the values of every item in the linked list, starting from the head
	*/
	void print_nodes() {
		Node* curr; 
		std::cout << "The list contains: "; 
		for (curr = head; curr != nullptr; curr = curr->next)
			printf("%d ", curr->value);
		printf("\n"); 
	}
private:
	Node *head, *tail;
	int size; 
};

int main() {

	/** 
		Examples below show how to use the function methods
	*/

	List l; 
	Node* n1 = new Node();	
	Node* n2 = new Node(); 
	Node* n3 = new Node();
	Node* n4 = new Node();
	Node* n5 = new Node();
	Node* n6 = new Node();
	Node* n7 = new Node(); 
	Node* n8 = new Node(); 

	// Set values of nodes n1 to n8
	n1->value = 1; 
	n2->value = 2; 
	n3->value = 3; 
	n4->value = 0;
	n5->value = -1;
	n6->value = -2;
	n7->value = 27; 
	n8->value = -100; 

	// Insert 3 nodes, 1 2 3 at the end of the list
	l.insert_end(n1); 
	l.insert_end(n2);
	l.insert_end(n3);

	// Insert 3 nodes, -2, -1, 0 at the beginning of the list
	l.insert_start(n4); 
	l.insert_start(n5); 
	l.insert_start(n6); 

	// Use n7 to test insert_after method
	l.insert_after(n1->value, n7); 

	// Use n8 to test insert_before method
	l.insert_before(n7->value, n8); 

	// Can test delete_node on any desired node
	l.delete_node(-100); 

	// Prints addresses of each node
	std::cout << "Address of n1: " << n1 << std::endl;
	std::cout << "Address of n2: " << n2 << std::endl;
	std::cout << "Address of n3: " << n3 << std::endl;
	std::cout << "Address of n4: " << n4 << std::endl;
	std::cout << "Address of n5: " << n5 << std::endl;
	std::cout << "Address of n6: " << n6 << std::endl;
	std::cout << "Address of n7: " << n7 << std::endl;
	std::cout << "Address of n8: " << n8 << std::endl;

	// Tries to find the desired value
	std::cout << l.find(0) << std::endl; 
	std::cout << l.find(1) << std::endl;
	std::cout << l.find(2) << std::endl;
	std::cout << l.find(3) << std::endl;
	std::cout << l.find(-0) << std::endl;
	std::cout << l.find(-1) << std::endl;
	std::cout << l.find(-2) << std::endl;
	std::cout << l.find(27) << std::endl;
	std::cout << l.find(-100) << std::endl;

	l.print_info(); 
	l.print_nodes(); 
}