#include <iostream>
#include "BigInt.h"
#include <algorithm>
#include <utility>
#include <cmath>
BigInt::BigInt() {
    str="0";
    sign=1;
}
BigInt::BigInt(std::string& str2,int i) {
    //std::cout << "Non const " << std::endl;
    str=str2;
    if(i==-1)
    {
        sign=-1;
    }
    else 
    {
        sign=1;
    }
}
BigInt::BigInt(std::string && str2, int i) {
    //std::cout << "Move constructor for strings called\n";
    str=str2;
    if(i==-1)
    {
        sign=-1;
    }
    else 
    {
        sign=1;
    }
}

BigInt::~BigInt() {
    this->str="";
    this->sign=0;
}
BigInt& BigInt::operator=(const BigInt &b) {
    //std::cout << "Deep copy assignment called" << std::endl;
    this->str=b.str;
    this->sign=b.sign;
    
    return *this;
}
BigInt& BigInt::operator=(BigInt &&b) {
    this->str=b.str;
    this->sign=b.sign;
    return *this;
}
bool BigInt::IsPos() {
    return sign==1;
}
bool BigInt::IsNeg() {
    return sign==-1;
}

BigInt::BigInt(const BigInt& b) {
    //std::cout << "Copy constructor for BigInt called\n";
    this->str=b.str;
    this->sign=b.sign;
}
BigInt::BigInt(BigInt&& b) {
    //std::cout << "Move constructor for BigInt called\n";
    this->str=b.str;
    this->sign=b.sign;
}




bool BigInt::IsSign(const BigInt& a,const BigInt& b,int c,int d) const {
    return (a.sign==c && b.sign==d);
}

void BigInt::print() {
    if(this->IsPos()) std::cout << this->str << std::endl;
    else std::cout << "-" << this->str << std::endl;
}

int BigInt::length() const {
    return str.length();
}
int BigInt::operator[](int64_t i) const {
    return str[i]-'0';
}

int BigInt::ab_comp(const BigInt& a,const BigInt& b)  const {
    int m=a.length();
    int n=b.length();
    if(m>n) return 1;
    if(m<n) return -1;
    else
    {
        auto it1=a.str.begin();
        auto it1_end=a.str.end();
        auto it2=b.str.begin();
        auto it2_end=b.str.end();
        
        for(;it1!=it1_end && it2!=it2_end;++it1,++it2)
        {
            if(*it1<*it2)
                return -1;
            else if(*it1>*it2)
                return 1;
        }
        return 0;
    }    
} 
int BigInt::ab_comp2(const BigInt& a,const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2)  const {
    int64_t m = end1-start1+1;
    int64_t n=end2-start2+1;
    if(m>n)
        return 1;
    if(m<n)
        return -1;
    else
    {
        auto it1=a.str.rbegin() + (a.length()-end1-1);
        auto it1_end=a.str.rend() - start1;
        auto it2=b.str.rbegin()+ (b.length()-end2-1);
        auto it2_end=b.str.rend() - start2;
        for(;it1!=it1_end && it2!=it2_end;++it1,++it2)
        {
            if(*it1<*it2)
            {
                return -1;
            }
            else if(*it1>*it2)
            {
                return 1;
            }
        }
        return 0;
    }
}

BigInt BigInt::add(const BigInt &a, const BigInt &b) const {
    // use 3 iterator
        // it1 and it2 --
    // it3 ++
    
    ; // get length + 1
    BigInt c(std::string(a.length()+1,'0'));    
    int res=0;
    int carry=0;
    auto it1=a.str.rbegin();
    auto it1_end=a.str.rend();

    auto it2=b.str.rbegin();
    auto it2_end=b.str.rend();
    
    auto it3=c.str.begin();    
    for(;it2!=it2_end;++it1,++it2,++it3)
    {
        res=(*it1-'0')+(*it2-'0')+carry;
        *it3=char(((res)%10)+'0');
        carry=(res)/10;
    }
    for(;it1!=it1_end;++it1,++it3)
    {
        res=(*it1-'0')+carry;
        carry=res/10;
        *it3=char(((res)%10)+'0');
    }
    *it3=char((carry)+'0');
    if(c.str[c.str.length()-1]=='0' && c.str.length()>1)
        c.str.pop_back();
    std::reverse(c.str.begin(),c.str.end());
    return c;
}

BigInt BigInt::add2(const BigInt& a,const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2) const {
    int e=(end1-start1+1)+1; // get length + 1
    BigInt c(std::string(e,'0'));
    int carry=0;
    int res=0;
    auto it1=a.str.begin() + start1;
    auto it1_end=a.str.begin() + end1 + 1;
    auto it2=b.str.begin() + start2;
    auto it2_end=b.str.begin() + end2 + 1;
    auto it3=c.str.begin();
    
    // fine until here
    for(;it2!=it2_end;++it1,++it2,++it3)
    {
        res=(*it1-'0')+(*it2-'0')+carry;
        *it3=char(((res)%10)+'0');
        carry=(res)/10;
    }
    for(;it1!=it1_end;++it1,++it3)
    {
        res=(*it1-'0')+carry;
        carry=res/10;
        *it3=char(((res)%10)+'0');
    }
    *it3=char((carry)+'0');
    //std::cout << c << std::endl;
    auto itc=c.str.rbegin();
    while(*itc++ == '0' && c.length()>1)
    {
        c.str.pop_back();
    }
    return c;
}
BigInt BigInt::subtract2(const BigInt &a, const BigInt &b,int64_t start1, int64_t end1, int64_t start2, int64_t end2) const
{
    int e=(end1-start1)+1; 
    BigInt c(std::string(e,'0'));
    int carry=0;
    int res=0;
    auto it1=a.str.begin() + start1;
    auto it1_end=a.str.begin() + end1 + 1;
    auto it2=b.str.begin() + start2;
    auto it2_end=b.str.begin() + end2 + 1;
    
    auto it3=c.str.begin();
    //auto it3_end=c.str.end();
    
    for(;it2!=it2_end;++it1,++it2,++it3)
    {
        //std::cout << *it1 << " " << *it2 << std::endl;
        res=((*it1-'0')-(*it2-'0')-carry);
        if(res<0)
        {
            res+=10;
            carry=1;
        }
        else
        {
            carry=0;
        }
        *it3=res+'0';
    }
    for(;it1!=it1_end;++it1,++it3) {
        res=(*it1-'0')-carry;
        if(res<0)
        {
            res=res+10;
            carry=1;
        }
        else
        {
            carry=0;
        }
        *it3=res+'0';
    }
    
    auto itc=c.str.rbegin();
    while(*itc++ == '0' && c.length()>1)
        c.str.pop_back();
    return c;
}
BigInt BigInt::subtract(const BigInt &a, const BigInt &b) const {
    BigInt c(std::string(a.length(),'0'));

    int res=0;
    int carry=0;
    auto it1=a.str.rbegin();
    auto it1_end=a.str.rend();

    auto it2=b.str.rbegin();
    auto it2_end=b.str.rend();
    
    auto it3=c.str.begin();
    //auto it3_end=c.str.end();
    
    
     for(;it2!=it2_end;++it1,++it2,++it3)
    {
        //std::cout << *it1 << " " << *it2 << std::endl;
        res=((*it1-'0')-(*it2-'0')-carry);
        if(res<0)
        {
            res+=10;
            carry=1;
        }
        else
        {
            carry=0;
        }
        *it3=res+'0';
    }
    for(;it1!=it1_end;++it1,++it3) {
        res=(*it1-'0')-carry;
        if(res<0)
        {
            res=res+10;
            carry=1;
        }
        else
        {
            carry=0;
        }
        *it3=res+'0';
    }

    auto itc=c.str.rbegin();
    while(*itc++ == '0' && c.length()>1)
        c.str.pop_back();
    std::reverse(c.str.begin(),c.str.end());
    return c;
}

BigInt BigInt::por_add(const BigInt& a,const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2){

    int p=ab_comp2(a,b,start1,end1,start2,end2);
    if(p==1)
    {
        if(IsSign(a,b,1,1))
            return add2(a,b,start1,end1,start2,end2);
        else if(IsSign(a,b,-1,-1))
            return add2(a,b,start1,end1,start2,end2).minus();
        else if(IsSign(a,b,1,-1))
            return subtract2(a,b,start1,end1,start2,end2);
        else if(IsSign(a,b,-1,1))
            return subtract2(a,b,start1,end1,start2,end2).minus();
    }
    if(p==-1)
    {
        if(IsSign(a,b,1,1))
            return add2(b,a,start2,end2,start1,end1);
        else if(IsSign(a,b,-1,-1))
            return add2(b,a,start2,end2,start1,end1).minus();
        else if(IsSign(a,b,1,-1))
            return subtract2(b,a,start2,end2,start1,end1).minus();
        else if(IsSign(a,b,-1,1))
            return subtract2(b,a,start2,end2,start1,end1);
    }
    if(p==0)
    {
        if(IsSign(a,b,1,-1))
        {
            return BigInt("0",1);
        }
        else if(IsSign(a,b,-1,1))
        {
            return BigInt("0",1);
        }
        else if(IsSign(a,b,1,1))
        {
            return add2(a,b,start1,end1,start2,end2);
        }
        else
        {
            return add2(a,b,start1,end1,start2,end2).minus();
        }
    }
}
BigInt BigInt::por_sub(const BigInt& a,const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2){
    int p=ab_comp2(a,b,start1,end1,start2,end2);
    if(p==1)
    {
        if(IsSign(a,b,1,1))
            return subtract2(a,b,start1,end1,start2,end2);
        else if(IsSign(a,b,-1,-1))
            return subtract2(a,b,start1,end1,start2,end2).minus();
        else if(IsSign(a,b,1,-1))
            return add2(a,b,start1,end1,start2,end2);
        else if(IsSign(a,b,-1,1))
            return add2(a,b,start1,end1,start2,end2).minus();
    }
    if(p==-1)
    {
        if(IsSign(a,b,1,1))
            return subtract2(b,a,start2,end2,start1,end1).minus();
        else if(IsSign(a,b,-1,-1))
            return subtract2(b,a,start2,end2,start1,end1);
        else if(IsSign(a,b,1,-1))
            return add2(b,a,start2,end2,start1,end1);
        else if(IsSign(a,b,-1,1))
            return add2(b,a,start2,end2,start1,end1).minus();
    }
    if(p==0)
    {
        if(IsSign(a,b,1,-1))
        {
            return add2(b,a,start2,end2,start1,end1);
        }
        if(IsSign(*this,b,-1,1))
        {
            return add2(b,a,start2,end2,start1,end1).minus();
        }
        else if(IsSign(a,b,1,1))
        {
            return BigInt("0",1);
        }
        else
        {
            return BigInt("0",1);
        }
    }
}
BigInt BigInt::multiply_wrapper(BigInt &a, BigInt &b) {
    BigInt bi1=a;
    BigInt bi2=b;
    std::reverse(bi1.str.begin(),bi1.str.end());
    std::reverse(bi2.str.begin(),bi2.str.end());
    BigInt bi3 = multiply(bi1,bi2,0,bi1.length()-1,0,bi2.length()-1);
    std::reverse(bi3.str.begin(),bi3.str.end());
    return bi3;
}

BigInt BigInt::sim_mul(BigInt& a, BigInt &b, int64_t start1, int64_t end1, int64_t start2, int64_t end2)
{
    BigInt c(std::string(end1-start1+1+end2-start2+1,'0'));    
    int res=0;
    int carry=0;
    
    auto it1=a.str.begin()+start1;
    auto it1_end=a.str.begin()+end1+1;
    auto it2=b.str.begin()+start2;
    auto it2_end=b.str.begin()+end2+1;
    
    auto it3=c.str.begin();
    auto counter=it3;
    //auto it3_end=c.str.end();
    for(;it2!=it2_end;++it2)
    {
        it3=counter;
        carry=0;
        for(it1=a.str.begin()+start1;it1!=it1_end;++it1)
        {
            res=(*it1-'0')*(*it2-'0')+carry+(*it3-'0');
            carry=(res)/10;
            *it3=char((res%10)+'0');
            ++it3;
        }
        *it3=char(((*it3-'0'+carry)%10)+'0');
        ++counter;
    }
    
    auto itc=c.str.rbegin();
    while(*itc++ == '0' && c.length()>1)
    {
        c.str.pop_back();
    }
    return c;
}
BigInt BigInt::multiply(BigInt &a, BigInt &b, int64_t start1, int64_t end1, int64_t start2, int64_t end2)
{       
    if(end1-start1+1<70 || end2-start2+1<70)
    {   
        return sim_mul(a,b,start1,end1,start2,end2);
    }
    int64_t m1=end1+start1;
    int64_t m2=end2+start2;
    m1=std::ceil(m1*1.0/2);
    m2=std::ceil(m2*1.0/2);
    m1=std::min(m1,m2);
    BigInt lh1=por_add(a,a,start1,m1-1,m1,end1);
    BigInt lh2=por_add(b,b,start2,m1-1,m1,end2);
    BigInt z1=multiply(lh1,lh2,0,lh1.length()-1,0,lh2.length()-1); // (low1+high1)*(low2+high2)
    
    BigInt z2=multiply(a,b,m1,end1,m1,end2); // high
    
    BigInt z0=multiply(a,b,start1,m1-1,start2,m1-1); // low
    
    BigInt z20=por_add(z2,z0,0,z2.length()-1,0,z0.length()-1);
    z1=por_sub(z1,z20,0,z1.length()-1,0,z20.length()-1);
    int64_t m3=std::min(end1-start1,end2-start2);
    m3= std::ceil(m3*1.0/2);
    z2.str.reserve(m3*2+z2.str.length());
    z2.str=std::string(m3*2,'0')+z2.str;
    z1.str.reserve(m3+z1.length()+z0.length()+1);
    z1.str=std::string(m3,'0')+z1.str;
    z1 = por_add(z1,z0,0,z1.length()-1,0,z0.length()-1);
    return por_add(z2,z1,0,z2.length()-1,0,z1.length()-1);
}

BigInt BigInt::operator +(const BigInt& b) const  {

    int p=ab_comp(*this,b);
    if(p==1)
    {
        if(IsSign(*this,b,1,1))
            return add(*this,b);
        else if(IsSign(*this,b,-1,-1))
            return add(*this,b).minus();
        else if(IsSign(*this,b,1,-1))
            return subtract(*this,b);
        else if(IsSign(*this,b,-1,1))
            return subtract(*this,b).minus();
    }
    if(p==-1)
    {
        if(IsSign(*this,b,1,1))
            return add(b,*this);
        else if(IsSign(*this,b,-1,-1))
            return add(b,*this).minus();
        else if(IsSign(*this,b,1,-1))
            return subtract(b,*this).minus();
        else if(IsSign(*this,b,-1,1))
            return subtract(b,*this);
    }
    if(p==0)
    {
        if(IsSign(*this,b,1,-1) || IsSign(*this,b,-1,1))
        {
            return BigInt("0",1);
        }
        else if(IsSign(*this,b,1,1))
        {
            return add(*this,b);
        }
        else
        {
            return add(*this,b).minus();
        }
    }
}

BigInt BigInt::operator -(const BigInt& b) const {
    int p=ab_comp(*this,b);
    if(p==1)
    {
        if(IsSign(*this,b,1,1))
            return subtract(*this,b);
        else if(IsSign(*this,b,-1,-1))
            return subtract(*this,b).minus();
        else if(IsSign(*this,b,1,-1))
            return add(*this,b);
        else if(IsSign(*this,b,-1,1))
            return add(*this,b).minus();
    }
    if(p==-1)
    {
        if(IsSign(*this,b,1,1))
            return subtract(b,*this).minus();
        else if(IsSign(*this,b,-1,-1))
            return subtract(b,*this);
        else if(IsSign(*this,b,1,-1))
            return add(b,*this);
        else if(IsSign(*this,b,-1,1))
            return add(b,*this).minus();
    }
    if(p==0)
    {
        if(IsSign(*this,b,1,-1))
        {
            return add(b,*this);
        }
        if(IsSign(*this,b,-1,1))
        {
            return add(b,*this).minus();
        }
        else if(IsSign(*this,b,1,1))
        {
            return BigInt("0",1);
        }
        else
        {
            return BigInt("0",1);
        }
    }
}

BigInt BigInt::operator *(BigInt& b) {
    if(this->length()==b.length() && b.length()==1 && (((*this)[0]==0) || b[0]==0))
    {
        return BigInt("0");
    }
    if(IsSign(*this,b,1,-1)||IsSign(*this,b,-1,1))
    {
        return multiply_wrapper(*this,b).minus();
    }
    else
    {
        return multiply_wrapper(*this,b);
    }
      
}

bool BigInt::operator ==(const BigInt &b) const {
    bool IsSameSign=IsSign(*this,b,1,1) || IsSign(*this,b,-1,-1);
    return IsSameSign && ab_comp2(*this,b,0,this->str.length()-1,0,b.str.length()-1)==0;
}


std::ostream& operator<<(std::ostream& os, const BigInt& b) {
    if(b.sign==1)
    {
        os << b.str;
    }
    else
        os << '-'<<b.str;
    return os;
}
