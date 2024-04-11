#pragma once
#include <iostream>

using namespace std;

class treeNode {
private:
	int value;
	int height;
	treeNode* parent;
	treeNode* leftChild;
	treeNode* rightChild;
	void changeParent(treeNode* newParent);
	void changeLeftChild(treeNode* newLeftChild);
	void changeRightChild(treeNode* newRightChild);
	void rotateRight(treeNode* pNode, treeNode* cNode);
	void rotateLeft(treeNode* pNode, treeNode* cNode);
	void rotateLR(treeNode* pNode, treeNode* cNode);
	void rotateRL(treeNode* pNode, treeNode* cNode);
public:
	void addLeaf(int leafValue);
	void print();
	treeNode* search(int searchValue);
	void remove(treeNode* &root);
	treeNode();
	treeNode(int initialValue);
	void display(treeNode* aNode, int positionNumber);
	~treeNode();
};