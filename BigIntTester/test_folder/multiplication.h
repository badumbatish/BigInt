TEST(MULTIPLICATION,same1){
    BigInt a("7",1);
    BigInt b("1",1);
    EXPECT_EQ(BigInt("7",1),a*b);
}

TEST(MULTIPLICATION,same2){
    BigInt a("7",1);
    BigInt b("1",-1);
    EXPECT_EQ(BigInt("7",-1),a*b);
}

TEST(MULTIPLICATION,same3){
    BigInt a("7",-1);
    BigInt b("1",1);
    EXPECT_EQ(BigInt("7",-1),a*b);
}

TEST(MULTIPLICATION,same4){
    BigInt a("7",-1);
    BigInt b("1",-1);
    EXPECT_EQ(BigInt("7",1),a*b);
}

TEST(MULTIPLICATION,same5){
    BigInt a("56",1);
    BigInt b("7",1);
    EXPECT_EQ(BigInt("392",1),a*b);
}

TEST(MULTIPLICATION,same6){
    BigInt a("56",1);
    BigInt b("7",-1);
    EXPECT_EQ(BigInt("392",-1),a*b);
}

TEST(MULTIPLICATION,same7){
    BigInt a("56",-1);
    BigInt b("7",1);
    EXPECT_EQ(BigInt("392",-1),a*b);
}

TEST(MULTIPLICATION,same8){
    BigInt a("56",-1);
    BigInt b("7",-1);
    EXPECT_EQ(BigInt("392",1),a*b);
}

TEST(MULTIPLICATION,same9){
    BigInt a("7",1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("0",1),a*b);
}

TEST(MULTIPLICATION,same10){
    BigInt a("7",-1);
    BigInt b("0",1);
    EXPECT_EQ(BigInt("0",1),a*b);
}

TEST(MULTIPLICATION,same11){
    BigInt a("0",1);
    BigInt b("7",-1);
    EXPECT_EQ(BigInt("0",1),a*b);
}

TEST(MULTIPLICATION,same12){
    BigInt a("0",1);
    BigInt b("7",1);
    EXPECT_EQ(BigInt("0",1),a*b);
}

TEST(MULTIPLICATION,same13){
    BigInt a("16",1);
    BigInt b("7",1);
    EXPECT_EQ(BigInt("112",1),a*b);
}

TEST(MULTIPLICATION,same14){
    BigInt a("34",1);
    BigInt b("77",1);
    EXPECT_EQ(BigInt("2618",1),a*b);
}

TEST(MULTIPLICATION,same15){
    BigInt a("9909",1);
    BigInt b("998",1);
    EXPECT_EQ(BigInt("9889182",1),a*b);
}

TEST(MULTIPLICATION,same16){
    BigInt a("250",1);
    BigInt b("250",1);
    EXPECT_EQ(BigInt("62500",1),a*b);
}


TEST(MULTIPLICATION,same17){
    BigInt a("123487333388",1);
    BigInt b("1",1);
    EXPECT_EQ(BigInt("123487333388",1),a*b);
}

TEST(MULTIPLICATION,same18){
    BigInt a("5",1);
    BigInt b("4",1);
    EXPECT_EQ(BigInt("20",1),a*b);
}

TEST(MULTIPLICATION,same19){
    BigInt a("3141592653589793238462643383279502884197169399375105820974944592",1);
    BigInt b("2718281828459045235360287471352662497757247093699959574966967627",1);
    EXPECT_EQ(BigInt("85397342226735670654635508695465744950348885357651149618796"
    "01127067743044893204848617875072216249073013374895871952806582723184",1),a*b);
}