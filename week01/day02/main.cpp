#include <iostream>
#include "math_utils.h"
int main() {
    const int k=44; //Using const when values should NOT change:
    int n,a,b,c;
    double d;
    std::cout << "Hello, future Qt developer!\n";
    std::cout << "a=" << a << "b="<< b<<"\n";

    std::cout << "Factorial of what?\n";
    std::cin >> n;
    if (n < 0) {
        std::cout << "Factorial is not defined for negative numbers.\n";
        return 1;
    }
    std::cout << factorial(n) <<"\n";
    std::cout << "a=" << a << "b="<< b<<"\n";

    std::cout << "How many Fibonacci numbers?\n";
    std::cin >> n;
    if (n < 0) {
        std::cout << "Fibonacci is not defined for negative numbers.\n";
        return 1;
    }
    fibonacci(n);
    std::cout << "a=" << a << "b="<< b<<"\n";

    std::cout << "GCD of what numbers?\n";
    std::cin >> a >> b;
    std::cout << "GCD = " << gcd(a, b) << '\n';
    std::cout << "a=" << a << "b="<< b<<"\n";

    std::cout << "LCM of what numbers?\n";
    std::cin >> a >> b;
    std::cout << "LCM = " << lcm(a, b) << '\n';
    std::cout << "a=" << a << "b="<< b<<"\n";

    std::cout << "Is prime of what?\n";
    std::cin >> a ;
    isPrime(a);
    std::cout << "a=" << a << "b="<< b<<"\n";

    normalize(a,b); //References are best shown with functions that change values
    std::cout << "a=" << a << "b="<< b<<"\n";

    std::cout << "Factorial of what?\n";
    std::cin >> d;
    if (n < 0) {
        std::cout << "Factorial is not defined for negative numbers.\n";
        return 1;
    }
    std::cout << factorial(d) <<"\n"; //You can reuse the SAME function name with different inputs.


    std::cout << "GCD of three numbers?\n";
    std::cin >> a >> b>> c;
    std::cout << "GCD = " << gcd(a, c) << '\n';

    return 0;
}

