#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 1000000   // 数组最大有1000000行

int a[N+1][3];      // 用全局二维数组储存输入的元素

int compare(int A[3], int B[3])     // 用于比较数组元素的函数
{
    if (A[0] < B[0] || (A[0] == B[0] && A[1] < B[1]) || (A[0] == B[0] && A[1] == B[1] && A[2] < B[2]))
        return 0;
    return 1;
}

void exchange(int A[3], int B[3])       // 用于交换数组元素的函数
{
    int temp;
    for (int i = 0;i < 3; i++)
    {
        temp = A[i];
        A[i] = B[i];
        B[i] = temp;
    }
}

int partition(int p, int r)     // 划分数组的函数
{
    int array[3] = {a[r][0], a[r][1], a[r][2]};
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (compare(a[j], array) == 0)
        {
            i++;
            exchange(a[i], a[j]);
        }
    }
    exchange(a[i + 1], a[r]);
    return i + 1;
}

int randomized_partition(int p, int r)      // 随机抽样
{
    srand((unsigned)time(NULL));
    int i = rand() % (r - p + 1) + p;
    exchange(a[r], a[i]);
    return partition(p, r);
}

void randomized_quicksort(int p, int r)     // 快速排序
{
    if (p < r)
    {
        int q = randomized_partition(p, r);
        randomized_quicksort(p, q - 1);
        randomized_quicksort(q + 1, r);
    }
}

int main()
{
    int n, i;
    scanf("%d", &n);    // 输入待排序数组个数
    // 输入待排序数组
    for (i = 0; i < n; i++)
        scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
    randomized_quicksort(0, n - 1);
    // 输出排序后的数组
    for (i = 0; i < n; i++)
        printf("%d %d %d\n", a[i][0], a[i][1], a[i][2]);
    return 0;
}