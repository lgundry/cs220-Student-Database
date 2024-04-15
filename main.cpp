#include <iostream>
#include <string>
#include "drt.h"
using namespace std;
int main(int argc, char const *argv[])
{
    SDB* myDB = new SDB();
    while (true) {
        DRT* myDRT = new DRT(myDB);
        string command;
        string action;
        string name;
        string grade;
        getline(cin, command);

        int delimOne = 0;
        int delimTwo = 0;


        // get action
        for (int i = 0; i < command.size(); i++) {
            if (command[i] == ' ') {
                delimOne = i;
                break;
            }
        }
        for (int i = delimOne; i < command.size(); i++) {
            bool nameSpace = false;
            if (command[i] == ' ') {
                if (nameSpace) {
                    delimTwo = i;
                    break;
                }
                nameSpace = true;
            }
        }

        action = command.substr(0, delimOne);
        name = command.substr(delimOne + 1, delimTwo - delimOne - 1);
        grade = command.substr(delimTwo + 1, command.size() - delimTwo - 1);

        // ADD "Student Name" "Student Grade"
        // The Student Name is just what it sounds like: last name then comma then space then first
        // name, for example "Einstein, Albert". The grade is a course grade like "B+".
        if (action == "ADD") {
            myDB->addLeaf(name, grade);
        }

        // PRINT
        // This will print all student names and grades, in alphabetical order.
        if (action == "PRINT") {
            myDB->print();
        }

        // RPRINT
        // This will print all student names and grades, in reverse alphabetical order.

        // REMOVE "Student Name"
        // Removes the student with the given name. If the student doesn't exist, the program prints
        // an error message.

        // LOOKUP "Student Name"
        // Prints the grade associated with that name. If that student does not exist, it prints out the
        // Students’ Names that occur before and after the requested one.

        // EXIT
        // The program terminates.
        delete myDRT;
    }
    delete myDB;
    return 0;
}