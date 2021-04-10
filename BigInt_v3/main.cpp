#include <iostream>
#include <chrono>
#include <vector>
#include "BigInt.h"

int main()
{
    BigInt a("17",1);
    std::cout << a << std::endl;
    BigInt b("9",0);
    std::cout << b << std::endl;
    std::cout << a-b << std::endl;
    return 0;
}