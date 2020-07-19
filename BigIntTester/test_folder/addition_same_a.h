
TEST(ADDITION_SAME_A,same)
{
    BigInt a("54",1);
    BigInt b("81",1);
    EXPECT_EQ(BigInt("135",1),a+b);
}

TEST(ADDITION_SAME_A,same1){
    BigInt a("19",1);
    BigInt b("91",1);
    EXPECT_EQ(BigInt("110",1),a+b);
}

TEST(ADDITION_SAME_A,same2){
    BigInt a("91",1);
    BigInt b("19",1);
    EXPECT_EQ(BigInt("110",1),a+b);
}

TEST(ADDITION_SAME_A,same3){
    BigInt a("0",1);
    BigInt b("17",1);
    EXPECT_EQ(BigInt("17",1),a+b);
}

TEST(ADDITION_SAME_A,same4){
    BigInt a("17",1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("17",1),a+b);
}

TEST(ADDITION_SAME_A,same5){
    BigInt a("111342563457640",1);
    BigInt b("425345245234530",1);
    EXPECT_EQ(BigInt("536687808692170",1),a+b);
}
TEST(ADDITION_SAME_A,same6){
    BigInt a("9909",1);
    BigInt b("998",1);
    EXPECT_EQ(BigInt("10907",1),a+b);
}



