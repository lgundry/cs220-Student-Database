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
    if (key == "") {
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
    }
    else {
        data = myDB->privateSearch(key)->getName();
        next = myDB->getNext(key);
        prev = myDB->getPrev(key);
    }
}

bool DRT::modify(string key, string data) {
    return true;
}

