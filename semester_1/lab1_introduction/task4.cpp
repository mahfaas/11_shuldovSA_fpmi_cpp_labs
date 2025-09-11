#include <iostream>

int main()
{
    int k;
    std::cout << "Enter k: ";
    if(!(std::cin >> k) || k < 0) 
    {
        std::cout << "Error!" << std::endl;
        return 0;
    }
    int i;
    if(k % 2 == 0)
        i = 2;
    else
        i = 1;
    long long fact = 1;
    for(; i <= k; i+=2)
        fact *= i;
    std::cout << "Factorial = " << fact << std::endl;
    return 0;
}