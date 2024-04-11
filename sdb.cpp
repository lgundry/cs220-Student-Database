#include "binaryTree.h"

// constructor
binaryTree::binaryTree() {
	root = nullptr;
}

// destructor
binaryTree::~binaryTree() {
	delete root;
	root = nullptr;
}

// print
void binaryTree::print() {
	root->print();
}

// add leaf
void binaryTree::addLeaf(int leafValue) {
	if (!root)
		root = new treeNode(leafValue);
	else
		root->addLeaf(leafValue);
}

// search
bool binaryTree::search(int searchValue) {
	if (!root)return false;
	return (root->search(searchValue)!=nullptr);
}

// remove
bool binaryTree::remove(int valueToRemove) {
	treeNode* temp = privateSearch(valueToRemove);
	if (!temp)return false;

	temp->remove(root);
	return true;
}

// private version of search
treeNode* binaryTree::privateSearch(int searchValue) {
	if (!root)return nullptr;
	return root->search(searchValue);
}

// facy form of print
void binaryTree::display() {
	root->display(root, 0);
}