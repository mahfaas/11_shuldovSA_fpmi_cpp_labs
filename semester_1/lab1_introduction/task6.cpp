#include <iostream>

int main()
{
    int n;
    std::cout << "Enter n: ";
    if(!(std::cin >> n) || n <= 0) 
    {
        std::cout << "Error!" << std::endl;
        return 0;
    }
    int sum = 0;
    for(int i = 1; i <= 2 * n; i += 2)
        sum += i;
    std::cout << "Sum = " << sum << std::endl;
    return 0;
}