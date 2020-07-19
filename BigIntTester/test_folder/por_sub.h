
TEST(POR_SUB_SAME_A,same)
{
    BigInt a("10",1);
    BigInt b("10",1);
    EXPECT_EQ(BigInt("0",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_A,same1){
    BigInt a("19",1);
    BigInt b("91",1);
    EXPECT_EQ(BigInt("72",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_A,same2){
    BigInt a("91",1);
    BigInt b("19",1);
    EXPECT_EQ(BigInt("72",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_A,same3){
    BigInt a("0",1);
    BigInt b("17",1);
    EXPECT_EQ(BigInt("17",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_A,same4){
    BigInt a("17",1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("17",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_A,same5){
    BigInt a("0",1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("0",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_A,same6){
    BigInt a("1000",1);
    BigInt b("999",1);
    EXPECT_EQ(BigInt("1",1),a.por_sub_wrapper(a,b));
}


TEST(POR_SUB_SAME_B,same)
{
    BigInt a("10",-1);
    BigInt b("10",-1);
    EXPECT_EQ(BigInt("0",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_B,same1){
    BigInt a("19",-1);
    BigInt b("91",-1);
    EXPECT_EQ(BigInt("72",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_B,same2){
    BigInt a("91",-1);
    BigInt b("19",-1);
    EXPECT_EQ(BigInt("72",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_B,same3){
    BigInt a("0",1);
    BigInt b("17",-1);
    EXPECT_EQ(BigInt("17",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_B,same4){
    BigInt a("17",-1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("17",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_SAME_B,same5){
    BigInt a("0",1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("0",1),a.por_sub_wrapper(a,b));
}




TEST(POR_SUB_DIFF_A,same)
{
    BigInt a("10",1);
    BigInt b("10",-1);
    EXPECT_EQ(BigInt("20",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_A,same1){
    BigInt a("19",1);
    BigInt b("91",-1);
    EXPECT_EQ(BigInt("110",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_A,same2){
    BigInt a("91",1);
    BigInt b("19",-1);
    EXPECT_EQ(BigInt("110",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_A,same3){
    BigInt a("0",1);
    BigInt b("17",-1);
    EXPECT_EQ(BigInt("17",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_A,same4){
    BigInt a("17",1);
    BigInt b("9",-1);
    EXPECT_EQ(BigInt("26",1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_A,same5){
    BigInt a("91",1);
    BigInt b("55",-1);
    EXPECT_EQ(BigInt("146",1),a.por_sub_wrapper(a,b));
}




TEST(POR_SUB_DIFF_B,same)
{
    BigInt a("10",-1);
    BigInt b("10",1);
    EXPECT_EQ(BigInt("20",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_B,same1){
    BigInt a("19",-1);
    BigInt b("91",1);
    EXPECT_EQ(BigInt("110",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_B,same2){
    BigInt a("91",-1);
    BigInt b("19",1);
    EXPECT_EQ(BigInt("110",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_B,same3){
    BigInt a("9",-1);
    BigInt b("17",1);
    EXPECT_EQ(BigInt("26",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_B,same4){
    BigInt a("17",-1);
    BigInt b("9",1);
    EXPECT_EQ(BigInt("26",-1),a.por_sub_wrapper(a,b));
}

TEST(POR_SUB_DIFF_B,same5){
    BigInt a("91",-1);
    BigInt b("55",1);
    EXPECT_EQ(BigInt("146",-1),a.por_sub_wrapper(a,b));
}



