#pragma once
#include <string>
#include <algorithm>
#include <vector>
class BigInt
{
private:

    int sign;
    std::string str;
    // Subroutine for multiplication
    BigInt por_add(const BigInt& a,const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2);
    BigInt por_sub(const BigInt& a,const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2);
    
    // Subroutine for por_add and por_sub
    BigInt add2(const BigInt& a,const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2) const;
    BigInt subtract2(const BigInt &a, const BigInt &b, int64_t start1, int64_t end1, int64_t start2, int64_t end2) const;
    
    // Subroutine for operator + and -
    BigInt add(const BigInt& a,const BigInt& b) const;
    BigInt subtract(const BigInt &a, const BigInt &b) const;
    
    
    BigInt multiply(BigInt const& , BigInt const& , int64_t start1, int64_t end1, int64_t start2, int64_t end2);
    BigInt multiply_wrapper( BigInt &,  BigInt &);
public:
    BigInt(); // default constructor
    BigInt(const BigInt&);
    BigInt(BigInt&&);
    BigInt(const std::string&,int i=1,bool is_reverse=1); //  constructor#2
    BigInt(std::string&&, int i=1, bool is_reverse=1); // constructor#3 
    BigInt& operator=(const BigInt &); //copy assignment operator
    BigInt& operator=(BigInt &&); // move assignment operator
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
   
    //BigInt& operator=(BigInt &&);
    ~BigInt();
    void print();
    int length() const;
    bool IsPos();
    bool IsNeg();
    bool IsSign(const BigInt&,const BigInt&, int,int) const;
    
    int operator[](int64_t) const;
    int ab_comp(const BigInt&, const BigInt&) const;
    int ab_comp2(const BigInt&,const BigInt&, int64_t , int64_t, int64_t, int64_t) const;
    BigInt sim_mul(BigInt const &a, BigInt const &b, int64_t start1, int64_t end1, int64_t start2, int64_t end2);



    
    BigInt por_add_wrapper(const BigInt&a, const BigInt&b)
    {
        BigInt a1=a;
        BigInt b1=b;

        BigInt c=por_add(a1,b1,0,a1.length()-1,0,b1.length()-1);

        return c;
    }
    BigInt por_sub_wrapper(const BigInt&a, const BigInt&b)
    {
        BigInt a1=a;
        BigInt b1=b;

        BigInt c=por_sub(a1,b1,0,a1.length()-1,0,b1.length()-1);
        return c;
    }
    BigInt operator +(const BigInt& b) const;
    BigInt operator -(const BigInt&) const;
    BigInt operator *(BigInt& b) ;
    bool   operator ==(const BigInt& b) const;
    
    friend std::ostream& operator<<(std::ostream&, const BigInt&);
};
