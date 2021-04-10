#include "../catch.hpp"
#include "../includer.h"

TEST_CASE("SUBTRACT + -","SUBTRACTION") {
    SECTION("|a|==|b|") {
        BigInt a("10",1);
        BigInt b("10",0);
        CHECK(BigInt("20",1)==a-b);

        a = BigInt("10",0);
        b = BigInt("10",1);
        CHECK(BigInt("20",0)==a-b);
    }

    SECTION("|a|>|b|") {
        BigInt a("17",1);
        BigInt b("9",0);
        CHECK(BigInt("26",1)==a-b);

        a = BigInt("17",0);
        b = BigInt("9",1);
        CHECK(BigInt("26",0)==a-b);
        
        a = BigInt("91",0);
        b = BigInt("55",1);
        CHECK(BigInt("146",0)==a-b);

        a = BigInt("91",1);
        b = BigInt("55",0);
        CHECK(BigInt("146",1)==a-b);

        a = BigInt("91",1);
        b = BigInt("19",0);
        CHECK(BigInt("110",1)==a-b);

        a = BigInt("91",0);
        b = BigInt("19",1);
        CHECK(BigInt("110",0)==a-b);
    }

    SECTION("|a|<|b|") {
        BigInt a("19",1);
        BigInt b("91",0);
        CHECK(BigInt("110",1)==a-b);

        a = BigInt("19",0);
        b = BigInt("91",1);
        CHECK(BigInt("110",0)==a-b);

        a = BigInt("0",1);
        b = BigInt("17",0);
        CHECK(BigInt("17",1)==a-b);

        a = BigInt("9",0);
        b = BigInt("17",1);
        CHECK(BigInt("26",0)==a-b);

        
    }
}

TEST_CASE("SUBTRACT + +","SUBTRACTION") {
    SECTION("|a|==|b|") {
        BigInt a("10",1);
        BigInt b("10",1);
        CHECK(BigInt("0",1)==a-b);

        a = BigInt("0",1);
        b = BigInt("0",1);
        CHECK(BigInt("0",1)==a-b);
    }

    SECTION("|a|>|b|") {
        BigInt a("91",1);
        BigInt b("19",1);
        CHECK(BigInt("72",1)==a-b);

        a = BigInt("17",1);
        b = BigInt("0",1);
        CHECK(BigInt("17",1)==a-b);

        a = BigInt("1000",1);
        b = BigInt("999",1);
        CHECK(BigInt("1",1)==a-b);

        a = BigInt("11556",1);
        b = BigInt("1773",1);
        CHECK(BigInt("9783",1)==a-b);
    }

    SECTION("|a|<|b|") {
        BigInt a("19",1);
        BigInt b("91",1);
        CHECK(BigInt("72",0)==a-b);

        a = BigInt("0",1);
        b = BigInt("17",1);
        CHECK(BigInt("17",0)==a-b);
    }
}

TEST_CASE("SUBTRACT - -","SUBTRACTION") {
    SECTION("|a|==|b|") {
        BigInt a("10",0);
        BigInt b("10",0);
        CHECK(BigInt("0",1)==a-b);

        a = BigInt("0",1);
        b = BigInt("0",1);
        CHECK(BigInt("0",1)==a-b);
    }

    SECTION("|a|>|b|") {
        BigInt a("91",0);
        BigInt b("19",0);
        CHECK(BigInt("72",0)==a-b);

        a = BigInt("17",0);
        b = BigInt("0",1);
        CHECK(BigInt("17",0)==a-b);
    }

    SECTION("|a|<|b|") {
        BigInt a("19",0);
        BigInt b("91",0);
        CHECK(BigInt("72",1)==a-b);

        a = BigInt("0",1);
        b = BigInt("17",0);
        CHECK(BigInt("17",1)==a-b);
    }
}
