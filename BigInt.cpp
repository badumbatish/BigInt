#include "BigInt.h"
#include <algorithm>
#include <arm_neon.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <ranges>
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

  if (this->v.size() < b.v.size())
    this->v.append_range(std::ranges::views::iota(
        0u, static_cast<uint32_t>(b.v.size() - v.size())));
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
  if (this->v.size() < b.v.size())
    this->v.append_range(std::ranges::views::iota(
        0u, static_cast<uint32_t>(b.v.size() - v.size())));
  int64_t res = 0;
  int64_t carry = 0;
  auto it1 = (*this).v.begin();
  auto it1_end = (*this).v.end();

  auto it2 = b.v.begin();
  auto it2_end = b.v.end();

  for (; it2 != it2_end; ++it1, ++it2) {
    res = (int64_t)(*it1) - (*it2) - carry;
    if (res < 0) {
      res *= -1;
      carry = 1;
    } else {
      carry = 0;
    }
    *it1 = res;
  }
  for (; it1 != it1_end; ++it1) {
    res = (int64_t)(*it1) - carry;
    if (res < 0) {
      res *= -1;
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
                         int64_t start2, int64_t end2) const {
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
                              int64_t start2, int64_t end2) const {
  // Base case: use standard multiplication for small numbers
  if (end1 - start1 + 1 <= LONG_MULT_SIZE ||
      end2 - start2 + 1 <= LONG_MULT_SIZE) {
    return this->long_mult(b, start1, end1, start2, end2);
  }

  // Calculate lengths of numbers
  int64_t len1 = end1 - start1 + 1;
  int64_t len2 = end2 - start2 + 1;

  // Calculate split point (middle)
  int64_t m = std::min(len1, len2) / 2;

  // Calculate midpoints for both numbers
  int64_t mid1 = start1 + m;
  int64_t mid2 = start2 + m;

  auto mid3 = std::min(mid1, mid2);
  // Split numbers into high and low parts:
  // a = a1 * B^m + a0
  // b = b1 * B^m + b0
  // where B is the base (10 in this case)

  // Calculate z0 = a0 * b0 (low parts)
  BigInt z0 = this->karatsuba_mult(b, start1, mid3 - 1, start2, mid3 - 1);

  // Calculate z2 = a1 * b1 (high parts)
  BigInt z2 = this->karatsuba_mult(b, mid3, end1, mid3, end2);

  // Calculate (a0 + a1) and (b0 + b1)
  BigInt lh1 = this->range_add(*this, start1, mid3 - 1, mid3, end1);
  BigInt lh2 = b.range_add(b, start2, mid3 - 1, mid3, end2);

  // Calculate z1 = (a0 + a1)(b0 + b1) - z0 - z2
  BigInt z1 = lh1.karatsuba_mult(lh2, 0, lh1.size() - 1, 0, lh2.size() - 1);
  z1 = z1 - z0 - z2;

  // Combine results:
  // result = z2 * B^(2m) + z1 * B^m + z0
  z2.v.insert(z2.v.begin(), 2 * m, 0); // Multiply z2 by B^(2m)
  z1.v.insert(z1.v.begin(), m, 0);     // Multiply z1 by B^m

  BigInt result = z2 + z1 + z0;

  // Remove leading zeros
  while (result.v.size() > 1 && result.v.back() == 0) {
    result.v.pop_back();
  }

  return result;
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
  // Sizes are equal; compare using NEON
  const int chunk_size = 4; // NEON processes 4 x 32-bit integers in one go
  int n = this->size();
  int i = n - chunk_size;

  // Process chunks of 4 elements
  for (; i >= 0; i -= chunk_size) {
    // Load 4 elements from both vectors
    auto a_chunk = vld1q_u32(&(this->v[i]));
    auto b_chunk = vld1q_u32(&(b.v[i]));

    // Compare elements
    auto a_gt_b = vcgtq_u32(a_chunk, b_chunk); // a > b
    auto b_gt_a = vcgtq_u32(b_chunk, a_chunk); // b > a

    // Check if any mismatch occurred
    if (vmaxvq_u32(a_gt_b) > 0) { // Any a > b
      for (int j = 0; j < chunk_size; ++j) {
        if (this->v[i + j] > b.v[i + j])
          return 1;
        else if (this->v[i + j] < b.v[i + j])
          return -1;
      }
    }

    if (vmaxvq_u32(b_gt_a) > 0) { // Any b > a
      for (int j = 0; j < chunk_size; ++j) {
        if (this->v[i + j] > b.v[i + j])
          return 1;
        else if (this->v[i + j] < b.v[i + j])
          return -1;
      }
    }
  }

  // Handle remaining elements that don't fit into a full chunk
  for (int j = (i + chunk_size) - 1; j >= 0; --j) {
    if (this->v[j] > b.v[j])
      return 1;
    if (this->v[j] < b.v[j])
      return -1;
  }

  return 0;
}

int BigInt::partial_comparison(const BigInt &b, int64_t start1, int64_t end1,
                               int64_t start2, int64_t end2) const {
  int64_t m = end1 - start1 + 1; // Size of this BigInt range
  int64_t n = end2 - start2 + 1; // Size of b's range

  // Check size differences first
  if (m > n)
    return 1;
  if (m < n)
    return -1;

  // Size matches; proceed with element-wise comparison
  int64_t len = m; // Total elements to compare

  // Compute reverse iterators
  auto it1 = (*this).v.rbegin() + ((*this).size() - end1 - 1);
  auto it2 = b.v.rbegin() + (b.size() - end2 - 1);

  const int chunk_size = 4; // NEON processes 4 elements at a time
  int64_t i = len - chunk_size;

  // Process elements in chunks of 4 using NEON
  for (; i >= 0; i -= chunk_size, it1 += chunk_size, it2 += chunk_size) {
    // Load 4 elements from both ranges
    uint32x4_t a_chunk = vld1q_u32(&(*it1));
    uint32x4_t b_chunk = vld1q_u32(&(*it2));

    // Compare a_chunk > b_chunk and a_chunk < b_chunk
    uint32x4_t a_gt_b = vcgtq_u32(a_chunk, b_chunk);
    uint32x4_t b_gt_a = vcgtq_u32(b_chunk, a_chunk);

    // Reduce results to a single value
    uint32_t any_a_gt_b = vmaxvq_u32(a_gt_b);
    uint32_t any_b_gt_a = vmaxvq_u32(b_gt_a);

    // Determine comparison outcome if there's a mismatch
    if (any_a_gt_b > 0)
      return 1; // This BigInt range is greater
    if (any_b_gt_a > 0)
      return -1; // b's range is greater
  }

  // Handle any remaining elements that didn't fit in chunks
  for (; i >= 0; --i, ++it1, ++it2) {
    if (*it1 > *it2)
      return 1;
    if (*it1 < *it2)
      return -1;
  }

  // All elements matched
  return 0;
}
