#include <iostream>
#include "mersenne.h"

int main()
{
    long long a, b;
    std::cout << "Enter a and b: " << std::endl;

    if (!(std::cin >> a >> b))
    {
        std::cout << "Error!" << std::endl;
        return 0;
    }

    try
    {
        auto res = GetMersenneInRange(a, b);

        if (res.empty())
        {
            std::cout << "No Mersenne numbers in the range" << std::endl;
        }
        else
        {
            for (long long x : res)
                std::cout << x << " ";
            std::cout << std::endl;
        }
    }
    catch (const std::invalid_argument &)
    {
        std::cout << "Error!" << std::endl;
    }

    return 0;
}
