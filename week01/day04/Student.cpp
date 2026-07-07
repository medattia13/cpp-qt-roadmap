#include "Student.hpp"
#include <iostream>
#include <cstring>
#include <utility>

// Default constructor
String::String()
    : data(nullptr), length(0)
{
}

// Constructor from C-string
String::String(const char* str)
{
    length = std::strlen(str);
    data = new char[length + 1];
    std::strcpy(data, str);
}

// Copy constructor
String::String(const String& other)
{
    length = other.length;

    if (other.data) {
        data = new char[length + 1];
        std::strcpy(data, other.data);
    } else {
        data = nullptr;
    }

    std::cout << "Copy constructor\n";
}

// Copy assignment operator
String& String::operator=(const String& other)
{
    if (this != &other) {

        delete[] data;

        length = other.length;

        if (other.data) {
            data = new char[length + 1];
            std::strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    std::cout << "Copy assignment\n";

    return *this;
}

// Move constructor
String::String(String&& other) noexcept
    : data(other.data), length(other.length)
{
    other.data = nullptr;
    other.length = 0;

    std::cout << "Move constructor\n";
}

// Move assignment operator
String& String::operator=(String&& other) noexcept
{
    if (this != &other) {

        delete[] data;

        data = other.data;
        length = other.length;

        other.data = nullptr;
        other.length = 0;
    }

    std::cout << "Move assignment\n";

    return *this;
}

// Destructor
String::~String()
{
    delete[] data;
}

// Print the string
void String::print() const
{
    if (data)
        std::cout << data << '\n';
    else
        std::cout << "(empty)\n";
}

// Return the string length
std::size_t String::size() const
{
    return length;
}

Student::Student(std::string n)
{
    name = n;
}

Student::Student(const Student& other)
{
    name = other.name;
    std::cout << "Copy constructor called" << std::endl;
};

Buffer:: Buffer(int value) {
    data = new int(value);
}
    // Move constructor
Buffer::Buffer(Buffer&& other)
{
    data = other.data;
    other.data = nullptr;
    std::cout << "Move constructor called\n";
}
Buffer::~Buffer() {
        delete data;
}


