#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>
#include <algorithm>

const int MAX_N = 1000;

void merge(int*, int, int, int, int*, bool(*)(int, int));
void mergeSort(int*, int, int, int*, bool(*)(int, int));
void bubbleSort(int*, int, bool(*)(int, int));
void sortSelection(int*, int, bool(*)(int, int));
void sortInsertion(int*, int, bool(*)(int, int));

int** AllocateMatrix(int, int);
void DeleteMatrix(int**, int );
void FillKeyboard(int**, int, int);
bool FillRandom(int**, int, int);
void PrintMatrix(int**, int, int);

void chooseSortType(int&, bool(*&)(int, int));

bool ascComp(int x, int y)  { return x > y; } 
bool desComp(int x, int y)  { return x < y; } 

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

    int sortType;
    bool (*comp)(int, int) = nullptr;
    chooseSortType(sortType, comp);
    for(int i = 0; i < n; i++)
    {
        switch(sortType)
        {
            case 1:
                bubbleSort(mat[i], m, comp);
                break;
            case 2:
                sortSelection(mat[i], m, comp);
                break;
            case 3:
                sortInsertion(mat[i], m, comp);
                break;
            case 4:
            {
                int* temp = new int[m];
                mergeSort(mat[i], 0, m, temp, comp);
                delete[] temp;
                break;
            }
            default:
                std::cout << "Error! Invalid sort type" << std::endl;
                break;
        }
    }

    std::cout << "Matrix after sorting rows:" << std::endl;
    PrintMatrix(mat, n, m);

    DeleteMatrix(mat, n);
    return 0;
}

void merge(int* a, int left, int mid, int right, int* temp, bool (*comp)(int, int))
{
    int i = left;
    int j = mid;
    int k = left;

    while(i < mid && j < right)
    {
        if(comp(a[i], a[j]))
        {
            temp[k] = a[j];
            j++;
        }
        else
        {
            temp[k] = a[i];
            i++;
        }
        k++;
    }
    while(i < mid)
    {
        temp[k] = a[i];
        i++;
        k++;
    }
    while(j < right)
    {
        temp[k] = a[j];
        j++;
        k++;
    }

    for(int t = left; t < right; t++)
        a[t] = temp[t];
}

void mergeSort(int* a, int left, int right, int* temp, bool (*comp)(int, int))
{
    if(right - left <= 1) return;

    int mid = (left + right) / 2;

    mergeSort(a, left, mid, temp, comp);
    mergeSort(a, mid, right, temp, comp);

    merge(a, left, mid, right, temp, comp);
}

void bubbleSort(int* a, int n, bool (*comp)(int, int))
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(comp(a[j], a[j + 1]))
                std::swap(a[j], a[j + 1]);
        }
    }
}

void sortSelection(int* a, int n, bool (*comp)(int, int))
{
    for(int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for(int j = i + 1; j < n; j++)
        {
            if(comp(a[minIndex], a[j]))
                minIndex = j;
        }
        std::swap(a[i], a[minIndex]);
    }
}

void sortInsertion(int* a, int n, bool (*comp)(int, int))
{
    for(int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;
        while(j >= 0 && comp(a[j], key))
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

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

void chooseSortType(int& sortType, bool(*&comp)(int, int))
{
    std::cout << "Enter the type of sort: 1 - bubble, 2 - selection, 3 - insertion, 4 - merge" << std::endl;
    std::cin >> sortType;
    std::cout << "Enter the type of element arrangement 1 - ascending order, 2 - descending order: " << std::endl;
    int ar;
    std::cin >> ar;

    if(ar == 1)
        comp = ascComp;
    else if(ar == 2)
        comp = desComp;
    else
    {
        std::cout << "Error! Invalid arrangement type" << std::endl;
        comp = ascComp;
    }
}
