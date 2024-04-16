#pragma once
#include "sdb.h"
#include <string>
#include <iostream>
using namespace std;

class SDB;

// Data Retrieval System
class DRT {
private:
    SDB* myDB;
    string data, next, prev;

public:
    DRT(SDB* aDB);
    DRT(DRT *aDRT);
    ~DRT();
    void search(string key);
    string getData();
    string getPrev();
    string getNext();
};