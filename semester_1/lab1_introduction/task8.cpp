#include <iostream>

int main() 
{
    double prev, cur, next;
    int k = 0;
    std::cout << "Enter 10 real numbers: " << std::endl;
    std::cin >> prev;
    std::cin >> cur;
    if(prev < cur)
        k++;
    for(int i = 2; i < 10; i++) 
    {
        std::cin >> next;
        if(cur < prev && cur < next) 
            k++;
        prev = cur;
        cur = next;
    }
    if(cur < prev) 
        k++;
    std::cout << "Number of elements less than their neighbors: " << k << std::endl;
    return 0;
}