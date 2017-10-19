#include <iostream>
#include <math.h>
#include <queue>

/***********************************************
  Data Structure Practice: Binary Search Tree
***********************************************/

struct Node {
	// Constructor
	Node(int n)
		:value(n), left(NULL), right(NULL)
	{}

	// Copy Constructor
	Node(Node* n) {
		this->left = n->left;
		this->right = n->right;
		this->value = n->value;
		std::cout << "I'm being copied!!!!" << std::endl; 
	}

	// Member variables
	Node* left;
	Node* right;
	int value;
};

class Tree
{
public:
	// Constructor
	Tree()
		: root(new Node(1)), size(1), height(1)
	{
		q.push(root); 
	}

	// Copy Constructor
	Tree(const Tree& rhs)
	{
		this->root		= rhs.root;
		this->size		= rhs.size;
		this->height	= rhs.height; 
	}

	// Destructor 
	~Tree()
	{
		deletePostOrder(root);
	}

	// Functions to push a node to the left or right child position
	void push_left(Node* curr, Node* next)
	{
		curr->left = next;
		q.push(next); 
		size++;
		unsigned int temp = ceil((size - 1) / 2.0); 
		height = temp > height ? temp : height; 
	}
	void push_right(Node* curr, Node* next)
	{
		curr->right = next;
		q.push(next);
		size++;
		unsigned int temp = ceil((size - 1) / 2.0);
		height = temp > height ? temp : height;
	}

	// Checks if the tree is empty
	bool isEmpty() const
	{
		if (size)
			return false;
		return true;
	}

	// Returns the size of the tree
	int getSize() const
	{
		return size;
	}

	// Returns the height of the tree
	int getHeight() const
	{
		return height; 
	}

	// Returns the root of the tree 
	Node* getRoot() {
		return root;
	}

	/*******************************
	 Breadth first search traversal:
	*******************************/

	// Level Order Traversal
	void printLevelOrder(Node* n)
	{
		while (!q.empty())
		{
			std::cout << q.front().value << " "; 
			q.front() = NULL;		// Reassign copied pointer to new memory location before popping off queue
			q.pop(); 
		}
	}

	/*******************************
	  Depth first search traversal:
	*******************************/

	// In-order Traversal
	void printInOrder(Node* n)
	{
		if (!n)
			return;
		printInOrder(n->left);
		std::cout << n->value << " ";
		printInOrder(n->right);
	}

	// Pre-order Traversal
	void printPreOrder(Node* n)
	{
		if (!n)
			return;
		std::cout << n->value << " ";
		printPreOrder(n->left);
		printPreOrder(n->right);
	}

	// Post-order Traversal
	void printPostOrder(Node* n)
	{
		if (!n)
			return;
		printPostOrder(n->left);
		printPostOrder(n->right);
		std::cout << n->value << " ";
	}

	// Delete Tree Using Post-Order Traversal
	void deletePostOrder(Node* n)
	{
		if (!n)
			return;
		deletePostOrder(n->left);
		deletePostOrder(n->right);
		std::cout << "Deleting node: " << n << std::endl;	// Prints out the address of node-to-be-deleted
		delete n;
	}

private:
	Node* root;
	unsigned int size, height; 
	std::queue<Node> q; 
};

int main()
{
	Tree t;
	Node* n1 = new Node(2);
	Node* n2 = new Node(3);
	Node* n3 = new Node(4);
	Node* n4 = new Node(5);
	Node* n5 = new Node(6);
	Node* n6 = new Node(7);
	t.push_left(t.getRoot(), n1);
	t.push_right(t.getRoot(), n2);
	t.push_left(n1, n3);
	t.push_right(n1, n4);
	t.push_left(n2, n5);
	t.push_right(n2, n6);

	if (!t.isEmpty()) {
		printf("The size of the tree is: %d\n", t.getSize());
		printf("The height of the tree is: %d\n\n", t.getHeight());
	}
	std::cout << "Printing tree in level order:\n";
	t.printLevelOrder(t.getRoot());
	std::cout << std::endl;
	
	std::cout << "Printing tree in order:\n";
	t.printInOrder(t.getRoot());
	std::cout << std::endl;

	std::cout << "Printing tree in pre-order:\n";
	t.printPreOrder(t.getRoot());
	std::cout << std::endl;

	std::cout << "Printing tree in post-order:\n";
	t.printPostOrder(t.getRoot());
	std::cout << std::endl;
	std::cout << std::endl;
}