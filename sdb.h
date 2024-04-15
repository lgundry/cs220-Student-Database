#pragma once
#include "studentNode.h"
#include <string>

class studentNode;

class SDB {
private:
	friend class studentNode;
	friend class DRT;

	studentNode* root;

	studentNode* privateSearch(string searchValue);

public:
	SDB();
	~SDB();
	void display();
	void addLeaf(string newName, string newGrade);
	void print();
	bool search(string searchValue);
	bool remove(string valueToRemove);
	bool isEmpty();
	string getFirst();
	string getNext(string key);
	string getPrev(string key);
	string getLast();
	string findLastBefore(string key);
	string findFirstAfter(string key);
};