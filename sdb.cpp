#include "sdb.h"

// constructor
SDB::SDB() {
	root = nullptr;
}

// destructor
SDB::~SDB() {
	delete root;
	root = nullptr;
}

// print
void SDB::print() {
	root->print();
}

// add leaf
void SDB::addLeaf(string newName, string newGrade) {
	if (!root)
		root = new studentNode(newName, newGrade, this);
	else
		root->addLeaf(newName, newGrade, this);
}

// search
bool SDB::search(string searchValue) {
	if (!root)return false;
	return (root->search(searchValue)!=nullptr);
}

// remove
bool SDB::remove(string valueToRemove) {
	studentNode* temp = privateSearch(valueToRemove);
	if (!temp)return false;

	temp->remove(root);
	return true;
}

// private version of search
studentNode* SDB::privateSearch(string searchValue) {
	if (!root)return nullptr;
	return root->search(searchValue);
}

// facy form of print
void SDB::display() {
	root->display(root, 0);
}

bool SDB::isEmpty() {
	return !root;
}

string SDB::getFirst() {
	if (!root) return "";
	return root->getFirst()->getName();
}
string SDB::getNext(string key) {
	if (!root) return "";
	studentNode* temp = root->search(key);
	if (!temp)return "";
	return temp->getNext()->getName();
}
string SDB::getPrev(string key) {
	if (!root) return "";
	studentNode* temp = root->search(key);
	if (!temp)return "";
	return temp->getPrev()->getName();
}
string SDB::getLast() {
	if (!root) return "";
	return root->getLast()->getName();
}
string SDB::findLastBefore(string key) {
	if (!root) return "";
	studentNode* temp = root->search(key);
	if (temp) return temp->getName();
	return temp->findLastBefore(key)->getName();
}
string SDB::findFirstAfter(string key) {
	if (!root) return "";
	studentNode* temp = root->search(key);
	if (temp) return temp->getName();
	return temp->findFirstAfter(key)->getName();
}