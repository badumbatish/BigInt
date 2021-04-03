#include "../catch.hpp"
#include "../includer.h"

TEST_CASE("ADDITION", "a") {
    BigInt a("10",1);
    BigInt b("10",-1);
    bool exp = (BigInt("0",1) == (a+b));
    REQUIRE(exp);
}