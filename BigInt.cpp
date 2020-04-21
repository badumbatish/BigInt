#include <iostream>
#include "BigInt.h"
#include <algorithm>
#include <utility>
#include <cmath>
BigInt::BigInt() {
    str="";
    sign=1;
}
BigInt::BigInt(std::string& str2,int i,int keepOldString) {
    //std::cout << "Non const " << std::endl;
    if(keepOldString==1)
    {
        //std::cout << "Deep copy" << std::endl;
        str=str2;
    }
    else
    {
        //std::cout << "Shallow copy" << std::endl;
        str=std::move(str2);
    }
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
    str=std::move(str2);
    if(i==-1)
    {
        sign=-1;
    }
    else 
    {
        sign=1;
    }
}
BigInt::BigInt(const std::string&str2, int i) {
    //std::cout << "Const" << std::endl;
    this->str=str2;
    if(i==-1)
    {
        sign=-1;
    }
    else 
    {
        sign=1;
    }
}
BigInt::BigInt(BigInt &b,int keepOldString)
{
    //std::cout << "YES " << " with " << b.sign;

    if(keepOldString==1)
    {
        //std::cout << "Deep copy" << std::endl;
        str=b.str;
        sign=b.sign;
    }
    else
    {
        //std::cout << "Shallow copy" << std::endl;
        str=std::move(b.str);
        sign=std::move(b.sign);
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
    this->str=std::move(b.str);
    this->sign=std::move(b.sign);
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
    this->str=std::move(b.str);
    this->sign=std::move(b.sign);
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

int BigInt::ab_comp(const BigInt& a,const BigInt& b, int start1, int end1, int start2, int end2)  const {
    int m = end1-start1;
    int n=end2-start2;
    if(m>n)
    {
        return 1;
    }
    if(m<n)
    {
        return -1;
    }
    else
    {
        for(int i=start1;i<=end1;i++)
        {
            if(a[i]<b[i])
            {
                return -1;
            }
            else if(a[i]>b[i])
            {
                return 1;
            }
        }
        return 0;
    }
}

BigInt BigInt::add(const BigInt &a, const BigInt &b) const {
    
    int e=a.length()+1; // get length + 1
    BigInt c(std::string(e,'0'));
    int m=a.length()-b.length();
    int res=0;
    int carry=0;
    int j=0;
    for(int i=e-2;i>=m;i--)
    {
        int p=a[i];
        int q=b[i-m];
        res=(p+q);
        c.str[j++]=char(((res+carry)%10)+'0');
        if(res>9)
        {
            carry=1;
        }
        else
        {
            carry=0;
        }
    }
    if(carry==1)
    {
        if(m!=0)
        {
            res=a[m-1];
        }
        else
        {
            res=0;
        }
        c.str[j++]=char(((res+carry)%10)+'0');
        m--;
        carry=0;
    }
    for(int i=m-1;i>=0;i--)
    {
        res=a[i];
        c.str[j++]=char(res+'0');
    }
    if(c.str[c.str.length()-1]=='0' && c.str.length()>1)
        c.str.pop_back();
    std::reverse(c.str.begin(),c.str.end());
    return c;
}
BigInt BigInt::add2(const BigInt& a,const BigInt& b, int start1, int end1, int start2, int end2) const {
    int e=(end1-start1+1)+1; // get length + 1
    BigInt c=std::string(e,'0');
    int carry=0;
    int res=0;
    int m=end1;
    int n=end2;
    int i;
    for(i=0;i<e,m>=start1,n>=start2;i++)
    {
        res=a[m--]+b[n--];
        
        c.str[i]=char(((res+carry)%10)+'0');
        
        if(res>9)
        {
            carry=1;
        }
        else
        {
            carry=0;
        }
    }

    for(i;i<e,m>=start1;i++)
    {
        res=a[m--];
        
        c.str[i]=char(((res+carry)%10)+'0');
        if(carry==1)
        {
            carry=0;
        }
    }
    if(carry==1)
    {
        c.str[e-1]='1';
    }
    while(c.str[--e]=='0')
        c.str.pop_back();
    std::reverse(c.str.begin(),c.str.end());
    return c;
}

BigInt BigInt::subtract(const BigInt &a, const BigInt &b) const {
    int e=a.length(); // get length + 1
    BigInt c(std::string(e,'0'));
    //std::cout << "after " << std::endl;
    //c = BigInt(std::string(a.length(),'1'));

    int m=a.length()-b.length();
    int res=0;
    int carry=0;
    int j=0;
    for(int i=e-1;i>=m;i--)
    {
        int p=a[i];
        int q=b[i-m];
        if(p<q)
        {
            res=(p+10)-(q);
        }
        else
            res=(p)-(q);
        if(res==0) res+=10;
        c.str[j++]=char(((res-carry)%10)+'0');
        if(p<q)
        {
            carry=1;
        }
        else
        {
            carry=0;
        }
    }
    if(carry==1)
    {
        res=a[m-1];
        c.str[j++]=char(((res-carry)%10)+'0');
        carry=0;
        m--;
    }
    for(int i=m-1;i>=0;i--)
    {
        res=a[i];
        c.str[j++]=char(res+'0');
    }
    if(c.str[c.str.length()-1]=='0' && c.str.length()>1)
    c.str.pop_back();
    std::reverse(c.str.begin(),c.str.end());
    return c;
}
BigInt BigInt::subtract2(const BigInt &a, const BigInt &b, int start1, int end1, int start2, int end2) const {
    int e=(end1-start1)+1; // get length + 1
    BigInt c=std::string(e,'0');
    int carry=0;
    int res=0;
    int m=end1;
    int n=end2;
    int i;
    for(i=0;i<e,m>=start1,n>=start2;i++)
    {
        int p=a[m--];
        int q=b[n--];
        if(p<q)
        {
            res=p+10-q;
        }
        else
            res=p-q;
        
        if(res==0)
            res+=10;
        c.str[i]=char(((res-carry)%10)+'0');
        
        if(p<q)
        {
            carry=1;
        }
        else
        {
            carry=0;
        }
    }
    
    for(i;i<e,m>=start1;i++)
    {
        res=a[m--];
        res=res-carry;
        if(res<0)
        {
            res+=10;
        }
        c.str[i]=char(((res)%10)+'0');
        if(carry==1)
        {
            carry=0;
        }
    }
    
    if(c.str[e-1]=='0') c.str.pop_back();
    std::reverse(c.str.begin(),c.str.end());
    return c;
}

BigInt BigInt::por_add(const BigInt& a,const BigInt& b, int start1, int end1, int start2, int end2) const {

    int p=ab_comp(a,b,start1,end1,start2,end2);
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
            return subtract2(b,a,start2,end2,start1,end1).minus();
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
BigInt BigInt::por_sub(const BigInt& a,const BigInt& b, int start1, int end1, int start2, int end2) const {
    int p=ab_comp(a,b,start1,end1,start2,end2);
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
void BigInt::reLength(BigInt &a, BigInt &b)
{
    if(a.length()==b.length())
    {
        return;
    }
    int64_t m=std::max(a.length(),b.length());
    if(m-a.length()>0)
    {
        a.str=std::string(m-a.length(),'0')+a.str;
    }
    if(m-b.length()>0)
    {
        b.str=std::string(m-b.length(),'0')+b.str;
    }
}
BigInt BigInt::multiply(BigInt& a, BigInt& b, int start1, int end1, int start2, int end2)
{
    reLength(a,b);
    int m=end1-start1;
    if(m==1 && a[0]==0 && b[0]==0)
    {
        return IntToBigInt((a[end1])*(b[end2]));
    }
    if(m==0)
    {
        return IntToBigInt(a[end1]*b[end2]);
    }
    
    int m1=std::ceil(1.0*m/2);
    //std::cout << m1 << std::endl;
    BigInt lh1=por_add(a,a,start1,m1-1,m1,end1);
    BigInt lh2=por_add(b,b,start1,m1-1,m1,end1);
    
    BigInt z0=multiply(a,b,m1,end1,m1,end2); // low
    
    reLength(lh1,lh2);
    
    
    BigInt z1=multiply(lh1,lh2,0,lh1.length()-1,0,lh1.length()-1); // (low1+high1)*(low2+high2)
    BigInt z2=multiply(a,b,start1,m1-1,start2,m1-1);
    
    BigInt p=por_sub(z1,por_add(z2,z0,0,z2.length()-1,0,z0.length()-1),0,z1.length()-1,0,std::max(z2.length()-1,z0.length()-1));
    p.str+=std::string((end1-start1+1)/2,'0');
    z2.str+=std::string((end1-start1+1),'0');
    
    return por_add(z2,por_add(p,z0,0,p.length()-1,0,z0.length()-1),0,z2.length()-1,0,std::max(p.length()-1,z0.length()-1));
}
BigInt BigInt::multiply_wrapper(BigInt &a, BigInt &b)
{
    BigInt bi1=a.str;
    BigInt bi2=b.str;
    
    int64_t p=std::max(bi1.length(),bi2.length());

    if(p-bi1.length()>0)
    {
        bi1.str=std::string(p-bi1.length(),'0')+bi1.str;
    }
    if(p-bi2.length()>0)
    {
        bi2.str=std::string(p-bi2.length(),'0')+bi2.str;
    }
    
    return multiply(bi1,bi2,0,bi1.length()-1,0,bi1.length()-1);
}
BigInt BigInt::operator +(const BigInt& b) const {
    int m=this->length()-1;
    int n=b.length()-1;
    int p=ab_comp(*this,b,0,m,0,n);
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
            return subtract(b,*this).minus();
    }
    if(p==0)
    {
        if(IsSign(*this,b,1,-1))
        {
            return BigInt("0",1);
        }
        else if(IsSign(*this,b,-1,1))
        {
            return BigInt("0",1);
        }
        else if(IsSign(*this,b,1,1))
        {
            return add(b,*this);
        }
        else
        {
            return add(*this,b).minus();
        }
    }
}

BigInt BigInt::operator -(const BigInt& b) const {
    int m=this->str.length()-1;
    int n=b.str.length()-1;
    int p=ab_comp(*this,b,0,m,0,n);
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
    return multiply_wrapper(*this,b);
}

bool BigInt::operator ==(const BigInt &b) const {
    bool IsSameSign=IsSign(*this,b,1,1) || IsSign(*this,b,-1,-1);
    return IsSameSign && ab_comp(*this,b,0,this->str.length()-1,0,b.str.length()-1)==0;
}

BigInt BigInt::IntToBigInt(int64_t t)
{
    bool isNegative = false;
    int64_t m=t;
    if(m==0)
    {
        return BigInt("0");
    }
    if(m<0)
    {
        isNegative=true;
        m*=-1;
    }
    int i=1;
    std::string s="";
    while(m>0)
    {
        s=char(m%10+'0')+s;
        m/=10;
    }
    
    BigInt bi(s,1,-1);
    
    if(isNegative)
        return bi.minus();
    else
        return bi;
    
}
std::ostream& operator<<(std::ostream& os, const BigInt& b)
{
    if(b.sign==1)
    {
        os << b.str;
    }
    else
        os << '-'<<b.str;
    return os;
}