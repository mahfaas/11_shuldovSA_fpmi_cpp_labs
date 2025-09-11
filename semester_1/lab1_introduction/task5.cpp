#include <iostream>

int main()
{
    int n, m;
    std::cout << "Enter n and m: ";
    if(!(std::cin >> n >> m) || n <= 0 || m <= 0) 
    {
        std::cout << "Error!" << std::endl;
        return 0;
    }
    for(int i = 2; i <= std::min(n, m); i++)
    {
        if(n % i == 0 && m % i == 0)
            std::cout << i << " ";
    }
    return 0;
}