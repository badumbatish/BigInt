#include "../catch.hpp"
#include "../includer.h"

TEST_CASE("PROPORTIONAL ADDITION + -, - +", "por_add") {
    SECTION("|a|==|b|") {
        BigInt a("10",1);
        BigInt b("10",-1);
        CHECK(BigInt("0",1)==a.por_add_wrapper(a,b));

        a = BigInt("10",-1);
        b = BigInt("10",1);
        CHECK(BigInt("0",1)==a.por_add_wrapper(a,b));
    }

    SECTION("|a|>|b|") {
        BigInt a("91",1);
        BigInt b("19",-1);
        CHECK(BigInt("72",1)==a.por_add_wrapper(a,b));
            
        a = BigInt("91",-1);
        b = BigInt("19",1);
        CHECK(BigInt("72",-1)==a.por_add_wrapper(a,b));

        a = BigInt("17",-1);
        b = BigInt("0",1);
        CHECK(BigInt("17",-1)==a.por_add_wrapper(a,b));
    }

    SECTION("|a|<|b|") {
        BigInt a("19",1);
        BigInt b("91",-1);
        CHECK(BigInt("72",-1)==a.por_add_wrapper(a,b));

        a = BigInt("19",-1);
        b = BigInt("91",1);
        CHECK(BigInt("72",1)==a.por_add_wrapper(a,b));

        a = BigInt("0",1);
        b = BigInt("17",-1);
        CHECK(BigInt("17",-1)==a.por_add_wrapper(a,b));

        a = BigInt("17",1);
        b = BigInt("99",-1);
        CHECK(BigInt("82",-1)==a.por_add_wrapper(a,b));

        a = BigInt("9",1);
        b = BigInt("10",-1);
        CHECK(BigInt("1",-1)==a.por_add_wrapper(a,b));

        a = BigInt("17",-1);
        b = BigInt("99",1);
        CHECK(BigInt("82",1)==a.por_add_wrapper(a,b));

        a = BigInt("9",-1);
        b = BigInt("10",1);
        CHECK(BigInt("1",1)==a.por_add_wrapper(a,b));
    }
}

TEST_CASE("PROPORTIONAL ADDITION + +", "por_add") {
    SECTION("|a|==|b|") {
        BigInt a("99",1);
        BigInt b("99",1);
        CHECK(BigInt("198",1)==a.por_add_wrapper(a,b));
    }

    SECTION("|a|>|b|") {
        BigInt a("91",1);
        BigInt b("19",1);
        CHECK(BigInt("110",1)==a.por_add_wrapper(a,b));

        a = BigInt("17",1);
        b = BigInt("0",1);
        CHECK(BigInt("17",1)==a.por_add_wrapper(a,b));

        a = BigInt("9909",1);
        b = BigInt("998",1);
        CHECK(BigInt("10907",1)==a.por_add_wrapper(a,b));
    }

    SECTION("|a|<|b|") {
        BigInt a("54",1);
        BigInt b("81",1);
        CHECK(BigInt("135",1)==a.por_add_wrapper(a,b));

        a = BigInt("0",1);
        b = BigInt("17",1);
        CHECK(BigInt("17",1)==a.por_add_wrapper(a,b));

        a = BigInt("111342563457640",1);
        b = BigInt("425345245234530",1);
        CHECK(BigInt("536687808692170",1)==a.por_add_wrapper(a,b));
    }
}

TEST_CASE("PROPORTIONAL ADDITION - -", "por_add") {
    SECTION("|a|==|b|") {
        BigInt a("10",-1);
        BigInt b("10",-1);
        CHECK(BigInt("20",-1)==a.por_add_wrapper(a,b));
    }

    SECTION("|a|>|b|") {
        BigInt a("91",-1);
        BigInt b("19",-1);
        CHECK(BigInt("110",-1)==a.por_add_wrapper(a,b));

        a = BigInt("17",-1);
        b = BigInt("0",1);
        CHECK(BigInt("17",-1)==a.por_add_wrapper(a,b));
    }

    SECTION("|a|<|b|") {
        BigInt a("19",-1);
        BigInt b("91",-1);
        CHECK(BigInt("110",-1)==a.por_add_wrapper(a,b));

        a = BigInt("0",1);
        b = BigInt("17",-1);
        CHECK(BigInt("17",-1)==a.por_add_wrapper(a,b));

        a = BigInt("9",-1);
        b = BigInt("10",-1);
        CHECK(BigInt("19",-1)==a.por_add_wrapper(a,b));
    }
}