#include "BigInt.h"
#include <iterator>
#include <utility>
BigInt &BigInt::operator+=(BigInt const &b) {
  int p = this->ab_comp(b);
  if (p == 1) {
    if (this->IsSign(b, 1, 1))
      return this->add(b);
    else if (this->IsSign(b, 0, 0))
      return (this->add(b)).minus();
    else if (this->IsSign(b, 1, 0))
      return this->subtract(b);
    else if (this->IsSign(b, 0, 1))
      return (this->subtract(b)).minus();
  }
  if (p == -1) {
    if (this->IsSign(b, 1, 1)) {
      (*this) = (BigInt(b).add(*this));
      return (*this);
    } else if (this->IsSign(b, 0, 0)) {
      (*this) = (BigInt(b).add(*this)).minus();
      return (*this);
    } else if (this->IsSign(b, 1, 0)) {
      (*this) = (BigInt(b).subtract(*this)).minus();
      return (*this);
    } else if (this->IsSign(b, 0, 1)) {
      (*this) = BigInt(b).subtract(*this);
      return (*this);
    }
  }
  if (p == 0) {
    if (this->IsSign(b, 1, 0) || this->IsSign(b, 0, 1)) {
      this->v = {0};
      this->sign = 1;
      return *this;
    } else if (this->IsSign(b, 1, 1)) {
      return this->add(b);
    } else {
      return (this->add(b)).minus();
    }
  }

  std::unreachable();
}
BigInt BigInt::operator+(BigInt const &b) { return (BigInt(*this) += b); }
BigInt &BigInt::operator-=(BigInt const &b) {
  int p = this->ab_comp(b);
  if (p == 1) {
    if (this->IsSign(b, 1, 1))
      return this->subtract(b);
    else if (this->IsSign(b, 0, 0))
      return (this->subtract(b)).minus();
    else if (this->IsSign(b, 1, 0))
      return this->add(b);
    else if (this->IsSign(b, 0, 1))
      return (this->add(b)).minus();
  }
  if (p == -1) {
    if (this->IsSign(b, 1, 1)) {
      (*this) = (BigInt(b).subtract(*this)).minus();
      return (*this);
    } else if (this->IsSign(b, 0, 0)) {
      (*this) = BigInt(b).subtract(*this);
      return (*this);
    } else if (this->IsSign(b, 1, 0)) {
      (*this) = BigInt(b).add(*this);
      return (*this);
    } else if (this->IsSign(b, 0, 1)) {
      (*this) = (BigInt(b).add(*this)).minus();
      return (*this);
    }
  }
  if (p == 0) {
    if (this->IsSign(b, 1, 0)) {
      (*this).add(b);
      return (*this);
    }
    if (this->IsSign(b, 0, 1)) {
      (*this).add(b);
      (*this).minus();
      return (*this);
    } else if (this->IsSign(b, 1, 1)) {
      this->v = {0};
      this->sign = 1;
      return *this;
    } else {
      this->v = {0};
      this->sign = 1;
      return *this;
    }
  }
  std::unreachable();
}

BigInt BigInt::operator-(BigInt const &b) { return BigInt(*this) -= b; }
BigInt BigInt::operator*(BigInt const &b) {
  if (this->size() == b.size() && b.size() == 1 &&
      (((*this)[0] == 0) || b[0] == 0)) {
    return BigInt("0");
  }
  if (this->IsSign(b, 1, 0) || this->IsSign(b, 0, 1)) {
    return (this->multiply(b, 0, this->size() - 1, 0, b.size() - 1)).minus();
  } else {
    return (this->multiply(b, 0, this->size() - 1, 0, b.size() - 1));
  }
}

BigInt &BigInt::operator=(BigInt const &b) {
  this->v = b.v;
  this->sign = b.sign;
  return (*this);
}

BigInt &BigInt::operator=(BigInt &&b) {
  (*this) = b;
  return (*this);
}

BigInt &BigInt::operator+=(uint32_t n) {
  BigInt b(n);
  (*this) += b;

  return (*this);
}

BigInt &BigInt::operator-=(uint32_t n) {
  BigInt b(n);
  (*this) -= b;
  return (*this);
}

bool BigInt::operator>=(const BigInt &b) {

  if (this->sign > b.sign)
    return true;
  if (this->sign < b.sign)
    return false;

  int abs_comp = this->ab_comp(b);
  if (abs_comp == 0)
    return true;
  if ((abs_comp == 1 && this->sign == 1) || (abs_comp == -1 && b.sign == 0))
    return true;
  return false;
}
bool BigInt::operator>(const BigInt &b) {
  if (this->sign > b.sign)
    return true;
  if (this->sign < b.sign)
    return false;

  int abs_comp = this->ab_comp(b);
  if (abs_comp == 0)
    return false;
  if ((abs_comp == 1 && this->sign == 1) || (abs_comp == -1 && b.sign == 0))
    return true;
  return false;
}
bool BigInt::operator<(const BigInt &b) { return !((*this) >= b); }
bool BigInt::operator<=(const BigInt &b) { return !((*this) > b); }

bool BigInt::operator>(int64_t n) {
  BigInt b(n, n >= 0);
  return (*this) > b;
}
bool BigInt::operator>=(int64_t n) {
  BigInt b(n, n >= 0);
  return (*this) >= b;
}
bool BigInt::operator<(int64_t n) { return (*this) >= n; }
bool BigInt::operator<=(int64_t n) { return (*this) > n; }
