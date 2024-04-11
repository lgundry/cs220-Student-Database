#include "treeNode.h"

// basic constructor
treeNode::treeNode() {
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	value = 0;
}

// constructor
treeNode::treeNode(int initialValue) {
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	value = initialValue;
}

// add leaf
void treeNode::addLeaf(int leafValue) {
	if (leafValue < value) {
		if (leftChild)
			leftChild->addLeaf(leafValue);
		else {
			leftChild = new treeNode(leafValue);
			leftChild->changeParent(this);
		}
	}
	else {
		if (rightChild)
			rightChild->addLeaf(leafValue);
		else {
			rightChild = new treeNode(leafValue);
			rightChild->changeParent(this);
		}
	}
}

// change parent
void treeNode::changeParent(treeNode* newParent) {
	parent = newParent;
}

// change left child
void treeNode::changeLeftChild(treeNode* newLeftChild) {
	leftChild = newLeftChild;
}

// change right child
void treeNode::changeRightChild(treeNode* newRightChild) {
	rightChild = newRightChild;
}

// print the tree - linear
void treeNode::print() {
	if (leftChild)
		leftChild->print();
	cout << value << " ";
	if (rightChild)
		rightChild->print();
}

// destructor
treeNode::~treeNode() {
	delete leftChild;
	leftChild = nullptr;
	delete rightChild;
	rightChild = nullptr;
	//how do i take care of my parent's child that points to me
	parent = nullptr;
}

// search the tree for searchValue
treeNode* treeNode::search(int searchValue) {
	if (value == searchValue)return this;
	if (searchValue < value) {
		if (!leftChild)return nullptr;
		return leftChild->search(searchValue);
	}
	if (!rightChild)return nullptr;
	return rightChild->search(searchValue);
}

// remove the node
void treeNode::remove(treeNode* &root) {

	if (leftChild) {
		leftChild->parent = this->parent;		
		if (rightChild) {
			treeNode* grandChild = leftChild->rightChild;
			leftChild->rightChild = this->rightChild;
			if (rightChild)
				rightChild->parent = leftChild;
			treeNode* temp = rightChild;
			while (temp->leftChild)temp = temp->leftChild;
			temp->leftChild = grandChild;
			if(grandChild)
				grandChild->parent = temp;
			temp = nullptr;
			grandChild = nullptr;
		}
		if (parent) {
			
			if(parent->rightChild==this)
				parent->rightChild = leftChild;//fails if root
			else
				parent->leftChild = leftChild;
		}
		else {
			root = leftChild;
			if (leftChild)
				leftChild->parent = nullptr;
		}
		parent = nullptr;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	else if (rightChild) {
		rightChild->parent = parent;
		if (parent) {
			if (parent->rightChild == this)
				parent->rightChild = leftChild;
			else
				parent->leftChild = leftChild;
		}
		else {
			root = rightChild;
			if (rightChild)
				rightChild->parent = nullptr;
		}
		parent = nullptr;
		rightChild = nullptr;
	}
	else {
		if (parent) {

			if (parent->rightChild == this)
				parent->rightChild = nullptr;
			else
				parent->leftChild = nullptr;
		}
		else
			root = nullptr;
		parent = nullptr;
	}
	delete this;
}

// fancy print - displays the tree in tree form
void treeNode::display(treeNode* aNode, int positionNumber) {
	if (aNode) {
		cout << aNode->value << endl;
		if (aNode->rightChild == nullptr && aNode->leftChild == nullptr)
			return;
		cout << '|';
		for (int i = 0; i < positionNumber; i++)
			cout << ' ';
		cout << "|_";
		display(aNode->rightChild, positionNumber + 1);
		cout << '|';
		for (int i = 0; i < positionNumber; i++)
			cout << ' ';
		cout << "|_";
		display(aNode->leftChild, positionNumber + 1);
	}
	else
		cout << '\b'<<endl;

}