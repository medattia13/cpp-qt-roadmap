#include "MyClasses.hpp"
#include <iostream>
using namespace std;

//Person::Person(string n) : name(n) {} //using a member initializer list (the preferred style
    //The initializer list constructs name directly with "Alice" instead of constructing it first as an empty string and then assigning to it.
        //This is generally more efficient and is the idiomatic C++ approach.
void Person::print() const
    {//the const after the function means This function promises not to modify the object.
            //A non-const member function cannot be called on a const object because it might modify the object.
        std::cout << name<< endl;
    }

File::File(const char* name)
    {
        file = fopen(name, "r");
    }

File::~File()
    {
        if (file)
             fclose(file);
    }

void Car::drive() {
    std::cout << "Driving...\n";
    }
