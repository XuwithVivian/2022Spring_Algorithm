#include<stdio.h>

// 二分查找函数
int BINARY_SEARCH(int b[], int len, int key)
{
    int low = 1, high = len;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (b[mid] == key)
            return mid;
        else if (b[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return low;
}

int FIND_LIS(int a[], int n)
{
    int b[n + 1], c[n];
    /*
    c[i]储存数组a中以a[i]为最后一个元素的最长递增子序列长度
    b[i]储存数组a数组中长度为i的最长递增子序列的最后一个元素的最小值。
    */
    int length = 1;
    b[1] = a[0];
    c[0] = 1;
    for (int i = 1; i < n; i++)
    {
        if (a[i] < b[1])
        {
            b[1] = a[i];
            c[i] = 1;
        }
        else if (a[i] > b[length])
        {
            length++;
            b[length] = a[i];
            c[i] = length;
        }
        else
        {
            int j = BINARY_SEARCH(b, length, a[i]);     // b[j-1]<a[i]<=b[j]
            b[j] = a[i];
            c[i] = j;
        }
    }
    return length;
}

int main()
{
    int n, k;
    scanf("%d", &n);
    if (n == 0)
    {
        k = 0;
        printf("%d", k);
        return 0;
    }
    int a[n];
    for (int i = 0; i < n;i++)
        scanf("%d", &a[i]);
    k = FIND_LIS(a, n);
    printf("%d", k);    // 输出最长递增子序列的长度
    return 0;
}