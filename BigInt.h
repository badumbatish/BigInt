#pragma once
#include <string>
#include <vector>

class BigInt {
private:
  bool is_nonnegative = 1;
  std::vector<uint32_t> v;
  // BASE OF BigInt, meaing each entries in the vector = 2^32
  static constexpr uint32_t BASE = UINT32_MAX;
  static constexpr uint32_t LONG_MULT_SIZE = 1;

  BigInt &add(BigInt const &b);
  BigInt &subtract(BigInt const &b);

  BigInt range_add(const BigInt &b, int64_t start1, int64_t end1,
                   int64_t start2, int64_t end2) const;

  BigInt karatsuba_mult(BigInt const &b, int64_t start1, int64_t end1,
                        int64_t start2, int64_t end2) const;
  BigInt long_mult(BigInt const &b, int64_t start1, int64_t end1,
                   int64_t start2, int64_t end2) const;

  bool IsPos();
  bool IsNeg();
  bool IsSameSign(BigInt const &b, int c, int d) const {
    return (this->is_nonnegative == c && b.is_nonnegative == d);
  }

  inline BigInt &invert() {
    this->is_nonnegative = !this->is_nonnegative;
    return *this;
  }
  inline BigInt &minus() {
    this->is_nonnegative = 0;
    return *this;
  }
  inline BigInt &plus() {
    this->is_nonnegative = 1;
    return *this;
  }

public:
  BigInt(); // default constructor
  BigInt(BigInt const &);
  BigInt(BigInt &&);
  BigInt(std::string const &b, bool sign = 1,
         int base = 10); //  constructor#2 for string
  BigInt(uint32_t n, bool sign = 1);
  BigInt(std::vector<uint32_t> &&, bool sign = 1);

  BigInt &operator=(BigInt const &); // copy assignment operator
  BigInt &operator=(BigInt &&);      // move assignment operator

  ~BigInt();
  void print();
  size_t size() const;
  uint32_t operator[](size_t) const;

  BigInt operator+(BigInt const &b);
  BigInt operator-(BigInt const &b);
  BigInt operator*(BigInt const &b);
  bool operator==(BigInt const &b) const;

  BigInt &add(uint32_t n);
  BigInt &subtract(uint32_t n);
  BigInt &mult(uint32_t n);

  BigInt &operator*=(uint32_t n);
  BigInt &operator+=(uint32_t n);
  BigInt &operator-=(uint32_t n);

  bool operator>(int64_t n);
  bool operator>=(int64_t n);
  bool operator<(int64_t n);
  bool operator<=(int64_t n);
  bool operator==(int64_t n);

  int full_comparison(BigInt const &b) const;
  int partial_comparison(const BigInt &b, int64_t start1, int64_t end1,
                         int64_t start2, int64_t end2) const;
  bool operator>=(BigInt const &b);
  bool operator>(const BigInt &b);
  bool operator<(const BigInt &b);
  bool operator<=(const BigInt &b);

  BigInt &operator+=(BigInt const &b);
  BigInt &operator-=(BigInt const &b);
  BigInt &operator*=(BigInt &b);
  BigInt &operator/=(BigInt &b);

  friend std::ostream &operator<<(std::ostream &, const BigInt &);
};
