#include "../catch.hpp"
#include "../includer.h"

TEST_CASE("Different signs + -", "ADDITION") {
    SECTION("EQUAL ABSOLUTE") {
        BigInt a("10",1);
        BigInt b("10",-1);
        REQUIRE(BigInt("0",1) == a+b);

        a = BigInt("10",-1);
        b = BigInt("10",1);
        CHECK(BigInt("0",1)==a+b);
    }
    
    SECTION("a>b") {
        BigInt a("19",1);
        BigInt b("91",-1);
        CHECK(BigInt("72",-1) == a+b);

        a = BigInt("0",1);
        b = BigInt("17",-1);
        CHECK(BigInt("17",-1) == a+b);

        a = BigInt("17",1);
        b = BigInt("99",-1);
        CHECK(BigInt("82",-1) == a+b);

        a = BigInt("9",1);
        b = BigInt("10",-1);
        CHECK(BigInt("1",-1) == a+b);
    }
    

    SECTION("a<b") {
        BigInt a("19",-1);
        BigInt b("91",1);
        CHECK(BigInt("72",1)==a+b);

        a = BigInt("91",-1);
        b = BigInt("19",1);
        CHECK(BigInt("72",-1)==a+b);

        a = BigInt("17",-1);
        b = BigInt("0",1);
        CHECK(BigInt("17",-1)==a+b);

        a = BigInt("17",-1);
        b = BigInt("99",1);
        CHECK(BigInt("82",1)==a+b);

        a = BigInt("9",-1);
        b = BigInt("10",1);
        CHECK(BigInt("1",1)==a+b);
    }
}

TEST_CASE("SAME SIGN + +", "ADDITION") {
    
}

TEST_CASE("SAME SIGN - -", "ADDITION") {
    
}