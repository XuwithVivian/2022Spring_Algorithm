#include<stdio.h>

#define N 1800000   // 待排序数字个数最大值

int a[N + 1];   // 用全局数组储存

// 计数排序，用于对每一十进制位排序
void counting_sort(int array[], int n, int digit)
{
    int temp[10] = {0};     // 提供临时存储空间
    int store[n], i, num;        // store数组存放排序的输出,num用于存储所需排序位上的数
    for (i = 0; i < n; i++)
    {
        num = (array[i] / digit) % 10;
        temp[num]++;
    }
    for (i = 1; i < 10; i++)
        temp[i] = temp[i] + temp[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        num = (array[i] / digit) % 10;
        store[temp[num] - 1] = array[i];
        temp[num]--;
    }
    for (i = 0; i < n; i++)     // 将储存在Store数组中的元素移入array数组
        array[i] = store[i];
}

// 基数排序函数
void radixsort(int array[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] > max)
            max = array[i];
    }   // 寻找数组中最大元素
    for (int digit = 1; max / digit != 0; digit = digit * 10)   // digit表示排序的位
    {
        counting_sort(array, n, digit);     // 调用计数排序对每一位进行排序
        if (digit == 1000000000)    // 若到达digit所能到达最大位则终止，防止digit溢出
            break;
    }
}

int main()
{
    int n;
    int i, j;
    scanf("%d", &n);    // 输入正整数n
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);     // 输入数组元素
    radixsort(a, n);    // 调用基数排序
    for (i = 0; i < n - 1; i++)
        printf("%d ", a[i]);
    printf("%d", a[n - 1]);     // 输出排序后的数组元素
    return 0;
}