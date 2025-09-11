#include <iostream>

/*При больших значениях n сумма становиться слишком большой и ее значение не влазит в 
стандартные типы данных поэтому программа выводит неправильные значения */

int main()
{
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    long long sum = 0;
    for(int i = 1; i <= n; i++)
    {
        long long prod = 1;
        for(int j = 1; j <= i; j++)
            prod *= i;
        sum += prod;
    }
    std::cout << "Sum = " << sum << std::endl;
    return 0;
}