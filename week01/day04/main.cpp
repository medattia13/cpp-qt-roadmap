#include <iostream>
#include "Student.hpp"

int main()
{
    Student s1("Alice");
    Student s2 = s1;   // Calls the copy constructor

    std::cout << s2.name << std::endl;
    Buffer b1(10);

    Buffer b2 = std::move(b1);
        String s1("Hello");
        // Copy constructor
        String s2 = s1;
        // Copy assignment
        String s3;
        s3 = s1;
        // Move constructor
        String s4 = std::move(s1);
        // Move assignment
        String s5;
        s5 = std::move(s2);
        std::cout << "\nObjects:\n";
        s3.print();
        s4.print();
        s5.print();
        std::cout << "\nMoved-from objects:\n";
        s1.print();
        s2.print();
        return 0;
}
