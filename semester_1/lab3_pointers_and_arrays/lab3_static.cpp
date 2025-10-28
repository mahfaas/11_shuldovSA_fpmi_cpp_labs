#include <iostream>
#include <cmath>
#include <random>
#include <stdexcept>

const int MAX_SIZE = 100;

bool safeInput(int &x)
{
    std::cin >> x;
    if(std::cin.fail())
    {
        std::cout << "Error! Input must be a number." << std::endl;
        return false;
    }
    return true;
}

void keyboardEnter(int* arr, int n)
{
    std::cout << "Enter " << n << " integers:" << std::endl;
    for(int i = 0; i < n; ++i)
    {
        if(!safeInput(arr[i]))
        {
            std::cout << "Error! Invalid input for array element." << std::endl;
            return;
        }
    }
}

void readRange(int &a, int &b)
{
    std::cout << "Enter a and b (a <= b): ";
    if(!safeInput(a) || !safeInput(b))
    {
        throw std::runtime_error("Error! Invalid input for range.");
    }
    if(a > b)
    {
        throw std::runtime_error("Error! Invalid range: a > b.");
    }
}

void randEnter(int* arr, int n, int a, int b, std::mt19937 &gen)
{
    std::uniform_int_distribution<> dis(a, b);
    for(int i = 0; i < n; i++)
    {
        arr[i] = dis(gen);
    }
}

void printArray(const int* arr, int n)
{
    for(int i = 0; i < n; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

long long sumOddIndex(const int* arr, int n)
{
    long long sum_odd = 0;
    for(int i = 0; i < n; i += 2)
    {
        sum_odd += arr[i];
    }
    return sum_odd;
}

long long productBetweenPositives(const int* arr, int n)
{
    int first_pos = -1, last_pos = -1;
    for(int i = 0; i < n; ++i)
    {
        if(arr[i] > 0)
        {
            if(first_pos == -1)
            {
                first_pos = i;
            }
            last_pos = i;
        }
    }

    if(first_pos == -1)
    {
        throw std::runtime_error("Error! No positive elements found.");
    }
    if(first_pos == last_pos)
    {
        throw std::runtime_error("Error! Only one positive element found.");
    }
    if(last_pos - first_pos == 1)
    {
        throw std::runtime_error("Error! Positive elements are adjacent.");
    }

    long long product = 1;
    for(int i = first_pos + 1; i < last_pos; i++)
    {
        product *= arr[i];
    }
    return product;
}

void compressArray(int* arr, int n, int N)
{
    int new_n = 0;
    for(int i = 0; i < n; ++i)
    {
        if(std::abs(arr[i]) >= N)
        {
            arr[new_n++] = arr[i];
        }
    }
    for(int i = new_n; i < n; ++i)
    {
        arr[i] = 0;
    }
}

int main()
{
    int arr[MAX_SIZE];
    int n;
    std::cout << "Enter the number of elements: ";
    if(!safeInput(n))
    {
        return 0;
    }
    if(n < 1 || n > MAX_SIZE)
    {
        std::cout << "Error! Invalid n" << std::endl;
        return 0;
    }

    std::mt19937 gen(45218965);

    std::cout << "Choose filling method: 1 - keyboard, 2 - random: ";
    int choice;
    if(!safeInput(choice))
    {
        return 0;
    }

    switch(choice)
    {
        case 1:
        {
            keyboardEnter(arr, n);
            break;
        }
        case 2:
        {
            int a, b;
            try
            {
                readRange(a, b);
            }
            catch(const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                return 0;
            }
            randEnter(arr, n, a, b, gen);
            break;
        }
        default:
        {
            std::cout << "Error! Invalid choice" << std::endl;
            return 0;
        }
    }

    std::cout << "Array: ";
    printArray(arr, n);

    long long sum_odd = sumOddIndex(arr, n);
    std::cout << "Sum of elements with odd numbers: " << sum_odd << std::endl;

    try
    {
        long long product = productBetweenPositives(arr, n);
        std::cout << "Product between first and last positive: " << product << std::endl;
    }
    catch(const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    int N;
    std::cout << "Enter N: ";
    if(!safeInput(N))
    {
        return 0;
    }
    compressArray(arr, n, N);

    std::cout << "Array after compression: ";
    printArray(arr, n);

    return 0;
}
