#include "studentNode.h"
using namespace std;

studentNode::studentNode() {
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	name = "";
	grade = "";
	height = 1;
}

studentNode::studentNode(string newName, string newGrade, SDB* aDB) {
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	name = newName;
	grade = newGrade;
	myDB = aDB;
	height = 1;
}
// TODO: Add rotations and replace data if newName == name
void studentNode::addLeaf(string newName, string newGrade, SDB* aDB) {
	if (newName == name) { // if they are the same, replace data and exit
		grade = newGrade;
		return;
	}

	if (newName < name) { // unchanged
		if (leftChild)
			leftChild->addLeaf(newName, newGrade, aDB);
		else {
			leftChild = new studentNode(newName, newGrade, aDB);
			leftChild->changeParent(this);
		}
	}
	else {
		if (rightChild)
			rightChild->addLeaf(newName, newGrade, aDB);
		else {
			rightChild = new studentNode(newName, newGrade, aDB);
			rightChild->changeParent(this);
		}
	}

	// set heights
	int leftHeight = maxHeight(leftChild);
	int rightHeight = maxHeight(rightChild);
	if (leftHeight > rightHeight)
		height = leftHeight;
	else
		height = rightHeight;

	// Balance
	if (leftChild && rightChild) {
		int dif = leftChild->height - rightChild->height;
		// The difference should never be more than 2 - if less than 2, no need to rotate
		switch(dif) {
			case 2: // leftChild is greater
				if (leftChild->leftChild >= leftChild->rightChild)
					rotateRight(leftChild, this);
				else
					rotateLR(leftChild->rightChild, leftChild, this);
			case -2: // rightChild is greater
				if (rightChild->rightChild >= rightChild->leftChild)
					rotateLeft(rightChild, this);
				else
					rotateRL(rightChild->leftChild, rightChild, this);
		}
	}
	else {
		if (rightChild && rightChild->height > 1)
			rotateLeft(rightChild, this);
		if (leftChild && leftChild->height > 1)
			rotateRight(leftChild, this);
	}
}

void studentNode::changeParent(studentNode* newParent) {
	parent = newParent;
}
void studentNode::changeLeftChild(studentNode* newLeftChild) {
	leftChild = newLeftChild;
}
void studentNode::changeRightChild(studentNode* newRightChild) {
	rightChild = newRightChild;
}
void studentNode::print() {
	if (leftChild)
		leftChild->print();
	cout << name + ": " + grade << endl;
	if (rightChild)
		rightChild->print();
}

studentNode::~studentNode() {
	delete leftChild;
	leftChild = nullptr;
	delete rightChild;
	rightChild = nullptr;
	//how do i take care of my parent's child that points to me
	parent = nullptr;
}

studentNode* studentNode::search(string key) {
	
	if (name == key)return this;
	if (key < name) {
		if (!leftChild)return nullptr;
		return leftChild->search(key);
	}
	if (!rightChild)return nullptr;
	return rightChild->search(key);
}

void studentNode::remove(studentNode* &root) {

	if (leftChild) {
		leftChild->parent = this->parent;		
		if (rightChild) {
			studentNode* grandChild = leftChild->rightChild;
			leftChild->rightChild = this->rightChild;
			if (rightChild)
				rightChild->parent = leftChild;
			studentNode* temp = rightChild;
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

void studentNode::display(studentNode* aNode, int positionNumber) {
	if (aNode) {
		cout << aNode->name + ": " + aNode->grade << endl;
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

string studentNode::getName() {
	return name;
}
string studentNode::getGrade() {
	return grade;
}
studentNode *studentNode::getFirst() {
	studentNode *temp = myDB->root;
	while (temp->leftChild)
		temp = temp->leftChild;
	return temp;
}
studentNode *studentNode::getPrev() {
	studentNode *prev;
	if (!parent || this == parent->leftChild) {
		// root case & left child case
		prev = leftChild;
		while (prev->rightChild)
			prev = prev->rightChild;
		return prev;
	}
	else {
		// right child case
		if (leftChild) {
			prev = leftChild;
			while (prev->rightChild)
				prev = prev->rightChild;
			return prev;
		}
		else
			return parent;
	}
}
studentNode *studentNode::getNext() {
	studentNode *next;
	if (!parent || this == parent->rightChild) {
		// root case & left child case
		next = rightChild;
		while (next->leftChild)
			next = next->leftChild;
		return next;
	}
	else {
		// right child case
		if (rightChild) {
			next = rightChild;
			while (next->leftChild)
				next = next->leftChild;
			return next;
		}
		else
			return parent;
	}
}
studentNode *studentNode::getLast() {
	studentNode *temp = myDB->root;
	while (temp->rightChild)
		temp = temp->rightChild;
	return temp;
}

string studentNode::getLastBefore(string key) {
	studentNode *temp = myDB->root;
	while (!false) {
		while (key > temp->getName()) {
			if (temp->rightChild)
				temp = temp->rightChild;
			else
				return temp->getName();
		}
		while (key < temp->getName()) {
			if (temp->leftChild)
				temp = temp->leftChild;
			else
				return "";
		}
	}
}
string studentNode::getFirstAfter(string key) {
	studentNode *temp = myDB->root;
	while (!false) {
		while (key > temp->getName()) {
			if (temp->rightChild)
				temp = temp->rightChild;
			else
				return "";
		}
		while (key < temp->getName()) {
			if (temp->leftChild)
				temp = temp->leftChild;
			else
				return temp->getName();
		}
	}
}

// AVL Specific
void studentNode::rotateRight(studentNode *pNode, studentNode *gpNode) {
	studentNode *pNodeRC = pNode->rightChild;
	pNode->rightChild = gpNode;
	studentNode *gpNodeP = gpNode->parent;
	gpNode->parent = pNode;
	pNode->parent = gpNodeP;
	gpNode->leftChild = pNodeRC;
	if (pNodeRC)
		pNodeRC->parent = gpNode;
	if (gpNodeP) {
		if (gpNode == gpNodeP->leftChild)
			gpNodeP->leftChild = pNode;
		else
			gpNodeP->rightChild = pNode;
	}
	gpNodeP = nullptr;
	pNodeRC = nullptr;
	pNode->height = maxHeight(pNode->leftChild);
	gpNode->height = maxHeight(pNode->leftChild);
}
void studentNode::rotateLeft(studentNode *pNode, studentNode *gpNode) {
	studentNode *pNodeLC = pNode->leftChild;
	pNode->leftChild = gpNode;
	studentNode *gpNodeP = gpNode->parent;
	gpNode->parent = pNode;
	pNode->parent = gpNodeP;
	gpNode->rightChild = pNodeLC;
	if (pNodeLC)
		pNodeLC->parent = gpNode;
	if (gpNodeP) {
		if (gpNode == gpNodeP->leftChild)
			gpNodeP->leftChild = pNode;
		else
			gpNodeP->rightChild = pNode;
	}
	else {
		myDB->root = pNode;
	}
	gpNodeP = nullptr;
	pNodeLC = nullptr;
	pNode->height = maxHeight(pNode->rightChild);
	gpNode->height = maxHeight(pNode->rightChild);
}
void studentNode::rotateRL(studentNode *cNode, studentNode *pNode, studentNode *gpNode) {
	rotateRight(pNode, cNode);
	rotateLeft(gpNode, cNode);
}
void studentNode::rotateLR(studentNode *cNode, studentNode *pNode, studentNode *gpNode) {
	rotateLeft(pNode, cNode);
	rotateRight(gpNode, cNode);
}
int studentNode::maxHeight(studentNode *aNode) { // adjust heights
	if (!aNode)
		return 1;
	else {
		int leftHeight = maxHeight(aNode->leftChild);
		int rightHeight = maxHeight(aNode->rightChild);
		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else {
			return rightHeight + 1;
		}
	}
}