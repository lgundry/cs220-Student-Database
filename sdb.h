#pragma once
#include "studentNode.h"
#include "drt.h"
#include <string>

using namespace std;

class studentNode;
class DRT;

class SDB {
private:
	friend class studentNode;

	studentNode* root;
	DRT *myDRT;

	studentNode* privateSearch(string searchValue);

public:
	SDB();
	~SDB();
	void display();
	void addLeaf(string newName, string newGrade);
	void print();
	bool editNode(string key, string data);
	bool oldSearch(string searchValue);
	bool remove(string valueToRemove);
	bool isEmpty();
	string getFirst();
	string getNext(string key);
	string getPrev(string key);
	string getLast();
	string findLastBefore(string key);
	string findFirstAfter(string key);
	DRT* search(string key);
	DRT *modify(string key, string data);
};