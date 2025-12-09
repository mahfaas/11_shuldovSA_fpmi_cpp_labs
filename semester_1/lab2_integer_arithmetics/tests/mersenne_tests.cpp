#include "gtest/gtest.h"
#include "../mersenne.h"
#include <vector>
#include <iostream>

TEST(MersenneTests, NormalRange)
{
    std::cout << ">>> START NORMAL RANGE TEST\n";   
    auto res = GetMersenneInRange(1, 20);
    std::vector<long long> expected = {1, 3, 7, 15};
    EXPECT_EQ(res, expected);
}


TEST(MersenneTests, NoNumbersInRange)
{
    auto res = GetMersenneInRange(2, 2);
    EXPECT_TRUE(res.empty());
}

TEST(MersenneTests, SingleBorderValue)
{
    auto res = GetMersenneInRange(7, 7);
    std::vector<long long> expected = {7};
    EXPECT_EQ(res, expected);
}

TEST(MersenneTests, LargeRange)
{
    auto res = GetMersenneInRange(1, 100);
    std::vector<long long> expected = {1, 3, 7, 15, 31, 63};
    EXPECT_EQ(res, expected);
}

TEST(MersenneTests, InvalidRange_A_Greater_Than_B)
{
    EXPECT_THROW(GetMersenneInRange(10, 5), std::invalid_argument);
}

TEST(MersenneTests, NegativeValues)
{
    EXPECT_THROW(GetMersenneInRange(-1, 10), std::invalid_argument);
    EXPECT_THROW(GetMersenneInRange(0, -5), std::invalid_argument);
}
