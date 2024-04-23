// Logan Gundry
#include <iostream>
#include <string>
#include "DRT.h"
#include "SDB.h"
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

// I cannot figure out for the life of me why these methods (print and rprint) don't work. I looked at my search and finder methods to no avail.
void print(SDB *myDB)
{
    DRT* temp = myDB->search("");
    if (temp->getNext() == "" && temp->getPrev() == "") {
        cout << "No students in the database" << endl;
        return;
    }
    do {
        cout << temp->getNext() << endl;
    } while ((temp = myDB->search(temp->getNext()))->getNext() != "");
}
void rprint(SDB *myDB)
{
    DRT* temp = myDB->search("");
    if (temp->getNext() == "" && temp->getPrev() == "") {
        cout << "No students in the database" << endl;
        return;
    }
    do {
        cout << temp->getPrev() << endl;
    } while ((temp = myDB->search(temp->getPrev()))->getPrev() != "");
}

int main(int argc, char const *argv[])
{
    cout << "Welcome to the student database. Your command options are as follows:\n"
         << "ADD <student name> <grade> | add a student to the database\n"
         << "REMOVE <student name> | remove a student from the database\n"
         << "LOOKUP <student name> | Look up a student's grade or check if an entry exists\n"
         << "PRINT | print all students in the database in alphabetical order\n"
         << "RPRINT | print all students in the database in reverse alphabetical order\n"
         << "EXIT | exit the program\n"
         << "HELP | display this list of commands\n"
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
        else if (action == "PRINT")
            print(myDB);

        // RPRINT
        // This will print all student names and grades, in reverse alphabetical order.
        else if (action == "RPRINT")
            rprint(myDB);

        // REMOVE "Student Name"
        // Removes the student with the given name. If the student doesn't exist, the program prints
        // an error message.
        else if (action == "REMOVE")
        {
            myDB->modify(name, "");
            if (myDB->search(name)->getData() == "")
            {
                cout << "Successfully removed " + name + " from the database" << endl;
            }
            else
            {
                cout << "Failed to remove " + name + " from the database" << endl;
            }
        }

        // LOOKUP "Student Name"
        // Prints the grade associated with that name. If that student does not exist, it prints out the
        // Students’ Names that occur before and after the requested one.
        else if (action == "LOOKUP")
        {
            DRT *tempDRT = myDB->search(name);
            if (tempDRT->getData() == "")
            {
                cout << "Student not found" << endl;
                if (tempDRT->getPrev() != "")
                    cout << "The student before " + name + " is " + tempDRT->getPrev() << endl;
                else cout << "There is no student before " + name << endl;
                if (tempDRT->getNext() != "")
                    cout << "The student after " + name + " is " + tempDRT->getNext() << endl;
                else cout << "There is no student after " + name << endl;
            }
            else
            {
                cout << "The grade for " + name + " is " + tempDRT->getData() << endl;
            }
        }

        // EXIT
        // The program terminates.
        else if (action == "EXIT")
            break;

        else if (action == "HELP") {
            cout << "Your command options are as follows:\n"
                 << "ADD <student name> <grade> | add a student to the database\n"
                 << "REMOVE <student name> | remove a student from the database\n"
                 << "LOOKUP <student name> | Look up a student's grade or check if an entry exists\n"
                 << "PRINT | print all students in the database in alphabetical order\n"
                 << "RPRINT | print all students in the database in reverse alphabetical order\n"
                 << "EXIT | exit the program\n"
                 << "HELP | display this list of commands\n"
                 << endl;
        }
        
        else
            cout << "Invalid command. Try HELP for a list of commands" << endl;
    }
    delete myDB;
    return 0;
}