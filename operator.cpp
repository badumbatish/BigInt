#include "BigInt.h"
#include <iterator>
#include <utility>
BigInt &BigInt::operator+=(BigInt const &b) {
  int p = this->full_comparison(b);
  if (p == 1) {
    if (this->IsSameSign(b, 1, 1))
      return this->add(b);
    else if (this->IsSameSign(b, 0, 0))
      return (this->add(b)).minus();
    else if (this->IsSameSign(b, 1, 0))
      return this->subtract(b);
    else if (this->IsSameSign(b, 0, 1))
      return (this->subtract(b)).minus();
  }
  if (p == -1) {
    if (this->IsSameSign(b, 1, 1)) {
      (*this) = (BigInt(b).add(*this));
      return (*this);
    } else if (this->IsSameSign(b, 0, 0)) {
      (*this) = (BigInt(b).add(*this)).minus();
      return (*this);
    } else if (this->IsSameSign(b, 1, 0)) {
      (*this) = (BigInt(b).subtract(*this)).minus();
      return (*this);
    } else if (this->IsSameSign(b, 0, 1)) {
      (*this) = BigInt(b).subtract(*this);
      return (*this);
    }
  }
  if (p == 0) {
    if (this->IsSameSign(b, 1, 0) || this->IsSameSign(b, 0, 1)) {
      this->v = {0};
      this->is_nonnegative = 1;
      return *this;
    } else if (this->IsSameSign(b, 1, 1)) {
      return this->add(b);
    } else {
      return (this->add(b)).minus();
    }
  }

  std::unreachable();
}
BigInt BigInt::operator+(BigInt const &b) { return (BigInt(*this) += b); }
BigInt &BigInt::operator-=(BigInt const &b) {
  is_nonnegative = !is_nonnegative;
  *this += b;
  is_nonnegative = !is_nonnegative;
  return *this;
}

BigInt BigInt::operator-(BigInt const &b) { return BigInt(*this) -= b; }
BigInt BigInt::operator*(BigInt const &b) {
  if (this->size() == b.size() && b.size() == 1 &&
      (((*this)[0] == 0) || b[0] == 0)) {
    return BigInt("0");
  }
  if (this->IsSameSign(b, 1, 0) || this->IsSameSign(b, 0, 1)) {
    return (this->karatsuba_mult(b, 0, this->size() - 1, 0, b.size() - 1))
        .minus();
  } else {
    return (this->karatsuba_mult(b, 0, this->size() - 1, 0, b.size() - 1));
  }
}

uint32_t BigInt::operator[](size_t i) const { return this->v[i]; }

BigInt &BigInt::operator*=(BigInt &rhs) {
  bool result_sign = is_nonnegative != rhs.is_nonnegative;
  *this = this->karatsuba_mult(rhs, 0, this->size() - 1, 0, rhs.size() - 1);
  is_nonnegative = result_sign && (*this) == BigInt("0");
  return *this;
}
BigInt &BigInt::operator=(BigInt const &b) {
  this->v = b.v;
  this->is_nonnegative = b.is_nonnegative;
  return (*this);
}

BigInt &BigInt::operator=(BigInt &&b) {
  this->is_nonnegative = b.is_nonnegative;
  this->v = std::move(b.v);
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

  if (this->is_nonnegative > b.is_nonnegative)
    return true;
  if (this->is_nonnegative < b.is_nonnegative)
    return false;

  int abs_comp = this->full_comparison(b);
  if (abs_comp == 0)
    return true;
  if ((abs_comp == 1 && this->is_nonnegative == 1) ||
      (abs_comp == -1 && b.is_nonnegative == 0))
    return true;
  return false;
}
bool BigInt::operator>(const BigInt &b) {
  if (this->is_nonnegative > b.is_nonnegative)
    return true;
  if (this->is_nonnegative < b.is_nonnegative)
    return false;

  int abs_comp = this->full_comparison(b);
  if (abs_comp == 0)
    return false;
  if ((abs_comp == 1 && this->is_nonnegative == 1) ||
      (abs_comp == -1 && b.is_nonnegative == 0))
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
