#include "DRT.h"
using namespace std;

DRT::DRT() {

}
DRT::DRT(string newData, string newNext, string newPrev) {
    data = newData;
    next = newNext;
    prev = newPrev;
}
DRT::~DRT() {

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