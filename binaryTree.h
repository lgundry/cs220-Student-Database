#pragma once
#include "treeNode.h"

class binaryTree {
private:
	treeNode* root;

	treeNode* privateSearch(int searchValue);

public:
	binaryTree();
	~binaryTree();
	void display();

	void addLeaf(int leafValue);
	void print();

	bool search(int searchValue);

	bool remove(int valueToRemove);

};