#include <iostream>

int main()
{
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    int sum = 0, mult = 1;
    for(int i = 1; i <= n; i++)
    {
        if(i % 2 == 0)
            sum += i;
        else
            mult *= i;
    }
    std::cout << "Sum - " << sum << std::endl;
    std::cout << "Product - " << mult << std::endl;
    return 0;
}