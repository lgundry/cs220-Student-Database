#pragma once
#include "sdb.h"
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
    ~DRT();
    bool search(string key);
    bool modify(string key, string data);
};