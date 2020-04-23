#include <iostream>
#include "BigInt.h"
#include <chrono>
int main()
{
    BigInt a("2500");
    BigInt b("2500");
    //std::cout << BigInt::reporter(a,0,a.length());
    std::cout << a*b << std::endl;
    return 0;
}