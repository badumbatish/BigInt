#include <iostream>
#include "BigInt.h"
#include <algorithm>
#include <utility>
#include <cmath>
BigInt::~BigInt() {

}
BigInt::BigInt(const BigInt& b) {
    this->v = b.v;
    this->sign = b.sign;
}
BigInt::BigInt() {
    this->sign=1;
    this->v = std::vector<uint32_t>(1,0);
}
BigInt::BigInt(std::string const & b,bool sign, int base) {
    this->v = std::vector<uint32_t>(1,0);
    for(auto it=b.begin();it!=b.end();it++) {
        (*this).mult(10);
        (*this).add(*it-'0');
    }
    this->sign = sign;
}
BigInt::BigInt(uint32_t n, bool sign) {
    if(n==UINT32_MAX) {
        this->v = std::vector<uint32_t>{0,1};
    } else 
    this->v = std::vector<uint32_t>{n};
    this->sign=sign;
}
BigInt::BigInt(std::vector<uint32_t>&& v, bool sign) {
    this->v = v;
    this->sign = sign;

}
size_t BigInt::size() const {
    return this->v.size();
}

uint32_t BigInt::operator[](size_t i) const  {
    return this->v[i];
}
BigInt::BigInt(BigInt&& a) {
    this->sign=a.sign;
    this->v = a.v;
}

BigInt& BigInt::mult(uint32_t n) {
    uint64_t store = 0;
    uint64_t carry = 0;
    for(auto it=v.begin();it!=v.end();it++) {
        store = (uint64_t)(*it)*n + carry;
        carry = store/(UINT32_MAX);
        (*it) = store%UINT32_MAX;
    }
    if(carry != 0) v.push_back(carry);
    return (*this);
}
BigInt& BigInt::add(uint32_t n) {
    uint64_t store=0;
    uint64_t carry=0;
    for(auto it=v.begin();it!=v.end();it++) {
        if(it==v.begin()) {
            store = (uint64_t)(*it)+n + carry;
        } else store = (uint64_t)(*it) + carry;
        carry = store / (UINT32_MAX);
        (*it) = store%UINT32_MAX;
    }
    if(carry != 0) v.push_back(carry);

    return (*this);
}
BigInt& BigInt::add(BigInt const & b)   {
    uint64_t res=0;
    uint32_t carry=0;
    auto it1=(*this).v.begin();
    auto it1_end=(*this).v.end();

    auto it2=b.v.begin();
    auto it2_end=b.v.end();
    
    for(;it2!=it2_end;++it1,++it2)
    {
        res=(uint64_t)(*it1)+(*it2)+carry;
        *it1=res%UINT32_MAX;
        carry=res/UINT32_MAX;
    }
    for(;it1!=it1_end;++it1)
    {
        res=(uint64_t)(*it1)+carry;
        *it1=res%UINT32_MAX;
        carry=res/UINT32_MAX;
    }
    if(carry!=0) this->v.push_back(carry);
    return (*this);
}
BigInt& BigInt::subtract(BigInt const & b)  {
    int64_t res=0;
    int64_t carry=0;
    auto it1=(*this).v.begin();
    auto it1_end=(*this).v.end();

    auto it2=b.v.begin();
    auto it2_end=b.v.end();
    
    for(;it2!=it2_end;++it1,++it2)
    {
        res=(int64_t)(*it1)-(*it2)-carry;
        if(res<0)
        {
            res+=UINT32_MAX;
            carry=1;
        }
        else
        {
            carry=0;
        }
        *it1=res;
    }
    for(;it1!=it1_end;++it1) {
        res=(int64_t)(*it1)-carry;
        if(res<0)
        {
            res=res+UINT32_MAX;
            carry=1;
        }
        else
        {
            carry=0;
        }
        *it1=res;
    }
    auto itc=(*this).v.rbegin();
    while(*itc++ == 0 && (*this).size()>1)
        (*this).v.pop_back();
    return (*this);
}
BigInt BigInt::add2(const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2) const {
    BigInt c(std::vector<uint32_t>((end1-start1+1)+1,0));
    uint64_t carry=0;
    uint64_t res=0;
    auto it1=(*this).v.begin() + start1;
    auto it1_end=(*this).v.begin() + end1 + 1;
    auto it2=b.v.begin() + start2;
    auto it2_end=b.v.begin() + end2 + 1;
    auto it3=c.v.begin();
    
    // fine until here
    for(;it2!=it2_end;++it1,++it2,++it3)
    {
        res=(uint64_t)(*it1)+(*it2)+carry;
        *it3=res%UINT32_MAX;
        carry=res/UINT32_MAX;
    }
    for(;it1!=it1_end;++it1,++it3)
    {
        res=(uint64_t)(*it1)+carry;
        carry=res/UINT32_MAX;
        *it3=res%UINT32_MAX;
    }
    *it3=carry;
    //std::cout << c << std::endl;
    auto itc=c.v.rbegin();
    while(*itc++ == 0 && c.size()>1)
    {
        c.v.pop_back();
    }
    return c;
}
BigInt BigInt::subtract2(const BigInt &b,int64_t start1, int64_t end1, int64_t start2, int64_t end2) const
{   
    BigInt c(std::vector<uint32_t>(end1-start1+1,'0'));
    int64_t res=0;
    int64_t carry=0;
    auto it1=(*this).v.begin() + start1;
    auto it1_end=(*this).v.end() + end1 + 1;

    auto it2=b.v.begin() + start2;
    auto it2_end=b.v.end() + end2 + 1;
    
    auto it3=c.v.begin();
    for(;it2!=it2_end;++it1,++it2)
    {
        res=(int64_t)(*it1)-(*it2)-carry;
        if(res<0)
        {
            res+=UINT32_MAX;
            carry=1;
        }
        else
        {
            carry=0;
        }
        *it3=res;
    }
    for(;it1!=it1_end;++it1) {
        res=(int64_t)(*it1)-carry;
        if(res<0)
        {
            res=res+UINT32_MAX;
            carry=1;
        }
        else
        {
            carry=0;
        }
        *it3=res;
    }
    auto itc=(c).v.rbegin();
    while(*itc++ == 0 && (*this).size()>1)
        (c).v.pop_back();
    return (c);
}
BigInt BigInt::long_mul(BigInt const &b, int64_t start1, int64_t end1, int64_t start2, int64_t end2) 
{
    BigInt c(std::vector<uint32_t>(end1-start1+1+end2-start2+1,0));
    uint64_t res=0;
    uint64_t carry=0;
    
    auto it1=(*this).v.begin()+start1;
    auto it1_end=(*this).v.begin()+end1+1;
    auto it2=b.v.begin()+start2;
    auto it2_end=b.v.begin()+end2+1;
    
    auto it3=c.v.begin();
    auto counter=it3;
    //auto it3_end=c.str.end();
    for(;it2!=it2_end;++it2)
    {
        it3=counter;
        carry=0;
        it1=(*this).v.begin()+start1;
        for(;it1!=it1_end;++it1)
        {
            res=(uint64_t)(*it1)*(*it2)+carry+(*it3);
            carry=res/UINT32_MAX;
            *it3=res%UINT32_MAX;
            ++it3;
        }
        *it3=((uint64_t)(*it3)+carry)%UINT32_MAX;
        ++counter;
    }
    
    auto itc=c.v.rbegin();
    while(*itc++ == 0 && c.size()>1)
    {
        c.v.pop_back();
    }
    c.v.shrink_to_fit();
    return c;
}

BigInt BigInt::por_add(BigInt const & b, int64_t start1, int64_t end1, int64_t start2, int64_t end2) const {
    int p=this->ab_comp2(b,start1,end1,start2,end2);
    if(p==1)
    {
        if(this->IsSign(b,1,1))
            return this->add2(b,start1,end1,start2,end2);
        else if(this->IsSign(b,0,0))
            return (this->add2(b,start1,end1,start2,end2)).minus();
        else if(this->IsSign(b,1,0))
            return this->subtract2(b,start1,end1,start2,end2);
        else if(this->IsSign(b,0,1))
            return (this->subtract2(b,start1,end1,start2,end2)).minus();
    }
    if(p==-1)
    {
        if(this->IsSign(b,1,1)) {
            return (BigInt(b).add2(*this,start2,end2,start1,end1));
        }
        else if(this->IsSign(b,0,0)) {
            return (BigInt(b).add2(*this,start2,end2,start1,end1)).minus();
            
        }
        else if(this->IsSign(b,1,0)) {
            return (BigInt(b).subtract2(*this,start2,end2,start1,end1)).minus();
            
         }
        else if(this->IsSign(b,0,1)) {
            return BigInt(b).subtract2(*this,start2,end2,start1,end1);
            
        }
    }
    if(p==0)
    {
        if(this->IsSign(b,1,0) || this->IsSign(b,0,1))
        {
            return BigInt(0,1);
        }
        else if(this->IsSign(b,1,1))
        {
            return this->add2(b,start1,end1,start2,end2);
        }
        else
        {
            return (this->add2(b,start1,end1,start2,end2)).minus();
        }
    }
}
BigInt BigInt::por_sub(BigInt const & b, int64_t start1, int64_t end1, int64_t start2, int64_t end2) const {
    int p=this->ab_comp2(b,start1,end1,start2,end2);
    if(p==1)
    {
        if(this->IsSign(b,1,1))
            return this->subtract2(b,start1,end1,start2,end2);
        else if(this->IsSign(b,0,0))
            return (this->subtract2(b,start1,end1,start2,end2)).minus();
        else if(this->IsSign(b,1,0))
            return this->add2(b,start1,end1,start2,end2);
        else if(this->IsSign(b,0,1))
            return (this->add2(b,start1,end1,start2,end2)).minus();
    }
    if(p==-1)
    {
        if(this->IsSign(b,1,1)) {
            return (BigInt(b).subtract2(*this,start2,end2,start1,end1)).minus();
        }
        else if(this->IsSign(b,0,0)) {
            return BigInt(b).subtract2(*this,start2,end2,start1,end1);
        }
        else if(this->IsSign(b,1,0)) {
            return BigInt(b).add2(*this,start2,end2,start1,end1);
        }
        else if(this->IsSign(b,0,1)) {
            return (BigInt(b).add2(*this,start2,end2,start1,end1)).minus();
        }
    }
    if(p==0)
    {
        if(this->IsSign(b,1,0))
        {   
            return (*this).add2(b,start1,end1,start2,end2);
        }
        if(this->IsSign(b,0,1))
        {
            return ((*this).add2(b,start1,end1,start2,end2)).minus();
            
        }
        else if(this->IsSign(b,1,1))
        {
            return BigInt(0,1);
        }
        else
        {
            return BigInt(0,1);
        }
    }
}
BigInt BigInt::multiply(BigInt const &b, int64_t start1, int64_t end1, int64_t start2, int64_t end2) {       
    if(end1-start1+1<=70 || end2-start2+1<=70)
    {   
        return this->long_mul(b,start1,end1,start2,end2);
    }
    int64_t m1=end1+start1;
    int64_t m2=end2+start2;
    m1=std::ceil(m1*1.0/2);
    m2=std::ceil(m2*1.0/2);
    m1=std::min(m1,m2);
    BigInt lh1=this->por_add(*this,start1,m1-1,m1,end1);
    BigInt lh2=b.por_add(b,start2,m1-1,m1,end2);
    BigInt z1=lh1.multiply(lh2,0,lh1.size()-1,0,lh2.size()-1); // (low1+high1)*(low2+high2)
    
    BigInt z2=this->multiply(b,m1,end1,m1,end2); // high
    
    BigInt z0=this->multiply(b,start1,m1-1,start2,m1-1); // low
    
    BigInt z20=z2.por_add(z0,0,z2.size()-1,0,z0.size()-1);
    z1=z1.por_sub(z20,0,z1.size()-1,0,z20.size()-1);
    int64_t m3=std::min(end1-start1,end2-start2);
    m3= std::ceil(m3*1.0/2);
    //z2.str.reserve(m3*2+z2.str.size());
    z2.v.insert(z2.v.begin(),m3*2,0);
    //z1.str.reserve(m3+z1.size()+z0.size()+1);
    z1.v.insert(z1.v.begin(),m3,0);

    z1+=z0;

    return z2+=z1;
}
bool BigInt::operator ==(BigInt const & b) const {
    if(v.size() != b.size()) {
        return false;
    }
    
    for(size_t i=0;i<v.size();i++) {
        if(v[i]!=b[i]) return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const BigInt& b) {
    if(b.sign==0) std::cout << "-";
    for(auto it=b.v.rbegin();it!=b.v.rend();it++) {
        std::cout << (*it) << " ";
    }
    return os;
}

BigInt& BigInt::operator *=(uint32_t n) {
    int positive = this->sign + (n>=0);
    if(positive==0 || positive == 2) {
        this->sign=1;
    } else this->sign=0;
    return this->mult(n); 
}

int BigInt::ab_comp(BigInt const & b) const  {
    if(this->size() > b.size()) return 1;
    if(this->size() < b.size()) return -1;
    for(int i=this->size()-1;i>=0;i--) {
        if((*this)[i]> b[i]) return 1;
        else if((*this)[i]<b[i]) return -1;
    }
    return 0;
}

int BigInt::ab_comp2(const BigInt& b, int64_t start1, int64_t end1, int64_t start2, int64_t end2)  const {
    int64_t m = end1-start1+1;
    int64_t n = end2-start2+1;
    if(m>n)
        return 1;
    if(m<n)
        return -1;
    else
    {
        auto it1=(*this).v.rbegin() + ((*this).size()-end1-1);
        auto it1_end=(*this).v.rend() - start1;
        auto it2=b.v.rbegin()+ (b.size()-end2-1);
        auto it2_end=b.v.rend() - start2;
        for(;it1!=it1_end && it2!=it2_end;++it1,++it2)
        {
            if(*it1<*it2) return -1;
            else if(*it1>*it2)return 1;
        }
        return 0;
    }
}
