
#include "gtest/gtest.h"
#include "fixed.h"

class AutomatonTestFixture : public ::testing::Test {

};

//Test constexpr explicit fixed(float x);
TEST(fixedTest, constructorFloat) {
    float x = 12.42;
    fp::fixed<8, 8> f(x);
    EXPECT_EQ(f.value, 3180);
}

//Test constexpr explicit fixed(double x);
TEST(fixedTest, constructorDouble) {
    double x = 12.42;
    fp::fixed<8, 8> f(x);
    EXPECT_EQ(f.value, 3180);
}

//Test fixed<Int, Frac>::fixed(const fixed &other)
TEST(fixedTest, constructorCopy) {
    float x = 12.42;
    fp::fixed<8, 8> f(x);
    fp::fixed<8, 8> f1(f);
    EXPECT_EQ(f.value, f1.value);
    EXPECT_TRUE(f1.fractional_part ==
                f.fractional_part);//We use EXPECT_TRUE insteed of EXPECT_EQ because it return the error: référence indéfinie vers « fp::fixed<8ul, 8ul>::fractional_part »
    EXPECT_TRUE(f1.integer_part == f.integer_part);
}

//Test &fixed<Int, Frac>::operator=(const fixed &other)
TEST(fixedTest, affectationSameFractionalAndInteger) {
    fp::fixed<8, 8> f1(12.34);
    fp::fixed<8, 8> f2(13.24);

    f1 = f2;

    EXPECT_EQ(f1.value, f2.value);
    EXPECT_EQ(double(f1), double(f2));
}

TEST(fixedTest, affectationDifferentFractionalAndInteger) {
    fp::fixed<8, 12> f1(12.34);
    fp::fixed<8, 8> f2(13.24);

    f1 = f2;

    EXPECT_EQ(double(f1), double(f2));
}

//Test fixed<Int, Frac>::operator float() const
TEST(fixedTest, floatValue) {
    double x = 12.42;
    fp::fixed<8, 8> f(x);
    EXPECT_EQ(f.value, 3180);
    EXPECT_NEAR((float) (12.421875), float(f), 0.2);

}

//Test fixed<Int, Frac>::operator double() const
TEST(fixedTest, doubleValue) {
    double x = 12.42;
    fp::fixed<8, 8> f(x);
    EXPECT_EQ(f.value, 3180);
    EXPECT_NEAR(double(12.421875), double(f), 0.2);
}


//Test fixed &operator+=(const fixed &other);
TEST(fixedTest, plusEqualFixed) {
    double x1 = 12.42;
    fp::fixed<8, 8> f1(x1);
    double x2 = 12.42;
    fp::fixed<8, 8> f2(x2);
    EXPECT_EQ(3180 + 3180, (f1 += f2).value);

}

//Test fixed &operator+=(const fixed &other) not same int;
TEST(fixedTest, plusEqualFixedDifferentInt) {
    double x1 = 12.42;
    fp::fixed<13, 8> f1(x1);
    double x2 = 12.42;
    fp::fixed<8, 8> f2(x2);
    f1 += f2;
    EXPECT_EQ(3180 + 3180, f1.value);
}

//Test fixed &operator+=(const fixed &other) not same frac OVERFLOW
TEST(fixedTest, plusEqualFixedDifferentFracOver) {
    double x1 = 12.42;
    fp::fixed<8, 13> f1(x1);
    double x2 = 12.42;
    fp::fixed<8, 8> f2(x2);
    EXPECT_THROW(f1 += f2, std::overflow_error);
}


//Test fixed &operator+=(const fixed &other) not same frac Not overflow;
TEST(fixedTest, plusEqualFixedDifferentFrac) {
    double x1 = 12.42;
    fp::fixed<8, 4> f1(x1);
    double x2 = 12.42;
    fp::fixed<8, 8> f2(x2);
    f1 += f2;
    EXPECT_EQ(199 + 3180, f1.value);
}


//Test fixed<Int, Frac> &fixed<Int, Frac>::operator+=(float other)
TEST(fixedTest, plusEqualFloat) {
    double x1 = 12.42;
    fp::fixed<8, 8> f1(x1);
    float x2 = 12.42;
    EXPECT_EQ(3180 + 3180, (f1 += x2).value);

}

//Test fixed<Int, Frac> &fixed<Int, Frac>::operator+=(double other)
TEST(fixedTest, plusEqualDouble) {
    double x1 = 12.42;
    fp::fixed<8, 8> f1(x1);
    double x2 = 12.42;
    EXPECT_EQ(3180 + 3180, (f1 += x2).value);
}

//Test fixed<Int, Frac> &fixed<Int, Frac>::operator-=(double other)
TEST(fixedTest, moinsEqualDouble) {
    double x1 = 12.42;
    fp::fixed<8, 8> f1(x1);
    double x2 = 12.42;
    fp::fixed<8, 8> f2(x2);
    EXPECT_EQ(0, (f1 -= f2).value);

}

//Test fixed<Int, Frac> &fixed<Int, Frac>::operator-=(double other)
TEST(fixedTest,toString){
    double x1=12.42;
    fp::fixed<8,8> f1(x1);
    std::string myString=fp::to_string(f1);
    std::cout<< myString << std::endl;
    EXPECT_TRUE(true);
}

//Test fixed<std::max(I1, I2), std::max(F1, F2)> operator+(fixed<I1, F1> lhs, fixed<I2, F2> rhs)
TEST(fixedTest, plus) {
    fp::fixed<8, 8> f1(1.111);
    fp::fixed<8, 8> f2(2.22);
    f2 = f1 + f2;

    EXPECT_NEAR((double) (3.33), float(f2), 0.05);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
