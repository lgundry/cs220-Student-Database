#pragma once
#include "studentNode.h"
#include "DRT.h"

class DRT;

class SDB {
private:
	friend class studentNode;
	studentNode* root;
	DRT *myDRT;

	studentNode* privateSearch(string key);
	string getFirst();
	string getLast();
	string getLastBefore(string key);
	string getFirstAfter(string key);

public:
	SDB();
	~SDB();
	void addLeaf(string newname, string newGrade, SDB* aDB);
	void print();
	void display();
	bool remove(string valueToRemove);

	DRT* search(string key);
	DRT *modify(string key, string data);
};