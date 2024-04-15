#pragma once
#include "sdb.h"
#include <iostream>

using namespace std;

class SDB;

class studentNode {
private:

	string name, grade;
	int height;
	studentNode* parent;
	studentNode* leftChild;
	studentNode* rightChild;
	SDB* myDB;

	void changeParent(studentNode* newParent);
	void changeLeftChild(studentNode* newLeftChild);
	void changeRightChild(studentNode* newRightChild);
	int maxHeight(studentNode* aNode);
	void rotateRight(studentNode* pNode, studentNode* gpNode);
	void rotateLeft(studentNode* pNode, studentNode* gpNode);
	void rotateLR(studentNode* pNode, studentNode* gpNode);
	void rotateRL(studentNode* pNode, studentNode* gpNode);

public:
	void addLeaf(string newName, string newGrade, SDB* aDB);
	void print();
	studentNode* search(string searchValue);
	void remove(studentNode* &root);
	studentNode();
	studentNode(string newName, string newGrade, SDB* aDB);
	void display(studentNode* aNode, int positionNumber);
	~studentNode();
	string getName();
	string getGrade();
	studentNode* getFirst();
	studentNode* getNext();
	studentNode* getPrev();
	studentNode* getLast();	
	studentNode* findFirstAfter(string key);
	studentNode* findLastBefore(string key);
};