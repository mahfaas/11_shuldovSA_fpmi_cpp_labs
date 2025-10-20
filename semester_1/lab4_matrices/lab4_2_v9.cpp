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

int FindLong(int** mat, int n, int m, int& bestLen)
{
    int bestRow = 0;
    bestLen = 1;

    for(int i = 0; i < n; i++)
    {
        int curLen = 1;
        int maxInRow = 1;
        for(int j = 1; j < m; j++)
        {
            if(mat[i][j] > mat[i][j - 1])
                curLen++;
            else
                curLen = 1;

            if(curLen > maxInRow)
                maxInRow = curLen;
        }

        if(maxInRow > bestLen)
        {
            bestLen = maxInRow;
            bestRow = i; 
        }
    }
    return bestRow;
}

int main()
{
    int n, m;
    std::cout << "Enter number of rows: ";
    std::cin >> n;
    std::cout << "Enter number of columns: ";
    std::cin >> m;
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

    int bestLen;
    int bestRow = FindLong(mat, n, m, bestLen);

    std::cout << "Longest strictly increasing sequence length: " << bestLen << std::endl;
    std::cout << "First row containing such sequence: " << bestRow << std::endl;

    DeleteMatrix(mat, n);
    return 0;
}
