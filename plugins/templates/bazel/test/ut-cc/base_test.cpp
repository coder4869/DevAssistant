#include "base_test.h"
#include <gtest/gtest.h>

class TestDemo : public ::testing::Test {
public:
    TestDemo() : base_test() { }
    ~TestDemo() { }

    void SetUp() override { }
    void TearDown() override { }

    BaseTest base_test;
};


TEST(BaseTest, Base) {
    EXPECT_LT(0, 1);
}

TEST_F(TestDemo, Base) {
    EXPECT_EQ(1, 1);
}

TEST_F(TestDemo, Skip) {
    GTEST_SKIP() << "Skip TestDemo.Skip";
    EXPECT_GT(2, 1);
}
