#include <iostream>
#include <random>
#include <iomanip>
#include <stdexcept>
#include <cstdint>
#include <cstddef>

std::int32_t GetIntegerInput()
{
    std::int32_t value;
    if (!(std::cin >> value))
    {
        throw std::runtime_error("Error: input is not an integer!");
    }
    return value;
}

void AllocateMatrix(std::int32_t **&mat, std::size_t n, std::size_t m)
{
    if (n == 0 || m == 0)
    {
        throw std::invalid_argument("Error: matrix dimensions must be positive!");
    }

    mat = new std::int32_t *[n];
    for (std::size_t i = 0; i < n; ++i)
    {
        mat[i] = new std::int32_t[m];
    }
}

void DeleteMatrix(std::int32_t **&mat, std::size_t n)
{
    if (mat == nullptr)
    {
        return;
    }

    for (std::size_t i = 0; i < n; ++i)
    {
        delete[] mat[i];
    }
    delete[] mat;
    mat = nullptr;
}

void GetDimensions(std::size_t &n, std::size_t &m)
{
    std::cout << "Enter number of rows: ";
    std::int32_t rows = GetIntegerInput();

    std::cout << "Enter number of columns: ";
    std::int32_t cols = GetIntegerInput();

    if (rows <= 0 || cols <= 0)
    {
        throw std::invalid_argument("Error: matrix dimensions must be positive!");
    }

    n = static_cast<std::size_t>(rows);
    m = static_cast<std::size_t>(cols);
}

void FillKeyboard(std::int32_t **mat, std::size_t n, std::size_t m)
{
    std::cout << "Enter " << n * m << " integer(s):\n";
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < m; ++j)
        {
            mat[i][j] = GetIntegerInput();
        }
    }
}

void GetRandomBounds(std::int32_t &a, std::int32_t &b)
{
    std::cout << "Enter integer bounds a and b for random (inclusive interval [a, b]): ";
    a = GetIntegerInput();
    b = GetIntegerInput();

    if (a > b)
    {
        throw std::logic_error("Error: a must not be greater than b!");
    }
}

void FillMatrixRandom(std::int32_t **mat, std::size_t n, std::size_t m, std::mt19937 &gen)
{
    std::int32_t a = 0;
    std::int32_t b = 0;
    GetRandomBounds(a, b);

    std::uniform_int_distribution<std::int32_t> dis(a, b);

    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < m; ++j)
        {
            mat[i][j] = dis(gen);
        }
    }
}

void PrintMatrix(std::int32_t **mat, std::size_t n, std::size_t m)
{
    std::cout << "Matrix:\n";
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < m; ++j)
        {
            std::cout << std::setw(6) << mat[i][j];
        }
        std::cout << '\n';
    }
}

bool ColumnHasZero(std::int32_t **mat, std::size_t n, std::size_t colIdx)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        if (mat[i][colIdx] == 0)
        {
            return true;
        }
    }
    return false;
}

std::size_t CountColsNoZero(std::int32_t **mat, std::size_t n, std::size_t m)
{
    std::size_t cols_no_zero = 0;

    for (std::size_t j = 0; j < m; ++j)
    {
        if (!ColumnHasZero(mat, n, j))
        {
            ++cols_no_zero;
        }
    }

    return cols_no_zero;
}

std::size_t FindLongestIncreasingRow(std::int32_t **mat, std::size_t n, std::size_t m, std::size_t &bestLen)
{
    if (n == 0 || m == 0)
    {
        throw std::runtime_error("Error: matrix must have positive dimensions!");
    }

    std::size_t bestRow = 0;
    bestLen = 1;

    for (std::size_t i = 0; i < n; ++i)
    {
        std::size_t curLen = 1;
        std::size_t maxInRow = 1;

        for (std::size_t j = 1; j < m; ++j)
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

std::int32_t GetChoice()
{
    std::cout << "Choose filling method: 1 - keyboard, 2 - random: ";
    std::int32_t choice = GetIntegerInput();

    if (choice != 1 && choice != 2)
    {
        throw std::invalid_argument("Error: incorrect menu choice!");
    }

    return choice;
}

int main()
{
    std::int32_t **mat = nullptr;
    std::size_t n = 0;
    std::size_t m = 0;

    std::mt19937 gen(45218965);

    try
    {
        GetDimensions(n, m);
        AllocateMatrix(mat, n, m);

        std::int32_t choice = GetChoice();

        if (choice == 1)
        {
            FillKeyboard(mat, n, m);
        }
        else
        {
            FillMatrixRandom(mat, n, m, gen);
        }

        PrintMatrix(mat, n, m);

        std::size_t colsNoZero = CountColsNoZero(mat, n, m);
        std::cout << "Number of columns without zeros: " << colsNoZero << '\n';

        std::size_t bestLen = 0;
        std::size_t bestRow = FindLongestIncreasingRow(mat, n, m, bestLen);

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
