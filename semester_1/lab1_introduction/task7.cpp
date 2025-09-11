#include <iostream>

int main()
{
    int n;
    std::cout << "Enter amount of numbers: ";
    if(!(std::cin >> n) || n < 0) 
    {
        std::cout << "Error!" << std::endl;
        return 0;
    }
    std::cout << "Enter sequence: " << std::endl;
    double sum, max = -10000000., min = 10000000.;
    for(int i = 0; i < n; i++)
    {
        double x;
        if(std::cin >> x)
        {
            sum += x;
            if(x > max)
                max = x;
            if(x < min)
                min = x;
        }
        else
        {
            std::cout << "Error!" << std::endl;
            return 0;
        }
    }
    std::cout << "Arithmetic mean = " << sum / (1. * n) << std::endl;
    std::cout << "Max = " << max << std::endl;
    std::cout << "Min = " << min << std::endl;
    return 0;
}