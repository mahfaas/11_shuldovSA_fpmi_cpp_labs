#include <iostream>

const int MAX_N = 1000;

void sortBuble(int* a, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            if(std::abs(a[i]) > std::abs(a[j]))
                std::swap(a[i], a[j]);
        }
    }
}

bool enterArray(int* a, int n)
{
    for(int i = 0; i < n; i++)
    {
        int x;
        if(!(std::cin >> x))
            return false;
        a[i] = x;
    }
    return true;
}

int main()
{
    std::cout << "Enter size of array - ";
    int n;
    std::cin >> n;
    std::cout << "Enter array: " << std::endl;
    int mas[MAX_N];
    if(!enterArray(mas, n))
    {
        std::cout << "Error!" << std::endl;
        return 0;
    }
    std::cout << "Array before: " << std::endl;
    for(int i = 0; i < n; i++)
        std::cout << mas[i] << " ";
    std::cout << std::endl;  
    sortBuble(mas, n);
    std::cout << "Sorted array: " << std::endl;
    for(int i = 0; i < n; i++)
        std::cout << mas[i] << " ";
    std::cout << std::endl;
    return 0;
}