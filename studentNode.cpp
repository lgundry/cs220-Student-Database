#include "studentNode.h"

// basic constructor
studentNode::studentNode() {
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	name = "";
	grade = "";
}

// constructor
studentNode::studentNode(string newName, string newGrade, SDB* aDB) {
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	
	height = 0;
}

// add leaf
void studentNode::addLeaf(string newName, string newGrade, SDB* aDB) {
	if (newName < name) {
		if (leftChild) {
			leftChild->addLeaf(newName, newGrade, aDB);
			if (leftChild->height - rightChild->height > 1) {
				if (leftChild->leftChild->height < leftChild->rightChild->height)
					rotateLR(leftChild, this);
				else
					rotateRight(leftChild, this);
			}
			else if (rightChild->height = leftChild->height > 1) {
				if (rightChild->rightChild->height < rightChild->leftChild->height)
					rotateRL(rightChild, this);
				else
					rotateLeft(rightChild, this);
			}
		}
		else {
			leftChild = new studentNode(newName, newGrade, aDB);
			leftChild->changeParent(this);
		}
	}
	else {
		if (rightChild) {
			rightChild->addLeaf(newName, newGrade, aDB);
			if (rightChild->height - leftChild->height > 1) {
				if (rightChild->rightChild->height < rightChild->leftChild->height)
					rotateRL(rightChild, this);
				else
					rotateLeft(rightChild, this);
			}
			else if (leftChild->height - rightChild->height > 1) {
				if (leftChild->leftChild->height < leftChild->rightChild->height)
					rotateLR(leftChild, this);
				else
					rotateRight(leftChild, this);
			}
		}
		else {
			rightChild = new studentNode(newName, newGrade, aDB);
			rightChild->changeParent(this);
		}
	}
}

// change parent
void studentNode::changeParent(studentNode* newParent) {
	parent = newParent;
}

// change left child
void studentNode::changeLeftChild(studentNode* newLeftChild) {
	leftChild = newLeftChild;
}

// change right child
void studentNode::changeRightChild(studentNode* newRightChild) {
	rightChild = newRightChild;
}

// print the tree - linear
void studentNode::print() {
	if (leftChild)
		leftChild->print();
	cout << name + " " + grade << " ";
	if (rightChild)
		rightChild->print();
}

// destructor
studentNode::~studentNode() {
	delete leftChild;
	leftChild = nullptr;
	delete rightChild;
	rightChild = nullptr;
	//how do i take care of my parent's child that points to me
	parent = nullptr;
}

// search the tree for searchValue
studentNode* studentNode::search(string searchValue) {
	if (name == searchValue)return this;
	if (searchValue < name) {
		if (!leftChild)return nullptr;
		return leftChild->search(searchValue);
	}
	if (!rightChild)return nullptr;
	return rightChild->search(searchValue);
}

// remove the node
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

// fancy print - displays the tree in tree form
void studentNode::display(studentNode* aNode, int positionNumber) {
	if (aNode) {
		cout << aNode->name + " " + aNode->grade<< endl;
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

int studentNode::maxHeight(studentNode* aNode) {
	if (!aNode)return 0;
	int leftHeight = maxHeight(aNode->leftChild);
	int rightHeight = maxHeight(aNode->rightChild);
	if (leftHeight > rightHeight)
		return leftHeight + 1;
	else
		return rightHeight + 1;
	return 0;
}

// rotations
void studentNode::rotateRight(studentNode* pNode, studentNode* gpNode) {
	studentNode* pNodeRC = pNode->rightChild;
	pNode->rightChild = gpNode;
	studentNode* gpNodeP = gpNode->parent;
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
	else {
		myDB->root = pNode;
	}
	pNode->height = maxHeight(pNode->leftChild);
	gpNode->height = maxHeight(gpNode->rightChild);
	gpNodeP = nullptr;
	pNodeRC = nullptr;
}
void studentNode::rotateLeft(studentNode* pNode, studentNode* gpNode) {
	studentNode* pNodeLC = pNode->leftChild;
	pNode->leftChild = gpNode;
	studentNode* gpNodeP = gpNode->parent;
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
	pNode->height = maxHeight(pNode->rightChild);
	gpNode->height = maxHeight(gpNode->leftChild);
	gpNodeP = nullptr;
	pNodeLC = nullptr;
}
void studentNode::rotateLR(studentNode* pNode, studentNode* gpNode) {
	rotateLeft(pNode, pNode->rightChild);
	rotateRight(pNode->parent, gpNode);
}
void studentNode::rotateRL(studentNode* pNode, studentNode* gpNode) {
	rotateRight(pNode, pNode->leftChild);
	rotateLeft(pNode->parent, gpNode);
}

string studentNode::getName() {
	return name;
}

string studentNode::getGrade() {
	return grade;
}

studentNode* studentNode::getFirst() {
	if (!leftChild) return this;
	return leftChild->getFirst();
}
studentNode* studentNode::getNext() {
	if (this == parent->leftChild) return parent;
	if (!rightChild) return nullptr;
	studentNode* temp = rightChild;
	while (temp->leftChild) temp = temp->leftChild;
	return temp;
}
studentNode* studentNode::getPrev() {
	if (this == parent->rightChild) return parent;
	if (!leftChild) return nullptr;
	studentNode* temp = leftChild;
	while (temp->rightChild) temp = temp->rightChild;
	return temp;
}
studentNode* studentNode::getLast() {
	if (!rightChild) return this;
	return rightChild->getLast();
}
studentNode* studentNode::findFirstAfter(string key) {
	if (key < name) {
		if (!leftChild) return this;
		return leftChild->findFirstAfter(key);
	}
	if (!rightChild) return nullptr;
	return rightChild->findFirstAfter(key);
}
studentNode* studentNode::findLastBefore(string key) {
	if (key > name) {
		if (!rightChild) return this;
		return rightChild->findLastBefore(key);
	}
	if (!leftChild) return nullptr;
	return leftChild->findLastBefore(key);
}