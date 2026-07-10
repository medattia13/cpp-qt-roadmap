#include <vector>
#include <memory>
#include "MyClasses.hpp"

using namespace std;

void changecolor(unique_ptr<Car> ptr)
{
    ptr->color="Red";
}

int main() {
    Person p{"Alice"};;
    p.name = "Mohamed";  // Store a value in the name member
    p.print();         // Call the print function

    //RAII (Resource Acquisition Is Initialization
    File f("test.txt"); // use file then destructor automatically closes it

    std::unique_ptr<Car> car = std::make_unique<Car>();
    std::cout << "Car object is created\n";
    car-> color="Turquoise";
    std::cout << "Car color is " << car->color << std::endl;
    car->drive();
    //no need to delete unique pointer here
    std::unique_ptr<Car> car2 = std::move(car);
    if (car == nullptr)
        std::cout << "Car object is empty\n";
    car2->drive();
    auto car3 = std::make_unique<Car>();
    std::cout << "Car color is " << car3->color << std::endl;

    changecolor(std::move(car3));

    if (!car3)
        std::cout << "Ownership transferred\n";
    auto s1 = std::make_shared<Car>();

    {
        auto s2 = s1;
        std::cout << s1.use_count() << std::endl;
    }

    std::cout << "One owner left\n";
        std::cout << "Number of owners=" << s1.use_count() << std::endl;
    std::weak_ptr<Car> wp = s1;
    std::cout  << "A weak pointer wp, a child doesn't on:" << s1.use_count() << std::endl;
    std::cout  << "Number of owners=" << s1.use_count() << std::endl;

    if (auto temp = wp.lock()) {//Accessing a weak_ptr You must convert it to a shared_ptr first using lock().
        std::cout << temp->color << std::endl;}

    return 0;
}

