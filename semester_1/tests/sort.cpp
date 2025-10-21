#include <iostream>

const int MAX_N = 1000;

void sortBubble(int* a, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(a[j] > a[j + 1])
                std::swap(a[j], a[j + 1]);
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
    sortBubble(mas, n);
    std::cout << "Sorted array: " << std::endl;
    for(int i = 0; i < n; i++)
        std::cout << mas[i] << " ";
    std::cout << std::endl;
    return 0;
}