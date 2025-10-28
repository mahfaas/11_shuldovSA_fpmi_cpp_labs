#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <stdexcept>

bool safeInput(double &x)
{
    std::cin >> x;
    if(std::cin.fail())
    {
        std::cout << "Error! Input must be a number." << std::endl;
        return false;
    }
    return true;
}

bool safeInputInt(int &x)
{
    std::cin >> x;
    if(std::cin.fail())
    {
        std::cout << "Error! Input must be an integer." << std::endl;
        return false;
    }
    return true;
}

void merge(double* a, int left, int mid, int right, double* temp)
{
    int i = left;
    int j = mid;
    int k = left;

    while(i < mid && j < right)
    {
        if(a[i] <= a[j])
        {
            temp[k] = a[i];
            ++i;
        }
        else
        {
            temp[k] = a[j];
            ++j;
        }
        ++k;
    }
    while(i < mid)
    {
        temp[k] = a[i];
        ++i;
        ++k;
    }
    while(j < right)
    {
        temp[k] = a[j];
        ++j;
        ++k;
    }

    for(int t = left; t < right; ++t)
    {
        a[t] = temp[t];
    }
}

void mergeSort(double* a, int left, int right, double* temp)
{
    if(right - left <= 1)
    {
        return;
    }

    int mid = (left + right) / 2;
    mergeSort(a, left, mid, temp);
    mergeSort(a, mid, right, temp);
    merge(a, left, mid, right, temp);
}

void keyboardEnter(double* arr, int n)
{
    std::cout << "Enter " << n << " floats:" << std::endl;
    for(int i = 0; i < n; ++i)
    {
        if(!safeInput(arr[i]))
        {
            std::cout << "Error! Invalid input for array element." << std::endl;
            return;
        }
    }
}

void readRange(double &a, double &b)
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

void randEnter(double* arr, int n, double a, double b, std::mt19937 &gen)
{
    std::uniform_real_distribution<> dis(a, b);
    for(int i = 0; i < n; ++i)
    {
        arr[i] = dis(gen);
    }
}

void printArray(const double* arr, int n)
{
    for(int i = 0; i < n; ++i)
    {
        std::cout << std::fixed << std::setprecision(2) << arr[i] << " ";
    }
    std::cout << std::endl;
}

int countDistinct(double* arr, int n)
{
    if(n == 0)
    {
        return 0;
    }

    double* temp = new double[n];
    mergeSort(arr, 0, n, temp);
    delete[] temp;

    int distinct = 1;
    for(int i = 1; i < n; ++i)
    {
        if(arr[i] != arr[i - 1])
        {
            ++distinct;
        }
    }
    return distinct;
}

double productAfterMaxAbs(const double* arr, int n)
{
    if(n == 0)
    {
        throw std::runtime_error("Error! Empty array.");
    }

    int max_abs_idx = 0;
    double max_abs = std::abs(arr[0]);
    for(int i = 1; i < n; ++i)
    {
        if(std::abs(arr[i]) > max_abs)
        {
            max_abs = std::abs(arr[i]);
            max_abs_idx = i;
        }
    }

    if(max_abs_idx >= n - 1)
    {
        throw std::runtime_error("Error! Max absolute element is the last one.");
    }

    double product = 1.0;
    for(int i = max_abs_idx + 1; i < n; ++i)
    {
        product *= arr[i];
    }
    return product;
}

void transformArray(double* arr, int n)
{
    for(int i = 0; i < n; ++i)
    {
        if(arr[i] >= 0)
        {
            for(int j = i + 1; j < n; ++j)
            {
                if(arr[j] < 0)
                {
                    double temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    break;
                }
            }
        }
    }
}

int main()
{
    int n;
    std::cout << "Enter the number of elements: ";
    if(!safeInputInt(n))
    {
        return 0;
    }
    if(n < 1)
    {
        std::cout << "Error! Invalid n" << std::endl;
        return 0;
    }

    double* arr = new double[n];
    std::mt19937 gen(45218965);

    {
        int choice;
        std::cout << "Choose filling method: 1 - keyboard, 2 - random: ";
        if(!safeInputInt(choice))
        {
            delete[] arr;
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
                double a, b;
                try
                {
                    readRange(a, b);
                }
                catch(const std::runtime_error &e)
                {
                    std::cout << e.what() << std::endl;
                    delete[] arr;
                    return 0;
                }
                randEnter(arr, n, a, b, gen);
                break;
            }
            default:
            {
                std::cout << "Error! Invalid choice" << std::endl;
                delete[] arr;
                return 0;
            }
        }
    }

    std::cout << "Array: ";
    printArray(arr, n);

    int distinct = countDistinct(arr, n);
    std::cout << "Number of distinct elements: " << distinct << std::endl;

    try
    {
        double product = productAfterMaxAbs(arr, n);
        std::cout << "Product after max abs element: " << std::fixed << std::setprecision(2) << product << std::endl;
    }
    catch(const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    transformArray(arr, n);

    std::cout << "Array after transformation: ";
    printArray(arr, n);

    delete[] arr;
    return 0;
}
