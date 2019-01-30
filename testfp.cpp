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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
