#include <iostream>
#include <chrono>
#include "BigInt.h"

int main()
{
    BigInt a("19",1);
    BigInt b("91",-1);
    BigInt c = a+b;
    std::cout << c << std::endl;
    return 0;
}
