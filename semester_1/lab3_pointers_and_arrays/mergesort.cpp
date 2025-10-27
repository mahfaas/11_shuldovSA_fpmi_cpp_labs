#include <iostream>

const int MAX_N = 1000;

void merge(int* a, int left, int mid, int right, int* temp)
{
    int i = left;
    int j = mid;
    int k = left;

    while(i < mid && j < right)
    {
        if(a[i] <= a[j])
        {
            temp[k] = a[i];
            i++;
        }
        else
        {
            temp[k] = a[j];
            j++;
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

void mergeSort(int* a, int left, int right, int* temp)
{
    if(right - left <= 1) return;

    int mid = (left + right) / 2;

    mergeSort(a, left, mid, temp);
    mergeSort(a, mid, right, temp);

    merge(a, left, mid, right, temp);
}

int main() 
{
    int a[MAX_N];   
    int tmp[MAX_N];     

    int n = 7;
    int sample[] = {38, 27, 43, 3, 9, 82, 10};
    for (int i = 0; i < n; i++)
        a[i] = sample[i];

    std::cout << "Original: ";
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    mergeSort(a, 0, n, tmp);

    std::cout << "Sorted:   ";
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    return 0;
}
