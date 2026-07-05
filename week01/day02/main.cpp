#include <iostream>
// Function declaration
int factorial_f(int n);
void fibonacci(int n);
int gcd(int a,int b);
int lcm(int a,int b);
void prime_checking(int a);
void normalize(int &a, int &b);

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
    std::cout << factorial_f(n) <<"\n";
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
    prime_checking(a);
    std::cout << "a=" << a << "b="<< b<<"\n";

    normalize(a,b); //References are best shown with functions that change values
    std::cout << "a=" << a << "b="<< b<<"\n";

    std::cout << "Factorial of what?\n";
    std::cin >> d;
    if (n < 0) {
        std::cout << "Factorial is not defined for negative numbers.\n";
        return 1;
    }
    std::cout << factorial_f(d) <<"\n"; //You can reuse the SAME function name with different inputs.


    std::cout << "GCD of three numbers?\n";
    std::cin >> a >> b>> c;
    std::cout << "GCD = " << gcd(a, c) << '\n';

    return 0;
}
int factorial_f(int n) {
    int res=1;
    for (int i = 1; i <= n; i++) {
        res*=i;
    }
    return res;
}

void fibonacci(int n) {
    int a = 0, b = 1;

    for (int i = 0; i < n; i++) {
        std::cout << a << " ";
        int next = a + b;
        a = b;
        b = next;
    }
    std::cout << "\n";
    return;
}
int gcd(int a,int b){
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

void prime_checking(int a){
    if (a <= 1) {
        std::cout << "Not prime\n";
        return;
    }
    for (int b = 2; b * b <= a; b++) {
        if (a % b == 0) {
            std::cout << "Not prime because divisible by " << b << '\n';
            return;
        }
    }
    std::cout << "Is prime\n";
}

void normalize(int &a, int &b) {
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
}
// overloaded versions (double input)
double factorial(double n) {
    int intN = (int)n;
    return factorial(intN);
}

int gcd(int a, int b, int c) {
    return gcd(gcd(a, b), c);
}
