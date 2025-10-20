#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip>

int main()
{
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;
    if(n < 1)
    {
        std::cout << "Error! Invalid n" << std::endl;
        return 0;
    }

    double* arr = new double[n];

    int choice;
    std::cout << "Choose filling method: 1 - keyboard, 2 - random: ";
    std::cin >> choice;
    if(choice == 1)
    {
        std::cout << "Enter " << n << " floats:" << std::endl;
        for(int i = 0; i < n; i++)
            std::cin >> arr[i];
    }
    else if(choice == 2)
    {
        double a, b;
        std::cout << "Enter a and b (a <= b): ";
        std::cin >> a >> b;
        if(a > b)
        {
            std::cout << "Error! Invalid a, b" << std::endl;
            delete[] arr;
            return 0;
        }
        
        std::mt19937 gen(45218965);
        std::uniform_real_distribution<> dis(a, b);
        for(int i = 0; i < n; i++)
            arr[i] = dis(gen);
    }
    else
    {
        std::cout << "Error! Invalid choice" << std::endl;
        delete[] arr;
        return 0;
    }

    std::cout << "Array: ";
    for(int i = 0; i < n; i++)
        std::cout << std::fixed << std::setprecision(2) << arr[i] << " ";
    std::cout << std::endl;

    double* sorted_arr = new double[n];
    for(int i = 0; i < n; i++)
        sorted_arr[i] = arr[i];
    std::sort(sorted_arr, sorted_arr + n);
    int distinct = 1;
    if(n > 0)
    {
        for(int i = 1; i < n; i++)
        {
            if(sorted_arr[i] != sorted_arr[i-1])
                distinct++;
        }
    }
    else
        distinct = 0;
    std::cout << "Number of distinct elements: " << distinct << std::endl;
    delete[] sorted_arr;

    int max_abs_idx = 0;
    double max_abs = std::abs(arr[0]);
    for(int i = 1; i < n; i++)
    {
        if(std::abs(arr[i]) > max_abs)
        {
            max_abs = std::abs(arr[i]);
            max_abs_idx = i;
        }
    }
    double product = 1.0;
    bool can_compute = false;
    if(max_abs_idx < n - 1)
    {
        for(int i = max_abs_idx + 1; i < n; i++)
            product *= arr[i];
        can_compute = true;
    }
    if(can_compute)
        std::cout << "Product after max abs element: " << std::fixed << std::setprecision(2) << product << std::endl;
    else
        std::cout << "Cannot compute product: max abs is the last element" << std::endl;

    double* new_arr = new double[n];
    int idx = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] < 0)
            new_arr[idx++] = arr[i];
    }
    for(int i = 0; i < n; i++)
    {
        if(arr[i] >= 0)
            new_arr[idx++] = arr[i];
    }
    delete[] arr;
    arr = new_arr;

    std::cout << "Array after transformation: ";
    for(int i = 0; i < n; i++)
        std::cout << std::fixed << std::setprecision(2) << arr[i] << " ";
    std::cout << std::endl;

    delete[] arr;
    return 0;   
}