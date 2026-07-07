#include <vector>
#include <memory>
#include "MyClasses.hpp"

using namespace std;

void changecolor(std::unique_ptr<Car> ptr)
{
    ptr->color="Red";
}

int main() {
    const int k=44; //Using const when values should NOT change:
    int x = 5;
    int& r = x;//  Instead of copying objects. use references and no copy is made.
    int* ptr = &x;
    int* const ptr_const = &x; // a constant pointer can't be null
    const int* ptr_to_const = &k; // the pointed value is constant
    const int* const ptr_both_const = &k;// both the pointer and varable are const

    *ptr_const = 20;  //
    Person p{"Alice"};;

    std::cout << "x=" << x<<" int& r = x="<<r;
    std::cout << "\nr = 10 yields";
    r = 10;
    std::cout << "x=" << x<<" int& r = x="<<r;

    std::cout << "\nx=" << x<<" int* ptr = &x="<<ptr;
    std::cout << "\n*p = 7 yields";
    *ptr = 7;
    std::cout << "\nx=" << x<<" int* ptr = &x= "<<ptr;
    p.name = "Mohamed";  // Store a value in the name member

    p.print();         // Call the print function

    //RAII (Resource Acquisition Is Initialization
    File f("test.txt"); // use file then destructor automatically closes it
    vector<int> v1 = {1,2,3,4};

    vector<int> v2 = move(v1);

    cout << v1.size() << endl;
    cout << v2.size() << endl;

    std::unique_ptr<int> ptr_u = std::make_unique<int>(10); //A unique_ptr owns an object exclusively. When it goes out of scope, the object is automatically deleted.

    std::cout << *ptr_u << std::endl;

    std::unique_ptr<Car> car = std::make_unique<Car>();

    car->drive();
    //no need to delete unique pointer here

    std::unique_ptr<Car> car2 = std::move(car);

    if (car == nullptr)
        std::cout << "p1 is empty\n";

    car2->drive();

    auto pp = std::make_unique<Car>();

    changecolor(std::move(pp));

    if (!pp)
        std::cout << "Ownership transferred\n";
    auto s1 = std::make_shared<Car>();

    {
        auto s2 = s1;
        std::cout << s1.use_count() << std::endl;
    }

    std::cout << "One owner left\n";
        std::cout << s1.use_count() << std::endl;
    std::weak_ptr<Car> wp = s1;

    std::cout << s1.use_count() << std::endl;

 //   if (auto temp = wp.lock()) {
     //   std::cout << *temp->color << std::endl;}
    auto sp = std::make_shared<int>(200);

    std::weak_ptr<int> wp2 = sp;

    if (auto temp = wp2.lock()) { //Accessing a weak_ptr You must convert it to a shared_ptr first using lock().
        std::cout << *temp << std::endl;
    }
    return 0;
}

