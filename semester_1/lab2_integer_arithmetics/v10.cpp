#include <iostream>

int main() 
{
    long long a, b;
    std::cout << "Enter a and b: " << std::endl;
    if(!(std::cin >> a >> b) || a < 0 || b < 0 || a > b)
    {
        std::cout << "Error!" << std::endl;
        return 0;
    }
    long long cur = 1; 
    bool f = false;
    while(true) 
    {
        if(cur >= a && cur <= b) 
        {
            std::cout << cur << " ";
            f = true;
        }
        cur = 2 * cur + 1;
        if(cur > b) 
            break;
    }
    if(!f) 
        std::cout << "No Mersenne numbers in the range(" << std::endl;
    return 0;
}