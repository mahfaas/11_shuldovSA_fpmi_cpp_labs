#include "mersenne.h"
#include <stdexcept>


std::vector<long long> GetMersenneInRange(long long a, long long b)
{
    if (a < 0 || b < 0 || a > b)
    {
        throw std::invalid_argument("Invalid range");
    }

    std::vector<long long> result;
    long long cur = 1;

    while (cur <= b)
    {
        if (cur >= a)
        {
            result.push_back(cur);
        }

        if (cur > (__LONG_LONG_MAX__ - 1) / 2)
            break;

        cur = 2 * cur + 1;
    }

    return result;
}
