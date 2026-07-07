#ifndef MYCLASS_HPP
#define MYCLASS_HPP
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Person
{
public:
    string name;
    Person(string n) : name(n) {}
    void print() const {}
};
class File
{
    FILE* file;

public:
    File(const char* name){}
    ~File(){}
};

class Car {
public:
    string color;
    Car() {}
    ~Car() {}

    void drive() {}
};
#endif
