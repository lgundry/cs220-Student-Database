#include "studentNode.h"
using namespace std;

studentNode::studentNode()
{
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	name = "";
	grade = "";
	height = 1;
}

studentNode::studentNode(string newName, string newGrade, SDB *aDB)
{
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	name = newName;
	grade = newGrade;
	myDB = aDB;
	height = 1;
}
// TODO: Add rotations and replace data if newName == name
void studentNode::addLeaf(string newName, string newGrade, SDB *aDB)
{
	if (newName == name)
	{ // if they are the same, replace data and exit
		grade = newGrade;
		return;
	}

	if (newName < name)
	{ // unchanged
		if (leftChild)
			leftChild->addLeaf(newName, newGrade, aDB);
		else
		{
			leftChild = new studentNode(newName, newGrade, aDB);
			leftChild->changeParent(this);
		}
	}
	else
	{
		if (rightChild)
			rightChild->addLeaf(newName, newGrade, aDB);
		else
		{
			rightChild = new studentNode(newName, newGrade, aDB);
			rightChild->changeParent(this);
		}
	}

	// set heights
	height = maxHeight(this);

	// Balance the tree - using a wack algorithm I made up
	switch (chooseMove(this))
	{
	case 0: // no move
		break;
	case 1:
		rotateLeft(this->rightChild, this);
		break;
	case 2:
		rotateRight(this->leftChild, this);
		break;
	case 3:
		rotateRL(this->rightChild->leftChild, this->rightChild, this);
		break;
	case 4:
		rotateLR(this->leftChild->rightChild, this->leftChild, this);
		break;
	}
}

void studentNode::changeParent(studentNode *newParent)
{
	parent = newParent;
}
void studentNode::changeLeftChild(studentNode *newLeftChild)
{
	leftChild = newLeftChild;
}
void studentNode::changeRightChild(studentNode *newRightChild)
{
	rightChild = newRightChild;
}
void studentNode::print()
{
	if (leftChild)
		leftChild->print();
	cout << name + ": " + grade << endl;
	if (rightChild)
		rightChild->print();
}

studentNode::~studentNode()
{
	delete leftChild;
	leftChild = nullptr;
	delete rightChild;
	rightChild = nullptr;
	// how do i take care of my parent's child that points to me
	parent = nullptr;
	myDB = nullptr;
}

studentNode *studentNode::search(string key)
{

	if (name == key)
		return this;
	if (key < name)
	{
		if (!leftChild)
			return nullptr;
		return leftChild->search(key);
	}
	if (!rightChild)
		return nullptr;
	return rightChild->search(key);
}

void studentNode::remove(studentNode *&root)
{
	studentNode *nodeToRotate = nullptr;
	if (leftChild)
	{
		leftChild->parent = this->parent;
		if (rightChild)
		{
			studentNode *grandChild = leftChild->rightChild;
			leftChild->rightChild = this->rightChild;
			if (rightChild)
				rightChild->parent = leftChild;
			studentNode *temp = rightChild;
			while (temp->leftChild)
				temp = temp->leftChild;
			temp->leftChild = grandChild;
			if (grandChild)
				grandChild->parent = temp;
			temp = nullptr;
			grandChild = nullptr;
		}
		if (parent)
		{

			if (parent->rightChild == this) { // fails if root
				parent->rightChild = leftChild;
				nodeToRotate = parent->rightChild;
			}
			else {
				parent->leftChild = leftChild;
				nodeToRotate = parent->leftChild;
			}
			parent->height = maxHeight(parent);
		}
		else
		{
			root = leftChild;
			nodeToRotate = root;
			if (leftChild)
				leftChild->parent = nullptr;
			root->height = maxHeight(root);
		}
		parent = nullptr;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	else if (rightChild)
	{
		rightChild->parent = parent;
		if (parent)
		{
			if (parent->rightChild == this) {
				parent->rightChild = leftChild;
				nodeToRotate = parent->rightChild;
			}
			else {
				parent->leftChild = leftChild;
				nodeToRotate = parent->leftChild;
			}
			parent->height = maxHeight(parent);
		}
		else
		{
			root = rightChild;
			nodeToRotate = root;
			if (rightChild)
				rightChild->parent = nullptr;
			root->height = maxHeight(root);
		}
		parent = nullptr;
		rightChild = nullptr;
	}
	else
	{
		if (parent)
		{
			nodeToRotate = parent;
			if (parent->rightChild == this)
				parent->rightChild = nullptr;
			else
				parent->leftChild = nullptr;
		}
		else
			root = nullptr;
		parent = nullptr;
	}

	// Balance the tree - using a wack algorithm I made up
	switch (chooseMove(nodeToRotate))
	{
	case 0: // no move
		break;
	case 1:
		rotateLeft(nodeToRotate->rightChild, nodeToRotate);
		break;
	case 2:
		rotateRight(nodeToRotate->leftChild, nodeToRotate);
		break;
	case 3:
		rotateRL(nodeToRotate->rightChild->leftChild, nodeToRotate->rightChild, nodeToRotate);
		break;
	case 4:
		rotateLR(nodeToRotate->leftChild->rightChild, nodeToRotate->leftChild, nodeToRotate);
		break;
	}



	delete this;
}

void studentNode::display(studentNode *aNode, int positionNumber)
{
	if (aNode)
	{
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
		cout << '\b' << endl;
}

string studentNode::getName()
{
	return name;
}
string studentNode::getGrade()
{
	return grade;
}
studentNode *studentNode::getFirst()
{
	studentNode *temp = myDB->root;
	while (temp->leftChild)
		temp = temp->leftChild;
	return temp;
}
studentNode *studentNode::getPrev()
{
	studentNode *prev = nullptr;
	if (!parent || this == parent->leftChild)
	{
		// root case & left child case
		prev = leftChild;
		if (prev)
			while (prev->rightChild)
				prev = prev->rightChild;
		return prev;
	}
	else
	{
		// right child case
		if (leftChild)
		{
			prev = leftChild;
			while (prev->rightChild)
				prev = prev->rightChild;
			return prev;
		}
		else
			return parent;
	}
}
studentNode *studentNode::getNext()
{
	studentNode *next = nullptr;
	if (!parent || this == parent->rightChild)
	{
		// root case & left child case
		next = rightChild;
		if (next)
			while (next->leftChild)
				next = next->leftChild;
		return next;
	}
	else
	{
		// right child case
		if (rightChild)
		{
			next = rightChild;
			while (next->leftChild)
				next = next->leftChild;
			return next;
		}
		else
			return parent;
	}
}
studentNode *studentNode::getLast()
{
	studentNode *temp = myDB->root;
	while (temp->rightChild)
		temp = temp->rightChild;
	return temp;
}

string studentNode::getLastBefore(string key)
{
	studentNode *temp = myDB->root;
	while (!false)
	{
		while (key > temp->getName())
		{
			if (temp->rightChild)
				temp = temp->rightChild;
			else
				return temp->getName();
		}
		while (key < temp->getName())
		{
			if (temp->leftChild)
				temp = temp->leftChild;
			else
				return "";
		}
	}
}
string studentNode::getFirstAfter(string key)
{
	studentNode *temp = myDB->root;
	while (!false)
	{
		while (key > temp->getName())
		{
			if (temp->rightChild)
				temp = temp->rightChild;
			else
				return "";
		}
		while (key < temp->getName())
		{
			if (temp->leftChild)
				temp = temp->leftChild;
			else
				return temp->getName();
		}
	}
}

// AVL Specific:

// Choose a move: 0 = no move, 1 = left, 2 = right, 3 = rl, 4 = lr
int studentNode::chooseMove(studentNode *aNode)
{
	// Explaination: 00 = RL, 11 = LR, 01 = right, 10 = left
	bool leftRotate = false;  // if flipped, move contains a left rotation
	bool rightRotate = false; // if flipped, move contains a right rotation

	// check if rotation is needed - return 0 if not
	if (aNode->leftChild)
	{
		if (aNode->rightChild)
		{
			if (abs(aNode->leftChild->height - aNode->rightChild->height) <= 1)
				return 0;
		}
		else
		{
			if (aNode->leftChild->height <= 1)
				return 0;
		}
	}
	if (aNode->rightChild)
	{
		if (aNode->rightChild->height <= 1)
			return 0;
	}

	// flip bools
	studentNode *temp = aNode;
	for (int i = 0; i < 2; i++)
	{
		if (temp->leftChild)
		{
			if (temp->rightChild)
			{
				if (temp->leftChild->height - temp->rightChild->height > 1)
				{
					if (leftRotate)
						leftRotate = !leftRotate;
					else
					{
						rightRotate = true;
						temp = temp->leftChild;
					}
				}
				else
				{
					leftRotate = true;
					temp = temp->rightChild;
				}
			}
			else
			{
				if (leftRotate)
					leftRotate = !leftRotate;
				else
				{
					rightRotate = true;
					temp = temp->leftChild;
				}
			}
		}
		else
		{
			leftRotate = true;
			temp = temp->rightChild;
		}
	}
	temp = nullptr;

	// choose and return move
	if (!rightRotate && !leftRotate)
		return 3;
	else if (rightRotate && !leftRotate)
		return 2;
	else if (!rightRotate && leftRotate)
		return 1;
	else if (rightRotate && leftRotate)
		return 4;
	return 0;
}

void studentNode::rotateRight(studentNode *pNode, studentNode *gpNode)
{
	studentNode *pNodeRC = pNode->rightChild;
	pNode->rightChild = gpNode;
	studentNode *gpNodeP = gpNode->parent;
	gpNode->parent = pNode;
	pNode->parent = gpNodeP;
	gpNode->leftChild = pNodeRC;
	if (pNodeRC)
		pNodeRC->parent = gpNode;
	if (gpNodeP)
	{
		if (gpNode == gpNodeP->leftChild)
			gpNodeP->leftChild = pNode;
		else
			gpNodeP->rightChild = pNode;
	}
	else
	{
		myDB->root = pNode;
	}
	gpNodeP = nullptr;
	pNodeRC = nullptr;
	gpNode->height = maxHeight(gpNode);
	pNode->height = maxHeight(pNode);
}
void studentNode::rotateLeft(studentNode *pNode, studentNode *gpNode)
{
	studentNode *pNodeLC = pNode->leftChild;
	pNode->leftChild = gpNode;
	studentNode *gpNodeP = gpNode->parent;
	gpNode->parent = pNode;
	pNode->parent = gpNodeP;
	gpNode->rightChild = pNodeLC;
	if (pNodeLC)
		pNodeLC->parent = gpNode;
	if (gpNodeP)
	{
		if (gpNode == gpNodeP->leftChild)
			gpNodeP->leftChild = pNode;
		else
			gpNodeP->rightChild = pNode;
	}
	else
	{
		myDB->root = pNode;
	}
	gpNodeP = nullptr;
	pNodeLC = nullptr;
	gpNode->height = maxHeight(gpNode);
	pNode->height = maxHeight(pNode);
}
void studentNode::rotateRL(studentNode *cNode, studentNode *pNode, studentNode *gpNode)
{
	rotateRight(cNode, pNode);
	rotateLeft(cNode, gpNode);
}
void studentNode::rotateLR(studentNode *cNode, studentNode *pNode, studentNode *gpNode)
{
	rotateLeft(cNode, pNode);
	rotateRight(cNode, gpNode);
}
int studentNode::maxHeight(studentNode *aNode)
{ // returns the height of aNode
	if (!aNode)
		return 1;
	else
	{
		int leftHeight = 0;
		int rightHeight = 0;
		if (aNode->leftChild)
			leftHeight = aNode->leftChild->height;
		if (aNode->rightChild)
			rightHeight = aNode->rightChild->height;
		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}