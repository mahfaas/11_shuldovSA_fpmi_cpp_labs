#include <iostream>
#include <random>
#include <iomanip>
#include <stdexcept>

int GetIntegerInput()
{
    int value;
    if (!(std::cin >> value))
    {
        throw std::runtime_error("Error: input is not an integer!");
    }
    return value;
}

int **AllocateMatrix(int n, int m)
{
    if (n <= 0 || m <= 0)
    {
        throw std::invalid_argument("Error: matrix dimensions must be positive!");
    }

    int **mat = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        mat[i] = new int[m];
    }
    return mat;
}

void DeleteMatrix(int **mat, int n)
{
    if (mat == nullptr)
    {
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

void FillKeyboard(int **mat, int n, int m)
{
    std::cout << "Enter " << n * m << " integers:\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            mat[i][j] = GetIntegerInput();
        }
    }
}

void GetRandomBounds(int &a, int &b)
{
    std::cout << "Enter integer bounds a and b for random(inclusive interval [a, b]): ";
    a = GetIntegerInput();
    b = GetIntegerInput();

    if (a > b)
    {
        throw std::logic_error("Error: a must not be greater than b!");
    }
}

void FillRandom(int **mat, int n, int m, std::mt19937 &gen)
{
    int a = 0;
    int b = 0;
    GetRandomBounds(a, b);

    std::uniform_int_distribution<> dis(a, b);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            mat[i][j] = dis(gen);
        }
    }
}

void PrintMatrix(int **mat, int n, int m)
{
    std::cout << "Matrix:\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cout << std::setw(6) << mat[i][j];
        }
        std::cout << '\n';
    }
}

int FindLong(int **mat, int n, int m, int &bestLen)
{
    int bestRow = 0;
    bestLen = 1;

    for (int i = 0; i < n; ++i)
    {
        int curLen = 1;
        int maxInRow = 1;

        for (int j = 1; j < m; ++j)
        {
            if (mat[i][j] > mat[i][j - 1])
            {
                ++curLen;
            }
            else
            {
                curLen = 1;
            }

            if (curLen > maxInRow)
            {
                maxInRow = curLen;
            }
        }

        if (maxInRow > bestLen)
        {
            bestLen = maxInRow;
            bestRow = i;
        }
    }

    return bestRow;
}

void GetDimensions(int &n, int &m)
{
    std::cout << "Enter number of rows: ";
    n = GetIntegerInput();

    std::cout << "Enter number of columns: ";
    m = GetIntegerInput();

    if (n <= 0 || m <= 0)
    {
        throw std::invalid_argument("Error: matrix dimensions must be positive!");
    }
}

int GetChoice()
{
    std::cout << "Choose filling method: 1 - keyboard, 2 - random: ";
    int choice = GetIntegerInput();

    if (choice != 1 && choice != 2)
    {
        throw std::invalid_argument("Error: incorrect menu choice!");
    }

    return choice;
}

int main()
{
    int **mat = nullptr;
    int n = 0;
    int m = 0;

    std::random_device rd;
    std::mt19937 gen(rd());

    try
    {
        GetDimensions(n, m);
        mat = AllocateMatrix(n, m);

        int choice = GetChoice();
        if (choice == 1)
        {
            FillKeyboard(mat, n, m);
        }
        else
        {
            FillRandom(mat, n, m, gen);
        }

        PrintMatrix(mat, n, m);

        int bestLen = 0;
        int bestRow = FindLong(mat, n, m, bestLen);

        std::cout << "Longest strictly increasing sequence length: " << bestLen << '\n';
        std::cout << "First row containing such sequence: " << bestRow + 1 << '\n';
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Memory allocation error: " << e.what() << '\n';
        DeleteMatrix(mat, n);
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        DeleteMatrix(mat, n);
        return 1;
    }

    DeleteMatrix(mat, n);
    return 0;
}
