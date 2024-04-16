#include <iostream>
#include <string>
#include "drt.h"
using namespace std;

void getParts(string command, string &action, string &key, string &data)
{
    // get action
    int delimOne = 0;
    int delimTwo = 0;
    for (int i = 0; i < command.size(); i++)
    {
        if (command[i] == ' ')
        {
            delimOne = i;
            break;
        }
    }
    bool nameSpace = false;
    for (int i = delimOne + 1; i < command.size(); i++)
    {
        if (command[i] == ' ')
        {
            if (nameSpace)
            {
                delimTwo = i;
                break;
            }
            nameSpace = true;
        }
    }
    if (delimOne == 0)
    {
        action = command;
    }
    else
    {
        action = command.substr(0, delimOne);
        key = command.substr(delimOne + 1, delimTwo - delimOne - 1);
        data = command.substr(delimTwo + 1, command.size() - delimTwo - 1);
    }
}

void print(SDB *myDB) {
    myDB->search("");
}

int main(int argc, char const *argv[])
{
    cout << "Welcome to the student database. Your command options are as follows:\n"
         << "ADD <student name> <grade>\n"
         << endl;

    SDB *myDB = new SDB();
    while (true)
    {
        cout << "Enter a command" << endl;
        std::string command;
        std::string action;
        std::string name;
        std::string grade;
        getline(cin, command);

        getParts(command, action, name, grade);

        // ADD "Student Name" "Student Grade"
        // The Student Name is just what it sounds like: last name then comma then space then first
        // name, for example "Einstein, Albert". The grade is a course grade like "B+".
        if (action == "ADD")
        {
            if (myDB->modify(name, grade))
            {
                cout << "Successfully added " + name + " to the database" << endl;
            }
            else
            {
                cout << "Failed to add " + name + " to the database" << endl;
            }
        }

        // PRINT
        // This will print all student names and grades, in alphabetical order.
        if (action == "PRINT")
            print(myDB);

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
    }
    delete myDB;
    return 0;
}