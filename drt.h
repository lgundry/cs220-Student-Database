#pragma once
#include <iostream>
#include <string>
using namespace std;

class DRT {
private:
    string data, next, prev;
public:
    DRT();
    DRT(string newData, string newNext, string newPrev);
    ~DRT();
    string getData();
    string getNext();
    string getPrev();
};