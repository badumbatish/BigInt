#include "BigInt.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
BigInt::~BigInt() {}
BigInt::BigInt(const BigInt &b) {
  this->v = b.v;
  this->is_nonnegative = b.is_nonnegative;
}
BigInt::BigInt() {
  this->is_nonnegative = true;
  this->v = std::vector<uint32_t>(1, 0);
}
BigInt::BigInt(std::string const &b, bool sign, int base) {
  this->v = std::vector<uint32_t>(1, 0);
  for (auto it = b.begin(); it != b.end(); it++) {
    (*this).mult(10);
    (*this).add(*it - '0');
  }
  this->is_nonnegative = sign;
}

BigInt::BigInt(uint32_t n, bool sign) {
  if (n == BASE) {
    this->v = {0, 1};
  } else
    this->v = {n};
  this->is_nonnegative = sign;
}

BigInt::BigInt(std::vector<uint32_t> &&v, bool sign) {
  this->v = v;
  this->is_nonnegative = sign;
}
size_t BigInt::size() const { return this->v.size(); }

BigInt::BigInt(BigInt &&a) : is_nonnegative(a.is_nonnegative), v(a.v) {}

BigInt &BigInt::mult(uint32_t n) {
  uint64_t store = 0;
  uint64_t carry = 0;
  for (auto &num : v) {
    store = (uint64_t)(num)*n + carry;
    carry = store / (BASE);
    num = store % BASE;
  }
  if (carry != 0)
    v.push_back(carry);
  return (*this);
}
BigInt &BigInt::add(uint32_t n) {
  uint64_t store = 0;
  uint64_t carry = 0;
  for (auto num = v.begin(); num != v.end(); num++) {
    if (num == v.begin()) {
      store = (uint64_t)(*num) + n + carry;
    } else
      store = (uint64_t)(*num) + carry;
    carry = store / (BASE);
    (*num) = store % BASE;
  }
  if (carry != 0)
    v.push_back(carry);

  return (*this);
}
BigInt &BigInt::add(BigInt const &b) {
  uint64_t res = 0;
  uint32_t carry = 0;
  auto it1 = (*this).v.begin();
  auto it1_end = (*this).v.end();

  auto it2 = b.v.begin();
  auto it2_end = b.v.end();

  for (; it2 != it2_end; ++it1, ++it2) {
    res = (uint64_t)(*it1) + (*it2) + carry;
    *it1 = res % BASE;
    carry = res / BASE;
  }
  for (; it1 != it1_end; ++it1) {
    res = (uint64_t)(*it1) + carry;
    *it1 = res % BASE;
    carry = res / BASE;
  }
  if (carry != 0)
    this->v.push_back(carry);
  return (*this);
}
BigInt &BigInt::subtract(BigInt const &b) {
  int64_t res = 0;
  int64_t carry = 0;
  auto it1 = (*this).v.begin();
  auto it1_end = (*this).v.end();

  auto it2 = b.v.begin();
  auto it2_end = b.v.end();

  for (; it2 != it2_end; ++it1, ++it2) {
    res = (int64_t)(*it1) - (*it2) - carry;
    if (res < 0) {
      res += BASE;
      carry = 1;
    } else {
      carry = 0;
    }
    *it1 = res;
  }
  for (; it1 != it1_end; ++it1) {
    res = (int64_t)(*it1) - carry;
    if (res < 0) {
      res = res + BASE;
      carry = 1;
    } else {
      carry = 0;
    }
    *it1 = res;
  }
  auto itc = (*this).v.rbegin();
  while (*itc++ == 0 && (*this).size() > 1)
    (*this).v.pop_back();
  return (*this);
}

BigInt BigInt::long_mult(BigInt const &b, int64_t start1, int64_t end1,
                         int64_t start2, int64_t end2) {
  BigInt c(std::vector<uint32_t>(end1 - start1 + 1 + end2 - start2 + 1, 0));
  uint64_t res = 0;
  uint64_t carry = 0;

  auto it1 = (*this).v.begin() + start1;
  auto it1_end = (*this).v.begin() + end1 + 1;
  auto it2 = b.v.begin() + start2;
  auto it2_end = b.v.begin() + end2 + 1;

  auto it3 = c.v.begin();
  auto counter = it3;
  // auto it3_end=c.str.end();
  for (; it2 != it2_end; ++it2) {
    it3 = counter;
    carry = 0;
    it1 = (*this).v.begin() + start1;
    for (; it1 != it1_end; ++it1) {
      res = (uint64_t)(*it1) * (*it2) + carry + (*it3);
      carry = res / BASE;
      *it3 = res % BASE;
      ++it3;
    }
    *it3 = ((uint64_t)(*it3) + carry) % BASE;
    ++counter;
  }

  auto itc = c.v.rbegin();
  while (*itc++ == 0 && c.size() > 1) {
    c.v.pop_back();
  }
  c.v.shrink_to_fit();
  return c;
}

BigInt BigInt::range_add(BigInt const &b, int64_t start1, int64_t end1,
                         int64_t start2, int64_t end2) const {
  int64_t size1 = end1 - start1 + 1;
  int64_t size2 = end2 - start2 + 1;
  int64_t maxSize = std::max(size1, size2);

  BigInt c(std::vector<uint32_t>(maxSize + 1, 0));
  uint64_t carry = 0;
  uint64_t res = 0;

  auto it1 = (size1 > 0) ? (*this).v.begin() + start1 : (*this).v.end();
  auto it1_end = (size1 > 0) ? (*this).v.begin() + end1 + 1 : (*this).v.end();
  auto it2 = (size2 > 0) ? b.v.begin() + start2 : b.v.end();
  auto it2_end = (size2 > 0) ? b.v.begin() + end2 + 1 : b.v.end();
  auto it3 = c.v.begin();

  while (it1 != it1_end || it2 != it2_end) {
    uint64_t val1 = (it1 != it1_end) ? *it1++ : 0;
    uint64_t val2 = (it2 != it2_end) ? *it2++ : 0;

    res = val1 + val2 + carry;
    *it3++ = res % BASE;
    carry = res / BASE;
  }

  // Handle any remaining carry
  if (carry > 0) {
    *it3 = carry;
  }

  // Remove leading zeros
  auto itc = c.v.rbegin();
  while (*itc == 0 && c.v.size() > 1) {
    c.v.pop_back();
    ++itc;
  }

  return c;
}
BigInt BigInt::karatsuba_mult(BigInt const &b, int64_t start1, int64_t end1,
                              int64_t start2, int64_t end2) {
  if (end1 - start1 + 1 <= LONG_MULT_SIZE ||
      end2 - start2 + 1 <= LONG_MULT_SIZE) {
    return this->long_mult(b, start1, end1, start2, end2);
  }
  int64_t m1 = end1 + start1;
  int64_t m2 = end2 + start2;
  m1 = std::ceil(m1 * 1.0 / 2);
  m2 = std::ceil(m2 * 1.0 / 2);
  m1 = std::min(m1, m2);
  BigInt lh1 = this->range_add(*this, start1, m1 - 1, m1, end1);
  BigInt lh2 = b.range_add(b, start2, m1 - 1, m1, end2);
  BigInt z1 = lh1.karatsuba_mult(lh2, 0, lh1.size() - 1, 0,
                                 lh2.size() - 1); // (low1+high1)*(low2+high2)

  BigInt z2 = this->karatsuba_mult(b, m1, end1, m1, end2); // high

  BigInt z0 = this->karatsuba_mult(b, start1, m1 - 1, start2, m1 - 1); // low

  BigInt z20 = z2.range_add(z0, 0, z2.size() - 1, 0, z0.size() - 1);
  z1 -= z20;
  int64_t m3 = std::min(end1 - start1, end2 - start2);
  m3 = std::ceil(m3 * 1.0 / 2);
  z2.v.insert(z2.v.begin(), m3 * 2, 0);
  z1.v.insert(z1.v.begin(), m3, 0);

  z1 += z0;

  return z2 += z1;
}
bool BigInt::operator==(BigInt const &b) const {
  if (v.size() != b.size())
    return false;

  for (size_t i = 0; i < v.size(); i++) {
    if (v[i] != b[i])
      return false;
  }
  return true;
}

std::ostream &operator<<(std::ostream &os, const BigInt &b) {
  if (b.is_nonnegative == 0)
    std::cout << "-";
  for (auto it = b.v.rbegin(); it != b.v.rend(); it++)
    std::cout << (*it) << " ";

  return os;
}

BigInt &BigInt::operator*=(uint32_t n) {
  this->is_nonnegative = !(is_nonnegative ^ (n >= 0));
  return this->mult(n);
}

int BigInt::full_comparison(BigInt const &b) const {
  if (this->size() > b.size())
    return 1;
  if (this->size() < b.size())
    return -1;
  for (int i = this->size() - 1; i >= 0; i--) {
    if ((*this)[i] > b[i])
      return 1;
    else if ((*this)[i] < b[i])
      return -1;
  }
  return 0;
}

int BigInt::partial_comparison(const BigInt &b, int64_t start1, int64_t end1,
                               int64_t start2, int64_t end2) const {
  int64_t m = end1 - start1 + 1;
  int64_t n = end2 - start2 + 1;
  if (m > n)
    return 1;
  if (m < n)
    return -1;
  else {
    auto it1 = (*this).v.rbegin() + ((*this).size() - end1 - 1);
    auto it1_end = (*this).v.rend() - start1;
    auto it2 = b.v.rbegin() + (b.size() - end2 - 1);
    auto it2_end = b.v.rend() - start2;
    for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      if (*it1 < *it2)
        return -1;
      else if (*it1 > *it2)
        return 1;
    }
    return 0;
  }
}
