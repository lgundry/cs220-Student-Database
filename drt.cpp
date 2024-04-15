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
    if (key == "" && !myDB->search(key)) {
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
    else if (!myDB->search(key)) {
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
    else {
        data = myDB->privateSearch(key)->getName();
        next = myDB->getNext(key);
        prev = myDB->getPrev(key);
        return true;
    }
    return false;
}

bool DRT::modify(string key, string data) {
    return true;
}

