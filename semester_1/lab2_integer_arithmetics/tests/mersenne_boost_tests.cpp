#define BOOST_TEST_MODULE MersenneBoostTests
#include <boost/test/included/unit_test.hpp>

#include "../mersenne.h"
#include <vector>
#include <stdexcept>

BOOST_AUTO_TEST_CASE(NormalRange)
{
    auto res = GetMersenneInRange(1, 20);
    std::vector<long long> expected = {1, 3, 7, 15};
    BOOST_CHECK(res == expected);
}

BOOST_AUTO_TEST_CASE(NoNumbersInRange)
{
    auto res = GetMersenneInRange(2, 2);
    BOOST_CHECK(res.empty());
}

BOOST_AUTO_TEST_CASE(SingleBorderValue)
{
    auto res = GetMersenneInRange(7, 7);
    std::vector<long long> expected = {7};
    BOOST_CHECK(res == expected);
}

BOOST_AUTO_TEST_CASE(LargeRange)
{
    auto res = GetMersenneInRange(1, 100);
    std::vector<long long> expected = {1, 3, 7, 15, 31, 63};
    BOOST_CHECK(res == expected);
}

BOOST_AUTO_TEST_CASE(InvalidRange_A_Greater_Than_B)
{
    BOOST_CHECK_THROW(GetMersenneInRange(10, 5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(NegativeValues)
{
    BOOST_CHECK_THROW(GetMersenneInRange(-1, 10), std::invalid_argument);
    BOOST_CHECK_THROW(GetMersenneInRange(0, -5), std::invalid_argument);
}
