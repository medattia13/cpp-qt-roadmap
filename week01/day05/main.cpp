#include <iostream>
#include <cstring>
#include <utility>

/*
implement a simple String class that manages a char* buffer and correctly implements all five special member functions. It's a classic exercise that ties all of these concepts together.

*/
class String {
private:
    char* data;
    size_t length;

public:
    // Default constructor
    String()
        : data(nullptr), length(0) {}

    // Constructor from C-string
    String(const char* str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }

    // Copy constructor (deep copy)
    String(const String& other) {
        length = other.length;

        if (other.data) {
            data = new char[length + 1];
            std::strcpy(data, other.data);
        } else {
            data = nullptr;
        }

        std::cout << "Copy constructor\n";
    }

    // Copy assignment
    String& operator=(const String& other) {

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
    String(String&& other) noexcept
        : data(other.data), length(other.length) {

        other.data = nullptr;
        other.length = 0;

        std::cout << "Move constructor\n";
    }

    // Move assignment
    String& operator=(String&& other) noexcept {

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
    ~String() {
        delete[] data;
    }

    void print() const {
        if (data)
            std::cout << data << '\n';
        else
            std::cout << "(empty)\n";
    }

    size_t size() const {
        return length;
    }
};

int main() {

    String s1("Hello"); //constructor Allocates memory and copies the characters.

    // Copy constructor Creates a new buffer and copies the contents.
    String s2 = s1; // There are now two independent buffers, so destroying one object doesn't affect the other.

    // Copy assignment Steps:

   /*1.Check for self-assignment.
     2.Free old memory.
     3.Allocate new memory.
     4.Copy characters.
   Without the self-assignment check, this would fail: s1=s1 because you'd delete the data before trying to copy it.*/
    String s3;
    s3 = s1;

    // Move constructor No copying happens. Ownership of the buffer is transferred to s4. and s1 gets nullptr
    String s4 = std::move(s1);

    // Move assignment Steps:
    /* 1.Delete s5's current buffer.
       2.Take s2's pointer.
       3.Set s2.data = nullptr.
    Again, no character copying occurs.
    */
    String s5;
    s5 = std::move(s2);

    std::cout << "\nObjects:\n";

    s3.print();
    s4.print();
    s5.print();

    std::cout << "\nMoved-from objects:\n";

    s1.print();
    s2.print();
    //Frees the owned memory. It's safe even if data is nullptr, so moved-from objects can be destroyed without problems.
    // Destructor automatically called by th compiler
    //s2.~String();
    //s1.~String();
}
