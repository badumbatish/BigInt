#include "BigInt.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Multiplcation + -, - +", "multiplication") {
  SECTION("|a|==|b|") {}

  SECTION("|a|>|b|") {
    BigInt a("7", 1);
    BigInt b("1", 0);
    CHECK(BigInt("7", 0) == a * b);

    a = BigInt("7", 0);
    b = BigInt("1", 1);
    CHECK(BigInt("7", 0) == a * b);

    a = BigInt("56", 1);
    b = BigInt("7", 0);
    CHECK(BigInt("392", 0) == a * b);

    a = BigInt("56", 0);
    b = BigInt("7", 1);
    CHECK(BigInt("392", 0) == a * b);

    a = BigInt("7", 0);
    b = BigInt("0", 1);
    CHECK(BigInt("0", 1) == a * b);
  }

  SECTION("|a|<|b|") {
    BigInt a("0", 1);
    BigInt b("7", 0);
    CHECK(BigInt("0", 1) == a * b);
  }
}

TEST_CASE("Multiplcation + +", "multiplication") {
  SECTION("|a|==|b|") {
    BigInt a("250", 1);
    BigInt b("250", 1);
    CHECK(BigInt("62500", 1) == a * b);
  }

  SECTION("|a|>|b|") {
    BigInt a("7", 1);
    BigInt b("1", 1);
    CHECK(BigInt("7", 1) == a * b);

    a = BigInt("56", 1);
    b = BigInt("7", 1);
    CHECK(BigInt("392", 1) == a * b);

    a = BigInt("7", 1);
    b = BigInt("0", 1);
    CHECK(BigInt("0", 1) == a * b);

    a = BigInt("16", 1);
    b = BigInt("7", 1);
    CHECK(BigInt("112", 1) == a * b);

    a = BigInt("9909", 1);
    b = BigInt("998", 1);
    CHECK(BigInt("9889182", 1) == a * b);

    a = BigInt("123487333388", 1);
    b = BigInt("1", 1);
    CHECK(BigInt("123487333388", 1) == a * b);

    a = BigInt("5", 1);
    b = BigInt("4", 1);
    CHECK(BigInt("20", 1) == a * b);

    a = BigInt(
        "3141592653589793238462643383279502884197169399375105820974944592", 1);
    b = BigInt(
        "2718281828459045235360287471352662497757247093699959574966967627", 1);
    auto c = a * b;
    std::cerr
        << BigInt(
               "8539734222673567065463550869546574495034888535765114961879601"
               "12706774304489320484861787507221624907301337489587195280658"
               "2723184",
               1)
        << std::endl;
    std::cerr << c << std::endl;
    CHECK(BigInt("8539734222673567065463550869546574495034888535765114961879601"
                 "12706774304489320484861787507221624907301337489587195280658"
                 "2723184",
                 1) == c);
  }

  SECTION("|a|<|b|") {
    BigInt a("0", 1);
    BigInt b("7", 1);
    CHECK(BigInt("0", 1) == a * b);

    a = BigInt("34", 1);
    b = BigInt("77", 1);
    CHECK(BigInt("2618", 1) == a * b);
  }
}

TEST_CASE("Multiplcation - -", "multiplication") {
  SECTION("|a|==|b|") {}

  SECTION("|a|>|b|") {
    BigInt a("7", 0);
    BigInt b("1", 0);
    CHECK(BigInt("7", 1) == a * b);

    a = BigInt("56", 0);
    b = BigInt("7", 0);
    CHECK(BigInt("392", 1) == a * b);
  }

  SECTION("|a|<|b|") {}
}
