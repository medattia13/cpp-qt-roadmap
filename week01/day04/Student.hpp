#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <cstring>
#include <utility>
#include <cstddef>

class String {
private:
    char* data;
    size_t length;

public:
    // Default constructor
    String();
    // Constructor from C-string
    String(const char* str);
    // Copy constructor (deep copy)
    String(const String& other);
    // Copy assignment
    String& operator=(const String& other);
    // Move constructor
    String(String&& other) noexcept;
    // Move assignment
    String& operator=(String&& other) noexcept;
    // Destructor
    ~String();
    // Member functions
    void print() const;
    std::size_t size() const;};

class Student {
public:
    std::String name;

    Student(std::String n);
    Student(const Student& other); //copy constructor
};

class Buffer {
    int* data;
public:
    Buffer(int value);
    // Move constructor
    Buffer(Buffer&& other); //Notice the && (rvalue reference).
    ~Buffer();
};

#endif
