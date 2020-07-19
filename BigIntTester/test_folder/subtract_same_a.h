
TEST(SUBTRACT_SAME_A,same)
{
    BigInt a("10",1);
    BigInt b("10",1);
    EXPECT_EQ(BigInt("0",1),a-b);
}

TEST(SUBTRACT_SAME_A,same1){
    BigInt a("19",1);
    BigInt b("91",1);
    EXPECT_EQ(BigInt("72",-1),a-b);
}

TEST(SUBTRACT_SAME_A,same2){
    BigInt a("91",1);
    BigInt b("19",1);
    EXPECT_EQ(BigInt("72",1),a-b);
}

TEST(SUBTRACT_SAME_A,same3){
    BigInt a("0",1);
    BigInt b("17",1);
    EXPECT_EQ(BigInt("17",-1),a-b);
}

TEST(SUBTRACT_SAME_A,same4){
    BigInt a("17",1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("17",1),a-b);
}

TEST(SUBTRACT_SAME_A,same5){
    BigInt a("0",1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("0",1),a-b);
}

TEST(SUBTRACT_SAME_A,same6){
    BigInt a("1000",1);
    BigInt b("999",1);
    EXPECT_EQ(BigInt("1",1),a-b);
}

TEST(SUBTRACT_SAME_A,same7){
    BigInt a("11556",1);
    BigInt b("1773",1);
    EXPECT_EQ(BigInt("9783",1),a-b);
}