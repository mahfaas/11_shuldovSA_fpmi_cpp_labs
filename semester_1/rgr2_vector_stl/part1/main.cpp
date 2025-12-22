#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

void PrintVector(const std::vector<int> &v)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i != 0)
        {
            std::cout << ' ';
        }
        std::cout << v[i];
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> v;

    std::cout << "Enter integers (finish input with any non-integer symbol):\n";
    int x = 0;
    while (std::cin >> x)
    {
        v.push_back(x);
    }

    if (v.empty())
    {
        std::cout << "No numbers were entered.\n";
        return 1;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Vector: \n";
    PrintVector(v);

    long long sum = std::accumulate(v.begin(), v.end(), 0LL);
    std::cout << "Sum of numbers: " << sum << '\n';
    std::cout << "Total count of numbers: " << v.size() << '\n';

    int target = 0;
    std::cout << "Enter a number to count equals: ";
    std::cin >> target;
    std::cout << "Count of numbers equal to " << target << ": " << std::count(v.begin(), v.end(), target) << '\n';

    int n = 0;
    std::cout << "Enter n to count numbers greater than n: ";
    std::cin >> n;
    std::cout << "Count of numbers greater than " << n << ": " 
        << std::count_if(v.begin(), v.end(), [n](int value) { return value > n; }) << '\n';

    int mean = static_cast<int>(sum / static_cast<long long>(v.size()));
    std::replace_if(v.begin(), v.end(), [](int value)
                    { return value == 0; }, mean);
    std::cout << "Vector without 0's: \n";
    PrintVector(v);

    size_t l = 1;
    size_t r = 1;
    std::cout << "Enter interval l, r: ";
    std::cin >> l >> r;

    if (l < 1)
        l = 1;
    if (r < 1)
        r = 1;
    if (l > v.size())
        l = v.size();
    if (r > v.size())
        r = v.size();
    if (l > r)
        std::swap(l, r);

    long long interval_sum = std::accumulate(v.begin() + (l - 1), v.begin() + r, 0LL);
    std::transform(v.begin(), v.end(), v.begin(),
                [interval_sum](int value)
                   { return static_cast<int>(static_cast<long long>(value) + interval_sum); });
    std::cout << "Interval sum: " << interval_sum << '\n';
    PrintVector(v);

    auto mm = std::minmax_element(v.begin(), v.end());
    int diff = *mm.second - *mm.first;

    for (int &value : v)
    {
        if ((std::abs(value) % 2) == 0)
        {
            value = diff;
        }
    }
    std::cout << "Difference (max - min): " << diff << '\n';
    PrintVector(v);

    std::vector<int> result;
    result.reserve(v.size());
    std::vector<int> seen_abs;
    seen_abs.reserve(v.size());

    for (int value : v)
    {
        int a = std::abs(value);
        if (std::find(seen_abs.begin(), seen_abs.end(), a) == seen_abs.end())
        {
            seen_abs.push_back(a);
            result.push_back(value);
        }
    }

    v.swap(result);
    std::cout << "Vector without equals: \n";
    PrintVector(v);

    return 0;
}
