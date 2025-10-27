#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

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
        a[t] = temp[t];
}

void mergeSort(double* a, int left, int right, double* temp)
{
    if(right - left <= 1)
        return;

    int mid = (left + right) / 2;
    mergeSort(a, left, mid, temp);
    mergeSort(a, mid, right, temp);
    merge(a, left, mid, right, temp);
}

void keyboardEnter(double* arr, int n)
{
    std::cout << "Enter " << n << " floats:" << std::endl;
    for(int i = 0; i < n; ++i)
        std::cin >> arr[i];
}

bool randEnter(double* arr, int n)
{
    double a, b;
    std::cout << "Enter a and b (a <= b): ";
    std::cin >> a >> b;
    if(a > b)
    {
        std::cout << "Error! Invalid a, b" << std::endl;
        return false;
    }

    std::mt19937 gen(45218965);
    std::uniform_real_distribution<> dis(a, b);
    for(int i = 0; i < n; ++i)
        arr[i] = dis(gen);

    return true;
}

void printArray(const double* arr, int n)
{
    for(int i = 0; i < n; ++i)
        std::cout << std::fixed << std::setprecision(2) << arr[i] << " ";
    std::cout << std::endl;
}

int countDistinct(double* arr, int n)
{
    if(n == 0)
        return 0;
    /*доп массив создаю исключительно для сортировки
    можно использывать другую но эта мне очень нравится)*/
    double* temp = new double[n];
    mergeSort(arr, 0, n, temp);
    delete[] temp;

    int distinct = 1;
    for(int i = 1; i < n; ++i)
    {
        if(arr[i] != arr[i - 1])
            ++distinct;
    }
    return distinct;
}

bool productAfterMaxAbs(const double* arr, int n, double &product)
{
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
        return false;

    product = 1.0;
    for(int i = max_abs_idx + 1; i < n; ++i)
        product *= arr[i];
    return true;
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
        keyboardEnter(arr, n);
    else if(choice == 2)
    {
        if(!randEnter(arr, n))
        {
            delete[] arr;
            return 0;
        }
    }
    else
    {
        std::cout << "Error! Invalid choice" << std::endl;
        delete[] arr;
        return 0;
    }

    std::cout << "Array: ";
    printArray(arr, n);

    int distinct = countDistinct(arr, n);
    std::cout << "Number of distinct elements: " << distinct << std::endl;

    double product;
    if(productAfterMaxAbs(arr, n, product))
        std::cout << "Product after max abs element: " << std::fixed << std::setprecision(2) << product << std::endl;
    else
        std::cout << "Cannot compute product: max abs is the last element" << std::endl;

    transformArray(arr, n);

    std::cout << "Array after transformation: ";
    printArray(arr, n);

    delete[] arr;
    return 0;
}
