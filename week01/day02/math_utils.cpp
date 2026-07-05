#include "math_utils.h"
#include <iostream>

int factorial(int n) {
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

void isPrime(int a){
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
