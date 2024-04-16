#include "sdb.h"
#include <string>
using namespace std;

// constructor
SDB::SDB()
{
	root = nullptr;
	myDRT = new DRT(this);
}

// destructor
SDB::~SDB()
{
	delete root;
	root = nullptr;
	delete myDRT;
	myDRT = nullptr;
}

// print
void SDB::print()
{
	root->print();
}

// add leaf
void SDB::addLeaf(string newName, string newGrade)
{
	if (!root)
		root = new studentNode(newName, newGrade, this);
	else
		root->addLeaf(newName, newGrade, this);
}

// search
bool SDB::oldSearch(string searchValue)
{
	if (!root)
		return false;
	return (root->search(searchValue) != nullptr);
}

// remove
bool SDB::remove(string valueToRemove)
{
	studentNode *temp = privateSearch(valueToRemove);
	if (!temp)
		return false;

	temp->remove(root);
	return true;
}

// private version of search
studentNode *SDB::privateSearch(string searchValue)
{
	if (!root)
		return nullptr;
	return root->search(searchValue);
}

// facy form of print
void SDB::display()
{
	root->display(root, 0);
}

bool SDB::isEmpty()
{
	return !root;
}

string SDB::getFirst()
{
	DRT* tempDRT = search("");
	string ans = myDRT->getNext();
	myDRT = tempDRT;
	return ans;
}
string SDB::getNext(string key)
{
	return myDRT->getNext();
}
string SDB::getPrev(string key)
{
	return myDRT->getPrev();
}
string SDB::getLast()
{
	DRT *tempDRT = search("");
	string ans = myDRT->getPrev();
	myDRT = tempDRT;
	return ans;
}
string findFirstAfter(string key) {

}
string findLastBefore(string key) {
	
}
bool SDB::editNode(string key, string data)
{
	if (root->search(key))
	{
		root->modify(key, data);
		return true;
	}
	else
	{
		return false;
	}
}

// search database for key
DRT* SDB::search(string key)
{
	DRT *tempDRT = myDRT;
	myDRT = new DRT(this);
	myDRT->search(key);
	return tempDRT;
}

DRT *SDB::modify(string key, string data)
{
	// 	At all times, modify returns the DRT that search would have returned
	// JUST PRIOR to the modification made by modify. Discussed below are
	// the modifications made by modify.
	DRT *tempDRT = myDRT;
	DRT *myDRT = new DRT(this);

	// if key is "", do nothing.
	if (key == "")
		return tempDRT;

	// if key is not "" but not present in the database and data is "", do
	// nothing.
	if (search(key)->getData() == "" && data == "") {
		return tempDRT;
	}

	// if key is not "" but not present in the database and data is not "",
	// add <key,data> to the database.
	else if (search(key)->getData() == "" && data != "") {
		addLeaf(key, data);
		return tempDRT;
	}
	// if key is present in the database and data is "", remove key from the
	// database.
	else if (search(key)->getData() != "" && data == "") {
		studentNode *toRemove = privateSearch(key);
		toRemove->remove(root);
		return tempDRT;
	}
	// if key is present in the database and data is not "", replace the data
	// associated with key with the new data.
	else if (search(key)->getData() != "" && data != "") {
		editNode(key, data);
		return tempDRT;
	}
	return tempDRT;
}