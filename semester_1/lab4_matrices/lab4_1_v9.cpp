#include <iostream>
#include <random>
#include <iomanip>

int** AllocateMatrix(int n, int m)
{
    int** mat = new int*[n];
    for(int i = 0; i < n; i++)
        mat[i] = new int[m];
    return mat;
}

void DeleteMatrix(int** mat, int n)
{
    for(int i = 0; i < n; i++)
        delete[] mat[i];
    delete[] mat;
}

void FillKeyboard(int** mat, int n, int m)
{
    std::cout << "Enter " << n * m << " integers:" << std::endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            std::cin >> mat[i][j];
}

bool FillRandom(int** mat, int n, int m)
{
    double a, b;
    std::cout << "Enter a and b: ";
    std::cin >> a >> b;
    if(a > b)
    {
        std::cout << "Error! Invalid a, b" << std::endl;
        return false;
    }

    std::mt19937 gen(45218965);
    std::uniform_real_distribution<> dis(a, b);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            mat[i][j] = dis(gen);
    return true;
}

void PrintMatrix(int** mat, int n, int m)
{
    std::cout << "Matrix:" << std::endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            std::cout << std::setw(6) << mat[i][j];
        std::cout << std::endl;
    }
}

int CountColsNoZero(int** mat, int n, int m)
{
    int cols_no_zero = 0;
    for(int j = 0; j < m; j++)
    {
        bool has_zero = false;
        for(int i = 0; i < n; i++)
        {
            if(mat[i][j] == 0)
            {
                has_zero = true;
                break;
            }
        }
        if(!has_zero)
            cols_no_zero++;
    }
    return cols_no_zero;
}

int main()
{
    int n, m;
    std::cout << "Enter number of rows and columns: ";
    std::cin >> n >> m;
    if(n < 1 || m < 1)
    {
        std::cout << "Error! Invalid n or m" << std::endl;
        return 0;
    }

    int** mat = AllocateMatrix(n, m);

    int choice;
    std::cout << "Choose filling method: 1 - keyboard, 2 - random: ";
    std::cin >> choice;

    if(choice == 1)
        FillKeyboard(mat, n, m);
    else if(choice == 2)
    {
        if(!FillRandom(mat, n, m))
        {
            DeleteMatrix(mat, n);
            return 0;
        }
    }
    else
    {
        std::cout << "Error! Invalid choice" << std::endl;
        DeleteMatrix(mat, n);
        return 0;
    }

    PrintMatrix(mat, n, m);

    int ans = CountColsNoZero(mat, n, m);
    std::cout << "Number of columns without zeros: " << ans << std::endl;

    DeleteMatrix(mat, n);
    return 0;
}
