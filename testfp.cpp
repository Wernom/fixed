
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

/*TEST(fixedTest, constructorCopy) {
    float x = 12.42;
    fp::fixed<8, 8> f(x);
    fp::fixed<8, 8> f1(f);
    EXPECT_EQ(f.value, f1.value);
    EXPECT_EQ(f.fractional_part, f1.fractional_part);
    EXPECT_EQ(f.integer_part, f1.integer_part);
}*/

//Test fixed<Int, Frac>::operator float() const
TEST(fixedTest, floatValue){
    double x = 12.42;
    fp::fixed<8,8> f(x);
    EXPECT_EQ(f.value, 3180);
    EXPECT_NEAR((float)(12.421875),float(f),0.2);
}

//Test fixed<Int, Frac>::operator double() const
TEST(fixedTest, doubleValue) {
    double x = 12.42;
    fp::fixed<8, 8> f(x);
    EXPECT_EQ(f.value, 3180);
    EXPECT_NEAR((double) (12.421875), float(f), 0.2);

}


//Test fixed &operator+=(const fixed &other);
TEST(fixedTest,plusEqualFixed){
    double x1 = 12.42;
    fp::fixed<8,8> f1(x1);
    double x2 = 12.42;
    fp::fixed<8,8> f2(x2);
    EXPECT_EQ( 3180+3180, (f1+=f2).value);

}


//Test fixed<Int, Frac> &fixed<Int, Frac>::operator+=(float other)
TEST(fixedTest,plusEqualFloat){
    double x1 = 12.42;
    fp::fixed<8,8> f1(x1);
    float x2 = 12.42;
    EXPECT_EQ( 3180+3180, (f1+=x2).value);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
