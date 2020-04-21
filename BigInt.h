#pragma once
#include <string>

class BigInt
{
private:
    std::string str;
    int sign;

    // Subroutine for addition
    BigInt add(const BigInt& a,const BigInt& b) const;
   
    inline BigInt& minus()
    {
        this->sign=-1;
        return *this;
    }
    inline BigInt& plus()
    {
        this->sign=1;
        return *this;
    }
    BigInt subtract(const BigInt &a, const BigInt &b) const;
    
    BigInt multiply(BigInt&, BigInt&, int start1, int end1, int start2, int end2);
    BigInt multiply_wrapper( BigInt &,  BigInt &);
    
    void reLength(BigInt &a, BigInt &b);
public:
    BigInt(); // default constructor
    BigInt(const BigInt&);
    BigInt(BigInt&&);
    BigInt(std::string&,int i=1,int keepOldString=1); //  constructor#2
    BigInt(std::string&&, int i=1); // constructor#3 
    BigInt(const std::string&, int i=1); // constructor #4
    BigInt& operator=(const BigInt &); //copy assignment operator
    BigInt& operator=(BigInt &&); // move assignment operator
    BigInt(BigInt &,int keepOldString=1); //  move or copy

    //BigInt& operator=(BigInt &&);
    ~BigInt();
    void print();
    int length() const;
    bool IsPos();
    bool IsNeg();
    bool IsSign(const BigInt&,const BigInt&, int,int) const;
    
    int operator[](int64_t) const;
    int ab_comp(const BigInt&,const BigInt&, int , int, int, int) const;
    
    // Subroutine for multiplication
    BigInt por_add(const BigInt& a,const BigInt& b, int start1, int end1, int start2, int end2) const;
    BigInt por_sub(const BigInt& a,const BigInt& b, int start1, int end1, int start2, int end2) const;
    BigInt add2(const BigInt& a,const BigInt& b, int start1, int end1, int start2, int end2) const;
    BigInt subtract2(const BigInt &a, const BigInt &b, int start1, int end1, int start2, int end2) const;
    
    BigInt operator +(const BigInt& b) const;
    BigInt operator -(const BigInt&) const;
    BigInt operator *(BigInt& b) ;
    bool   operator ==(const BigInt& b) const;
    
    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    BigInt IntToBigInt(int64_t t);

    
};