#include "SDB.h"

SDB::SDB()
{
	root = nullptr;
	myDRT = new DRT();
}

SDB::~SDB()
{
	delete root;
	root = nullptr;
	delete myDRT;
	myDRT = nullptr;
}

void SDB::print()
{
	root->print();
}
void SDB::addLeaf(string newName, string newGrade, SDB *aDB)
{
	if (!root)
		root = new studentNode(newName, newGrade, aDB);
	else
		root->addLeaf(newName, newGrade, aDB);
}
bool SDB::remove(string valueToRemove)
{
	if (search(valueToRemove)->getData() != ""){
		root->remove(valueToRemove);
		return true;
	}
	return false;
}
studentNode *SDB::privateSearch(string searchValue)
{
	if (!root)
		return nullptr;
	return root->search(searchValue);
}
void SDB::display()
{
	root->display(root, 0);
}
string SDB::getFirst(){
	studentNode *temp = root->getFirst();
	return temp->getName();
}
string SDB::getLast() {
	studentNode *temp = root->getLast();
	return temp->getName();
}

string SDB::getLastBefore(string key) {
	return root->getLastBefore(key);
}
string SDB::getFirstAfter(string key) {
	return root->getFirstAfter(key);
}

DRT *SDB::search(string key)
{
	if (!root) return new DRT();
	string data = "", next = "", prev = "";
	// if key is "", then set the following fields in the Data Retrieval Tool (DRT):
	// data = ""
	// next = the first key in the database (or "" if empty)
	// prev = the last key in the database (or "" if empty)
	if (key == "") {
		data = "";
		next = getFirst();
		prev = getLast();
	}

	// if key is not "" but is not present in the database:
	// data = ""
	// next = the first key in the database following key (or "")
	// prev = the last key in the database preceding key (or "")
	else if (!root->search(key)) {
		data = "";
		next = getFirstAfter(key);
		prev = getLastBefore(key);
	}

	// if key is present in the database:
	// data = the data corresponding to key
	// next = the first key in the database following key (or "")
	// prev = the last key in the database preceding key (or "")
	else {
		studentNode *temp = root->search(key);
		data = temp->getGrade();
		if (temp->getNext())
			next = temp->getNext()->getName();
		else
			next = "";
		if (temp->getPrev())
			prev = temp->getPrev()->getName();
		else 
			prev = "";
	}
	myDRT = new DRT(data, next, prev);
	return myDRT;
}

DRT *SDB::modify(string key, string data)
{
	DRT *tempDRT;
	// At all times, modify returns the DRT that search would have returned
	// JUST PRIOR to the modification made by modify. Discussed below are
	// the modifications made by modify.
	
	// if key is "", do nothing.
	if (key == "")
		return myDRT;

	// if key is not "" but not present in the database and data is "", do
	// nothing.
	if (search(key)->getData() == "" && data == "")
		return myDRT;

	// if key is not "" but not present in the database and data is not "",
	// add <key,data> to the database.
	if (search(key)->getData() != key && data != "") {
		addLeaf(key, data, this);
		tempDRT = search(key);
		return tempDRT;
	}
	// if key is present in the database and data is "", remove key from the
	// database.
	if (data == "") {
		remove(key);
		tempDRT = search(key);
		return tempDRT;
	}

	// if key is present in the database and data is not "", replace the data
	// associated with key with the new data.
	if (data != "") {
		addLeaf(key, data, this);
		return myDRT;
	}
	return myDRT;
}
