#include <iostream>
#include "BigInt.h"
#include <chrono>
int main()
{
    
    
    /*
     * std::string b="012345";
    int start=2;
    int end=4;
    auto it=b.begin()+start;
    auto it_end=b.begin()+end+1;
    for(;it!=it_end;++it)
    {
        std::cout << *it << " ";
    }
     * 
     */
    BigInt a("9909");
    BigInt b("998");

    
    std::cout << a*b << std::endl;
    return 0;
}