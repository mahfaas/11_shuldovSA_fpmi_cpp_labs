#include <iostream>
#include <cmath>
#include <random>

int main()
{
    const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;
    if(n < 1 || n > MAX_SIZE)
    {
        std::cout << "Error! Invalid n" << std::endl;
        return 0;
    }
    int choice;
    std::cout << "Choose filling method: 1 - keyboard, 2 - random: ";
    std::cin >> choice;
    if(choice == 1)
    {
        std::cout << "Enter " << n << " integers:" << std::endl;
        for(int i = 0; i < n; i++)
            std::cin >> arr[i];
    }
    else if(choice == 2)
    {
        int a, b;
        std::cout << "Enter a and b (a <= b): ";
        std::cin >> a >> b;
        if(a > b)
        {
            std::cout << "Error!Invalid a, b" << std::endl;
            return 0;
        }
        std::mt19937 gen(45218965);
        std::uniform_int_distribution<> dis(a, b);
        for(int i = 0; i < n; i++)
            arr[i] = dis(gen);
    }
    else
    {
        std::cout << "Error! Invalid choice" << std::endl;
        return 0;
    }

    std::cout << "Array: ";
    for(int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    long long sum_odd = 0;
    for(int i = 0; i < n; i += 2)
        sum_odd += arr[i];
    std::cout << "Sum of elements with odd numbers: " << sum_odd << std::endl;

    int first_pos = -1, last_pos = -1;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > 0)
        {
            if(first_pos == -1) 
                first_pos = i;
            last_pos = i;
        }
    }
    long long product = 1;
    bool can_compute = false;
    if(first_pos != -1 && last_pos != -1 && first_pos < last_pos)
    {
        for(int i = first_pos + 1; i < last_pos; i++)
            product *= arr[i];
        can_compute = true;
    }
    if(can_compute)
        std::cout << "Product between first and last positive: " << product << std::endl;
    else

        std::cout << "Cannot compute product: not enough positive elements" << std::endl;

    int N;
    std::cout << "Enter N: ";
    std::cin >> N;
    int new_n = 0;
    for(int i = 0; i < n; i++)
    {
        if(std::abs(arr[i]) >= N)
            arr[new_n++] = arr[i];
    }
    for(int i = new_n; i < n; i++)
        arr[i] = 0;

    std::cout << "Array after compression: ";
    for(int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}