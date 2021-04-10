#include <iostream>
#include "BigInt.h"
#include <algorithm>
#include <utility>
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
    uint32_t carry=0;
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

