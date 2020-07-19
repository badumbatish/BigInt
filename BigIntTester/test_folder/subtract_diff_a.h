
TEST(SUBTRACT_DIFF_A,same)
{
    BigInt a("10",1);
    BigInt b("10",-1);
    EXPECT_EQ(BigInt("20",1),a-b);
}

TEST(SUBTRACT_DIFF_A,same1){
    BigInt a("19",1);
    BigInt b("91",-1);
    EXPECT_EQ(BigInt("110",1),a-b);
}

TEST(SUBTRACT_DIFF_A,same2){
    BigInt a("91",1);
    BigInt b("19",-1);
    EXPECT_EQ(BigInt("110",1),a-b);
}

TEST(SUBTRACT_DIFF_A,same3){
    BigInt a("0",1);
    BigInt b("17",-1);
    EXPECT_EQ(BigInt("17",1),a-b);
}

TEST(SUBTRACT_DIFF_A,same4){
    BigInt a("17",1);
    BigInt b("9",-1);
    EXPECT_EQ(BigInt("26",1),a-b);
}

TEST(SUBTRACT_DIFF_A,same5){
    BigInt a("91",1);
    BigInt b("55",-1);
    EXPECT_EQ(BigInt("146",1),a-b);
}



