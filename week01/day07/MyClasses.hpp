#ifndef MYCLASS_HPP
#define MYCLASS_HPP
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Person //class name
{
public:  // access specifier It means everything below this line can be accessed from outside the class.
    string name; //data member
    Person(string n) : name(n) {}//Constructor has the same name as the class run automatically and Initializes the object's data.
    //: name(n) is called a member initializer list It initializes the class variable name directly.
    void print() const ; //A member function acting on a const
};

class File
{
    FILE* file = nullptr; //this is private
public:
    File(const char* name);
    ~File();
};

//modern c++ rule of zero is used Since Car doesn't directly manage any resources
//(such as dynamically allocated memory, open files, or network sockets), no need to define a constructor or destructor.
class Car
{
public:
    string color = "Unknown";

    void drive();
};
#endif
