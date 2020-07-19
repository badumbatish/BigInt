
TEST(ADDITION_DIFF_B,same)
{
    BigInt a("10",-1);
    BigInt b("10",1);
    EXPECT_EQ(BigInt("0",1),a+b);
}

TEST(ADDITION_DIFF_B,same1){
    BigInt a("19",-1);
    BigInt b("91",1);
    EXPECT_EQ(BigInt("72",1),a+b);
}

TEST(ADDITION_DIFF_B,same2){
    BigInt a("91",-1);
    BigInt b("19",1);
    EXPECT_EQ(BigInt("72",-1),a+b);
}

TEST(ADDITION_DIFF_B,same3){
    BigInt a("17",-1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("17",-1),a+b);
}

TEST(ADDITION_DIFF_B,same4){
    BigInt a("17",-1);
    BigInt b("99",1);
    EXPECT_EQ(BigInt("82",1),a+b);
}

TEST(ADDITION_DIFF_B,same5){
    BigInt a("9",-1);
    BigInt b("10",1);
    EXPECT_EQ(BigInt("1",1),a+b);
}


