#include "testfp.h"
#include "gtest/gtest.h"
#include "fixed.h"

class AutomatonTestFixture : public ::testing::Test {

};

//Test constexpr explicit fixed(float x);
TEST(fixedTest, constructorFloat){
    float x = 12.42;
    fp::fixed<8,8> f(x);
    EXPECT_EQ(f.value, 3180);
}

//Test constexpr explicit fixed(double x);
TEST(fixedTest, constructorDouble){
    double x = 12.42;
    fp::fixed<8,8> f(x);
    EXPECT_EQ(f.value, 3180);
}


//Test fixed<Int, Frac>::operator float() const
TEST(fixedTest, floatValue){
    double x = 12.42;
    fp::fixed<8,8> f(x);
    EXPECT_EQ(f.value, 3180);
    EXPECT_NEAR((float)(12.421875),float(f),0.2);

}

//Test fixed<Int, Frac>::operator double() const
TEST(fixedTest, doubleValue){
    double x = 12.42;
    fp::fixed<8,8> f(x);
    EXPECT_EQ(f.value, 3180);
    EXPECT_NEAR((double)(12.421875),float(f),0.2);

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
