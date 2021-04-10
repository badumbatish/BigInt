#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <string_view>
#include <inttypes.h>

// BASE OF BigInt = 2^32
class BigInt
{
private:
    bool sign=1;
    std::vector<uint32_t> v;
    
public:
    BigInt(); // default constructor
    BigInt(BigInt const &); 
    BigInt(BigInt&&); 
    BigInt(std::string const & b, bool sign=1,int base=10); //  constructor#2 for string 
    BigInt(uint32_t n, bool sign=1);
    BigInt(std::vector<uint32_t>&&, bool sign=1);

    BigInt& operator=(BigInt const  &); //copy assignment operator 
    BigInt& operator=(BigInt &&); // move assignment operator
    inline BigInt& minus()
    {
        this->sign=0;
        return *this;
    }
    inline BigInt& plus()
    {
        this->sign=1;
        return *this;
    }
   

    BigInt& add(BigInt const &  b);
    BigInt& subtract(BigInt const &  b);
    BigInt& long_mul(BigInt const & b);
    //BigInt& operator=(BigInt &&);
    ~BigInt();
    void print();
    size_t size() const;
    bool IsPos();
    bool IsNeg();
    bool IsSign(BigInt const & b,int c,int d) const {
        return (this->sign==c && b.sign==d);
    }
    
    uint32_t operator[](size_t) const;

    BigInt operator +(BigInt const & b);
    BigInt operator -(BigInt const & b);
    BigInt operator *(BigInt& b) ;
    bool   operator ==(BigInt const & b) const ;
    
    BigInt& add(uint32_t n);
    BigInt& subtract(uint32_t n);
    BigInt& mult(uint32_t n);

    BigInt& operator *=(uint32_t n);
    BigInt& operator +=(uint32_t n);
    BigInt& operator -=(uint32_t n);
    
    bool operator >(int64_t n);
    bool operator >=(int64_t n);
    bool operator <(int64_t n);
    bool operator <=(int64_t n);
    bool operator ==(int64_t n);

    int ab_comp(BigInt const & b) const;
    bool operator >=(BigInt const & b);
    bool operator >(const BigInt& b);
    bool operator <(const BigInt& b);
    bool operator <=(const BigInt& b);

    BigInt& operator +=(BigInt const & b);
    BigInt& operator -=(BigInt const & b);
    BigInt& operator *=(BigInt& b);
    BigInt& operator /=(BigInt& b);

    friend std::ostream& operator<<(std::ostream&, const BigInt&);
};
