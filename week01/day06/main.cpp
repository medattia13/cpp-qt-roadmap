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
    car-> color="Turquoise";

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

    if (auto temp = wp.lock()) {
        std::cout << temp->color << std::endl;}
    auto sp = std::make_shared<int>(200);

    std::weak_ptr<int> wp2 = sp;

    if (auto temp = wp2.lock()) { //Accessing a weak_ptr You must convert it to a shared_ptr first using lock().
        std::cout << *temp << std::endl;
    }
    return 0;
}

