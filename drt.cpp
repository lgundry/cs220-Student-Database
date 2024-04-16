#include "drt.h"
#include <iostream>
#include <string>
using namespace std;

DRT::DRT(SDB* aDB) {
    myDB = aDB;
    data = "";
    next = "";
    prev = "";
}

// make a drt copy
DRT::DRT(DRT *aDRT) {
    myDB = aDRT->myDB;
    data = aDRT->data;
    next = aDRT->next;
    prev = aDRT->prev;
}

DRT::~DRT() {
    data = "";
    next = "";
    prev = "";
}

void DRT::search(string key) {
    if (key == "" && !myDB->oldSearch(key)) { // key is empty and does not exist in the database
        data = "";
        if (myDB->isEmpty()) {
            next = "";
            prev = "";
        }
        else {
            next = myDB->getFirst();
            prev = myDB->getLast();
        }
    }
    else if (!myDB->oldSearch(key)) { // key does not exist in the database
        data = "";
        if (myDB->isEmpty()) {
            next = "";
            prev = "";
        }
        else {
            next = myDB->findFirstAfter(key);
            prev = myDB->findLastBefore(key);
        }
    }
    else { // key exists in the database
        data = key;
        next = myDB->getNext(key);
        prev = myDB->getPrev(key);
    }
}
string DRT::getData() {
    return data;
}
string DRT::getNext() {
    return next;
}
string DRT::getPrev() {
    return prev;
}