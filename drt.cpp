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

DRT::~DRT() {
    data = "";
    next = "";
    prev = "";
}

bool DRT::search(string key) {
    if (key == "" && !myDB->search(key)) { // key is empty and does not exist in the database
        data = "";
        if (myDB->isEmpty()) {
            next = "";
            prev = "";
        }
        else {
            next = myDB->getFirst();
            prev = myDB->getLast();
        }
        return true;
    }
    else if (!myDB->search(key)) { // key does not exist in the database
        data = "";
        if (myDB->isEmpty()) {
            next = "";
            prev = "";
        }
        else {
            next = myDB->findFirstAfter(key);
            prev = myDB->findLastBefore(key);
        }
        return true;
    }
    else { // key exists in the database
        data = key;
        next = myDB->getNext(key);
        prev = myDB->getPrev(key);
        return true;
    }
    return false;
}

DRT* DRT::modify(string key, string data) {
    if (key != "" && !myDB->search(key) && data != "") {
        myDB->addLeaf(key, data);
        return this;
    }
    else if (key != "" && myDB->search(key) && data == "") {
        myDB->remove(key);
        return this;
    }
    else if (key != "" && myDB->search(key) && data != "") {
        myDB->modify(key, data);
        return this;
    }
    else {
        return nullptr;
    }
}

