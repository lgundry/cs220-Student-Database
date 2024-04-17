#pragma once
#include "SDB.H"
#include <iostream>
#include <string>
using namespace std;

class SDB;

class studentNode {
private:
	studentNode* parent;
	studentNode* leftChild;
	studentNode* rightChild;
	string name, grade;
	int height;
	SDB *myDB;
	void changeParent(studentNode* newParent);
	void changeLeftChild(studentNode* newLeftChild);
	void changeRightChild(studentNode* newRightChild);
public:
	studentNode();
	studentNode(string newName, string newGrade, SDB* aDB);
	~studentNode();
	void addLeaf(string newName, string newGrade, SDB* aDB);
	void remove(studentNode* &root);
	studentNode* search(string key);
	void print();
	void display(studentNode* aNode, int positionNumber);
	string getName();
	string getGrade();
	studentNode *getFirst();
	studentNode *getPrev();
	studentNode *getNext();
	studentNode *getLast();
	string getLastBefore(string key);
	string getFirstAfter(string key); 

	// AVL Specific
	void rotateRight(studentNode *pNode, studentNode *gpNode);
	void rotateLeft(studentNode *pNode, studentNode *gpNode);
	void rotateRL(studentNode *cNode, studentNode *pNode, studentNode *gpNode);
	void rotateLR(studentNode *cNode, studentNode *pNode, studentNode *gpNode);
	int maxHeight(studentNode *aNode);
};