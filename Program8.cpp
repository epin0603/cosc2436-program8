///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Eddie G. Pineda																			         //
//Date: 12/02/2022																				         //
//Program Statement: Design a class for a binary search tree capable of storing numbers. The class       //
//                   should have member functions: void insert(double x)                                 //
//                                                 bool search(double x)                                 //
//                                                 void inorder(vector& v)                               //
//                   The insert function should not use recursion, the search function should work       //
//                   by calling a private recursive member function: bool search(double x, BtreeNode *t) //
//                   The inorder function is passed an initially empty vector v, it fills v with the in  //
//                   in order list of numbers stored in the binary search tree.                          //
//                   The function int size() returns the number of nodes stored in the tree.             //
//                   Function int height() returns the height of the tree (number of levels).            //
//                   int width() computes the width of the tree (largest number of nodes at the same     //
//                   level.                                                                              //
//                   Design and implement a copy constructor and overloaded assignment operator.         //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
using namespace std;

class BinaryTree { //Binary search tree class
public:
	BinaryTree(); //Default constructor
	BinaryTree(const BinaryTree&); //Copy constructor
	void operator=(BinaryTree); //Overloaded assignment operator
	void insert(double); //Insert function
	bool search(double); //Search function
	void inorder(vector<double>&); //Inorder function
	int size(); //Size function
	int leafCount(); //leafCount function
	int height(); //height function
	int width(); //width function

private:
	class node { //Node class for the binary search tree
		friend class BinaryTree; //Connect both classes
		double value; //Value of current node
		node* left; //Left child
		node* right; //Right child

		node(double val1, node* left = NULL, node* right = NULL) { //Overloaded constructor of node
			value = val1; //Sets value to the desired value
			this->left = left; //Sets the left to the desired value
			this->right = right; //Sets the right to the desired value
		}
	};
	node* root; //Root node
	void insert(node*&, double); //Insert helper function
	bool search(node*, double); //Search helper function
	void inorder(vector<double>&, node*); //Helper inorder function
	int size(node*&); //Helper size function
	int count; //Stores a count of nodes
	int leafCount(node*); //Helper leafCount function
	int height(node*); //Helper height function
	int leftCount, rightCount; //Counters for the height function
	int width(node*); //Helper width function
	int mWidth; //mWidth stores the current maximum width
	int gWidth(node*,int); //gWidth returns the count of the current width
	static node* tCopy(node*); //Helper function for copy constructor
	static void destructTree(node*); //Destructor
};

BinaryTree::BinaryTree() { //Default constructor
	root = NULL; //Sets the root node to null
	count = 0; //Sets the count to 0
	leftCount = 0; //The leftCount variable is set to 0
	rightCount = 0; //The rightCount variable is set to 0
	mWidth = 0; //Sets the maximum width to 0
}

BinaryTree::BinaryTree(const BinaryTree& copyOrg) { //Copy constructor
	root = tCopy(copyOrg.root); //Sets root to a call from the helper function
}

BinaryTree::node* BinaryTree::tCopy(node* tNode) { //Helper copy constructor function
	if (tNode == NULL) { //Checks if node is NULL
		return NULL;
	}
	else {
		node* leftTail = tCopy(tNode->left); //Creates a pointer recursively for the left tail
		node* rightTail = tCopy(tNode->right); //Creates a pointer recursively for the right tail
		return new node(tNode->value, leftTail, rightTail); //Creates a new overloaded nodw with the values to copy the node
	}
}

void BinaryTree::operator=(BinaryTree rNode) { //Overloaded assignment operator
	destructTree(root); //Calls on destructor to destroy the original root
	root = tCopy(rNode.root); //Assigns root to the new root using the copy constructor
}

void BinaryTree::destructTree(node* tNode){ //Destructor
	if (!tNode) { //Checks if the node exists
		return; //Returns if it does not exist
	}
		destructTree(tNode->left); //Recursively destroys the left-child of the tree
		destructTree(tNode->right); //Recursively destroys the right-child of the tree
		delete tNode; //Deletes the current node
}

void BinaryTree::insert(double x) { //Insert function
	insert(root, x); //Calls on the helper function
}

void BinaryTree::insert(node*& tNode, double x) { //Helper insert function
	if (!tNode) { //Checks if the node exists
		tNode = new node(x); //Creates a new node with the same name
		return; //Returns
	}
	if (tNode->value == x) { //If the value is already present
		return; //Returns
	}
	if (x < tNode->value) { //If the value is less than the current node value
		insert(tNode->left, x); //Sets value as left child
	}
	else { //If the value is more than the current node value
		insert(tNode->right, x); //Sets the value to the right child
	}
}

bool BinaryTree::search(double x) { //Search function
	return search(root, x); //Calls on the search helper function
}

bool BinaryTree::search(node* tNode, double x) { //Helper search function
	while (tNode) { //While there are values in the node
		if (tNode->value == x) { //If the current node value is equal to x
			return true; //Return true
		}
		else if (x < tNode->value) { //Else if x is smaller than the current node value
			return search(tNode->left, x); //Calls on the private recursive member function(itself) to examine left-child values
		}
		else { //Else if x is greater than the current node value
			return search(tNode->right, x); //Calls on itself recursivelt to examine right0child values
		}
	}
	return false;
}

void BinaryTree::inorder(vector<double>& vec) { //Inorder function
	inorder(vec, root); //Calls on the helper inorder function
}

void BinaryTree::inorder(vector<double>& vec, node* tNode) { //Inorder helper function
	if (tNode) { //If the node exists
		inorder(vec, tNode->left); //Recursively call the inorder helper function with the left-child node
		vec.push_back(tNode->value); //Pushes back the current value into the vector
		inorder(vec, tNode->right); //Recursively call the inorder helper function with the right-child node
	}
}

int BinaryTree::size() { //Size function
	count = 0; //Sets the count to 0
	return size(root); //Returns a call for the helper function
}

int BinaryTree::size(node*& tNode) { //Helper size function
	if (tNode) { //If the node is not empty
		size(tNode->left); //Recursion on the left-child
		count++; //Increases the count by one
		size(tNode->right); //Recursion on the right-child
	}
	return count;
}

int BinaryTree::leafCount() { //leafCount function
	count = 0; //Sets the count to 0
	return leafCount(root); //Returns a call to the helper function
}

int BinaryTree::leafCount(node* tNode) { //Helper leafCount function
	if (tNode) { //Checks if the node exists
		leafCount(tNode->left); //Recursion on the left-child
		leafCount(tNode->right); //Recursion on the right-child
		if ((tNode->left == NULL) && (tNode->right == NULL)) { //If both left and right children are NULL
			count++; //Increase count by one
		}
	}
	return count;
}

int BinaryTree::height() { //height function
	return height(root); //Returns a call to the helper function
}

int BinaryTree::height(node* tNode) { //Helper height function
	if (!tNode) { //Checks if the node does not exist
		return 0;
	}
	leftCount = height(tNode->left); //Sets leftCount to a recursion call of the left-child
	rightCount = height(tNode->right); //Sets rightCount to a recursion call of the right-child

	if (leftCount > rightCount) { //If leftCount > rightCount
		return leftCount + 1;
	}
	else {
		return rightCount + 1;
	}
}

int BinaryTree::width() { //width function
	mWidth = 0; //Sets maximum width to 0
	return width(root); //Returns a call to the helper function
}

int BinaryTree::gWidth(node* tNode, int indx) { //Additional width function to get the width of each branch set
	if (tNode == NULL) { //If the node is equal to NULL
		return 0;
	}
	if (indx == 1) { //If the index is 1
		return 1;
	}
	else if(indx > 1) { //If the index is greater than 1
		return gWidth(tNode->left, indx - 1) + gWidth(tNode->right, indx - 1); //Return the sum of recursive functions to check the left and right children
	}
}

int BinaryTree::width(node* tNode) { //Helper width function
	int wM = 0; //Sets max width to 0
	int hNode = height(tNode); //Stores the height of the node

	for (int i = 1; i <= hNode; i++) { //For loop that parses through each index until the height of the tree is reached
		mWidth = gWidth(tNode, i); //Calls on the gWidth function to examine the width of the node at the current height index
		if (mWidth > wM) { //If width is greater than max width
			wM = mWidth;
		}
	}
	return wM; //Return max width
}

int main() {
	BinaryTree tTest; //Creates a binary tree
	vector<double> tVec; //Creates vector used in binary tree
	vector<double> tVec2; //Creates vector used in copy constructor

	//List of values used to test the binary tree
	tTest.insert(10.2);
	tTest.insert(12.1);
	tTest.insert(5.8);
	tTest.insert(14.6);
	tTest.insert(13.5);

	cout << "Binary tree search for 12.1: " << endl;
	if (tTest.search(12.1)) { //If statement uses the search function to look for a specific value in the tree
		cout << "The value 12.1 was found in the tree" << endl;
	}
	else { //If the value is not found
		cout << "The value was not found in the tree" << endl;
	}

	cout << endl << "Inorder function for original tree:";
	tTest.inorder(tVec); //Uses inorder function to organize the binary tree values in the tVec vector
	cout << endl;
	for (int i = 0; i < tVec.size(); i++) { //For loop used to parse through the entire vector
		cout << tVec[i] << " "; //Prints out the value for the current index in the vector
	}
	cout << endl;

	BinaryTree tTest2(tTest); //Binary tree used in copy constructor

	cout << endl << "Inorder function for copy tree:";
	tTest2.inorder(tVec2); //Uses inorder function to organize the binary tree values in the tVec vector
	cout << endl;
	for (int i = 0; i < tVec2.size(); i++) { //For loop used to parse through the entire vector
		cout << tVec2[i] << " "; //Prints out the value for the current index in the vector
	}
	cout << endl;

	tTest = tTest2;

	cout << endl << "Inorder function for original tree after overloaded assignment operator:";
	tTest.inorder(tVec); //Uses inorder function to organize the binary tree values in the tVec vector
	cout << endl;
	for (int i = 0; i < tVec.size(); i++) { //For loop used to parse through the entire vector
		cout << tVec[i] << " "; //Prints out the value for the current index in the vector
	}
	cout << endl;

	cout << endl << "The size of the binary search tree: " << tTest.size() << endl; //Prints out the current size of the tree
	cout << endl << "The leaf count is: " << tTest.leafCount() << endl; //Prints out the leaf count of the tree
	cout << endl << "The height of the tree: " << tTest.height() << endl; //Prints out the height of the tree
	cout << endl << "Tree width: " << tTest.width() << endl; //Prints out the width of the tree

	return 0;
}